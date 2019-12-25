#!/usr/bin/env sh

mkdir -p ./build/
cd ./build/ || exit
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan install ../ --build=missing -s compiler=gcc -s compiler.version="$(gcc -v 2>&1 | tail -1 | awk '{print $3}' | cut -d "." --fields=1)" -s compiler.libcxx=libstdc++
cmake -DCMAKE_BUILD_TYPE=Release ../
cmake --build ./ -j "$(nproc --all)"
# cp assets

echo -e "\n\nBuild completed.     Executables are located in build/bin/\n"

# If Conan is indefinitely locked run the following command :
# conan remove "*" -f && conan --remove locks && rm -rf ~/.conan/data/*
