# sha256 benchmarks

Benchmarks of different sha256 implementations.

## Motivation

I've been curious about where do sha256 implementations stand in terms of
performance on either CPU and GPU for a while. I'm aware that this is not a new
question, and that is majorly accepted that ASICs and FPGAs can do the best in 
this terrain (We talk hundreds of Terahashes per second).

I've been looking around for an answer to my question but haven't been very
lucky. How many hashes (double hashes) can we compute per second with a current
CPU or GPU?  ...

So I have decided to find out myself. 

**DISCLAIMER**: I do not intend to provide an exhaustive benchmark here, this is
project is fueled by curiosity and spare time.


## Findings

As mentioned, I have found attempts to answer this question on the Internet,
and so far, the answers were vague or had rather discouraging[^1] numbers: 65,139 H/s.[^3]

ASIC Bitcoin miners hashrates today are in the order of TH/s, let's see how far
can we get on a CPU/GPU!

Top 10 so far:

| Library or Tool                 | Average Run Time (1 hash) | Hashrate (H/s) | Machine          |
|---------------------------------|---------------------------|----------------|------------------|
| Hashlib (python)                | 0.000000005220000000 s    |  95.79 GH/s    | Intel i7 1.8 GHz |
| Linux coreutils sha256sum       | 0.000642492268000000 s    | 778.21  H/s    | Intel i7 1.8 GHz |
| OpenSSL sha256                  | 0.002975225151000002 s    | 168.05  H/s    | Intel i7 1.8 GHz |
| shasum                          | 0.014810544855000007 s    |  33.75  H/s    | Intel i7 1.8 GHz |


NOTE: In Bitcoin lingo, the hashrate measures the number of double-hashes per second a
miner can compute [^2].

For more benchmarks, check out this: [Benchmarks](Benchmarks.md)!

## The Repo

The repo is organized as follows

benchmarks  - Directory containing the programs for the different implementations I'm testing
results     - Directory containing logs and summaries of the benchmarks I've run.
README.md   - This file


--

[1] Question at stack overflow https://stackoverflow.com/questions/4764026/how-many-sha256-hashes-can-a-modern-computer-compute from 2012.

[2] https://bitcoin.stackexchange.com/questions/110056/how-many-sha256-hashes-can-a-single-thread-compute

[3] The answer may fall short today. I have run some benchmarks with a 2022 laptop, and just with Python's `hashlib`, I could reach 95 GH/s, way beyond the 65 MH/s from the answer! I'm impressed by Python's performance in this case, and I'm sure that other C++ libraries will kick ass! 🫏 So I'm looking forward to find out when to find the time. Also, I'm enthusiastic to have an answer!
