fn take_ownership_integer() -> u32 {
    let mut a = 10;
    let a_ptr: *mut u32 = &mut a;
    println!("The address of a is: {:p}", a_ptr);
    a
}

fn take_ownership_string() -> String {
    let a = String::from("abc");
    println!("The address of a_str is: {:p}", a.as_ptr());
    a
}

fn main() {
    let mut y = 10;
    let y_ptr: *mut i32 = &mut y;

    println!("The address of y is: {:p}", y_ptr);

    let mut b = take_ownership_integer();
    let b_ptr: *mut u32 = &mut b;
    println!("The address of b is: {:p}", b_ptr);

    let b_str = take_ownership_string();
    println!("The address of b_str is: {:p}", b_str.as_ptr());
}
