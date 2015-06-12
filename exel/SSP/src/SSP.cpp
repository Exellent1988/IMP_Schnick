#include<opencv2/core/core.hpp>
#include<opencv2/contrib/contrib.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include<vector>

using namespace cv;
using namespace std;



Mat Image_Overlay(Mat original_frame, Mat overlay, double anteil ){
	Mat output; double alpha = anteil ; double beta;
	cv::resize(overlay,overlay,Size(original_frame.cols,original_frame.rows)); //resize overlay to frame size


	if (!overlay.empty()) { // check for overlay
	            beta = ( 1.0 - anteil ); //beta Wert berechnung
	            addWeighted( original_frame, alpha, overlay, beta, 0.0, output);  // Pictureoverlay

	            return output;
	}
	else return original_frame ;


}
Mat Display_Text( Mat image, char* text, int height, int width, int size, int thik )
{
  Size textsize = getTextSize(text, CV_FONT_HERSHEY_COMPLEX, size, thik, 0);
  Point org((width- textsize.width), (height - textsize.height));
  int lineType = 2;

  putText( image, text, org, CV_FONT_HERSHEY_COMPLEX, size,
            Scalar(255, 255, 255), thik, lineType );
    return image;
}

int main(int argc, char* argv[])
{
    VideoCapture vid("vids/avi.avi"); // open the video file for reading
    VideoCapture cam;
    cam.open(0);


    if ( !cam.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the camera stream" << endl;
         return -1;
    }
    if ( !vid.isOpened() )  // if not success, exit program
    {
         cout << "Cannot open the video file" << endl;
         return -1;
    }

    //cap.set(CV_CAP_PROP_POS_MSEC, 300); //start the video at 300ms

    double fps = vid.get(CV_CAP_PROP_FPS); //get the frames per seconds of the video

     cout << "Frame per seconds : " << fps << endl;

    //namedWindow("Video",CV_WINDOW_AUTOSIZE); //create a window called "Video"
    //namedWindow("Camera",CV_WINDOW_AUTOSIZE); //create a window called "Camera"
    namedWindow("Overlay",CV_WINDOW_AUTOSIZE); //create a window called "Overlay"

    while(1)
    {
        Mat video_frame;
        Mat camera_frame;

        cam>>camera_frame;
        bool bSuccess = vid.read(video_frame); // read a new frame from video

        if (!bSuccess) //if not success, break loop
        {
                        cout << "Cannot read the frame from video file" << endl;
                       break;
        }

        Mat output = Image_Overlay(camera_frame,video_frame, 0.25);
        Mat output2 = Display_Text(output, "TEST TEXT", (output.rows),(output.cols),2,2);
        //imshow("Video", video_frame); //show the video_frame in "Video" window
        //imshow("Camera",camera_frame); //show camera stream
        imshow("Overlay",output2); //show camera stream

        if(waitKey(30) == 27) //wait for 'esc' key press for 30 ms. If 'esc' key is pressed, break loop
       {
                cout << "esc key is pressed by user" << endl;
                break;
       }
    }

    return 0;

}
