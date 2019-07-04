#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>

void listdir(const char *name)
{
	DIR				*dir;
	struct dirent	*entry;
	char			path[PATH_MAX];

	if (!(dir = opendir(name))) {
		return;
	}

	while ((entry = readdir(dir)) != NULL) {
		if (entry->d_type == DT_DIR) {
			if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
				continue ;
			}
			snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
			printf("[%s]\n", entry->d_name);
			listdir(path);
		} else {
			printf("%s\n", entry->d_name);
		}
	}
	closedir(dir);
}

int main(void) {
	listdir("..");
	return 0;
}
