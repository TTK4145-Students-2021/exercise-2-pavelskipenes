use std::thread;
use std::sync::{Arc, Mutex};

fn main() {
    let i: Arc<Mutex<i32>> = Arc::new(Mutex::new(0));

    let i_incrementing = i.clone();
    let i_decrementing = i.clone();

    let join_incrementing = thread::spawn(move || {
        for _ in 0..1_000_000 {
            *i_incrementing.lock().unwrap() += 1;
        }
    });
    
    let join_decrementing = thread::spawn(move || {
        for _ in 0..1_000_000 {
            *i_decrementing.lock().unwrap() -= 1;
        }

    });

    join_incrementing.join().unwrap();
    join_decrementing.join().unwrap();

    println!("The number is: {}", *i.lock().unwrap());
}

