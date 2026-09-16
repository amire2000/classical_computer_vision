#include <opencv2/core.hpp>

#include <iostream>

int main() {
  const cv::Mat image(2, 3, CV_8UC1, cv::Scalar{7});
  std::cout << "OpenCV " << CV_VERSION << " is ready: " << image.rows << "x"
            << image.cols << ", pixel sum = " << cv::sum(image)[0] << '\n';
}

