#!/bin/bash
. ../benchmarker.sh

NAME=shasum-$(shasum -v)
benchmarker -n $NAME -i abc -- shasum -a 256
