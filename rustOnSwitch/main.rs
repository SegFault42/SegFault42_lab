extern {
    fn consoleInit();
}

fn main() {
    unsafe {
        consoleInit();
    }
}
