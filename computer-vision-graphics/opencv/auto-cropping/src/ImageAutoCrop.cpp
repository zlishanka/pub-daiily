#include "ImageAutoCrop.h"

using namespace cv;
using namespace std;
ImageAutoCrop ::  ImageAutoCrop()
{
    largeBox = {0,0,0,0};
}

cv::Rect ImageAutoCrop :: getBox(const Mat& inImg)
{
    Mat srcImg = inImg;

    cvtColor( inImg, srcImg, COLOR_BGR2GRAY );
    double thresh = 0;
    double maxValue = 255;
    cv::threshold(srcImg,srcImg, thresh, maxValue, THRESH_OTSU);
    cvtColor( srcImg, srcImg, COLOR_GRAY2BGR );

    int height = srcImg.rows;
    int width  = srcImg.cols;

    auto has_border_color = [] (const vector<cv::Vec3b> &pixColors, cv::Vec3b &bcolor)
    {
        int nCount = 0;
        for( int i = 0; i < pixColors.size(); i++) {
            if( pixColors[i][0] >= bcolor[0] ||
                    pixColors[i][1] >= bcolor[1] ||
                    pixColors[i][2] >= bcolor[2]) nCount++;
        }

        if( nCount > 0.01*pixColors.size() ) return false;

        return true;
    };

    vector<cv::Vec3b> pixColors;

    auto getXmin = [&]( const cv::Mat &srcImg) {
        // top --->Bottom
        int height = srcImg.rows;
        int width  = srcImg.cols;
        int xmin = 0;
        pixColors.resize(width);
        for( int i = 0; i < height; i++) {
            for( int j = 0; j < width; j++)
                pixColors[j] = srcImg.at<cv::Vec3b>(xmin,j);
            if( !has_border_color(pixColors, bgColor) ) break;
            xmin++;
        }

        xmin = max(0, xmin);
        return xmin;
    };

    auto getXmax = [&]( const cv::Mat &srcImg)
    {
        // bottom--->top
        int height = srcImg.rows;
        int width  = srcImg.cols;
        int xmax   = height-1;
        pixColors.resize(width);
        for( int i = 0; i < height; i++) {
            for( int j = 0; j < width; j++)
                pixColors[j] = srcImg.at<cv::Vec3b>(xmax,j);
            if( !has_border_color(pixColors, bgColor) ) break;
            xmax--;
        }
        xmax = min(height-1, xmax);
        return xmax;
    };

    auto getYmin = [&](const cv::Mat &srcImg ) {
        // left--->right
        int height = srcImg.rows;
        int width  = srcImg.cols;
        int ymin = 0;
        pixColors.resize(height);
        for( int j = 0; j < width; j++) {
            for( int i = 0; i < height; i++)
                pixColors[i] = srcImg.at<cv::Vec3b>(i,ymin);
            if( !has_border_color(pixColors, bgColor) ) break;
            ymin++;
        }
        ymin = max(0, ymin);
        return ymin;
    };

    auto getYmax = [&]( const cv::Mat &srcImg) {
        // right---> left
        int height = srcImg.rows;
        int width  = srcImg.cols;
        int ymax = width-1;
        pixColors.resize(height);
        for( int j = 0; j < width; j++) {
            for( int i = 0; i < height; i++)
                pixColors[i] = srcImg.at<cv::Vec3b>(i,ymax);
            if( !has_border_color(pixColors, bgColor) ) break;
            ymax--;
        }
        ymax = min(width-1, ymax);
        return ymax;
    };

    int xmin = getXmin(srcImg);
    int xmax = getXmax(srcImg);

    int ymin = getYmin(srcImg);
    int ymax = getYmax(srcImg);

    if( firstBox) {
        largeBox[0] = xmin;
        largeBox[1] = ymin;
        largeBox[2] = xmax;
        largeBox[3] = ymax;
        firstBox    = false;
    }

    if( keep_large_box ) {
        xmin = min( xmin, largeBox[0]);
        ymin = min( ymin, largeBox[1]);
        xmax = max( xmax, largeBox[2]);
        ymax = max( ymax, largeBox[3]);
    }

    width  = ymax-ymin + 1;
    height = xmax-xmin + 1;

    cv::Rect roi(ymin, xmin, width, height);
    return roi;
}

cv::Mat ImageAutoCrop :: getCropped(const Mat& srcImg)
{
    cv::Rect roi = getBox(srcImg);
    auto dst = srcImg(roi);
    return dst;
}

void ImageAutoCrop :: drawBox(Mat& srcImg)
{
    cv::Rect roi = getBox(srcImg);

    rectangle(srcImg, roi, Scalar(0, 255, 0), 2, LINE_8);
}

cv::RotatedRect ImageAutoCrop :: getMinBox(const Mat &orgImg)
{
    Mat img;
    cvtColor(orgImg, img, COLOR_BGR2GRAY);

    Mat points;
    findNonZero(img, points);

    RotatedRect box = minAreaRect(points);
    return box;
}

cv::Mat  ImageAutoCrop :: getOrthoImage(const Mat &orgImg)
{
    RotatedRect box = getMinBox(orgImg);

    Point2f vtx[4];
    box.points(vtx);

    auto xmin = vtx[0].x;
    auto ymin = vtx[0].y;
    auto xmax = vtx[0].x;
    auto ymax = vtx[0].y;

    for( int i = 1; i < 3; i++) {
        xmin = std::min(xmin, vtx[i].x);
        ymin = std::min(ymin, vtx[i].y);
        xmax = std::max(xmax, vtx[i].x);
        ymax = std::max(ymax, vtx[i].y);
    }

    Rect roi(xmin,ymin, xmax-xmin, ymax-ymin);
    double dx = vtx[3].y - vtx[0].y;
    double dy = vtx[3].x - vtx[0].x;

    double theta = 180.0*atan2(dx,dy)/M_PI;

    auto img = rotate(orgImg, theta, 1);

    return img;
}

Mat ImageAutoCrop :: rotate(Mat src, double angle, bool recenter)
{
    int xold = src.cols;
    int yold = src.rows;

    Point2f pt(0.5*src.cols, 0.5*src.rows);
    Mat rot = getRotationMatrix2D(pt, angle, 1.0);

    int xnew = xold;
    int ynew = yold;

    if( recenter) {
        double cost = cos(M_PI*angle/180.0);
        double sint = sin(M_PI*angle/180.0);

        double xc[] = {-0.5*src.cols, -0.5*src.cols,  0.5*src.cols, 0.5*src.cols};
        double yc[] = {+0.5*src.rows, -0.5*src.rows, -0.5*src.rows, 0.5*src.rows};
        double xn[4], yn[4];
        for( int i = 0; i < 4; i++) {
            xn[i]  = cost*xc[i] - sint*yc[i];
            yn[i]  = sint*xc[i] + cost*yc[i];
        }
        double xmin = *std::min_element( xn, xn + 4);
        double xmax = *std::max_element( xn, xn + 4);
        double ymin = *std::min_element( yn, yn + 4);
        double ymax = *std::max_element( yn, yn + 4);
        xnew = xmax-xmin;
        ynew = ymax-ymin;
        rot.at<double>(0,2) += 0.5*(xnew-xold);
        rot.at<double>(1,2) += 0.5*(ynew-yold);
    }

    Mat dst;
    warpAffine(src, dst, rot, Size(xnew, ynew));

    return dst;
}

