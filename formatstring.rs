#![crate_type="dylib"]

extern {
    fn printf(fmt: *const u8, ...);
}

#[no_mangle]
pub extern fn function1() {
    println!("Address of printf: {:p}", &printf);
    let s1 = b"Hello, %s!\n\0";
    let s2 = b"world\0";
    unsafe {
        printf(&s1[0], &s2[0]);
    }
}
