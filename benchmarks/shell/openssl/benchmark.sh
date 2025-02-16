#!/bin/bash
. ../benchmarker.sh

NAME=$(openssl version | cut -d" " -f1,2 | sed 's/ /-/')

benchmarker -n $NAME -i abc -- openssl dgst -sha256 
