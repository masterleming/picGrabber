/*
 * main.cpp
 *
 *  Created on: 08-06-2013
 *      Author: Krzysztof Pilch
 */

#include <iostream>
#include <time.h>
#include <sstream>

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace std;

int main(int argc, char **argv)
{
	bool swapCameras = false;
	for (int i = 0; i < argc; i++)
	{
		if (!strcmp(argv[i], "swap"))
		{
			cout << "cameras swaped\n";
			swapCameras = true;
			break;
		}
	}

	cvNamedWindow("Cam1", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Cam2", CV_WINDOW_AUTOSIZE);
	VideoCapture capture1(0), capture2(1);
	Mat frame1, frame2;

	// Variables for Sterei Calibration
	vector<vector<Point2f> > imagePoints1, imagePoints2;
	int sampleNums = 25;
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	clock_t prevTimestamp = 0;
	int delay = 1000;
	Size boardSize(9, 6);

	// Acquisition of data for Stereo Calibration
	while (imagePoints1.size() < sampleNums)
	{
		capture1 >> frame1;
		capture2 >> frame2;

		if (swapCameras)
		{
			Mat tmp = frame1;
			frame1 = frame2;
			frame2 = tmp;
		}

		vector<Point2f> buff1, buff2;
		bool found1 = false, found2 = false;

		found1 = findChessboardCorners(frame1, boardSize, buff1,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK
						| CV_CALIB_CB_NORMALIZE_IMAGE);
		found2 = findChessboardCorners(frame2, boardSize, buff2,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK
						| CV_CALIB_CB_NORMALIZE_IMAGE);

		if (found1 && found2)
		{
			Mat viewGray1, viewGray2;
			cvtColor(frame1, viewGray1, CV_BGR2GRAY);
			cvtColor(frame2, viewGray2, CV_BGR2GRAY);
			cornerSubPix(viewGray1, buff1, Size(11, 11), Size(-1, -1),
					TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			cornerSubPix(viewGray2, buff2, Size(11, 11), Size(-1, -1),
					TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));

			if (clock() - prevTimestamp > delay * 0.001 * CLOCKS_PER_SEC )
			{
				imagePoints1.push_back(buff1);
				imagePoints2.push_back(buff2);
				prevTimestamp = clock();
			}

			stringstream leftS, rightS;
			leftS << "left" << imagePoints1.size() << ".jpg";
			rightS << "right" << imagePoints2.size() << ".jpg";

			imwrite(leftS.str(), frame1);
			imwrite(rightS.str(), frame2);
		}

		drawChessboardCorners(frame1, boardSize, Mat(buff1), found1);
		drawChessboardCorners(frame2, boardSize, Mat(buff2), found2);

		string msg = format("%d/%d", (int) imagePoints1.size(), sampleNums);
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(frame1.cols - 2 * textSize.width - 10,
				frame1.rows - 2 * baseLine - 10);
		putText(frame1, msg, textOrigin, 1, 1, RED);

		imshow("Cam1", frame1);
		imshow("Cam2", frame2);

		char c = cvWaitKey(33);
		if (c == 27)
			break;
	}

	return 0;
}
