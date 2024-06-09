[Memo]
2024/06/09
[Under windows]
mkdir build
cd build
cmake -G "Visual Studio 17 2022" -A x64 ..

#back to project root
cmake --build build --config Release

[Under linux]
make clean;make