#!/bin/bash

WARMUP=5
hyperfine -N --warmup $WARMUP 'openssl dgst -sha256 input.txt' --export-json result-benchmark-openssl.json
