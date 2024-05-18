#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <iostream>
#include <stdio.h>
#include <ctime>
#include <thread>
#include <unistd.h> 
using namespace cv;
using namespace std;

Mat uvc_frame; 
Mat cam_frame; 
Mat roi_img[4]; 
Mat wall_img(1080,1920,CV_8UC3,Scalar(0,0,0));   

bool has_resize=1;  
//mutex mtx; 

void camCapture(unsigned int camIdx, VideoCapture cap, const string name) 
{
    Mat frame; 
 
    int frameCnt = 0;
    int frameEmpty = 0;
    time_t start = std::time(nullptr);
    time_t now  = std::time(nullptr);
    for (;;)
    {
        // wait for a new frame from camera and store it into 'frame'
        cap.read(frame);

        frameCnt += 1;
        // check if we succeeded
        if (frame.empty()) {
	    if (frameEmpty%20 == 0) {
              cerr << "ERROR! blank frame grabbed from " << name << ", count=" << frameEmpty << endl;
            }
            frameEmpty += 1;
        }
	if (has_resize) {
	  Rect roi = Rect(5, 20, 1600, 900); 
	  Mat roi_frame = frame(roi); 
	  resize(roi_frame, roi_img[camIdx], Size(960, 540), 0.0, 0.0, INTER_CUBIC);		
	  //resize(roi_frame, roi_img[camIdx], Size(960, 540), 0.0, 0.0, INTER_LINEAR);		
	  //resize(roi_frame, roi_img[camIdx], Size(960, 540));		
	  //resize(roi_frame, roi_img[camIdx], Size(960, 540), 0.0, 0.0, INTER_AREA);		
        } 
        if (frameCnt % 1000 == 0) {
           now  = std::time(nullptr);
           cout << "camera=" << name << ", frameCnt = " <<  frameCnt << ", elipsed time=" << (now-start) << " sec" <<  endl;
           cout << "frameEmpty = " << frameEmpty << ", w=" << frame.cols << ", h=" << frame.rows << endl;
           cout << " " << endl;
        }

 	usleep(10000); 	
    }
   
} 


int main(int, char**)
{
    VideoCapture cap[6]; 

    int deviceID = 0;             // 0 = open default camera
    int apiID = cv::CAP_ANY;      // 0 = autodetect default API

    /* 
    for (int i = 0; i  < 6; i++) {

		cap[i].open(i, apiID);
    		// check if we succeeded
    		if (!cap[i].isOpened()) {
           		cerr << "ERROR! Unable to open camera " << i << endl;
           		return -1;
        	}
	 
 	if (i == 1 || i == 3) {  	// PTZ 
	  cap[i].set(CAP_PROP_FRAME_WIDTH, 1280); 
	  cap[i].set(CAP_PROP_FRAME_HEIGHT, 720); 
	  cap[i].set(CAP_PROP_FPS, 30); 
        }    
    }
    */	
    //cap[0].open("MINRRAY-TOP", apiID); 
    cap[0].open(2, apiID); 
    if (!cap[0].isOpened()) {
          cerr << "ERROR! Unable to open camera " << "TOP" << endl;
          return -1;
    }
    //cap[1].open("MINRRAY-FRONT", apiID); 
    cap[1].open(3, apiID); 
    if (!cap[1].isOpened()) {
          cerr << "ERROR! Unable to open camera " << "FRONT" << endl;
          return -1;
    }
    cout << "Start grabbing" << endl
        << "Press any key to terminate" << endl; 

    //thread avhd_cap(camCapture, 0, cap[0], "Av.io HD"); 
    //thread av4k_cap(camCapture, 3, cap[3], "Front");
    thread top_cap(camCapture, 0, cap[0], "top"); 
    thread front_cap(camCapture, 1, cap[1], "UVC");


     while (waitKey(1) != 'q') {

        for (int i = 0; i < 2; i++) {

            int x = i % 2;
            int y = i / 2;
            Rect roi(x * 960, y * 540, 960, 540);
	    if (!roi_img[i].empty()) {
            	roi_img[i].copyTo(wall_img(roi));
	    } 
        }



       imshow("AvailCV Upgrade", wall_img);
    }

   	

    //avhd_cap.join(); 
    //av4k_cap.join(); 
    top_cap.join();  
    front_cap.join();  
 
    destroyAllWindows(); 
 
    return 0;
}
