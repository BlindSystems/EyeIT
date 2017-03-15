#include "processingmanager.h"

ProcessingManager::ProcessingManager()
{

}

cv::Mat ProcessingManager::createVDisparity(cv::Mat image, int depth_width)
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
    vDisparity.convertTo(vDisparity, CV_8UC3);
    return vDisparity;
}



cv::Mat ProcessingManager::createGroundMap(cv::Mat vDisparity, cv::Mat depthMat)
{
    cv::Mat GroundMap = vDisparity.clone();
    int n = 10;
    int TH1 = 35;
    bool flag = 0;
    for (int x = 0; x < vDisparity.cols; x++)//i & j start do not include edges - seeds can't be in edges
    {
        for (int y = vDisparity.rows / 2; y < vDisparity.rows; y++)
        {
            if (vDisparity.at<uchar>(cv::Point(x, y)) - vDisparity.at<uchar>(cv::Point(x, y - n)) >= 50)
            {
                flag = 1;
                for (int i = 0; i < n; i++)
                {
                    if (vDisparity.at<uchar>(cv::Point(x, y - i)) - vDisparity.at<uchar>(cv::Point(x, y - i - 1)) < -20)
                        flag = 0;
                }
                if (flag == 1 && (vDisparity.at<uchar>(cv::Point(x, y)) > TH1))
                {
                    GroundMap.at<uchar>(cv::Point(x, y)) = 0; //This is ground
                    for (int k = 0; k < depthMat.cols + 0; k++)
                    {
                        if (abs(depthMat.at<uchar>(cv::Point(k, y)) - x) < 10)
                            depthMat.at<uchar>(cv::Point(k, y)) = 0;//for saperating between close obstacles (0) to ground (1)
                    }

                }
            }
        }
    }
    return depthMat;
}
