find_package(OpenCV 4 REQUIRED COMPONENTS core)

add_executable(hello_opencv apps/hello_opencv.cpp)
target_link_libraries(hello_opencv PRIVATE opencv_core)
target_compile_options(hello_opencv PRIVATE -Wall -Wextra -Wpedantic)
