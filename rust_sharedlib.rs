#![crate_type="dylib"]

#[no_mangle] pub extern fn function1() { println!("RUST: Hello, world!"); }
#[no_mangle] pub extern fn function2() { println!("RUST: \"is a sentence fragment\" is a sentence fragment."); }
#[no_mangle] pub extern fn function3() { println!("RUST: this function displays text too"); }
