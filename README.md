# sha256 benchmarks

Benchmarking SHA-256 implementations for CPU on GNU/Linux.

## Motivation

I've been curious about where sha256 implementations stand in terms of
performance on a desktop or server. How many hashes (double hashes) 
per second can a general purpose hardware (CPU or GPU or mix) achieve 
as of today?

I'm aware that this is not a new question, and that it is majorly accepted 
that ASICs and FPGAs can do the best in this terrain. We talk about hundreds
of Terahashes per second when it comes to the latest ASICs vs a few thousands(?) 
of hashes per second on a computer for general use.

I've been looking around for an answer to my question but haven't been very
lucky...

So I have decided to find out myself. 

**DISCLAIMER**: I do not intend to provide an exhaustive benchmark here, this
project is fueled by curiosity and spare time.


## Findings

ASIC miners today have hashrates in the order of TH/s, this is, they can calculate
trillion of double Sha256s (SHA-256d [^sha256-d]) per second[^btc-lingo]! 
Let's find out how far can we get on a CPU/GPU![^machine]

### The top 10 (so far):

| Library or Tool           | Average Run Time (1 hash) | Hashrate (H/s) | Machine          | Program            |
|---------------------------|---------------------------|----------------|------------------|--------------------|
| WolfSSL sha256            | 0.000000208375930786 s    | 2.40   MH/s    | Intel i7 1.8 GHz | C++                |
| Crypto++ sha256           | 0.000000257899368286 s    | 1.94   MH/s    | Intel i7 1.8 GHz | C++                |
| Bitcoin core's sha256     | 0.000000263093631744 s    | 1.90   MH/s    | Intel i7 1.8 GHz | C++                |
| Rust sha2 (sha256)        | 0.000000269746296400 s    | 1.85   MH/s    | Intel i7 1.8 GHz | Rust               |
| OpenSSL sha256            | 0.000000474000930786 s    | 1.05   MH/s    | Intel i7 1.8 GHz | C++                |
| Hashlib (python) sha256   | 0.000000583000000000 s    | 857.63 KH/s    | Intel i7 1.8 GHz | Python             |
| Linux coreutils sha256sum | 0.000642492268000000 s    | 778.21  H/s    | Intel i7 1.8 GHz | Command Line       |
| OpenSSL sha256 (CLI)      | 0.002975225151000002 s    | 168.05  H/s    | Intel i7 1.8 GHz | C/C++ Command Line |
| shasum                    | 0.014810544855000007 s    | 33.75   H/s    | Intel i7 1.8 GHz | Perl               |


For more benchmarks, check out this: [Benchmarks](docs/Benchmarks.md)!

## This Repository

The repo is organized as follows:

benchmarks  - Contains both setups and programs to benchmark different implementations. I use hyperfine, 
              pyperf, and custom c++ programs (using Folly) to run the benchmarks.
results     - Contains logs in json of the benchmarks I've run. These are produced by the different benchmarking
              tools I've used, and they may not contain the same info. I plan to work on a script to parse them
              and generate interesting information.
input       - Contains input file(s) used as input for sha256 algorithms. 
              At the moment I'm just using "abc" as input (abc.in).
docs        - Markdown stuff, some of it referenced from this README.
scripts     - Contains a simple script in bash to run the different benchmarks.
README.md   - This file.

## Running the Benchmarks

### Prerequisites
To run the benchmarks, make sure you have installed in your system the tools listed in the 
[dependencies](docs/Dependencies.md).  

I have run this on GNU/Linux (Ubuntu 20.04) so the instructions are for this 
distro, but you could find the packages for yours or compile them from source to make it work in your case.

### Compiling the C++ programs
This is straightforward as long as you have installed all the necessary libraries (see prerequisites).

On a terminal (or from your favorite IDE), use the root CMakeLists.txt available in benchmarks:
```bash
cd benchmarks
cmake -B build
cmake --build build
```

And you should be done!

### Running the Benchmarks
To run the benchmarks, you can use the `benchmark_all_tools.sh`:

```bash
cd benchmarks
./benchmark_all_tools.sh
```

After a series of logs will be generated and placed in the `results` directory.

### Running a specific benchmark
It is also possible to run just one benchmark for a specific library or command.
For example if I were to run the benchmark for `shasum`, I would just do as follows:

```bash
cd benchmarks
../scripts/benchmarker -c shasum
```

The result will be placed also in the `results` directory.



[^machine]: I'm running these tests on my laptop, a modest Lenovo model from 2020, on a virtualized Linux. 
            But I plan to run these on a more current native GNU/Linux machine in the near future.

[^sha256-d]: https://bitcoinwiki.org/wiki/sha-256d

[^btc-lingo]: https://bitcoin.stackexchange.com/questions/110056/how-many-sha256-hashes-can-a-single-thread-compute
