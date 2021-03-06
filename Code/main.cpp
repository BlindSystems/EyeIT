//needed includes
#include <sys/types.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <iostream>
#include <unistd.h>
#include <thread>
#include <cstdlib>

//opencv
#include "opencv2/imgproc/types_c.h"

//realsense
#include "rs_sdk.h"
#include "rs/core/projection_interface.h"
#include "rs/core/release_interface.h"
#include <librealsense/rs.hpp>

//our classes
#include "ObstacleManager.h"
#include "Object_Recognition.h"
#include "AudioManager.h"
#include "NavigationUtils.h"
#include "camera_utils.h"
#include "displaymanager.h"
#include "processingmanager.h"

//====MRAA includes
//#include "mraa.hpp"
#include <signal.h>
#include <csignal>  //Library from the C/++ standard libraries to allow for clean exits.

#define PROCESS_RATE 20



//mraa::Gpio *gpio;

    const char COLOR_WINDOW_NAME[] = "Collision Avoidance";
    const char DEPTH_WINDOW_NAME[] = "Depth View";
    const char EDGES_WINDOW_NAME[] = "edges";
    const char CCM_WINDOW_NAME[] = "ccm";
    const char PROCESSED_DEPTH_WINDOW_NAME[] = "processed View";
  

  //enum PinNumbers{C=16, R=18,L=20};



  /****create cv mat with RGB format from image_interface********/

  cv::Mat Image2Mat(camera_utils cu, rs::core::pixel_format format);
  void processOR(rs::core::correlated_sample_set* sample_set,cv::Mat depthMat_original, cv::Mat colorMat);

  //================OR Variables===============

  bool orInitilized=false;
  //===========================================

   
  ORUtils::ObjectRecognizer objRecognizer;
  ObstacleUtils::ObstacleDetector obsDetector;
  NavigationUtils::Navigator navigator;
  DisplayManager display;
  ProcessingManager ImageProcessor;
  AudioUtils::AudioManager audio;
  camera_utils cu;
  rs::core::status st;

  bool play = true;
  bool playback = true;
  char * playback_file_name;
  //int m_frame_number = 0;

  void my_handler(int s)
  {
      if (play)
      {
	  play = false;
      }
      else
      {
	  exit(1);
      }
  }
  
  int main(int argc, char** argv)
  {

      audio.play("welcome");
      cv::waitKey(1000);
     // audio.play("instructions");
      cv::waitKey(500);


      /***********************************configure GUI*********************************************/
      cv::namedWindow(COLOR_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(COLOR_WINDOW_NAME, 960, 540);
      cv::moveWindow(COLOR_WINDOW_NAME,100,50);
      cv::namedWindow(DEPTH_WINDOW_NAME, CV_WINDOW_NORMAL);
      cv::resizeWindow(DEPTH_WINDOW_NAME, 640, 360);
      cv::moveWindow(DEPTH_WINDOW_NAME,1100,50);

//      cv::namedWindow(PROCESSED_DEPTH_WINDOW_NAME, CV_WINDOW_NORMAL);
//      cv::resizeWindow(PROCESSED_DEPTH_WINDOW_NAME, 640, 360);
//      cv::moveWindow(PROCESSED_DEPTH_WINDOW_NAME,1400,200);
      //cv::startWindowThread();
      /**********************************************************************************************/


      /**********************handle ctrl-c - for proper closing of the camera***********************/
      struct sigaction sigIntHandler;
      sigIntHandler.sa_handler = my_handler;
      sigemptyset(&sigIntHandler.sa_mask);
      sigIntHandler.sa_flags = 0;
      sigaction(SIGINT, &sigIntHandler, NULL);
      /***********************************initialize device*****************************************/


      rs::core::correlated_sample_set* sample_set;
      int* col = NULL;
      cv::Mat m_blur, renderImage, depthMat, vDisparity , depthMat_original,colored_depth;
      std::string navigation_msg;
      char keyPressed =  0;

      std::thread t1;



      if (argc < 2)//on live mode
      {
          std::cerr<<"Mode is: Live" << std::endl;
          playback = false;
          cu.setMode( camera_utils::LIVE_STREAM);
      }
      else//on playback mode
      {
          if(access(argv[1], F_OK) == -1)
          {
              std::cerr << "playback file does not exist" << std::endl;
              return -1;
          }

          std::cerr<<"Mode is: Playback" << std::endl;
          playback_file_name = argv[1];
          cu.setMode( camera_utils::PLAYBACK);
          cu.setFileName(playback_file_name);
	
      }

      //create a playback enabled context with a given output file
      //rs::playback::context context(playback_file_name.c_str());

      //init the camera
      st = cu.init_camera(objRecognizer.impl,&objRecognizer.or_data,&objRecognizer.or_configuration);
      if (st!= rs::core::status_no_error)
      {
          std::cout<<"Camera initialization Failed"<<std::endl;
          return st;
      }

      display.createRects(cu.getColorInfo().width, cu.getColorInfo().height, cu.getDepthInfo().width, cu.getDepthInfo().height);


      //objRecognizer.print_objects();

      /***********************************start streaming*******************************************/

      objRecognizer.print_objects();

      while(play && (cu.getDevice())->is_streaming())//while user did not exit and device is streaming data
      {	  



          cu.getDevice()->wait_for_frames();
          sample_set = cu.get_sample_set();//get a sample from device

          cu.copy_color_to_cvmat(renderImage);//copy RGB image to cv mat
          cu.copy_depth_to_cvmat(depthMat_original);//copy depth image to cv mat
          //renderImage = Image2Mat(cu, cu.m_colorInfo.format);
          //depthMat_original = Image2Mat(cu, cu.m_depthInfo.format);


          if(!depthMat_original.empty())//if depth has data
          {
            depthMat_original.convertTo(depthMat,CV_8UC1,0.056);//convert  depth values - to receive RGB rang values
            keyPressed = (char)cv::waitKey(1);
            switch (keyPressed)
            {
                case 'o':  //OR option chosen
                    processOR(sample_set,depthMat_original,renderImage);
                    //t1 = std::thread(processOR, sample_set);
                    //t1.detach();
                    break;
                case 'q':   //Quit option chosen
                    play = false;
                    break;
                default:
                    if(( cu.getFrameNum() -1 )%PROCESS_RATE == 0)//check if reached rate time to process image for collision detection
                    {


                        m_blur = ImageProcessor.m_blurImage(depthMat,3,10);//blur - to avoid missing data
                        //m_blur = ImageProcessor.erodeImage(m_blur,9);
                        //m_blur = ImageProcessor.dilateImage(m_blur,9);
                        vDisparity = ImageProcessor.createVDisparity(m_blur, cu.getDepthInfo().width);//create v-disparity for ground removal
                        m_blur = ImageProcessor.createGroundMap(vDisparity, m_blur);//remove the ground from the image
                        col = obsDetector.get_all_collisions(m_blur);//search for collitions from all layers
                        navigation_msg = navigator.navigate(col);//navigate the user accurding to the collisions that were found on the different layers

                    }
                    //if ( cu.getFrameNum()%50 == 0)//time to process OR
                    //{
                        //objRecognizer.create_roi(cu.m_colorInfo.width/4,cu.m_colorInfo.height/4,cu.m_colorInfo.width/2,cu.m_colorInfo.height/2);
                        //t1 = std::thread(processOR, sample_set);
                        //t1.detach();
                    //}

                        colored_depth = cv::Mat(depthMat.rows,depthMat.cols,CV_8UC3);
                        cv::cvtColor(depthMat,colored_depth,CV_GRAY2RGB,3);

                        colored_depth = display.DisplayCollisions(colored_depth,col,navigation_msg,true);
                        renderImage = display.DisplayCollisions(renderImage,col,navigation_msg,false);

                        cv::imshow(DEPTH_WINDOW_NAME,colored_depth);// m_blur);
                        //cv::imshow(PROCESSED_DEPTH_WINDOW_NAME, vDisparity);//m_blur);
                        cv::imshow(COLOR_WINDOW_NAME, renderImage);

                        break;

          }
        }
      }

      cu.getDevice()->stop();
      //delete gpio;
      std::cout<<"exiting\n";
  }


//=============================================OR thread============================================================//
void processOR(rs::core::correlated_sample_set* sample_set,cv::Mat depthMat_original, cv::Mat colorMat)
{

    cv::Mat ccm, depth;
    rs::core::pointF32* color_points;
    int num = objRecognizer.prepareImage2OR(depthMat_original, colorMat, ccm, depth,&color_points, display, cu);

//    cv::namedWindow(CCM_WINDOW_NAME, CV_WINDOW_NORMAL);
//    cv::resizeWindow(CCM_WINDOW_NAME, 960, 540);
//    cv::moveWindow(CCM_WINDOW_NAME,100,100);

//    cv::namedWindow(DEPTH_WINDOW_NAME, CV_WINDOW_NORMAL);
//    cv::resizeWindow(DEPTH_WINDOW_NAME, 640, 360);
//    cv::moveWindow(DEPTH_WINDOW_NAME,1100,100);

//    cv::imshow(CCM_WINDOW_NAME, depth);
//    cv::imshow(DEPTH_WINDOW_NAME, ccm);
//    cv::waitKey(1000);

    for (int i = 0; i < num; i+=2) {
        int x = color_points[i].x;
        int y = color_points[i].y;
        int n_x = color_points[i+1].x;
        int n_y = color_points[i+1].y;
        int width = color_points[i + 1].x - color_points[i].x;
        int height = color_points[i + 1].y - color_points[i].y;

        objRecognizer.create_roi(x,y,width,height);
        //objRecognizer.create_roi(0,0,cu.getColorInfo().width,cu.getColorInfo().height);
        if(objRecognizer.find_objects(*sample_set))
            cv::waitKey(700);


    }
    cv::waitKey(1000);
    cu.release_images();//TODO: check
//    cv::destroyWindow(CCM_WINDOW_NAME);

}



//============================================= Image2Mat ===========================================================//

  cv::Mat Image2Mat(camera_utils cu, rs::core::pixel_format format)
  {
      cv::Mat cvMat;

      if(format == rs::core::pixel_format::rgb8)//color
      {
            cvMat.create(cu.getColorInfo().height, cu.getColorInfo().width, CV_8UC3);
            memcpy(cvMat.data,cu.getColorBuffer(), cvMat.elemSize() * cvMat.total());
            cv::cvtColor(cvMat,cvMat,CV_RGB2BGR);
      }

      else//depth
      {
            cvMat.create(cu.getDepthInfo().height, cu.getDepthInfo().width, CV_16UC1);
            memcpy(cvMat.data,cu.getDepthBuffer(), cvMat.elemSize() * cvMat.total());
      }
      return  cvMat;
  }

//================================= help functions ====================================================//

//  int8_t get_pixel_size(rs::format format)
//  {
//      switch(format)
//      {
//      case rs::format::any:
//	  return 0;
//      case rs::format::z16:
//	  return 2;
//      case rs::format::disparity16:
//	  return 2;
//      case rs::format::xyz32f:
//	  return 4;
//      case rs::format::yuyv:
//	  return 2;
//      case rs::format::rgb8:
//	  return 3;
//      case rs::format::bgr8:
//	  return 3;
//      case rs::format::rgba8:
//	  return 4;
//      case rs::format::bgra8:
//	  return 4;
//      case rs::format::y8:
//	  return 1;
//      case rs::format::y16:
//	  return 2;
//      case rs::format::raw8:
//	  return 1;
//      case rs::format::raw10:
//	  return 0;//not supported
//      case rs::format::raw16:
//	  return 2;
//      }
//  }



  //================================= vibration functions ====================================================//

  //This function is called a "signal handler." It allows a signal like "SIGINT" to exit the program cleanly.
  //In this case, the SIGINT will be generated by the OS when you press Ctrl+C on your keyboard.
  //void signal_handler(int sig) {
      /*
      delete gpio;
      std::cout << "Exiting." << std::endl;
      exit(0);
      */
  //}

  //void rotate(int pinNum, int length, bool flag){

  //signal(SIGINT, signal_handler); //This sets the event handler to the SIGINT signal. This is the signal generated by Ctrl+c.

      //std::cout << "Hello from Intel on Joule!" <<std::endl;	//Remember, c++ isn't whitespace-sensitive, so you can use "carriage returns" (split lines) in the middle of function calls.
      //<< "Press Ctrl+c to exit..." << std::endl;				//This is very useful when the function call will be long and otherwise unwieldy.
      //std::cout<<pinNum<<std::endl;

      /*
      gpio = new mraa::Gpio(pinNum);	//Instantiate the GPIO object so that we can access the pin. (Pin 100)

  //12 - center,14 - left,16 -right
      if (gpio) { //If the instantiation was successful...
          gpio->dir(mraa::DIR_OUT); //Set the pin as an output.

          //while (true) { //Begin an infinite loop. This will exit on pressing Ctrl+c, due to the event handler.
              gpio->write(flag); //gpio->write(n) writes the value "n" to the gpio object. If the value is 1, the output turns off, if it's 0 it turns on. This may seem counterintuitive, but it's called active-low.
              //sleep(1000/length);		//sleep(n) is exactly what it says on the tin. It makes the program (or thread) sleep for n seconds.
              //gpio->write(0);
              //sleep(1);
          //}
      }
      */
  //}

//  bool startedC=false,startedL=false,startedR=false;

//  void rotateDir(int collision)
//  {

//    std::cout<<"in rotate"<<std::endl;
//    std::cout<< "layer 0: "<<collision<<std::endl;

//    if((collision & ObstacleUtils::Obstacle::CENTER)!=0)
//    {
//      std::cout<<"Obstacle in Center"<<std::endl;//obstacle in center
//      if(!startedC)
//	{
//	  startedC=true;
//          rotate(PinNumbers::C, 1,startedC);
//	}
//    }
//    else					//center is free
//    {
//	startedC=false;
//	rotate(PinNumbers::C, 1,startedC);
//    }

//    if((collision & ObstacleUtils::Obstacle::LEFT)!=0)
//    {
//      std::cout<<"Obstacle in Left"<<std::endl;//obstacle in left
//      if(!startedL)
//      {
//	startedL=true;
//	rotate(PinNumbers::L, 1,startedL);
//      }
//    }
//    else
//    {
//      startedL=false;
//      rotate(PinNumbers::L, 1,startedL);
//    }

//    if((collision & ObstacleUtils::Obstacle::RIGHT)!=0)
//    {
//      std::cout<<"Obstacle in Right"<<std::endl;//obstacle in right
//      if(!startedR)
//      {
//	startedR=true;
//	rotate(PinNumbers::L, 1,startedR);
//      }
//    }
//    else
//    {
//      startedR=false;
//      rotate(PinNumbers::L, 1,startedR);
//    }
//  }
		    
