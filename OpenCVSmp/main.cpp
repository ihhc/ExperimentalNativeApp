#include <opencv2\imgcodecs.hpp>
#include <opencv2\highgui.hpp>
#include <opencv2\imgproc.hpp>
#include <opencv2\objdetect.hpp>
#include <iostream>

using namespace std;
using namespace cv;

int main()
{
	CascadeClassifier cl;
	cl.load("./haarcascade_frontalface_default.xml"); //better
	//cl.load("./haarcascade_frontalface_alt.xml");
	//cl.load("./haarcascade_frontalface_alt_tree.xml");
	//cl.load("./haarcascade_frontalface_alt2.xml");
	vector<Rect> faces;
	Mat frm;
	//static picture
	frm = imread("./0032018.jpg");
	cl.detectMultiScale(frm, faces);
	for (int i = 0; i < faces.size(); i++)
	{
		rectangle(frm, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 5);
	}
	imshow("test window", frm);
	waitKey(0);
	//camera
	VideoCapture cap(0);//default camera
	if (!cap.isOpened()) {
		cerr << "Unable to open camera\n";
		return -1;
	}
	while (1)
	{
		cap.read(frm);

		if (frm.empty()) {
			cerr << "blank frame grabbed\n";
			break;
		}
		cl.detectMultiScale(frm, faces);
		for (int i = 0; i < faces.size(); i++)
		{
			rectangle(frm, faces[i].tl(), faces[i].br(), Scalar(50, 50, 255), 5);
		}
		// show live cam
		imshow("test window", frm);
		if (waitKey(5) >= 0)
			break;
	}
	return 0;
}