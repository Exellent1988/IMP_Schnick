#include <opencv2/opencv.hpp>

using namespace cv;

int main(int argc, const char * argv[]) {
    Mat source = imread("coins.jpg", CV_LOAD_IMAGE_COLOR);
    
    Mat sourceGrayscaled;
    //Umwandeln in Graustufenbild
    cvtColor(source, sourceGrayscaled, CV_RGB2GRAY);
    
    // Graustufenbild mit 3x3 Filtermaske weichzeichnen
    blur(sourceGrayscaled, sourceGrayscaled, Size(3,3) );
    
    vector<Vec3f> circles;
    HoughCircles(sourceGrayscaled, circles, CV_HOUGH_GRADIENT, 1, sourceGrayscaled.rows/8, 120, 50, 0, 0);
    
    for(size_t i = 0; i < circles.size(); i++){
        // Kreismittelpunkt bestimmen
        Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
        // Kreisradius bestimmen
        int radius = cvRound(circles[i][2]);
        // Mittelpunkt einzeichnen
        circle(source, center, 4, Scalar(255,0,0), -1, 8, 0);
        // Kreiskontur einzeichnen
        circle(source, center, radius, Scalar(255,0,255), 3, 8, 0);
    }
    
    namedWindow("Source", WINDOW_AUTOSIZE);
    imshow("Source", source);
    
    waitKey(0);
    return 0;
}
kkk

//Test Test by Exel