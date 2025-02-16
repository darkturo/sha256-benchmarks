# !/bin/bash
#
# Depends: hyperfine
#

BASE_DIR=$(git rev-parse --show-toplevel)

RESULT_PREFIX="benchmark-shell"
WARMUP=5
RUNS=1000
INPUT=abc
CONFIG=""
NAME=""
MACHINE=""
COMMAND=""

usage() {
	echo "Usage: $0 [OPTIONS] {-c <config>|<command>}"
	echo "Options:"
	echo "  -w <warmup>  Number of warmup runs default 5"
	echo "  -r <runs>    Number of runs default 1000"
	echo "  -m <machine> Machine name default `hostname`"
	echo "  -n <name>    Name of the benchmark (derived from command if not provided)"
	echo "  -c <config>  Configuration file or a directory with a benchmark.cfg file"
        echo "               with information about the command to benchmark."
	echo "Examples:"
	echo "  $0 -c openssl/config"
	echo "  $0 -n 'openssl-custom' -i abc -- openssl dgst -sha256"
}

benchmarker() {
	RESULT_DIR=results
	if [ -n "$BASE_DIR" ]; then
		RESULT_DIR=$BASE_DIR/$RESULT_DIR
	fi

	while getopts "c:w:r:i:n:m:h" opt; do
		case $opt in
			c) CONFIG=$OPTARG
				;;
			w) WARMUP=$OPTARG
				;;
			r) RUNS=$OPTARG
				;;
			i) INPUT=$OPTARG
				;;
			n) NAME=$OPTARG
				;;
			m) MACHINE=$OPTARG
				;;
			h)
				usage
				exit 0
				;;
			\?) 
				echo "Invalid option -$OPTARG" >&2
				usage
				exit 1
				;;
		esac
	done

	if [ -n "$CONFIG" ]; then
		if [ -d "$CONFIG" ]; then
			CONFIG=$CONFIG/benchmark.cfg
		fi
		COMMAND=""
		. $CONFIG
	else
		if [ -z "$COMMAND" ]; then
			shift $((OPTIND -1))
			COMMAND=$@
		fi
	fi
	if [ -z "$MACHINE" ]; then
		MACHINE=$(hostname)
	fi
	if [ -z "$COMMAND" ]; then
		echo "Error: Please provide the command to run"
		exit 1
	fi
	if [ -z "$NAME" ]; then
		NAME=$(echo $COMMAND | cut -d " " -f 1)
	fi
	if [ -z "$INPUT" ]; then
		INPUT=abc
	fi
	INPUT=$BASE_DIR/inputs/${INPUT}.in

	RESULT_PATH=$RESULT_DIR/$RESULT_PREFIX-$NAME@$MACHINE.json
	BENCHMARK="hyperfine -w $WARMUP -r $RUNS -n $NAME --export-json $RESULT_PATH"
	echo "Running: $BENCHMARK '$COMMAND'"
	$BENCHMARK -- "$COMMAND < $INPUT"
	echo "Benchmark results saved to $RESULT_PATH"
}

if [ "$0" = "$BASH_SOURCE" ]; then
	benchmarker "$@"
fi
