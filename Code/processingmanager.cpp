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



cv::Mat ProcessingManager::createGroundMap(cv::Mat vDisparity, cv::Mat depthMat, int value)
{
    cv::Mat GroundMap = vDisparity.clone();
    int n = 10;
    int TH1 = 55;//we are interested only in big ares of ground. this value is the minimum required number of pixels per width line to be considered as ground.
    bool flag = 0;
    for (int x = 0; x < vDisparity.cols; x++)//i & j start do not include edges - seeds can't be in edges
    {
        for (int y = vDisparity.rows / 3; y < vDisparity.rows; y++)
        {
            if (vDisparity.at<uchar>(cv::Point(x, y)) - vDisparity.at<uchar>(cv::Point(x, y - n)) >= 30)//there is signicant different between current pixel to the n-th pixel from above
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
                            depthMat.at<uchar>(cv::Point(k, y)) = value;//for saperating between close obstacles (0) to ground (1)
                    }

                }
            }
        }
    }
    return depthMat;
}

cv::Mat ProcessingManager::removeClosePixels(cv::Mat img, int thresh, int newVal)
{
    cv::Mat filtered = img.clone();
    for (int i = 0; i < img.rows; ++i)
    {
        for (int j = 0; j < img.cols; ++j)
        {
            if(img.at<uchar>(i,j) <= thresh)
                filtered.at<uchar>(i,j) = newVal;
        }
    }
    return filtered;
}

cv::Mat ProcessingManager::removeEdges(cv::Mat src)
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
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x - 1, y)))
                //for 8-connectivity
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x + 1, y - 1)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x + 1, y + 1)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x - 1, y + 1)))
                + abs(src.at<uchar>(cv::Point(x, y)) - src.at<uchar>(cv::Point(x - 1, y - 1)));
            if (neighborsSum > TH2)
                EdgesRemoved.at<uchar>(cv::Point(x, y)) = 0;
            neighborsSum = 0;
        }
    }
    return EdgesRemoved;
}

rs::core::point3dF32* ProcessingManager::findConnectedComponents(cv::Mat img, cv::Mat originDepth, cv::Mat &ccm, int* pointsNum)
{

    int j = 0;
    cv::Mat stats, centroids;
    cv::Mat labelImage;
    int labels = cv::connectedComponentsWithStats(img, labelImage, stats, centroids, 8);
    rs::core::point3dF32* depth_points = new rs::core::point3dF32[labels*2];
    cv::cvtColor(img, ccm, CV_GRAY2RGB, 3);
    cv::RNG rng(12345);

    //cv::imshow("o_depth",originDepth);
    //cv::waitKey(1);
    cv::Mat depth;
    //originDepth = originDepth/4;
    originDepth.convertTo(depth,CV_8UC1,0.25);
    //depth = blurImage(depth,11);
    //depth = erodeImage(depth,7);
    //depth = dilateImage(depth,7);
    //depth = m_blurImage(depth,5);
    //cv::imshow("depth",depth/20);
    //cv::waitKey(1);

    for (size_t i = 0; i < labels; i++)
     {
         if (stats.at<int>(i, cv::CC_STAT_AREA) > 1000)
         {
             int x = stats.at<int>(i, cv::CC_STAT_LEFT);
             int y = stats.at<int>(i, cv::CC_STAT_TOP);
             int width = stats.at<int>(i, cv::CC_STAT_WIDTH);
             int height = stats.at<int>(i, cv::CC_STAT_HEIGHT);
             cv::Rect rect(x, y, width, height);
             cv::Scalar color = cv::Scalar(rng.uniform(0, 255), rng.uniform(0, 255), rng.uniform(0, 255));
             cv::rectangle(ccm, rect, color);

             if(!(x==0 && y==0))
             {
                 depth_points[j].x = (float)x;
                 depth_points[j].y = (float)y;
                 if((float)originDepth.at<unsigned short>(cv::Point(x,y))!=0)
                    depth_points[j].z = (float)originDepth.at<unsigned short>(cv::Point(x,y));
                 else if(originDepth.at<unsigned short>(cv::Point(x+width,y+height))!=0)
                    depth_points[j].z = originDepth.at<unsigned short>(cv::Point(x+width,y+height));
                 else
                     depth_points[j].z = 1000;


                 depth_points[j + 1].x = (float)x+width;
                 depth_points[j + 1].y = (float)y+height;
                 if(originDepth.at<unsigned short>(cv::Point(x+width,y+height))!=0)
                    depth_points[j + 1].z = (float)originDepth.at<unsigned short>(cv::Point(x+width,y+height));
                 else if(originDepth.at<unsigned short>(cv::Point(x,y))!=0)
                    depth_points[j].z = originDepth.at<unsigned short>(cv::Point(x,y));
                 else
                    depth_points[j + 1].z=1000;

                 j+=2;//2 edge-points (top-left and bottom-right) of each bounding box
             }
         }
     }
    *pointsNum = j;
    return depth_points;
}

cv::Mat ProcessingManager::erodeImage(cv::Mat src,int k_size,cv::MorphShapes shape)
{
    cv::Mat erode;
    cv::Mat element = cv::getStructuringElement( shape,cv::Size(k_size,k_size));
    cv::erode(src,erode,element);
    return erode;
}
cv::Mat ProcessingManager::dilateImage(cv::Mat src,int k_size,cv::MorphShapes shape)
{
    cv::Mat dilate;
    cv::Mat element = cv::getStructuringElement( shape,cv::Size(k_size,k_size));
    cv::dilate(src,dilate,element);
    return dilate;
}
cv::Mat ProcessingManager::m_blurImage(cv::Mat src,int k_size,int time)
{
    cv::Mat blur;
    cv::medianBlur(src, blur, k_size);
    for(int i = 0; i < time - 1; i++)
        cv::medianBlur(blur, blur, k_size);
    return blur;
}
cv::Mat ProcessingManager::g_blurImage(cv::Mat src,int k_size,int time)
{
    cv::Mat blur;
    cv::GaussianBlur(src, blur, cv::Size(k_size,k_size),1);
    for(int i = 0; i < time - 1; i++)
        cv::GaussianBlur(blur, blur, cv::Size(k_size,k_size),1);
    return blur;
}
