FROM gcr.io/oss-fuzz-base/base-builder
RUN git clone --depth=1 https://github.com/nlohmann/json.git $SRC/json
COPY build.sh $SRC/
COPY json_fuzzer.cpp $SRC/
