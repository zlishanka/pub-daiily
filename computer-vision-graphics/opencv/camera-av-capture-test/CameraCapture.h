#pragma once

#include <opencv2/opencv.hpp>

#include <map>
#include <vector>
#include <memory>
#include "BlockingQueue.h"

class CameraCaptureImpl;

class CameraCapture
{
public:
    CameraCapture();
    CameraCapture( const std::string &name, bool start_now = true);

    bool open( const std::string &name, bool start_now = true);

    bool read( cv::Mat &img) const;

    cv::Mat grabImage() const;

    bool isOpened() const;
    int  start();
    int  release();

    void setPixelFormat( const std::string &s);

    std::string getBackendName() const {
         return "avfoundation";
    }

    bool set(int propid, double value);
    double get( int propid) const;

    std::array<int,2> getBestDimensions() const;

    int  setConfiguration(int width, int height, int fps);
    void getCapabilities();

private:
    CameraCaptureImpl  *impl;
    /*
    int  setBestHeight( int height, bool prefer_higher_value = true);
    int  setBestWidth ( int width,  bool prefer_higher_value = true);
    int  setBestArea (  int height, int width,  bool prefer_higher_value = true);
    */
};

