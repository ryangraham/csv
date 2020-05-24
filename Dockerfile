FROM ubuntu:18.04
LABEL maintainer="ryangraham@gmail.com"

ENV DEBIAN_FRONTEND noninteractive

ENV BUILD_TOOLS \
    build-essential \
    autoconf \
    g++ \
    gcc \
    make \
    cmake

ENV TOOLS \
    ca-certificates \
    curl \
    git \
    sudo \
    unzip

RUN apt-get update \
    && apt-get install -y \
    $BUILD_TOOLS \
    $TOOLS \
    --no-install-recommends

RUN cd /tmp \
    && git clone https://github.com/ericniebler/range-v3.git \
    && mkdir range-v3/build \
    && cd range-v3/build \
    && cmake ../. -DRANGE_V3_TESTS=OFF -DRANGE_V3_HEADER_CHECKS=OFF -DRANGE_V3_EXAMPLES=OFF -DRANGE_V3_PERF=OFF \
    && make install
