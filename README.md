# sha256 benchmarks

A repo with benchmarks of different sha256 implementations.

## Introduction

I've been curious about where do sha256 implementations stand in terms of
performance on either CPU and GPU for a while. I'm aware that this is not a new
question, and that is majorly accepted that ASICs and FPGAs can do best. With
the craze of Bitcoin mining, the performance of hardware accelerated sha256
implementations has been improving every year, to get to the current state
where they can compute hashes in the order of Terahashes per second.

And despite I've been looking around my question is still unanswered; How many
hashes (double hashes) can we compute per second with a current CPU or GPU?

So I have decided to find out myself, although I do not intend this to be a
reference project, nor an exhaustive benchmark. I'm also aware that this
endeavor may end being just a waste of time, but hey, other people go fishing
on weekends, I'm just a curious cat looking for an answer.


## Findings

Well, I haven't run any benchmark yet, but the idea is to place here some
summary with my findings, nothing fancy.

As mentioned, I have found attempts to answer this question on the Internet,
and all of the few answers I found let the question with a vague answer, and in
many cases showing discouraging numnbers: 65,139 H/s [^1]. 


## The Repo

The repo is organised as follows

benchmarks  - Directory containing the programs for the different implementations I'm testing
results     - Directory containing logs and summaries of the benchmarks I've run.
README.md   - This file


--

[1] Question at stack overflow https://stackoverflow.com/questions/4764026/how-many-sha256-hashes-can-a-modern-computer-compute from 2012.

[2] https://bitcoin.stackexchange.com/questions/110056/how-many-sha256-hashes-can-a-single-thread-compute
