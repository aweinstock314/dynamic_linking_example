#![crate_type="dylib"]

extern {
    fn printf(fmt: *const u8, ...);
}

#[no_mangle]
pub extern fn function1() {
    println!("Address of printf: {:p}", &printf);
    //let s1 = b"Hello, %s!\n\0";
    //let s2 = b"world\0";
    let fmt = b"Hello!%n\n\0";
    let val: u8 = 0;
    println!("Before: {}", val);
    unsafe {
        printf(&fmt[0], &val);
    }
    println!("After: {}", val);
}
