#include <iostream>
#include <opencv2/opencv.hpp>
#include <array>
using namespace std;
using namespace cv;



int main()
{
	Mat img = imread("1.png");
	namedWindow("image");
	

	/*Draw a circle*/
	circle(img, Point(30, 40), 50, Scalar(255,255,255));

	/*Draw an ellipse*/
	ellipse(img, Point(100, 200), Size(50, 80), 0, 0, 360, Scalar(0, 0, 0), -1);

	/*Draw a Polygon*/
	array<Point, 5> convesPoints{ Point(100,100),Point(120,100),Point(130,120),Point(120,140),Point(100,140) };
	fillConvexPoly(img,convesPoints,Scalar(0,0,255),8);

	/*Draw a line*/
	line(img, Point(400, 500), Point(800, 500), Scalar(0,0,255,255), 2);

	/*Draw a rectangle*/
	rectangle(img, Rect(500, 20, 100, 50), Scalar(0, 255, 0), -1);

	/*Draw texts*/
	putText(img, "SomeText", Point(300, 300), FONT_HERSHEY_DUPLEX, 2, Scalar(255, 255, 0));


	imshow("image", img);
	waitKey(0);
	destroyWindow("image");
}