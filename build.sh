#!/bin/bash -eu
cd $SRC/json
cmake .
make -j$(nproc)
$CXX $CXXFLAGS -I$SRC/json/single_include -c $SRC/json_fuzzer.cpp -o json_fuzzer.o
$CXX $CXXFLAGS $LIB_FUZZING_ENGINE json_fuzzer.o -o $OUT/json_fuzzer