#!/bin/bash
. ../benchmarker.sh

NAME=$(sha256sum --version | head -1 | sed 's/ (GNU coreutil s) /-/')
benchmarker -n $NAME -i abc -- sha256sum 
