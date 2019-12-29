mkdir build
cd build
conan install ../ --build=missing -s compiler="Visual Studio" -s compiler.version=16 -s compiler.cppstd=17 -s build_type=Debug -g virtualenv
cmake -DCMAKE_BUILD_TYPE=Debug ../
cmake --build ./
cp -r ../assets ./bin
echo ""
echo "Compilation successfully completed !"
echo " ---- Executables are located in build/bin/"
cd ../
