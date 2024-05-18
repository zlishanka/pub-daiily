#pragma once

#include <opencv2/opencv.hpp>
#include <array>

class ImageAutoCrop
{
  public:
    ImageAutoCrop();

    void  keepLargeBox( bool v) { keep_large_box = v; }

    void      drawBox(cv::Mat& src);
    cv::Mat   getCropped(const cv::Mat& src);
    cv::Rect  getBox(const cv::Mat& src);
    cv::Vec3b bgColor = {5, 5, 5};
    cv::RotatedRect  getMinBox(const cv::Mat& src);
    cv::Mat   getOrthoImage(const cv::Mat &m);
  private:
    cv::Mat rotate(cv::Mat src, double angle, bool recenter);
    bool keep_large_box = false;
    std::array<int,4> largeBox;
    bool firstBox = true;
};
