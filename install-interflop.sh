#!/bin/bash

if [[ -z $1 ]]; then
    PREFIX=
    PREFIX_PATH=
else
    PREFIX="--prefix=$1"
    PREFIX_PATH=$1
fi

REPO=yohanchatelain

function check() {
    if [[ $? != 0 ]]; then
        echo "Error"
        exit 1
    fi
}

function Clone() {
    git clone $1
    check
}

function Cd() {
    cd $1
    check
}

function Autogen() {
    ./autogen.sh
    check
}

function Configure() {
    ./configure $@
    check
}

function Make() {
    make
    check
}

function MakeInstall() {
    make install
    check
}

function install_stdlib() {
    Clone https://github.com/${REPO}/interflop-stdlib
    Cd interflop-stdlib
    Autogen
    Configure ${PREFIX} --enable-warnings
    Make
    MakeInstall
    Cd ..
}

function install_backend() {
    Clone https://github.com/${REPO}/interflop-backend-$1
    Cd interflop-backend-$1
    Autogen
    Configure ${PREFIX} --enable-warnings
    Make
    MakeInstall
    Cd ..
}

install_stdlib
export PATH=${PREFIX_PATH}/bin:$PATH

backends=(bitmask cancellation checkcancellation checkdenormal checkfloatmax ieee mcaint mcaquad verrou vprec)
for backend in ${backends[@]}; do
    install_backend $backend
done

echo "export PATH=${PREFIX_PATH}/bin:$PATH" >>${PREFIX_PATH}/interflop-env.sh
echo "export LD_LIBRARY_PATH=$(interflop-config --libdir):$LD_LIBRARY_PATH" >>${PREFIX_PATH}/interflop-env.sh
