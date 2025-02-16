#!/bin/bash

WARMUP=5
hyperfine -N --warmup $WARMUP 'shasum -a 256 input.txt' --export-json result-benchmark-shasum.json
