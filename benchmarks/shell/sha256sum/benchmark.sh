#!/bin/bash

WARMUP=5
hyperfine -N --warmup $WARMUP 'sha256sum ../../../inputs/abc' --export-json result-benchmark-sha256sum.json
