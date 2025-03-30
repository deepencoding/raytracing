# Raytracing in One Weekend (My Implementation)

### Installation

##### Dependencies

- CMake

##### Instructions

1. Clone the repository in a folder
```bash
git clone https://github.com/deepencoding/raytracing.git
```

2. Make a build directory and move into it
```bash
mkdir build
cd build
```

3. Run CMake
```bash
cmake ..
```

4. Build the project
```bash
cmake --build .
```

- This will build the project for your suitable platform. For example, if you are on Linux, you will get a `raytracing` executable.

5. Run the project
```bash
./raytracing > output/image.ppm
```

- This will generate an image in the `output` folder. Basically we are forwarding the output to a .ppm file using the terminal.
- You can view the image using a program like GIMP. Or any other .ppm viewer app or online.

### Acknowledgements

- This project is based on [Raytracing in One Weekend](https://raytracing.github.io/books/RayTracingInOneWeekend.html) by [Peter Shirley](https://www.pbr-book.org/3ed-2018/Contents.html).
