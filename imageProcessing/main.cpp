//
//  main.cpp
//  imageProcessing
//
//  Created by Bo Wu on 11/14/14.
//  Copyright (c) 2014 Bo Wu. All rights reserved.
//

#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>

#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

void triangulate_Linear_LS(Mat mat_P_l, Mat mat_P_r, Mat warped_back_l, Mat warped_back_r, Mat point);

int main(int argc, char** argv)
{
    Mat image1, image2, image3, image4, image5;
    
    
    image1 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/1.jpg");
    
    double cM[] = {542.517, 0, 239.5, 0, 542.517, 319.5, 0, 0, 1};
    Mat cm1 = Mat(3, 3, CV_64FC1, cM);
    Mat cm2 = Mat(3, 3, CV_64FC1, cM);
    
    //Size imageSize = image1.size();
    //cout << imageSize << "\n";
    
    double dis[] = {0.06544, 0.54472, 0, -1.8268};
    Mat disCoe1 = Mat(4, 1, CV_64FC1, dis);
    Mat disCoe2 = Mat(4, 1, CV_64FC1, dis);
    //cout << disCoe1 << "\n";
    
    
    double rM1[] = {0.9961, -0.0871, 0, 0.0871, 0.9961, 0, 0, 0, 1};
    Mat rm1 = Mat(3, 3, CV_64FC1, rM1);
    
    double tV1[] = {0.001522, 0, 0.0349};
    Mat tv1 = Mat(3, 1, CV_64FC1, tV1);
    
    double rM2[] = {1, 0, 0, 0, 0.9800, -0.1700, 0, 0.1700, 0.9800};
    Mat rm2 = Mat(3, 3, CV_64FC1, rM2);
    
    double tV2[] = {0.006077, 0, 0.06946};
    Mat tv2 = Mat(3, 1, CV_64FC1, tV2);
    
    double rM3[] = {1, 0, 0, 0, 0.9659, -0.2588, 0, 0.2588, 0.9659};
    Mat rm3 = Mat(3, 3, CV_64FC1, rM3);
    
    double tV3[] = {0.0136, 0, 0.104};
    Mat tv3 = Mat(3, 1, CV_64FC1, tV3);
    
    //double rM4[] = {1, 0, 0, 0, 0.93, -0.34, 0, 0.34, 0.93};
    double rM4[] = {0.9396, -0.342, 0, 0.342, 0.9396, 0, 0, 0, 1};
    Mat rm4 = Mat(3, 3, CV_64FC1, rM4);
   
    double tV4[] = {0.02412, 0, 0.1368};
    Mat tv4 = Mat(3, 1, CV_64FC1, tV4);
    
    
    Mat R1 = Mat(3, 3, CV_64FC1);
    Mat R2 = Mat(3, 3, CV_64FC1);
    Mat P1 = Mat(3, 4, CV_64FC1);
    Mat P2 = Mat(3, 4, CV_64FC1);
    Mat Q  = Mat(4, 4, CV_64FC1);
    
    
    double imagePoint1[] = {243, 420};
    Mat iP1 = Mat(2, 1, CV_64FC1, imagePoint1);
    double imagePoint2[] = {196, 421};
    Mat iP2 = Mat(2, 1, CV_64FC1, imagePoint2);
    double imagePoint3[] = {143, 420};
    Mat iP3 = Mat(2, 1, CV_64FC1, imagePoint3);
    double imagePoint4[] = {89, 421};
    Mat iP4 = Mat(2, 1, CV_64FC1, imagePoint4);
    double imagePoint5[] = {32, 426};
    Mat iP5 = Mat(2, 1, CV_64FC1, imagePoint5);
    
    
    Mat points14D(4, 1, CV_64FC1);
    Mat points24D(4, 1, CV_64FC1);
    Mat points34D(4, 1, CV_64FC1);
    Mat points44D(4, 1, CV_64FC1);
    
    double cT0[] = {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0};
    Mat ct0 = Mat(3, 4, CV_64FC1, cT0);
    
    double cT1[] = {0.9961, -0.0871, 0, 0.001522, 0.0871, 0.9961, 0, 0, 0, 1, 0.0349};
    Mat ct1 = Mat(3, 4, CV_64FC1, cT1);
    
    //doyble cT4[] = {1, 0, 0, 0.2513, 0, 0.9396, -0.342, 0, 0, 0.342, 0.9396, 1.42508}
    double cT4[] = {0.9396, -0.342, 0, 0.1206, 0.342, 0.9396, 0, 0, 0, 0, 1, 0.684};
    //double cT4[] = {0.9396, 0, 0.342, 0.2513, 0, 1, 0, 0, -0.342, 0, 0.9396, 1.42508};
    Mat ct4 = Mat(3, 4, CV_64FC1, cT4);
    
    Mat Pro1 = Mat(3, 4, CV_64FC1);
    Pro1 = cm1 * ct0;
    cout << Pro1 << "\n";
    
    Mat Pro5 = Mat(3, 4, CV_64FC1);
    Pro5 = cm2 * ct4;
    cout << Pro5 << "\n";

    triangulate_Linear_LS(Pro1, Pro5, iP1, iP5, points14D);
    
    triangulatePoints(Pro1, Pro5, iP1, iP2, points14D);
    cout << points14D << "\n";
    
    //triangulatePoints(Pro1, Pro5, iP1, iP5, points24D);
    //cout << points24D << "\n";
    
    
    vector<vector<Point2f>> im1;
    
    vector<Point2f> im11;
    vector<Point2f> im12;
    vector<Point2f> im13;
    vector<Point2f> im14;
    vector<Point2f> im15;
    vector<Point2f> im16;
    vector<Point2f> im17;
    vector<Point2f> im18;
    
    im11.push_back(Point(244,219));
    im12.push_back(Point(371,234));
    im13.push_back(Point(417,208));
    im14.push_back(Point(293,94));
    im15.push_back(Point(284,186));
    im16.push_back(Point(334,323));
    im17.push_back(Point(418,379));
    im18.push_back(Point(425, 92));

    im1.push_back(im11);
    im1.push_back(im12);
    im1.push_back(im13);
    im1.push_back(im14);
    im1.push_back(im15);
    im1.push_back(im16);
    im1.push_back(im17);
    im1.push_back(im18);
    
    vector<vector<Point2f>> im5;
    
    vector<Point2f> im51;
    vector<Point2f> im52;
    vector<Point2f> im53;
    vector<Point2f> im54;
    vector<Point2f> im55;
    vector<Point2f> im56;
    vector<Point2f> im57;
    vector<Point2f> im58;
    
    im51.push_back(Point(30,207));
    im52.push_back(Point(160,239));
    im13.push_back(Point(202,217));
    im54.push_back(Point(81,89));
    im55.push_back(Point(73,183));
    im56.push_back(Point(126,325));
    im57.push_back(Point(204,378));
    im58.push_back(Point(210,102));
    
    im5.push_back(im51);
    im5.push_back(im52);
    im5.push_back(im53);
    im5.push_back(im54);
    im5.push_back(im55);
    im5.push_back(im56);
    im5.push_back(im57);
    im5.push_back(im58);
    
    
    vector<Point2f> iM1(8);
    vector<Point2f> iM5(8);
    
    iM1[0] = Point(244,210);
    iM1[1] = Point(371,234);
    iM1[2] = Point(417,208);
    iM1[3] = Point(293,94);
    iM1[4] = Point(284,186);
    iM1[5] = Point(334,323);
    iM1[6] = Point(418,379);
    iM1[7] = Point(425, 92);
    
    
    iM5[0] = Point(30,207);
    iM5[1] = Point(160,239);
    iM5[2] = Point(202,217);
    iM5[3] = Point(81,89);
    iM5[4] = Point(73,183);
    iM5[5] = Point(126,325);
    iM5[6] = Point(204,378);
    iM5[7] = Point(210,102);

    
    double imagePoint11[] = {244, 210};
    Mat iP11 = Mat(2, 1, CV_64FC1, imagePoint11);
    double imagePoint51[] = {30, 207};
    Mat iP51 = Mat(2, 1, CV_64FC1, imagePoint51);
    Mat point4d1 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP11, iP51, point4d1);
    triangulate_Linear_LS(Pro1, Pro5, iP11, iP51, point4d1);
    //cout << point4d1 << "\n";
    
    
    double imagePoint12[] = {371, 234};
    Mat iP12 = Mat(2, 1, CV_64FC1, imagePoint12);
    double imagePoint52[] = {160, 239};
    Mat iP52 = Mat(2, 1, CV_64FC1, imagePoint52);
    Mat point4d2 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP12, iP52, point4d2);
    triangulate_Linear_LS(Pro1, Pro5, iP12, iP52, point4d2);
    //cout << point4d2 << "\n";
    
    double imagePoint13[] = {417, 208};
    Mat iP13 = Mat(2, 1, CV_64FC1, imagePoint13);
    double imagePoint53[] = {202, 217};
    Mat iP53 = Mat(2, 1, CV_64FC1, imagePoint53);
    Mat point4d3 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP13, iP53, point4d3);
    triangulate_Linear_LS(Pro1, Pro5, iP13, iP53, point4d3);
    //cout << point4d3 << "\n";
    
    double imagePoint14[] = {293, 94};
    Mat iP14 = Mat(2, 1, CV_64FC1, imagePoint14);
    double imagePoint54[] = {81, 89};
    Mat iP54 = Mat(2, 1, CV_64FC1, imagePoint54);
    Mat point4d4 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP14, iP54, point4d4);
    triangulate_Linear_LS(Pro1, Pro5, iP14, iP54, point4d4);
    //cout << point4d4 << "\n";
    
    double imagePoint15[] = {284, 186};
    Mat iP15 = Mat(2, 1, CV_64FC1, imagePoint15);
    double imagePoint55[] = {83, 183};
    Mat iP55 = Mat(2, 1, CV_64FC1, imagePoint55);
    Mat point4d5 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP15, iP55, point4d5);
    triangulate_Linear_LS(Pro1, Pro5, iP15, iP55, point4d5);
    //cout << point4d5 << "\n";
    
    double imagePoint16[] = {334, 323};
    Mat iP16 = Mat(2, 1, CV_64FC1, imagePoint16);
    double imagePoint56[] = {126, 325};
    Mat iP56 = Mat(2, 1, CV_64FC1, imagePoint56);
    Mat point4d6 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP16, iP56, point4d6);
    triangulate_Linear_LS(Pro1, Pro5, iP16, iP56, point4d6);
    //cout << point4d6 << "\n";
    
    double imagePoint17[] = {418, 370};
    Mat iP17 = Mat(2, 1, CV_64FC1, imagePoint17);
    double imagePoint57[] = {204, 378};
    Mat iP57 = Mat(2, 1, CV_64FC1, imagePoint57);
    Mat point4d7 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP17, iP57, point4d7);
    triangulate_Linear_LS(Pro1, Pro5, iP17, iP57, point4d7);
    //cout << point4d7 << "\n";
    
    double imagePoint18[] = {425, 92};
    Mat iP18 = Mat(2, 1, CV_64FC1, imagePoint18);
    double imagePoint58[] = {210, 102};
    Mat iP58 = Mat(2, 1, CV_64FC1, imagePoint58);
    Mat point4d8 = Mat(4, 1, CV_64FC1);
    //triangulatePoints(Pro1, Pro5, iP18, iP58, point4d8);
    //cout << point4d8 << "\n";
    triangulate_Linear_LS(Pro1, Pro5, iP18, iP58, point4d8);
    //cout << point4d8 << "\n";
    
    double i1[] = {244, 210, 371, 234, 417, 208, 293, 94, 284, 186, 334, 323, 418, 379, 425, 92, 243, 420};
    
    Mat IM1 = Mat(2, 9, CV_64FC1, i1);
    
    //cout << IM1 <<"\n";
    
    double i5[] = {30, 207, 160, 239, 202, 217, 81, 89, 73, 183, 126, 325, 204, 378, 210, 102, 32, 426};

    Mat IM5 = Mat(2, 9, CV_64FC1, i5);
    
    Mat point4d = Mat(4, 9, CV_64FC1);
    
              
    Mat fm151 = findFundamentalMat(iM1, iM5, CV_FM_8POINT);
    Mat fm152 = findFundamentalMat(iM1, iM5, CV_FM_RANSAC, 3, 0.99);
    Mat fm153 = findFundamentalMat(iM1, iM5, CV_FM_LMEDS);
    
    //triangulatePoints(Pro1, Pro5, IM1, IM5, point4d);
    
    cout << fm151 << endl;
    cout << fm152 << endl;
    
    
    //Essential Matrix
    Mat E = cm1.t() * fm151 * cm1;
    
    //SVD on E
    SVD decomp = SVD(E);
    
    //U
    Mat U = decomp.u;
    
    
    //S
    Mat S(3, 3, CV_64F, Scalar(0));
    S.at<double>(0, 0) = decomp.w.at<double>(0, 0);
    S.at<double>(1, 1) = decomp.w.at<double>(0, 1);
    S.at<double>(2, 2) = decomp.w.at<double>(0, 2);
    
    //V
    Mat V = decomp.vt;
    
    //W
    Mat W(3, 3, CV_64F, Scalar(0));
    W.at<double>(0, 1) = -1;
    W.at<double>(1, 0) = 1;
    W.at<double>(2, 2) = 1;
    
    cout << decomp.w << endl;
    
    Mat r1 = Mat(3, 3, CV_64F);
    r1 = U * W.t() * V.t();
    
    Mat r2 = Mat(3, 3, CV_64F);
    r2 = U * W * V;
    
    Mat Z(3, 3, CV_64F, Scalar(0));
    Z.at<double>(0, 1) = 1;
    Z.at<double>(1, 0) = -1;
    
    Mat t1 = Mat(3, 1, CV_64F);
    t1 = U.col(2);
    //t1 = V * W * decomp.w * V.t();
    //t1 = V * Z * V.t();
    
    Mat t2 = Mat(3, 1, CV_64F);
    t2 = -U.col(2);

    hconcat(r2, t1, ct4);
    cout << ct4 << endl;
    
    Pro5 = cm1 * ct4;
    
    triangulatePoints(Pro1, Pro5, iP1, iP5, point4d);
    cout << "point 0: " << endl;
    cout << point4d << endl;
    
    triangulatePoints(Pro1, Pro5, iP11, iP51, point4d1);
    cout << "point 1: " << endl;
    cout << point4d1 << endl;
    
    triangulatePoints(Pro1, Pro5, iP12, iP52, point4d2);
    cout << "point 2:" << endl;
    cout << point4d2 << endl;
    
    triangulatePoints(Pro1, Pro5, iP13, iP53, point4d3);
    cout << "point 3:" << endl;
    cout << point4d3 << endl;
    
    triangulatePoints(Pro1, Pro5, iP14, iP54, point4d4);
    cout << "point 4:" << endl;
    cout << point4d4 << endl;
    
    triangulatePoints(Pro1, Pro5, iP15, iP55, point4d2);
    cout << "point 5:" << endl;
    cout << point4d5 << endl;
    
    triangulatePoints(Pro1, Pro5, iP16, iP56, point4d2);
    cout << "point 6:" << endl;
    cout << point4d6 << endl;
    
    
    triangulatePoints(Pro1, Pro5, iP17, iP57, point4d2);
    cout << "point 7:" << endl;
    cout << point4d7 << endl;
    
    triangulatePoints(Pro1, Pro5, iP18, iP58, point4d2);
    cout << "point 8:" << endl;
    cout << point4d8 << endl;
    
    
    const Scalar RED(0,0,255), GREEN(0,255,0);
    
    image1 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/1.jpg");
    image2 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/2.jpg");
    image3 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/3.jpg");
    image4 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/4.jpg");
    image5 = imread("/Users/bowu/Desktop/Research/Xcode/imageProcessing/imageProcessing/5.jpg");

    
    //circle(image1, Point(243, 420), 10, GREEN, -1);
    //circle(image2, Point(196, 421), 10, GREEN, -1);
    
    
    circle(image1, Point(244,210), 2, GREEN, -1);
    circle(image1, Point(371,234), 2, GREEN, -1);
    circle(image1, Point(417,208), 2, GREEN, -1);
    circle(image1, Point(293,94), 2, GREEN, -1);
    circle(image1, Point(284,186), 2, GREEN, -1);
    circle(image1, Point(334,323), 2, GREEN, -1);
    circle(image1, Point(418,379), 2, GREEN, -1);
    circle(image1, Point(425,92), 2, GREEN, -1);
    
    
    
    circle(image5, Point(30,207), 2, RED, -1);
    circle(image5, Point(160,239), 2, RED, -1);
    circle(image5, Point(202,217), 2, RED, -1);
    circle(image5, Point(81,89), 2, RED, -1);
    circle(image5, Point(73,183), 2, RED, -1);
    circle(image5, Point(126,325), 2, RED, -1);
    circle(image5, Point(204,378), 2, RED, -1);
    circle(image5, Point(210,102), 2, RED, -1);
    
    //namedWindow( "Display window", WINDOW_AUTOSIZE );
    //imshow( "Display window", image1);
    
    
    waitKey(0);
    return 0;
}

void triangulate_Linear_LS(Mat mat_P_l, Mat mat_P_r, Mat warped_back_l, Mat warped_back_r, Mat point)
{
    Mat A(4,3,CV_64FC1), b(4,1,CV_64FC1), X(3,1,CV_64FC1), W(1,1,CV_64FC1);
    W.at<double>(0,0) = 1.0;
    A.at<double>(0,0) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,0) - mat_P_l.at<double>(0,0);
    A.at<double>(0,1) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,1) - mat_P_l.at<double>(0,1);
    A.at<double>(0,2) = (warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,2) - mat_P_l.at<double>(0,2);
    A.at<double>(1,0) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,0) - mat_P_l.at<double>(1,0);
    A.at<double>(1,1) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,1) - mat_P_l.at<double>(1,1);
    A.at<double>(1,2) = (warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,2) - mat_P_l.at<double>(1,2);
    A.at<double>(2,0) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,0) - mat_P_r.at<double>(0,0);
    A.at<double>(2,1) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,1) - mat_P_r.at<double>(0,1);
    A.at<double>(2,2) = (warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,2) - mat_P_r.at<double>(0,2);
    A.at<double>(3,0) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,0) - mat_P_r.at<double>(1,0);
    A.at<double>(3,1) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,1) - mat_P_r.at<double>(1,1);
    A.at<double>(3,2) = (warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,2) - mat_P_r.at<double>(1,2);
    b.at<double>(0,0) = -((warped_back_l.at<double>(0,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,3) - mat_P_l.at<double>(0,3));
    b.at<double>(1,0) = -((warped_back_l.at<double>(1,0)/warped_back_l.at<double>(2,0))*mat_P_l.at<double>(2,3) - mat_P_l.at<double>(1,3));
    b.at<double>(2,0) = -((warped_back_r.at<double>(0,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,3) - mat_P_r.at<double>(0,3));
    b.at<double>(3,0) = -((warped_back_r.at<double>(1,0)/warped_back_r.at<double>(2,0))*mat_P_r.at<double>(2,3) - mat_P_r.at<double>(1,3));
    solve(A,b,X,DECOMP_SVD);
    vconcat(X,W,point);
}





