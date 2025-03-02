use sha2::{Digest, Sha256};
use std::{env, fs, fs::File, io::Write, time::Instant};
use serde_json::json;


fn sha256(input: &[u8]) -> Vec<u8> {
    let mut hasher = Sha256::new();
    hasher.update(input);
    hasher.finalize().to_vec()
}

fn benchmark_sha256(input: &[u8], iterations: usize) -> f64 {
    let start = Instant::now();
    for _ in 0..iterations {
        sha256(input);
    }
    let duration = start.elapsed();
    println!("Executed {} iterations in {:?}", iterations, duration);
    let avg_time = duration.as_secs_f64() * 1_000_000_000.0 / iterations as f64; // Convert to ns
    println!("Average time per call: {:?} ns", avg_time);
    avg_time
}

struct Args {
    input_file: String,
    json_file: String,
}

fn parse_args(args: Vec<String>) -> Result<Args, String> {
    let mut input_file = String::new();
    let mut json_file = String::new();

    let mut i = 1;
    while i < args.len() {
        match args[i].as_str() {
            "-input" => {
                if i + 1 < args.len() {
                    input_file = args[i + 1].clone();
                    i += 1;
                }
            }
            "-bm_json_verbose" => {
                if i + 1 < args.len() {
                    json_file = args[i + 1].clone();
                    i += 1;
                }
            }
            _ => {}
        }
        i += 1;
    }

    if input_file.is_empty() {
        return Err("Missing required argument: -input".to_string());
    }

    Ok(Args {
        input_file,
        json_file,
    })
}

fn usage() {
    println!("usage: PROGRAM -input INPUT_FILE [-bm_json_verbose <JSON_OUTPUT>]");
}

fn main() {
    let iterations = 1_000_000;

    let args = parse_args(env::args().collect()).unwrap_or_else(|err| {
        eprintln!("Error parsing arguments: {}", err);
        usage();
        std::process::exit(1);
    });

    let file_content= fs::read(&args.input_file).unwrap_or_else(|err| {
        eprintln!("Error reading file '{}': {}", args.input_file, err);
        usage();
        std::process::exit(1);
    });

    let avg_time = benchmark_sha256(&file_content, iterations);

    if args.json_file != "" {
        let json_output = json!([
            [
                file!(),
                "rust_sha256",
                avg_time
            ]
        ]);

        let mut file = File::create(&args.json_file).expect("Failed to create JSON file");
        file.write_all(json_output.to_string().as_bytes()).expect("Failed to write JSON");

        println!("Benchmark results saved to {}", args.json_file);
    }
}

