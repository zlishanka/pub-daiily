/**
 * gl_imshow
 *
 * Copyright (c) 2020 kamino410
 *
 * This software is published under the Apache License v2.0.
 * See https://github.com/kamino410/gl_imshow
 */

#include <string>
#include <opencv2/opencv.hpp>

#if defined(__APPLE__)
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif

//#include <GL/gl.h>
#include <GLFW/glfw3.h>
//#include "gl_imshow.hpp"
#include "BlockingQueue.h"
#include <array>

class GlRender
{
 public:
    GlRender();

    void init(const std::string &name, const std::array<int,2> &pos, const std::array<int,2> &dim);

    void setQueue( std::shared_ptr<BlockingQueue<cv::Mat> > q)
         {
	 imageQ = q;
	 }

    void keepAspectRation( bool kar) { keep_aspect_ratio = kar; }

    int  start();
    int  setFPS(float f) { fps = f; }

private:
    std::string winname = "GlRender";
    std::array<int,2>  pos;
    int  width  = 1920;
    int  height = 1080;
    float fps    = 30.0;
    bool keep_aspect_ratio = false;
    bool initialized  = false;
    bool use_shaders  = false;
    bool running      = false;
    bool auto_resize  = false;
    GLenum minFilter  = GL_LINEAR_MIPMAP_LINEAR;
    GLenum magFilter  = GL_LINEAR;
    GLenum wrapFilter = GL_CLAMP;

    GLFWwindow *window     = nullptr;
//    GL2dImagePanel *canvas = nullptr;
    std::shared_ptr<BlockingQueue<cv::Mat>>  imageQ;

    GLuint getTextureID(const cv::Mat &mat);
    void draw_frame(const cv::Mat& frame);
};
