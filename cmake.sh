#!/bin/bash

set -e

BUILD_DIR="build"

echo "Config CMAKE project in '$BUILD_DIR'..."


if [ "$1" == "--clean" ]; then
    echo "Delete old/existent build directory..."
    rm -rf "$BUILD_DIR"
fi

if [ ! -d "$BUILD_DIR" ]; then
    mkdir "$BUILD_DIR"
    echo "Directory '$BUILD_DIR' created."
fi

cmake -S . -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" -- -j$(nproc)

echo ""
echo "Build completed!"
echo "Exec file is in: $BUILD_DIR/"
