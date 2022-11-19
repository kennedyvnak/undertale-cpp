conan install . --build missing
cmake -S . -B build/release -DCMAKE_BUILD_TYPE=Release