#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <chrono>
#include <iostream>
#include "GlRender.h"
#include <thread>

using namespace std;
using namespace cv;

void keycallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (action == GLFW_PRESS || action == GLFW_REPEAT) {
        if (key == GLFW_KEY_ESCAPE) {
            glfwSetWindowShouldClose(window, GLFW_TRUE);
        }
    }
}

GlRender:: GlRender()
{
    initialized = false;
}

void GlRender:: init(const string &name, const array<int,2> &topleft, const array<int,2> &dim)
{
    if( window ) {
        glfwDestroyWindow(window);
    }

    initialized = false;

    winname = name;
    pos     = topleft;
    width   = dim[0];
    height  = dim[1];

    if (!glfwInit()) {
        std::cerr << "Failed to initialize glfw." << std::endl;
        exit(1);
    }

    if (atexit(glfwTerminate)) {
        glfwTerminate();
        std::cerr << "Failed to set atexit(glfwTerminate)." << std::endl;
        exit(1);
    }

    glfwWindowHint(GLFW_AUTO_ICONIFY, GL_FALSE);
    glfwWindowHint(GLFW_COCOA_GRAPHICS_SWITCHING, GL_TRUE);

    window = glfwCreateWindow(width, height, winname.c_str(), nullptr, nullptr);

    if (!window) {
        std::cerr << "Failed to create GL window." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSetWindowPos(window, topleft[0], topleft[1]);

    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize glew." << std::endl;
        glfwTerminate();
        exit(1);
    }

    glfwSwapInterval(1);
    glfwSetKeyCallback(window, keycallback);

    if( use_shaders) {
//        canvas = new GL2dImagePanel(width, height);
//        canvas->init();
    } else {
        glViewport(0, 0, width, height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, width, height, 0.0, 0.0, 100.0);
        glMatrixMode(GL_MODELVIEW);

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClearDepth(0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Clear the window
    }

    initialized = true;
}

GLuint GlRender :: getTextureID(const cv::Mat &mat)
{
    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Catch silly-mistake texture interpolation method for magnification
    if (magFilter == GL_LINEAR_MIPMAP_LINEAR  ||
            magFilter == GL_LINEAR_MIPMAP_NEAREST ||
            magFilter == GL_NEAREST_MIPMAP_LINEAR ||
            magFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        cout << "You can't use MIPMAPs for magnification - setting filter to GL_LINEAR" << endl;
        magFilter = GL_LINEAR;
    }

    // Set texture interpolation methods for minification and magnification
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);

    // Set texture clamping method
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapFilter);

    GLenum inputFormat = GL_BGR;
//      GLenum inputFormat       = GL_UNSIGNED_INT_8_8_8_8_REV;

    if (mat.channels() == 1)
    {
        inputFormat = GL_LUMINANCE;
    }

    glTexImage2D(GL_TEXTURE_2D,     // Type of texture
                 0,                 // Pyramid level (for mip-mapping) - 0 is the top level
                 GL_RGB,            // Internal colour format to convert to
                 mat.cols,          // Image width  i.e. 640 for Kinect in standard mode
                 mat.rows,          // Image height i.e. 480 for Kinect in standard mode
                 0,                 // Border width in pixels (can either be 1 or 0)
                 inputFormat, // Input image format (i.e. GL_RGB, GL_RGBA, GL_BGR etc.)
                 GL_UNSIGNED_BYTE,  // Image data type
                 mat.ptr());        // The actual image data itself

//glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, mat.cols, mat.rows, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, mat.ptr());


    // If we're using mipmaps then generate them. Note: This requires OpenGL 3.0 or higher
    if ( minFilter == GL_LINEAR_MIPMAP_LINEAR  ||
            minFilter == GL_LINEAR_MIPMAP_NEAREST ||
            minFilter == GL_NEAREST_MIPMAP_LINEAR ||
            minFilter == GL_NEAREST_MIPMAP_NEAREST)
    {
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    return textureID;
}

void GlRender :: draw_frame(const cv::Mat& frame)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_TEXTURE_2D);

    GLuint tex = getTextureID(frame);

    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex2i(0, 0);
    glTexCoord2i(0, 1);
    glVertex2i(0, height);
    glTexCoord2i(1, 1);
    glVertex2i(width, height);
    glTexCoord2i(1, 0);
    glVertex2i(width, 0);

    glEnd();

    glDeleteTextures(1, &tex);
    glDisable(GL_TEXTURE_2D);

}

int GlRender :: start()
{
    if( imageQ == nullptr) {
        cout << "Error: Image queue was not set: " <<  endl;
        return 1;
    }

    if( !initialized ) {
        auto img = imageQ->pop();
        int  w   = img.cols;
        int  h   = img.rows;
        init("GlRender", {0,0}, {w,h});
    }

    if( !initialized ) {
        cout << "Error: Window not initialized: " << endl;
        return 2;
    }

    auto t0  = getTickCount();

    int frameID = 0;
    int fps_count = 0;
    int wait_time = 24;
    while(1) {
        if(glfwWindowShouldClose(window)) break;

        auto img = imageQ->pop();

        if( auto_resize) {
            if( img.cols != width && img.rows != height) {
                init( winname, pos, {img.cols, img.rows});
//           cv::resize(img, img, {width, height} );
            }
        }

        glViewport(0, 0, width, height);
        glClearColor(0.5, 0.5, 0.5, 0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if( use_shaders ) {
//            canvas->updateImage(img);
//            canvas->draw();
        } else {
            draw_frame(img);
            std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        }

        glfwSwapBuffers(window);
        glfwPollEvents();

        frameID++;
        fps_count++;
        if (fps_count == 100) {
            auto t1 = getTickCount();
            double tp  = (t1-t0)/getTickFrequency();
            double curr_fps = fps_count/ tp;

            cout << "Rendering FPS: " << curr_fps << endl;

            if( curr_fps > fps) {
                wait_time += 1;
            }

            if( curr_fps < fps) {
                wait_time -= 1;
            }
            wait_time = max(1, wait_time);
            cout << "wait_time : " << wait_time << endl;
            t0 = t1;
            fps_count = 0;
        }
    }
}
