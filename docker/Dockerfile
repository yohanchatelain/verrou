# Build stage
ARG IMAGE_BASE=ubuntu:20.04
ARG VALGRIND_VERSION=3.20.0
ARG VALGRIND_BRANCH=VALGRIND_3_20_0
ARG VERROU_BRANCH=interflop
ARG NUM_THREADS=6

#Build Stage
FROM ${IMAGE_BASE} AS build

ARG VALGRIND_VERSION
ARG VALGRIND_BRANCH
ARG VERROU_BRANCH
ARG NUM_THREADS

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update \
    &&  apt-get install -y --reinstall ca-certificates \
    && update-ca-certificates \
    &&  apt-get install -y --no-install-recommends git build-essential automake python3 libc6-dbg \
    autogen dh-autoreconf autoconf automake autotools-dev libedit-dev libtool libz-dev binutils libmpfr-dev \
    && rm -fr /var/lib/apt/lists/*

RUN mkdir -p /build
WORKDIR /build

# Install interflop stdlib and backends
ARG BACKENDS="bitmask cancellation checkcancellation checkdenormal checkfloatmax ieee mcaint mcaquad verrou vprec"
RUN git clone --single-branch --depth=1 https://github.com/interflop/interflop-stdlib && \
    # Install interflop stdlib \
    cd interflop-stdlib && \
    ./autogen.sh && \
    ./configure && \
    make -j ${NUM_THREADS} && \
    make install && \
    cd .. ; \
    # Install interflop backends \
    for backend in ${BACKENDS}; do \
    git clone --single-branch --depth=1 https://github.com/interflop/interflop-backend-${backend} && \
    cd interflop-backend-${backend} && \
    ./autogen.sh && \
    ./configure && \
    make -j ${NUM_THREADS} && \
    make install && \
    cd .. ; done && \
    rm -rf interflop-backend-* interflop-stdlib

# Install valgrind + verrou
RUN git clone --branch=${VALGRIND_BRANCH} --single-branch --depth=1 git://sourceware.org/git/valgrind.git valgrind-${VALGRIND_VERSION}+verrou-dev && \
    cd /build/valgrind-${VALGRIND_VERSION}+verrou-dev && \
    # clone verrou \
    git clone --branch=${VERROU_BRANCH} --single-branch --depth=1 https://github.com/yohanchatelain/verrou.git verrou && \
    patch -p1 <verrou/valgrind.diff && \
    # install verrou \
    ./autogen.sh && \
    ./configure --enable-only64bit --enable-intrinsic-fma --prefix=/opt/valgrind-${VALGRIND_VERSION}+verrou-dev && \
    make -j ${NUM_THREADS} && \
    make install && \
    echo ". /opt/valgrind-${VALGRIND_VERSION}+verrou-dev/env.sh " >> /etc/bash.bashrc 