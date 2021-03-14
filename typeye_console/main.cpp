#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>

using namespace std;
using namespace cv;

double measureFps(VideoCapture &cap)
{
    double fps = cap.get(CAP_PROP_FPS);
    cout << "Frames per second using cap.get(CAP_PROP_FPS) : " << fps << endl;
    int num_frames = 120;
    time_t start, end;
    Mat frame;
    cout << "Capturing " << num_frames << " frames" << endl;
    time(&start);

    for(int i = 0; i < num_frames; i++)
        cap >> frame;

    time(&end);
    double seconds = difftime(end, start);
    cout << "Time taken : " << seconds << " seconds" << endl;

    fps = num_frames / seconds;
    cout << "Estmated frames per second : " << fps << endl;
    return fps;
}

int main(int argc, char *argv[])
{
    // Create a VideoCapture object and open the input file
    // If the input is the web camera, pass 0 instead of the video file name
    VideoCapture cap(0, cv::CAP_V4L2);

    // Check if camera opened successfully
    if(!cap.isOpened())
    {
      cout << "Error opening video stream or file" << endl;
      return -1;
    }

    measureFps(cap);

    while(1)
    {
      Mat frame;

      // Capture frame-by-frame
      cap >> frame;

      // If the frame is empty, break immediately
      if (frame.empty())
        break;
      // Display the resulting frame
      imshow( "Frame", frame );
      // Press  ESC on keyboard to exit
      char c=(char)waitKey(25);
      if(c==27)
        break;
    }

    // When everything done, release the video capture object
    cap.release();

    // Closes all the frames
    destroyAllWindows();
    return 0;
}
