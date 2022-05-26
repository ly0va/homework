use std::io::{ErrorKind, Read, Result, Write};
use std::net::{TcpListener, TcpStream};
use std::time::Duration;

fn handle_client<F>(mut stream: TcpStream, f: F) -> Result<()>
where
    F: FnOnce(u8) -> u8,
{
    let mut x = [0u8];
    stream.read_exact(&mut x)?;
    println!("Received x = {}", x[0]);
    let result = f(x[0]);
    println!("Computed result = {}", result);
    stream.write_all(&[result])?;
    Ok(())
}

fn f(x: u8) -> u8 {
    std::thread::sleep(Duration::from_secs(15));
    x + 10
}

fn g(x: u8) -> u8 {
    x / 5
}

fn main() -> Result<()> {
    let port;
    let function;

    if let Some(arg) = std::env::args().collect::<Vec<_>>().get(1) {
        port = if arg == "f" { 8080 } else { 8081 };
        function = if arg == "f" { f } else { g };
    } else {
        println!("Please specify to run `f` or `g` server");
        return Ok(());
    }

    let listener = TcpListener::bind(("127.0.0.1", port))?;
    listener
        .set_nonblocking(true)
        .expect("Cannot set non-blocking");

    for stream in listener.incoming() {
        match stream {
            Ok(s) => {
                println!("Connection acquired");
                handle_client(s, function)?;
            }
            Err(e) if e.kind() == ErrorKind::WouldBlock => {
                continue;
            }
            Err(e) => panic!("encountered IO error: {e}"),
        }
    }
    Ok(())
}
