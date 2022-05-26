use std::io::{self, BufRead, Read, Result, Write};
use std::net::TcpStream;
use std::time::{Duration, Instant};

struct Delegator {
    stream: TcpStream,
    result: Option<u16>,
}

impl Delegator {
    fn new(address: &str) -> Result<Self> {
        let stream = TcpStream::connect(address)?;
        stream
            .set_nonblocking(true)
            .expect("Cannot set non-blocking");
        Ok(Self {
            stream,
            result: None,
        })
    }

    fn request(&mut self, x: u8) -> Result<()> {
        self.stream.write_all(&[x])
    }

    fn check_result(&mut self) -> Option<u16> {
        if self.result.is_none() {
            let mut result = [0u8];
            match self.stream.read_exact(&mut result) {
                Ok(_) => self.result = Some(result[0] as u16),
                Err(ref e) if e.kind() == io::ErrorKind::WouldBlock => {
                    // continue waiting
                }
                Err(e) => panic!("encountered IO error: {e}"),
            }
        }
        self.result
    }
}

fn user_is_patient() -> bool {
    print!("Do you want to keep waiting? (Y/n): ");
    io::stdout().flush().unwrap();
    let mut line = String::new();
    io::stdin().lock().read_line(&mut line).unwrap();
    line.trim().to_lowercase() != "n"
}

fn main() -> Result<()> {
    let mut delegator_f = Delegator::new("127.0.0.1:8080")?;
    let mut delegator_g = Delegator::new("127.0.0.1:8081")?;

    let x = if let Some(arg) = std::env::args().collect::<Vec<_>>().get(1) {
        arg.parse().expect("Invalid argument")
    } else {
        println!("Please specify x");
        return Ok(());
    };

    delegator_f.request(x)?;
    delegator_g.request(x)?;

    let mut checkpoint = Instant::now();

    let result: u16 = loop {
        match (delegator_f.check_result(), delegator_g.check_result()) {
            (Some(f), Some(g)) => break f * g,
            (Some(0), _) | (_, Some(0)) => break 0,
            (_, _) => {
                if checkpoint.elapsed() >= Duration::from_secs(10) {
                    if !user_is_patient() {
                        return Ok(());
                    }
                    checkpoint = Instant::now();
                }
                continue;
            }
        }
    };

    println!("The result is: {}", result);
    Ok(())
}
