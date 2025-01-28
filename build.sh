#!/bin/bash
set -e

# Compile a biblioteca
clang -O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address \
      -c sds.c -o sds.o
ar rcs libsds.a sds.o

# Compile o fuzzer
clang -O1 -fno-omit-frame-pointer -gline-tables-only -fsanitize=address \
      -fsanitize=fuzzer -I/src/sds /src/fuzzer_sds.c -o /out/fuzzer_sds ./libsds.a
