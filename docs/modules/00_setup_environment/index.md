# Module 0: Setup Your Environment

This module installs and verifies the C++20, CMake, Ninja, and OpenCV
toolchain.

## Install prerequisites

This course targets Ubuntu 24.04, C++20, CMake, Ninja, and OpenCV 4.

```bash
sudo apt update
sudo apt install build-essential cmake ninja-build gdb libopencv-dev clang-format clang-tidy
```

Install these VS Code extensions: 
- C/C++ (`ms-vscode.cpptools`), -
- CMake Tools (`ms-vscode.cmake-tools`)
- CMake Format (`cheshirekow.cmake-format`).

---

## Build and run

```bash
cmake --preset debug
cmake --build --preset debug
./build/debug/modules/00_setup_environment/hello_opencv
```

Expected output includes the installed OpenCV version and `pixel sum = 42`.

---

## Source code

```cpp
--8<-- "modules/00_setup_environment/apps/hello_opencv.cpp"
```

`cv::Mat` creates a 2×3 single-channel image with every pixel set to `7`.
`cv::sum` adds those six pixels, producing `42`; `CV_VERSION` confirms which
OpenCV version was linked. Together, this checks that the compiler can include
and link OpenCV correctly.

---

## VS Code tasks

Open this folder in VS Code. `Ctrl+Shift+B` configures and builds the course;
`F5` builds and debugs `hello_opencv`.

To run without debugging, use **Terminal: Run Task** → **Run course binary...**.
The integrated terminal lists all built module executables; enter its number to
run it and view its output there. The selectable-runner implementation lives in
[`tools/run-binary.sh`](https://github.com/amire2000/classical_computer_vision/blob/main/tools/run-binary.sh).

For any module or practice target, use **Terminal: Run Task** → **Build CMake
target...**, then enter its CMake target name. Add the target to that module's
`CMakeLists.txt`; no new VS Code task is needed.

---

## Course documentation

Install the local MkDocs Material site from the repository root:

```bash
uv venv
uv pip install -r requirements-docs.txt
.venv/bin/mkdocs serve
```

Use `.venv/bin/mkdocs build --strict` to verify the site without starting its
server. In VS Code, use **Terminal: Run Task** → **Build documentation** to
verify the site or **Serve documentation** to start the auto-reloading local
site.
