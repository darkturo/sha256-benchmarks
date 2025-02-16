#!/bin/bash

WARMUP=5
hyperfine -N --warmup $WARMUP 'openssl dgst -sha256 ../../../inputs/abc' --export-json result-benchmark-openssl.json
