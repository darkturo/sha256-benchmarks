#!/bin/bash
#
# Run the bencharker for all the configured tools in this directory.
find -type f -name 'benchmark.cfg' | while read -r file; do
	echo "Running benchmarker for $(basename $(dirname $file)) ($file)"
	../scripts/benchmarker -c "$file"
	echo "-----------------------------------"
	echo ""
done
