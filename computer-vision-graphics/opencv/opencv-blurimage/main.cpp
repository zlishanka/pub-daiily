#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;

int main() {

  Mat img = imread("knee-1080p-full-auto-segmentation.png");
  
  Rect roi(10, 10, 100, 100); // x, y, width, height
  
  std::cout << "w=" <<img.cols << ", h=" <<img.rows<<std::endl;  
  //Mat blurred(roi.size(), CV_8UC3);
  Mat blurred; 
  GaussianBlur(img(roi), blurred, Size(51, 51), 0); 
  
  blurred.copyTo(img(roi));
  
  imwrite("blurred.png", img);
  
  return 0;
}
