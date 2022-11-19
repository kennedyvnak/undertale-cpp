conan install . --build missing
cmake -S . -B build/debug -DCMAKE_BUILD_TYPE=Debug