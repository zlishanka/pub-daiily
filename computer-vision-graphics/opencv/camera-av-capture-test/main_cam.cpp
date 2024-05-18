#include "CameraCapture.h"

#include <thread>
#include <chrono>
#include "GlRender.h"
#include <unistd.h> 
#include <ctime> 

using namespace cv;
using namespace std;

using ImageQueue = shared_ptr <BlockingQueue<cv::Mat>>; 

time_t start_t, now_t; 

void process_frame( CameraCapture *cap, ImageQueue imageQ)
{
    if( cap == nullptr) return;
    static int frameCnt = 0; 
    while(1) {
        //auto img = cap->grabImage().clone();
	cv::Mat img; 
        cap->read(img); 
        if( !img.empty() ) {
            int w = 1920/2;
            int h = 1080/2;
            cv::Rect rect(0, 0, w, h);
            auto cropped = img(rect);
//            cv::pyrDown(img,img);
            cv::resize(img,img,cv::Size(w,h), 0.0, 0.0, INTER_LINEAR);
//          imageQ->push(cropped);
            imageQ->push(img); 
	 if (frameCnt++%1000 == 0) {
	   now_t = std::time(nullptr); 
	   cout << "process_frame: time passed=" << (now_t - start_t) << " sec" << std::endl; 
         } 
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(30)); 
    }
}

void compose_frames( vector<ImageQueue> processedQ, ImageQueue renderQ)
{
    int numImages = processedQ.size();
    vector<Mat> images(numImages);

    cv::Mat bigImg;
    while(1) {
        for( int i = 0; i < numImages; i++)
            images[i] = processedQ[i]->pop();

        if( numImages == 1) {
            bigImg = images[0];
            //cv::cvtColor(bigImg, bigImg, COLOR_YUV2BGR_UYVY);
            if( renderQ ) renderQ->push(bigImg);
        }

        if( numImages == 4) {
            int w = 1920;
            int h = 1080;
            bigImg = Mat(1080, 1920, CV_8UC3, Scalar(0,0));
            cv::Rect rect1(0,0,w/2,h/2);
            images[0].copyTo(bigImg(rect1));

            cv::Rect rect2(w/2,0,w/2,h/2);
            images[1].copyTo(bigImg(rect2));

            cv::Rect rect3(0, h/2, w/2,h/2);
            images[2].copyTo(bigImg(rect3));

            cv::Rect rect4(w/2, h/2,w/2,h/2);
            images[3].copyTo(bigImg(rect4));
            cv::Mat rgb;
            //cv::cvtColor(bigImg, rgb, COLOR_YUV2BGR_UYVY);
            if( renderQ ) renderQ->push(bigImg);
        }
    }
}

void render_final_frame( ImageQueue renderQ)
{
    if( renderQ == nullptr) return;

    GlRender render;
    int w = 1920;
    int h = 1080;

    render.init("Camera", {0,0}, {w,h});
    render.setQueue( renderQ );
    render.start();

/*
     cv::namedWindow( "Img", cv::WINDOW_OPENGL );
        while(1) {
            auto img = renderQ->pop();
    //      cv::ogl::Buffer tex(img);
    //      imshow("Img", tex);
            imshow("Img", img);
            cv::waitKey(1);
    //        std::this_thread::sleep_for(std::chrono::milliseconds(30));
        }
*/
}

void multi_camera_system( const vector<string> &names)
{
    bool process = true;
    bool compose = true;
    bool render  = true;
    int numCams = names.size();

    vector<CameraCapture*> caps(numCams);
    for( int i = 0; i < numCams; i++) {
        auto newcap = new CameraCapture ( names[i] );
        caps[i] = newcap;
	if( newcap ) newcap->getCapabilities();
    }

    while(1) usleep(200); 
    vector<thread> processThreads;
    vector<ImageQueue>  processedQ;

    if( process ) {
        processedQ.resize( numCams );
        for( int i = 0; i < numCams; i++)  {
            processedQ[i] = make_shared<BlockingQueue<Mat>>();
            processedQ[i]->setCapacity(3);
            processThreads.push_back( thread(process_frame, caps[i], processedQ[i]));
        }
    }

    //while(1) usleep(200); 
    ImageQueue renderQ;
    if( render )
        renderQ = make_shared<BlockingQueue<Mat>>();

    thread composeThread = thread(compose_frames, processedQ, renderQ);

    render_final_frame( renderQ );

    composeThread.join();

    for( auto &th: processThreads)
        th.join();
}

int main(int argc, char *argv[])
{
    vector<string> cams;
    for( int i = 1; i < argc; i++)
        cams.push_back( argv[i] );

    start_t = std::time(nullptr); 
    multi_camera_system(cams);

    return 0;
}
