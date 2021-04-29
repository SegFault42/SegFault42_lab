package main

import (
	"fmt"
	"net/http"
	"sync"
	"text/template"

	inotify "gopkg.in/fsnotify/fsnotify.v0"
)

var (
	// TemplateExt is the extension for the physical template files. Failure
	// to set this to the same extension your physical template files have
	// will result in the failure to reload the files.
	TemplateExt = ".gohtml"

	// TemplatePath is the path to the directory containing the template files.
	// It defaults to the current directory, provided you call r.Watch("./")
	TemplatePath = ".//"
)

// Reloader is a struct used to contain the parsed template files as well
// as provide a sane API for locking and watching for events.
//
// Common usage would be inside a RenderTemplate sort of function similar to
//     r := reloader.New("my_path")
//     r.Watch()
//
//     ...
//
//     func RenderTemplate(w http.ResponseWriter, r *http.Request, name string, data interface{}) (err error) {
//         tmpl := r.Get[name]
//         err = tmpl.Execute(w, data)
//         if err != nil {
//             // handle error.
//         }
//         return
//     }
type Reloader struct {
	templates map[string]*template.Template

	*inotify.Watcher
	*sync.Mutex
}

func (r *Reloader) Get(name string) *template.Template {
	r.RLock()
	defer r.Unlock()
	if t, ok := r.templates[name]; ok {
		return t
	}
	return nil
}

// New returns an initialized Reloader that starts watching the given
// directories for all events.
func New(dirs ...string) *Reloader {
	watcher, err := inotify.NewWatcher()
	if err != nil {
		panic(err)
	}

	for _, path := range dirs {
		watcher.AddWatch(path, inotify.IN_ALL_EVENTS)
	}

	return &Reloader{
		Watcher: watcher,
		RWMutex: &sync.Mutex{},
	}
}

func (r *Reloader) Watch() {
	go func() {
		for {
			select {
			case evt := <-r.Watcher.Event:
				if eventIsWanted(evt.Mask) {
					fmt.Printf("File: %s Event: %s. Hot reloading.\n",
						evt.Name, evt.String())

					if err := r.reload(evt.Name); err != nil {
						fmt.Println(err)
					}
				}
			case err := <-r.Watcher.Error:
				fmt.Println(err)
			}
		}
	}()
}

func eventIsWanted(mask uint32) bool {
	return mask&inotify.IN_MODIFY != 0 ||
		mask&inotify.IN_CREATE != 0
}

func (r *Reloader) reload(name string) error {

	// Just for example purposes, and sssuming 'index.gohtml' is in the
	// same directory as this file.
	if name == TemplatePath+"reload.go" {
		return nil
	}

	if len(name) >= len(TemplateExt) &&
		name[len(name)-len(TemplateExt):] == TemplateExt {

		tmpl := template.Must(template.ParseFiles(name))

		// Gather what would be the key in our template map.
		// 'name' is in the format: "path/identifier.extension",
		// so trim the 'path/' and the '.extension' to get the
		// name (minus new extension) used inside of our map.
		key := name[len(TemplatePath) : len(name)-len(TemplateExt)]

		r.Lock()
		r.templates[key] = tmpl
		r.Unlock()

		return nil
	}

	return fmt.Errorf("Unable to reload file %s\n", name)

}

func main() {
	r := New("./")
	r.templates = map[string]*template.Template{
		"index": template.Must(template.ParseFiles("index.gohtml")),
	}

	r.Watch()

	render := func(w http.ResponseWriter, name string, data interface{}) (err error) {
		tmpl := r.templates[name]
		if err = tmpl.Execute(w, data); err != nil {
			panic(err)
		}
		return
	}

	handler := http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		w.Header().Set("Content-Type", "text/plain")
		data := struct {
			Name string
			Age  int
		}{
			"Eric",
			21,
		}
		render(w, "index", data)
	})

	http.Handle("/", handler)
	http.ListenAndServe("0.0.0.0:8000", nil)
}
