#include "CameraCapture.h"

#include <AVFoundation/AVCaptureDevice.h>
#include <AVFoundation/AVCaptureOutput.h>
#include <AVFoundation/AVFoundation.h>
#include <CoreMedia/CoreMedia.h>
#include <Foundation/Foundation.h>
#include <Foundation/NSArray.h>
#include <Foundation/NSString.h>

#include <memory>

using namespace std;
using namespace cv;
int frameid_count[4] = {0,0,0,0}; 

@interface CamCaptureDelegate : NSObject <AVCaptureVideoDataOutputSampleBufferDelegate>
{
    std::mutex  mymtx;
    cv::Mat yuvImg;
}

@property (assign) int camid;
@property (assign) int frameID;
@property (assign) NSCondition *mHasNewFrame;
@property (assign) CVImageBufferRef mCurrentImageBuffer;

- (void)captureOutput:(AVCaptureOutput *)output
    didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
    fromConnection:(AVCaptureConnection *)connection;

- (id) initCamID: (int)camid;
- (cv::Mat )getOutput;

@end


class CameraCaptureImpl
{
    static std::map<std::string, int> nameidmap;
public:
    static AVCaptureDevice *getDevice(const std::string &cam);
    static cv::Mat opencv_mat(CVImageBufferRef buf);
    static std::string getPixelFormatString(int id);
 
    CameraCaptureImpl() {}
    CameraCaptureImpl( const std::string &name, bool start_now = true);

    int open(const std::string &name, bool start_now = true);

    int getDeviceID( const std::string &name);

    int getID() const {
        return camid;
    }

    bool read( cv::Mat &img) const {
        img = [delegate getOutput];
        return 1;
    }

    cv::Mat grabImage() const {
        return [delegate getOutput];
    }

    bool isOpened() const {
         return is_camera_opened;
    }

    int  start();
    int  release();

    bool   set( int propid, double value);
    double get( int propid) const;

    int setPixelFormat( const std::string &s);
    int setBestHeight( int height, bool prefer_higher_value = true);
    int setBestWidth ( int width,  bool prefer_higher_value = true);
    int setBestArea (  int height, int width,  bool prefer_higher_value = true);

    std::array<int,2> getBestDimensions() const;

    int  setConfiguration(int width, int height, int fps);
    void getCapabilities();

private:
    int  camid;
    int  width  = 1920;
    int  height = 1080;
    int  fps    = 30;

    bool is_camera_opened = false;
    bool camera_started   = false;

    cv::Mat     currImg;
    std::string pixelformat = "422YpCbCr8";

    std::string camName;

    void register_camera();

    AVCaptureSession *session = nullptr;
    AVCaptureDeviceInput *input   = nullptr;
    AVCaptureVideoDataOutput *output  = nullptr;
    AVCaptureDevice *videoDevice = nullptr;
    CamCaptureDelegate *delegate = nullptr;
    NSDictionary *videoSettings  = nullptr;
    dispatch_queue_t dqueue;
};

std::map<string,int> CameraCaptureImpl :: nameidmap;

cv::Mat CameraCaptureImpl :: opencv_mat(CVImageBufferRef imageBuffer)
{
    CVPixelBufferLockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);
    size_t width = CVPixelBufferGetWidth(imageBuffer);
    size_t height = CVPixelBufferGetHeight(imageBuffer);
    OSType pixelFormat = CVPixelBufferGetPixelFormatType(imageBuffer);

    size_t bytesPerRow = CVPixelBufferGetBytesPerRow(imageBuffer);
    void *baseAddress = CVPixelBufferGetBaseAddress(imageBuffer);
    uint8_t* data = reinterpret_cast<uint8_t*>(baseAddress);
    cv::Mat img(height, width, CV_8UC2, data, bytesPerRow);
    CVPixelBufferUnlockBaseAddress(imageBuffer, kCVPixelBufferLock_ReadOnly);

    return img;
}

CameraCaptureImpl :: CameraCaptureImpl( const std::string &name, bool start_now)
{
     open(name, start_now);
}

void CameraCaptureImpl :: register_camera()
{
    if( nameidmap.find(camName) == nameidmap.end() ) {
        int nsize = nameidmap.size();
        nameidmap[camName] = nsize;
    }

    camid = nameidmap[camName];
}

int CameraCaptureImpl :: getDeviceID( const string &cam)
{
    if( nameidmap.find(cam) == nameidmap.end() )
        return -1;

    return nameidmap[cam];
}

@implementation CamCaptureDelegate
- (void)captureOutput:(AVCaptureOutput *)output
    didOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
    fromConnection:(AVCaptureConnection *)connection
{ 
    mymtx.lock(); 
    CVImageBufferRef pixelBuffer = CMSampleBufferGetImageBuffer(sampleBuffer);

    OSType pfmt = CVPixelBufferGetPixelFormatType(pixelBuffer);

    self.frameID++;
    //auto newimg = CameraCaptureImpl::opencv_mat(pixelBuffer);
    yuvImg = CameraCaptureImpl::opencv_mat(pixelBuffer);
    
    if (self.frameID%1000 == 0) { 
	cout << "callback camera Idx: " << self.camid << ", frameID=" << self.frameID << std::endl;  
    }

    //mymtx.lock();
    //yuvImg = newimg.clone();
    mymtx.unlock();
}

-(cv::Mat ) getOutput {
       // For testing we are passing rgb
       cv::Mat rgb; 
       int loop_count = 0; 
       //static int frameid_count = 0; 
       if (frameid_count[self.camid]++ % 1000 == 0) {
	 cout << "getOutput camera Idx: " << self.camid << ", frameID=" << self.frameID << ",frameCnt=" << frameid_count[self.camid] << std::endl;  
       }   
       while (1) {
          mymtx.lock();
          if (yuvImg.empty()) {
            mymtx.unlock();
            usleep(10000); 
            if (loop_count++ % 1000 == 0) {
		cout << "stuck at getOutput - " << loop_count << std::endl; 
            } 
          } else {
            mymtx.unlock();
            break;
          }
       } 
        
       //cv::cvtColor(yuvImg, rgb, COLOR_BGRA2BGR); 
       // if we capture as yuv format 422 or 420 
       mymtx.lock(); 	
       cv::cvtColor(yuvImg, rgb, COLOR_YUV2BGR_UYVY);
       mymtx.unlock(); 	
       return rgb;

      return yuvImg; 
}

- (id) initCamID:(int)camid
{
    self = [super init];
    if( self)
    {
        self.camid   = camid;
        self.frameID = 0;
    }
    return self;
}

/*
- (string) getPixelFormatString:(int)pixfmt
{
    switch (pixfmt) {
    case kCVPixelFormatType_32BGRA:
        return "32BGRA";
    case kCVPixelFormatType_32ARGB:
        return "32ARGB";
    case kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange:
        return "420YpCbCr8BiPlanarVideoRange";
    case kCVPixelFormatType_420YpCbCr8BiPlanarFullRange:
        return "420YpCbCr8BiPlanarFullRange";
    case kCVPixelFormatType_420YpCbCr8Planar:
        return "420YpCbCr8Planar";
    case kCVPixelFormatType_422YpCbCr8:
        return "422YpCbCr8";
    case kCVPixelFormatType_24RGB:
        return "24RGB";
    case kCVPixelFormatType_4444YpCbCrA8:
        return "4444YpCbCrA8";
    default:
        return "Unknown format";
    }
}
*/
@end

AVCaptureDevice * CameraCaptureImpl :: getDevice(const string &name)
{
    NSArray<AVCaptureDevice *> *devices = [AVCaptureDevice devices];
    for (AVCaptureDevice *device in devices)
    {
        if ([device.localizedName isEqualToString:@(name.c_str())]) {
            return device;
        }
    }
    return nil;
}

string CameraCaptureImpl :: getPixelFormatString(int pixfmt)
{
    switch (pixfmt) {
    case kCVPixelFormatType_32BGRA:
        return "32BGRA";
    case kCVPixelFormatType_32ARGB:
        return "32ARGB";
    case kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange:
        return "420YpCbCr8BiPlanarVideoRange";
    case kCVPixelFormatType_420YpCbCr8BiPlanarFullRange:
        return "420YpCbCr8BiPlanarFullRange";
    case kCVPixelFormatType_420YpCbCr8Planar:
        return "420YpCbCr8Planar";
    case kCVPixelFormatType_422YpCbCr8:
        return "422YpCbCr8";
    case kCVPixelFormatType_24RGB:
        return "24RGB";
    case kCVPixelFormatType_4444YpCbCrA8:
        return "4444YpCbCrA8";
    default:
        return "Unknown format";
    }
}

bool CameraCaptureImpl :: set(int propid, double value)
{
   switch( propid)
   {
      case CAP_PROP_FRAME_WIDTH:
           width = value;
           return 1;
      case CAP_PROP_FRAME_HEIGHT:
           height = value;
           return 1;
      case CAP_PROP_FPS:
           fps = value;
           return 1;
    }
    return 0;
}

double CameraCaptureImpl :: get(int propid) const
{
   switch( propid)
   {
      case CAP_PROP_FRAME_WIDTH:
           return width;
      case CAP_PROP_FRAME_HEIGHT:
           return height;
      case CAP_PROP_FPS:
           return fps;
    }
    return 0.0;
}

int CameraCaptureImpl :: open( const string &camname, bool start_now)
{
    camName = camname;
    cv::Mat emptyImg;

    is_camera_opened = false;
    camera_started   = false;

    @autoreleasepool {
        std::cout << "Opening Camera : " << camname << std::endl;

        videoDevice = getDevice(camname);

        if (!videoDevice) {
            std::cerr << "Could not find a camera with the given name." << camname << std::endl;
            return -1;
        }

        register_camera();

        // Create an AVCaptureSession
        session = [[AVCaptureSession alloc] init];

#if 0
        //Set FPS
        for (AVCaptureConnection *connection in [session connections]) {
            for (AVCaptureInputPort *port in [connection inputPorts]) {
                if ([[port mediaType] isEqual:AVMediaTypeVideo]) {
                    // Set the minimum and maximum frame duration
                    connection.videoMinFrameDuration = CMTimeMake(1, 30);
                    connection.videoMaxFrameDuration = CMTimeMake(1, 30);
                }
            }
        }
#endif 
        session.sessionPreset = AVCaptureSessionPresetHigh;

        // Create an AVCaptureDeviceInput with the video device
        NSError *error = nil;

        // Create a new AVCaptureDeviceInput with the device
        input = [AVCaptureDeviceInput deviceInputWithDevice:videoDevice error:&error];

        if (!input) {
            std::cout << "Error creating capture device input: "
                      << error.localizedDescription.UTF8String << std::endl;
            return -1;
        }
#if 0
        CMTime minFrameDuration = videoDevice.activeVideoMinFrameDuration;
        CMTime maxFrameDuration = videoDevice.activeVideoMaxFrameDuration;
        float minFPS = minFrameDuration.timescale / minFrameDuration.value;
        float maxFPS = maxFrameDuration.timescale / maxFrameDuration.value;
        float currentFPS = minFrameDuration.timescale / minFrameDuration.value;
        std::cout << "Device supports fps between " << minFPS << " and " << maxFPS  << " Current FPS " << currentFPS << std::endl;
#endif 
        // Add the input to the session
        if (![session canAddInput:input]) {
            std::cout << "Error adding capture device input to session" << std::endl;
            return -1;
        }

        // Add the input to the session
        [session addInput:input];

        // Create a new AVCaptureVideoDataOutput
        output = [[AVCaptureVideoDataOutput alloc] init];

        setConfiguration(width, height, fps);

        // Set the capture callback function
        // Create a new dispatch queue
        dqueue =  dispatch_queue_create(camName.c_str(), DISPATCH_QUEUE_SERIAL);

        delegate = [[CamCaptureDelegate alloc] initCamID:camid ];

        // Set the sample buffer delegate and dispatch queue
        [output setSampleBufferDelegate:delegate queue:dqueue];

        // Add the output to the session
        if (![session canAddOutput:output]) {
            std::cout << "Error adding video data output to session" << std::endl;
            return -1;
        }

        // Add the output to the session
        [session addOutput:output];
    }

    is_camera_opened = true;

    if( start_now ) start();
}

int CameraCaptureImpl :: start()
{
    [session startRunning];
    camera_started = true;
    return 0;
}

int CameraCaptureImpl :: release()
{ 
    cout << "CameraCaptureImpl release gets called" << std::endl; 
    NSAutoreleasePool* localpool = [[NSAutoreleasePool alloc] init];

    [session stopRunning];

    [session release];
    [input release];

    [output release];
    [delegate release];
    [localpool drain];

    is_camera_opened = false;
    return 0;
}

int CameraCaptureImpl :: setConfiguration(int lwidth, int lheight, int lfps)
{
    NSError *error = nil;

    bool success = [videoDevice lockForConfiguration:&error];
    if( !success ) return 1;

    width  = lwidth;
    height = lheight;
    fps    = lfps; 


    NSArray *formats = videoDevice.formats;
    AVCaptureDeviceFormat *targetFormat = nil;
    AVFrameRateRange *targetRange = nil;
    float minFPS = fps , maxFPS = fps;

    for (AVCaptureDeviceFormat *format in formats) {
        for (AVFrameRateRange *range in format.videoSupportedFrameRateRanges) {
            std::cout << "Range " << " max " << range.maxFrameRate << " min " <<  range.minFrameRate << " device " << videoDevice.localizedName.UTF8String << std::endl;
            if ((range.maxFrameRate <= 31 && range.minFrameRate >= 29) || (range.maxFrameRate >= 15 && range.minFrameRate <= 30 )) {
                targetFormat = format;
                targetRange = range;
                std::cout << " Found range  " << targetRange.minFrameRate << ", " << targetRange.maxFrameRate << std::endl;
                //minFPS = range.minFrameRate;
                //maxFPS = range.maxFrameRate;
                break;
            }
        }
        if (targetFormat != nil) {
            break;
        }
    }
#if 0
    if (targetFormat != nil) {
        videoDevice.activeFormat = targetFormat;
        videoDevice.activeVideoMinFrameDuration =  targetRange.minFrameDuration;// CMTimeMake(1, minFPS);
        videoDevice.activeVideoMaxFrameDuration = targetRange.minFrameDuration;//CMTimeMake(1, maxFPS);
    } else {
        std::cout << "No suitable format found to match fps" << std::endl;
    }
#endif 

    videoSettings = [NSDictionary dictionaryWithObjectsAndKeys:
                                  [NSNumber numberWithDouble:1.0*width], (id)kCVPixelBufferWidthKey,
                                  [NSNumber numberWithDouble:1.0*height], (id)kCVPixelBufferHeightKey,
                                  [NSNumber numberWithUnsignedInt:kCVPixelFormatType_422YpCbCr8],
                                  (id)kCVPixelBufferPixelFormatTypeKey,
                                  nil];

    output.videoSettings = videoSettings;

    if (targetFormat != nil) {
        videoDevice.activeFormat = targetFormat;
        videoDevice.activeVideoMinFrameDuration =  targetRange.minFrameDuration;// CMTimeMake(1, minFPS);
        videoDevice.activeVideoMaxFrameDuration = targetRange.minFrameDuration;//CMTimeMake(1, maxFPS);
    } else {
        std::cout << "No suitable format found to match fps" << std::endl;
    }
    
    [videoDevice unlockForConfiguration];

    return 0;
}

void CameraCaptureImpl :: getCapabilities()
{
    cout << "Camera: " << camName << ", camid=" << camid << endl;

    @autoreleasepool {
        NSArray *formats = [videoDevice formats];

        for (AVCaptureDeviceFormat *format in formats) {
            CMFormatDescriptionRef formatDesc = format.formatDescription;
            FourCharCode fourcc = CMFormatDescriptionGetMediaSubType(formatDesc);

            std::string fstr(reinterpret_cast<const char*>(&fourcc), 4);

            cout << "Fourcc: "  << fstr<< " ";

            CMVideoDimensions videoDimensions = CMVideoFormatDescriptionGetDimensions(formatDesc);
            cout << "Resolution: " <<  videoDimensions.width << "x" <<  videoDimensions.height << " ";

            for (AVFrameRateRange *fpsRange in format.videoSupportedFrameRateRanges) {
                cout << "FPS-Range: " <<  fpsRange.minFrameRate << "-" << fpsRange.maxFrameRate << endl;
            }
        }
    }
}

CameraCapture::CameraCapture()
{
 impl = new CameraCaptureImpl();
}

CameraCapture::CameraCapture( const std::string &name, bool start_now)
{
 impl = new CameraCaptureImpl(name, start_now);
}

bool CameraCapture :: open( const std::string &name, bool start_now)
{
   if( impl == nullptr) return 1;
   return impl->open(name,start_now);
}

cv::Mat CameraCapture::grabImage() const
{
   if( impl == nullptr) return cv::Mat();
   return impl->grabImage();
}

bool CameraCapture::read( cv::Mat &img) const
{
   if( impl == nullptr) {
       img = cv::Mat();
       return 1;
   }

   return impl->read(img);
}

int CameraCapture::start() 
{
    if( impl == nullptr) return 1;
    return impl->start();
}

int CameraCapture::release() 
{
    if( impl == nullptr) return 1;
    return impl->release();
}

int CameraCapture :: setConfiguration(int lwidth, int lheight, int lfps)
{
    if( impl == nullptr) return 1;
    return impl->setConfiguration(lwidth, lheight, lfps);
}

void CameraCapture :: getCapabilities()
{
    if( impl == nullptr) return;
    impl->getCapabilities();
}

bool CameraCapture :: isOpened() const
{
    if( impl == nullptr) return 1;
    return impl->isOpened();

}

bool CameraCapture :: set(int propid, double value)
{
    if( impl == nullptr) return false;
    return impl->set(propid, value);
}

double CameraCapture :: get(int propid) const
{
    if( impl == nullptr) return 0.0;
    return impl->get(propid);
}
