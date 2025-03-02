use sha2::{Digest, Sha256};
use std::{env, fs, time::Instant};

fn sha256(input: &[u8]) -> Vec<u8> {
    let mut hasher = Sha256::new();
    hasher.update(input);
    hasher.finalize().to_vec()
}

fn benchmark_sha256(input: &[u8], iterations: usize) {
    let start = Instant::now();
    for _ in 0..iterations {
        sha256(input);
    }
    let duration = start.elapsed();
    println!("Executed {} iterations in {:?}", iterations, duration);
    println!(
        "Average time per call: {:?} ns",
        duration.as_nanos() / iterations as u128
    );
}

fn main() {
    let args: Vec<String> = env::args().collect();

    // Check for the -input flag and read file name
    if args.len() != 3 || args[1] != "-input" {
        eprintln!("Usage: {} -input FILE_NAME", args[0]);
        std::process::exit(1);
    }

    let file_name = &args[2];
    let file_content = fs::read(file_name).unwrap_or_else(|err| {
        eprintln!("Error reading file '{}': {}", file_name, err);
        std::process::exit(1);
    });

    let iterations = 1_000_000;
    benchmark_sha256(&file_content, iterations);
}

