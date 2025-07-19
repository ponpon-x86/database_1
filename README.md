# database_1
**Note:** the project uses *conan*. You can build it using *conan* with the following commands:
```
conan install . --output-folder=build --build=missing
cmake --preset conan-default
cmake --build --preset conan-release
```
There's also an executable file at *build/Release/database_1.exe*.