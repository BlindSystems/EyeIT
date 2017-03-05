// License: Apache 2.0. See LICENSE file in root directory.
// Copyright(c) 2016 Intel Corporation. All Rights Reserved.

#include <memory>
#include <iostream>
#include "rs_sdk.h"
#include <unistd.h>
#include <thread>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include "opencv2/opencv.hpp"

#include <exception>
#include <limits>


#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

using namespace cv;

/// Global variables
Mat src, erosion_dst, dilation_dst;
const std::string SRC_WINDOW_NAME = "source";
const std::string M_BLUR_WINDOW_NAME = "m_blur";
const std::string CANNY_WINDOW_NAME = "edges";
const std::string LABLES_WINDOW_NAME = "labels";

int erosion_elem = 0;
int erosion_size = 0;
int dilation_elem = 0;
int dilation_size = 0;
int const max_elem = 2;
int const max_kernel_size = 21;

void Erosion(int, void*);
void Dilation(int, void*);


std::string image_name = "images.jpg";
std::string folder_name = "C:\\Users\\clopians\\Documents\\EyeIT\\dark\\";


cv::Mat createVDisparity(cv::Mat image)
{
    cv::Mat vDisparity = cv::Mat::zeros(image.rows, 256, CV_32S);
    for (int i = 0; i < image.rows; i++)
    {
        for (int j = 0; j < image.cols; j++)
        {
            int index = image.at<uchar>(i, j);
            int origVal = vDisparity.at<int>(i, index);
            int newVal = origVal + 1;
            vDisparity.at<int>(i, index) = newVal;
        }
    }
    int counter = 0;
    for (int i = 0; i < vDisparity.rows; i++)
    {
        for (int j = 0; j < vDisparity.cols; j++)
            counter += vDisparity.at<int>(i, j);
        if (counter != image.cols)
            std::cout << "problem: in vDisparity the row: " << i << " has in total " << counter << " values, not " << image.cols << std::endl;
        counter = 0;
    }
    std::string vDisparityName = "vDisparity.png";
    std::string full_path = folder_name + vDisparityName;
    vDisparity.convertTo(vDisparity, CV_8UC3);
    //bool b = cv::imwrite(full_path, vDisparity);
    return vDisparity;
}

void createSeedMap(cv::Mat image)
{

    cv::Mat seedMap = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);//all pixels are black - the seeds will be colored in white

    for (int i = 1; i < image.rows - 1; i++)//i & j start do not include edges - seeds can't be in edges
    {
        for (int j = 1; j < image.cols - 1; j++)
        {
            if (image.at<uchar>(i, j - 1) == image.at<uchar>(i - 1, j - 1) && image.at<uchar>(i + 1, j - 1) == image.at<uchar>(i - 1, j - 1) && image.at<uchar>(i - 1, j) == image.at<uchar>(i - 1, j - 1) && image.at<uchar>(i, j) != image.at<uchar>(i - 1, j - 1))
                seedMap.at<int>(i, j) = 255;//seed found - color in white
        }
    }
    std::string seedMapName = image_name.substr(0, image_name.size() - 4) + "_seedMap.png";
    imwrite(folder_name + seedMapName, seedMap);
}

cv::Mat removeEdges(cv::Mat src)
{
    cv::Mat EdgesRemoved = src.clone();
    int TH2 = 20;
    int neighborsSum = 0;
    for (int y = 1; y < src.rows - 1; y++)//i & j start do not include edges - seeds can't be in edges
    {
        for (int x = 1; x < src.cols - 1; x++)
        {
            neighborsSum = abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x, y - 1)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x + 1, y)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x, y + 1)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x - 1, y)));
            if (neighborsSum > TH2)
                EdgesRemoved.at<uchar>(cv::Point(x, y)) = 0;
            neighborsSum = 0;
        }
    }
    return EdgesRemoved;
}

cv::Mat createGroundMap(cv::Mat vd, cv::Mat src)
{
    cv::Mat GroundMap = vd.clone();
    cv::Mat depthMat = src.clone();
    int n = 10;
    int TH1 = 55;
    bool flag = 0;
    //cv::Mat depthMat = cv::imread(folder_name + image_name, cv::IMREAD_GRAYSCALE);
    //cv::invert(depthMat, depthMat);
    for (int x = 0; x < vd.cols; x++)//i & j start do not include edges - seeds can't be in edges
    {
        for (int y = vd.rows * 0.25; y < vd.rows; y++)
        {
            if (vd.at<uchar>(cv::Point(x, y)) - vd.at<uchar>(cv::Point(x, y - n)) >= 30)
            {
                flag = 1;
                for (int i = 0; i < n; i++)
                {
                    if (vd.at<uchar>(cv::Point(x, y - i)) - vd.at<uchar>(cv::Point(x, y - i - 1)) < -20)
                        flag = 0;
                }
                if (flag == 1 && (vd.at<uchar>(cv::Point(x, y)) > TH1))
                {
                    GroundMap.at<uchar>(cv::Point(x, y)) = 0; //This is ground
                    for (int k = 0; k < depthMat.cols + 0; k++)
                    {
                        if (abs(depthMat.at<uchar>(cv::Point(k, y)) - x) < 10)
                            depthMat.at<uchar>(cv::Point(k, y)) = 0;
                    }
                }
            }
        }
    }
    //imshow("ground map", GroundMap);
    //std::string seedMapName = image_name.substr(0, image_name.size() - 4) + "_groundMap.png";
    //imwrite(folder_name + seedMapName, GroundMap);
    return depthMat;
}

cv::Mat inverse(cv::Mat src)
{

    cv::Mat invSrc = cv::Scalar::all(255) - src;
    return invSrc;
}

cv::Mat filterPossibleDescendingStairsPoints(cv::Mat src)
{
    cv::Mat filteredImage  = cv::Mat::zeros(src.rows, src.cols, CV_8UC1);
    int TH3 = 50;
    for (int x = 0; x < src.cols; x++)
    {
        for (int y = 1; y < src.rows; y++)
        {
            if (src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x, y - 1)) >= 50)
            {
                filteredImage.at<uchar>(cv::Point(x, y)) = 255;
            }
        }
    }
    return filteredImage;
}

//cv::Mat findLines(cv::Mat src)
//{
//	//cv::Mat cdst(src.rows, src.cols, CV_8UC3);
//
//
//	cv::Ptr<cv::LineSegmentDetector> ls = cv::createLineSegmentDetector(cv::LSD_REFINE_STD);//LSD_REFINE_NONE
//	double start = double(cv::getTickCount());
//	std::vector<cv::Vec4f> lines_std;
//	cv::Mat lines_width;
//	// Detect the lines
//	ls->detect(src, lines_std, lines_width);
//	size_t c = lines_std.capacity();
//	size_t s = lines_std.size();
//
//	//double duration_ms = (double(cv::getTickCount()) - start) * 1000 / cv::getTickFrequency();
//	//std::cout << "It took " << duration_ms << " ms." << std::endl;
//	// Show found lines
//	cv::Mat drawnLines(src);
//	ls->drawSegments(drawnLines, lines_std);
//
//	//std::vector<cv::Vec4i> lines_htp;
//	//cv::HoughLinesP(src, lines_htp, 1, CV_PI / 180, 50, 50, 10);
//	//for (size_t i = 0; i < 1000/*lines_htp.size()*/; i++)
//	//{
//	//	cv::Vec4i l = lines_htp[i];
//	//	try
//	//	{
//	//		line(drawnLines, cv::Point(l[0], l[1]), cv::Point(l[2], l[3]), cv::Scalar(255, 0, 0), 2, CV_AA);
//	//	}
//	//	catch (const std::exception&)
//	//	{
//	//		std::cout << "failed!";
//	//	}
//	//}
//
//
//	//cv::Mat dst, cdst;
//	//cv::Canny(src, dst, 50, 200, 3);
//	//cv::cvtColor(dst, cdst, CV_GRAY2BGR);
//	//std::vector<cv::Vec2f> lines;
//	//// detect lines
//	//cv::HoughLines(dst, lines, 1, CV_PI / 180, 150,0, 0);
//
//	//// draw lines
//	//for (size_t i = 0; i < lines.size(); i++)
//	//{
//	//	float rho = lines[i][0], theta = lines[i][1];
//	//	cv::Point pt1, pt2;
//	//	double a = cos(theta), b = sin(theta);
//	//	double x0 = a*rho, y0 = b*rho;
//	//	pt1.x = cvRound(x0 + 1000 * (-b));
//	//	pt1.y = cvRound(y0 + 1000 * (a));
//	//	pt2.x = cvRound(x0 - 1000 * (-b));
//	//	pt2.y = cvRound(y0 - 1000 * (a));
//	//	line(cdst, pt1, pt2, cv::Scalar(0, 0, 255), 3, CV_AA);
//	//}
//
//	return drawnLines;
//}



int main(int argc, char* argv[]){





        //cv::Mat image = cv::imread(folder_name + image_name, cv::IMREAD_GRAYSCALE);
        cv::Mat image = cv::imread("/home/ntuser-chavy/Desktop/Project/EyeIT/Images/Original_Images/images.jpg", cv::IMREAD_GRAYSCALE);
        if (image.cols == 0)
        {
            std::cout << "Failed to open image " << image_name << std::endl;
            return 1;
        }

        cv::Mat invSrc = inverse(image);
        cv::Mat edges = removeEdges(invSrc);
        cv::Mat vDisparity = createVDisparity(edges);
        cv::Mat groundRemoved = createGroundMap(vDisparity, edges);
        cv::Mat colored(groundRemoved.size(), CV_8UC3);
        cv::cvtColor(groundRemoved, colored, CV_GRAY2BGR);
        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::findContours(colored, contours, hierarchy, CV_RETR_CCOMP, cv::CHAIN_APPROX_SIMPLE);
        cv::Mat markers (colored.size(),CV_32S);
        markers = cv::Scalar::all(0);
        int compCount = 0;
        for (int idx = 0; idx >= 0; idx = hierarchy[idx][0], compCount++)
            cv::drawContours(markers, contours, idx, cv::Scalar::all(compCount + 1), -1, 8, hierarchy, INT_MAX);
        //cv::Mat markers = colored.clone();
        //markers.convertTo(markers, CV_32SC1);
        cv::watershed(colored, markers);

        std::vector<cv::Vec3b> colorTab;
        for (int i = 0; i < compCount; i++)
        {
            int b = cv::theRNG().uniform(0, 255);
            int g = cv::theRNG().uniform(0, 255);
            int r = cv::theRNG().uniform(0, 255);
            colorTab.push_back(cv::Vec3b((uchar)b, (uchar)g, (uchar)r));
        }
        cv::Mat wshed(markers.size(), CV_8UC3);
        // paint the watershed image
        for (int i = 0; i < markers.rows; i++)
            for (int j = 0; j < markers.cols; j++)
            {
                int index = markers.at<int>(i, j);
                if (index == -1)
                    wshed.at<cv::Vec3b>(i, j) = cv::Vec3b(255, 255, 255);
                else if (index <= 0 || index > compCount)
                    wshed.at<cv::Vec3b>(i, j) = cv::Vec3b(0, 0, 0);
                else
                    wshed.at<cv::Vec3b>(i, j) = colorTab[index - 1];
            }
        wshed = wshed*0.5 + groundRemoved*0.5;

        cv::Mat PossiblePoints = filterPossibleDescendingStairsPoints(invSrc);
        //cv::Mat lines = findLines(image/*PossiblePoints*/);
        //cv::imshow("depth map", image);


        //cv::Mat vDisparity = createVDisparity(image);
        //createSeedMap(image);
        //createGroundMap(vDisparity);

        return 0;







//    std::string imagesFolder = argv[1];
//    std::vector<std::string> images;

//    DIR *dir;
//    class dirent *ent;
//    class stat st;

//    dir = opendir(argv[1]);
//    while ((ent = readdir(dir)) != NULL)
//    {
//        const std::string file_name = ent->d_name;
//        const std::string full_file_name = imagesFolder + "/" + file_name;

//        if (file_name[0] == '.')
//            continue;

//        if (stat(full_file_name.c_str(), &st) == -1)
//            continue;

//        const bool is_directory = (st.st_mode & S_IFDIR) != 0;

//        if (is_directory)
//            continue;

//        images.push_back(full_file_name);
//    }
//    closedir(dir);

//        cv::namedWindow(SRC_WINDOW_NAME, CV_WINDOW_NORMAL);
//        cv::moveWindow(SRC_WINDOW_NAME, 100, 100);

//        cv::namedWindow(M_BLUR_WINDOW_NAME, CV_WINDOW_NORMAL);
//        cv::moveWindow(M_BLUR_WINDOW_NAME, 500, 100);

//        cv::namedWindow(CANNY_WINDOW_NAME, CV_WINDOW_NORMAL);
//        cv::moveWindow(CANNY_WINDOW_NAME, 1000, 100);

//        cv::namedWindow(LABLES_WINDOW_NAME, CV_WINDOW_NORMAL);
//        cv::moveWindow(LABLES_WINDOW_NAME, 1500, 100);

//        uchar max = 0/*std::numeric_limits<char>::min()*/;
//        uchar min = 255/*std::numeric_limits<char>::max()*/;

//        for(std::string img : images)
//        {
//                src = cv::imread(img,cv::IMREAD_GRAYSCALE);
//                /*for (size_t i = 0; i < src.rows; i++)
//                {
//                    for (size_t j = 0; j < src.cols; j++)
//                    {
//                        if (src.at<uchar>(i, j) < min)
//                            min = src.at<uchar>(i, j);
//                        if (src.at<uchar>(i, j) > max)
//                            max = src.at<uchar>(i, j);
//                    }
//                }
//                std::cout << "min = " << (int)min << " max = " << (int)max << std::endl;
//                min = 255;
//                max = 0;*/

//                cv::Mat g_blur, m_blur,mult,lap, lap_draw, th;
//                cv::Size s(5,5);
//                double sigmaX = 0.0, factor = 4.0;
//                mult = src * factor;
//                cv::medianBlur(mult, m_blur, 3);
//                cv::GaussianBlur(mult, g_blur, s, sigmaX );
//                //src = m_blur.clone();

//                //cv::threshold(mult, mult, 70, 255, cv::THRESH_BINARY_INV);

//                /// Apply Laplace function
//                Laplacian(m_blur, lap, CV_16S, 3, 1, 0, BORDER_DEFAULT);
//                convertScaleAbs(lap, lap_draw);

//                Mat canny;
//                Canny(m_blur, canny, 50, 150, 3);


//                //connected components method
//                cv::Mat lables;
//                cv::connectedComponents(m_blur, lables);

//                cv::imshow(SRC_WINDOW_NAME, mult);
//                //cv::waitKey(1);
//                cv::imshow(M_BLUR_WINDOW_NAME, m_blur);
//                //cv::waitKey(1);
//                cv::imshow(CANNY_WINDOW_NAME, canny);
//                //cv::waitKey(1);
//                cv::imshow(LABLES_WINDOW_NAME, lables);
//                cv::waitKey(1000);

//                // Create a kernel that we will use for accuting/sharpening our image
//                            Mat kernel = (Mat_<float>(3, 3) <<
//                                1, 1, 1,
//                                1, -8, 1,
//                                1, 1, 1); // an approximation of second derivative, a quite strong kernel
//                                          // do the laplacian filtering as it is
//                                          // well, we need to convert everything in something more deeper then CV_8U
//                                          // because the kernel has some negative values,
//                                          // and we can expect in general to have a Laplacian image with negative values
//                                          // BUT a 8bits unsigned int (the one we are working with) can contain values from 0 to 255
//                                          // so the possible negative number will be truncated
//                            Mat imgLaplacian;
//                            Mat sharp = src; // copy source image to another temporary one
//                            filter2D(sharp, imgLaplacian, CV_32F, kernel);
//                            src.convertTo(sharp, CV_32F);
//                            Mat imgResult = sharp - imgLaplacian;
//                            // convert back to 8bits gray scale
//                            imgResult.convertTo(imgResult, CV_8UC3);
//                            imgLaplacian.convertTo(imgLaplacian, CV_8UC3);
//                            // imshow( "Laplace Filtered Image", imgLaplacian );
//                            //imshow("New Sharped Image", imgResult);

//                            // Create binary image from source image
//                            Mat bw;
//                            //cvtColor(src, bw, CV_BGR2GRAY);
//                            threshold(src, bw, 200, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
//                            //imshow("Binary Image", bw);

//                            // Perform the distance transform algorithm
//                            Mat dist;
//                            distanceTransform(bw, dist, CV_DIST_L2, 3);
//                            // Normalize the distance image for range = {0.0, 1.0}
//                            // so we can visualize and threshold it
//                            normalize(dist, dist, 0, 1., NORM_MINMAX);
//                            //imshow("Distance Transform Image", dist);

//                            // Threshold to obtain the peaks
//                            // This will be the markers for the foreground objects
//                            threshold(dist, dist, .4, 1., CV_THRESH_BINARY);
//                            // Dilate a bit the dist image
//                            Mat kernel1 = Mat::ones(3, 3, CV_8UC1);
//                            dilate(dist, dist, kernel1);
//                            //imshow("Peaks", dist);

//                            // Create the CV_8U version of the distance image
//                            // It is needed for findContours()
//                            Mat dist_8u;
//                            dist.convertTo(dist_8u, CV_8U);
//                            // Find total markers
//                            std::vector<std::vector<cv::Point>> contours;
//                            findContours(dist_8u, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);


//                            // Create the marker image for the watershed algorithm
//                            Mat markers = Mat::zeros(dist.size(), CV_32SC1);
//                            // Draw the foreground markers
//                            for (size_t i = 0; i < contours.size(); i++)
//                                drawContours(markers, contours, static_cast<int>(i), Scalar::all(static_cast<int>(i) + 1), -1);
//                            // Draw the background marker
//                            circle(markers, Point(5, 5), 3, CV_RGB(255, 255, 255), -1);
//                            imshow(LABLES_WINDOW_NAME, markers /** 10000*/);

//                            // Perform the watershed algorithm
//                            watershed(src, markers);
//                            Mat mark = Mat::zeros(markers.size(), CV_8UC1);
//                            markers.convertTo(mark, CV_8UC1);
//                            bitwise_not(mark, mark);
//                            //    imshow("Markers_v2", mark); // uncomment this if you want to see how the mark
//                            // image looks like at that point
//                            // Generate random colors
//                            std::vector<Vec3b> colors;
//                            for (size_t i = 0; i < contours.size(); i++)
//                            {
//                                int b = theRNG().uniform(0, 255);
//                                int g = theRNG().uniform(0, 255);
//                                int r = theRNG().uniform(0, 255);
//                                colors.push_back(Vec3b((uchar)b, (uchar)g, (uchar)r));
//                            }
//                            // Create the result image
//                            Mat dst = Mat::zeros(markers.size(), CV_8UC3);
//                            // Fill labeled objects with random colors
//                            for (int i = 0; i < markers.rows; i++)
//                            {
//                                for (int j = 0; j < markers.cols; j++)
//                                {
//                                    int index = markers.at<int>(i, j);
//                                    if (index > 0 && index <= static_cast<int>(contours.size()))
//                                        dst.at<Vec3b>(i, j) = colors[index - 1];
//                                    else
//                                        dst.at<Vec3b>(i, j) = Vec3b(0, 0, 0);
//                                }
//                            }
//                            // Visualize the final image
//                            imshow("Final Result", dst);



//                /*cv::imshow(COLOR_WINDOW_NAME, src);
//                cv::waitKey(1);*/

//                /*
//                //flood_fill
//                // Threshold.
//                // Set values equal to or above 220 to 0.
//                // Set values below 220 to 255.
//                cv::Mat im_th;
//                cv::threshold(src, im_th, 100, 255, cv::THRESH_BINARY_INV);

//                // Floodfill from point (0, 0)
//                cv::Mat im_floodfill = im_th.clone();
//                floodFill(im_floodfill, cv::Point(0, 0), cv::Scalar(255));

//                // Invert floodfilled image
//                cv::Mat im_floodfill_inv;
//                cv::bitwise_not(im_floodfill, im_floodfill_inv);

//                // Combine the two images to get the foreground.
//                cv::Mat im_out = (im_th | im_floodfill_inv);

//                /// Create windows
//                namedWindow("Erosion Demo", CV_WINDOW_AUTOSIZE);
//                namedWindow("Dilation Demo", CV_WINDOW_AUTOSIZE);
//                cvMoveWindow("Dilation Demo", src.cols, 0);

//                /// Create Erosion Trackbar
//                createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Erosion Demo",
//                    &erosion_elem, max_elem,
//                    Erosion);

//                createTrackbar("Kernel size:\n 2n +1", "Erosion Demo",
//                    &erosion_size, max_kernel_size,
//                    Erosion);

//                /// Create Dilation Trackbar
//                createTrackbar("Element:\n 0: Rect \n 1: Cross \n 2: Ellipse", "Dilation Demo",
//                    &dilation_elem, max_elem,
//                    Dilation);

//                createTrackbar("Kernel size:\n 2n +1", "Dilation Demo",
//                    &dilation_size, max_kernel_size,
//                    Dilation);

//                /// Default start
//                Erosion(0, 0);
//                Dilation(0, 0);

//                waitKey(0);
//                */


//        }

//        return true;
//        return 0;

//    return 0;
}
/**  @function Erosion  */
void Erosion(int, void*)
{
    int erosion_type;
    if (erosion_elem == 0) { erosion_type = MORPH_RECT; }
    else if (erosion_elem == 1) { erosion_type = MORPH_CROSS; }
    else if (erosion_elem == 2) { erosion_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement(erosion_type,
        Size(2 * erosion_size + 1, 2 * erosion_size + 1),
        Point(erosion_size, erosion_size));

    /// Apply the erosion operation
    erode(src, erosion_dst, element);
    imshow("Erosion Demo", erosion_dst);
}

/** @function Dilation */
void Dilation(int, void*)
{
    int dilation_type;
    if (dilation_elem == 0) { dilation_type = MORPH_RECT; }
    else if (dilation_elem == 1) { dilation_type = MORPH_CROSS; }
    else if (dilation_elem == 2) { dilation_type = MORPH_ELLIPSE; }

    Mat element = getStructuringElement(dilation_type,
        Size(2 * dilation_size + 1, 2 * dilation_size + 1),
        Point(dilation_size, dilation_size));
    /// Apply the dilation operation
    dilate(src, dilation_dst, element);
    imshow("Dilation Demo", dilation_dst);
}


