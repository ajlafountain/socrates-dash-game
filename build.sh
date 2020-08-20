#!/bin/bash

# Check to see if there are build artifacts and remove them

# Build the project in a temporary directory, removing it afterwards
# Each step only happens if the last was successful
# cmake -DCMAKE_TOOLCHAIN_FILE=$PWD/vcpkg/scripts/buildsystems/vcpkg.cmake -B build_tmp -S . &&

[ 0 = 0 ] && {
    [ -d build_linux ] && rm -r build_linux
    cmake -B build_linux -S . -Wno-dev &&
    cd build_linux && make && cd .. &&
    echo "Success building linux!" || echo "Failure building linux!"
}
[ 0 = 0 ] && {
    [ -d build_windows ] && rm -r build_windows
    cmake -DTO_WINDOWS=true -Wno-dev -B build_windows -S . && 
    cd build_windows && make &&
    cp "/usr/x86_64-w64-mingw32/bin/"*".dll" . && cd .. &&
    echo "Success building windows!" || echo "Failure building windows!"
}