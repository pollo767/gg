#!/bin/sh

if [ -z "$DEVKITPRO" ] || [ -z "$DEVKITARM" ]; then
    echo "Environment variables not set: DEVKITPRO DEVKITARM" >&2
    exit 1
fi

rm -rf build/
cmake-*/bin/cmake -B build . -DCMAKE_TOOLCHAIN_FILE=toolchain-gcc.cmake "$@"
