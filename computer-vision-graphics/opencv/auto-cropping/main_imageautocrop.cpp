#include "ImageAutoCrop.h"
#include <algorithm>

#include "../Utils/StopWatch.h"

using namespace std;
using namespace cv;

void process_image( const string &filename)
{
    ImageAutoCrop crop;

    auto srcImg = imread(filename);
    imshow("src", srcImg);

    StopWatch watch;

    watch.start();
    auto rect = crop.getBox(srcImg);

    /*
    crop.drawBox(srcImg);
    imshow("dst", srcImg);
    */

    Mat dstImg;
    dstImg = crop.getCropped(srcImg);
    imshow("cropped", dstImg);
    imwrite("cropped.png", dstImg);

    waitKey(0);
}

void process_video( const string &filename)
{
    ImageAutoCrop autocrop;
    autocrop.keepLargeBox(1);

    namedWindow("Frame", WINDOW_NORMAL);

    VideoCapture cap(filename);

    bool repeat = true;

    while(1) {
        Mat image;
        cap >> image;
        if( image.empty()) {
            if( repeat ) {
                    cap.set(CAP_PROP_POS_FRAMES, 0);
                    cap >> image;
	    }else {
		break;
	    }
	}
        image = autocrop.getCropped(image);
    //    autocrop.drawBox(image);
        if( !image.empty()) {
        imshow( "Frame", image);
        waitKey(1);
	}
    }
}

int main( int argc, char **argv)
{
    if( argc != 2) {
        cout << "Usage input " << endl;
        return 1;
    }

    process_video( argv[1] );


    return 0;
}
