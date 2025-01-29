FROM gcr.io/oss-fuzz-base/base-builder

RUN apt-get update && apt-get install -y make gcc git

RUN git clone https://github.com/antirez/sds.git $SRC/sds

WORKDIR $SRC/sds

COPY build.sh $SRC/
COPY fuzzer_sds.c $SRC/

RUN chmod +x $SRC/build.sh