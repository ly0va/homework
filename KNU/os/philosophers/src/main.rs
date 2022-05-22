use rand::prelude::*;
use std::sync::{Arc, Condvar, Mutex};
use std::thread;
use std::time::Duration;

#[derive(Debug, Clone, Copy, PartialEq)]
enum State {
    Thinking,
    Hungry,
    Eating,
}

impl Default for State {
    fn default() -> Self {
        State::Thinking
    }
}

#[derive(Debug, Clone, Copy, Default)]
struct Philosopher {
    state: State,
}

#[derive(Debug)]
struct Table<const N: usize = 5> {
    philosophers: Mutex<[Philosopher; N]>,
    condvars: [Condvar; N],
}

impl<const N: usize> Default for Table<N> {
    fn default() -> Self {
        Self {
            philosophers: Mutex::new([Philosopher::default(); N]),
            condvars: [0; N].map(|_| Condvar::default()),
        }
    }
}

impl<const N: usize> Table<N> {
    const fn next(i: usize) -> usize {
        (i + 1) % N
    }

    const fn prev(i: usize) -> usize {
        (i + N - 1) % N
    }

    fn take_chopsticks(&self, i: usize) {
        println!("Philosopher #{} is hungry!", i);
        let mut philosophers = self.philosophers.lock().unwrap();
        philosophers[i].state = State::Hungry;
        philosophers = self.condvars[i]
            .wait_while(philosophers, |philosophers| {
                philosophers[Self::next(i)].state == State::Eating
                    || philosophers[Self::prev(i)].state == State::Eating
            })
            .unwrap();
        philosophers[i].state = State::Eating;
    }

    fn put_chopsticks(&self, i: usize) {
        println!("Philosopher #{} is full.", i);
        let mut philosophers = self.philosophers.lock().unwrap();
        philosophers[i].state = State::Thinking;
        self.condvars[Self::next(i)].notify_one();
        self.condvars[Self::prev(i)].notify_one();
    }

    fn do_stuff(&self, i: usize, stuff: &str) {
        println!("Philosopher #{} is {}.", i, stuff);
        let duration = Duration::from_millis(rand::thread_rng().gen_range(1000..2000));
        thread::sleep(duration);
    }

    fn start_dinner(self) {
        let table = Arc::new(self);
        let mut handles = Vec::new();

        for i in 0..N {
            let table = Arc::clone(&table);
            let handle = thread::spawn(move || loop {
                table.do_stuff(i, "thinking");
                table.take_chopsticks(i);
                table.do_stuff(i, "eating");
                table.put_chopsticks(i);
            });
            handles.push(handle);
        }

        for handle in handles {
            handle.join().unwrap();
        }
    }
}

fn main() {
    let table = Table::<5>::default();
    table.start_dinner();
}
