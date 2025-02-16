#!/bin/bash

WARMUP=5
hyperfine -N --warmup $WARMUP 'shasum -a 256 ../../../inputs/abc' --export-json result-benchmark-shasum.json
