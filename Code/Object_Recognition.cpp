#include "Object_Recognition.h"

  
  rs::core::status ORUtils::ObjectRecognizer::initOR()
  {

        //create or implementaion
	//rs::object_recognition::or_video_module_impl impl;

	//request the first (index 0) supproted module config.
	rs::core::status st;
        rs::core::video_module_interface::supported_module_config cfg;
    st =impl.query_supported_module_config(0, cfg);
	if (st != rs::core::status_no_error)
		return st;

	//enables streams according to the supported configuration
    device->enable_stream(rs::stream::color, cfg.image_streams_configs[(int)rs::stream::color].size.width,
                                          cfg.image_streams_configs[(int)rs::stream::color].size.height,
		                                  rs::format::bgr8,
                                          cfg.image_streams_configs[(int)rs::stream::color].frame_rate);

    device->enable_stream(rs::stream::depth, cfg.image_streams_configs[(int)rs::stream::depth].size.width,
                                          cfg.image_streams_configs[(int)rs::stream::depth].size.height,
		                                  rs::format::z16,
                                          cfg.image_streams_configs[(int)rs::stream::depth].frame_rate);
	//device->enable_stream(rs::stream::color,rs::preset::best_quality);
	//device->enable_stream(rs::stream::depth,rs::preset::best_quality);

	//handling color image info (for later using)
	rs::core::image_info colorInfo ;
    colorInfo.height = cfg.image_streams_configs[(int)rs::stream::color].size.height;
    colorInfo.width = cfg.image_streams_configs[(int)rs::stream::color].size.width;
	colorInfo.format = rs::core::pixel_format::bgr8;
	colorInfo.pitch = colorInfo.width * 3;
	
	//handling depth image info (for later using)
	rs::core::image_info depthInfo;
    depthInfo.height = cfg.image_streams_configs[(int)rs::stream::depth].size.height;
    depthInfo.width = cfg.image_streams_configs[(int)rs::stream::depth].size.width;
	depthInfo.format = rs::core::pixel_format::z16;
	depthInfo.pitch = depthInfo.width * 2;

	
	device->start();


	// get the extrisics paramters from the camera
	rs::extrinsics ext  = device->get_extrinsics(rs::stream::depth, rs::stream::color);

	//get color intrinsics
	rs::intrinsics colorInt = device->get_stream_intrinsics(rs::stream::color);

	//get depth intrinsics
	rs::intrinsics depthInt = device->get_stream_intrinsics(rs::stream::depth);

	// after getting all parameters from the camera we need to set the actual_module_config 
	rs::core::video_module_interface::actual_module_config actualConfig;

		//1. copy the extrinsics 
		memcpy(&actualConfig.image_streams_configs[(int)rs::stream::color].extrinsics, &ext, sizeof(rs::extrinsics));

		//2. copy the color intrinsics 
		memcpy(&actualConfig.image_streams_configs[(int)rs::stream::color].intrinsics, &colorInt, sizeof(rs::intrinsics));

		//3. copy the depth intrinsics 
		memcpy(&actualConfig.image_streams_configs[(int)rs::stream::depth].intrinsics, &depthInt, sizeof(rs::intrinsics));

	// handling projection
    //rs::core::projection_interface* proj = rs::core::projection_interface::create_instance(&colorInt, &depthInt, &ext);
    //impl.set_projection(proj);

	//setting the selected configuration (after projection)



	st=impl.set_module_config(actualConfig);
	if (st != rs::core::status_no_error)
		return st;
        or_data = impl.create_output();
        or_configuration = impl.create_active_configuration();
        or_configuration->set_compute_engine(rs::object_recognition::compute_engine::GPU);
	
        return st;
  }

  rs::core::status ORUtils::ObjectRecognizer::set_rect()
  {
      rs::core::status s1, s2;
      s1 = or_configuration->set_roi(roi);
      s2 = or_configuration->apply_changes();
      if(s1 != rs::core::status_no_error || s2 != rs::core::status_no_error)
          return rs::core::status_data_not_changed;
      return rs::core::status_no_error;

  }

  void ORUtils::ObjectRecognizer::create_roi(int x, int y, int width, int height)
  {
      roi.x = x;
      roi.y = y;
      roi.width = width;
      roi.height = height;
  }

  bool ORUtils::ObjectRecognizer::find_objects(rs::core::correlated_sample_set& sample_set)
  {
      if(set_rect() != rs::core::status_no_error)
      {
          std::cout<<"Failed to set rect" << std::endl;
          return false;
      }
      if(impl.process_sample_set(sample_set) != rs::core::status_no_error)
      {
          std::cout<<"Failed to process sample" << std::endl;
          return false;
      }
      if(or_data->query_single_recognition_result(&recognition_data,array_size) != rs::core::status_no_error)
      {
          std::cout<<"Failed to query result" << std::endl;
          return false;
      }
      if(or_configuration->query_object_name_by_id(recognition_data[0].probability>0.8))
      {
         if(audio.play(or_configuration->query_object_name_by_id(recognition_data[0].label)))
         {
             cv::waitKey(800);
             int image_width = cu.getColorInfo().width;
             if((float)(roi.x + roi.width) < (float)(image_width)*(0.4))
             {
                 audio.play("on_your_left");
                 //return true;
             }
             else if((float)roi.x > (float)(image_width)*(0.6))
             {
                 audio.play("on_your_right");
                //return true;
             }
             else
                 audio.play("in_front_of_you");
         }
         return true;
      }
      return false;
  }


  void ORUtils::ObjectRecognizer::print_objects()
  {
      for(int i = 0; i<or_configuration->query_number_of_classes() ; i++)
          std::cout<<or_configuration->query_object_name_by_id(i)<<std::endl;
  }

  int ORUtils::ObjectRecognizer::prepareImage2OR(cv::Mat depthMat_original, cv::Mat colorMat, cv::Mat &depth_ccm, cv::Mat &color_ccm,rs::core::pointF32** color_points, DisplayManager display, camera_utils cu)
  {
      this->cu = cu;
      cv::Mat depthMat;
      //cv::Mat copy = depthMat_original.clone();
      //copy.convertTo(depthMat,CV_8UC1,0.056);
      depthMat_original.convertTo(depthMat,CV_8UC1,0.056);

      cv::Mat m_blur = ImageProcessor.m_blurImage(depthMat,3,10);
      //cv::imshow("m_blur",m_blur);
      //cv::waitKey(1);

      //cv::Mat vd = ImageProcessor.createVDisparity(m_blur,cu.getDepthInfo().width);
      //cv::Mat img = ImageProcessor.createGroundMap(vd,m_blur,255);
      //cv::imshow("img",img);
      //cv::waitKey(1);

      cv::Mat removed = ImageProcessor.removeClosePixels(m_blur,50); //remove too-close pixels (no depth data - holes)
      //cv::imshow("removed",removed);
      //cv::waitKey(1);

      cv::Mat erode = ImageProcessor.erodeImage(removed,9);       //smooth image
      //cv::imshow("erode",erode);
      //cv::waitKey(1);

      cv::Mat dilate = ImageProcessor.dilateImage(erode,9);       //smooth image
      //cv::imshow("dilate",dilate);
      //cv::waitKey(1);

      cv::Mat thr;                                                //remove far objects
      int th_v = 170;
      cv::threshold(dilate, thr, th_v, 255, cv::THRESH_TRUNC /*|| cv::THRESH_OTSU*/);
      thr = thr * 1.5;
      //cv::imshow("threshold",thr);
      //cv::waitKey(1);

      cv::Mat edges = ImageProcessor.removeEdges(thr);            //remove edges
      //cv::imshow("edges",edges);
      //cv::waitKey(1);

      cv::Mat blur_edges = ImageProcessor.m_blurImage(edges,3,3); //smooth image

      //cv::imshow("blur_edges",blur_edges);
      //cv::waitKey(1);

      //cv::Mat thr_otsu;
      //cv::threshold(edges, thr_otsu, th_v, 255, cv::THRESH_TRUNC || cv::THRESH_OTSU);
      //cv::imshow("thr_otsu",thr_otsu);
      //cv::waitKey(1);

      rs::core::point3dF32 *depth_points;
      int points_n;
      //cv::Mat ccm;
      depth_points = ImageProcessor.findConnectedComponents(blur_edges, depthMat_original, depth_ccm, &points_n);

      //depth_ccm = ccm.clone();


      *color_points = cu.projectPoints2ColorImage(depth_points,points_n);
      //cv::imshow("ccm",ccm);
      //cv::waitKey(1);

      color_ccm = colorMat.clone();
      display.drawRects(color_ccm,*color_points,points_n);
      //cv::namedWindow("color_ccm", CV_WINDOW_NORMAL);
      //cv::resizeWindow("color_ccm",640,360);
      //cv::imshow("color_ccm",color_ccm);
      //cv::waitKey(1);
      return points_n;
  }
//  rs::core::status ORUtils::ObjectRecognizer::set_rect(int thirdlayer)
//  {
    
//    rs::core::status st;
//    /*
//      if((thirdlayer & ObstacleUtils::Obstacle::ALL)!=0)
//    st = or_configuration->set_roi(rs::core::rect{0,0,1,1});//all image
//      else if((thirdlayer & ObstacleUtils::Obstacle::CENTER)!=0) //center only
//    st = or_configuration->set_roi(rs::core::rect{0.25,0,0.2,1});
//      else if((thirdlayer & ObstacleUtils::Obstacle::LEFT)!=0)  //Left only
//    st = or_configuration->set_roi(rs::core::rect{0,0,0.25,1});
//      else if((thirdlayer & ObstacleUtils::Obstacle::RIGHT)!=0) //Right only
//    st = or_configuration->set_roi(rs::core::rect{0.75,0,0.25,1});
//      else if((thirdlayer & ObstacleUtils::Obstacle::LEFT_CENTER)!=0)//Left & center
//    st = or_configuration->set_roi(rs::core::rect{0,0,0.75,1});
//      else if((thirdlayer & ObstacleUtils::Obstacle::RIGHT_CENTER)!=0)//Right & center
//    st = or_configuration->set_roi(rs::core::rect{0.25,0,0.75,1});
//      else
//	st = or_configuration->set_roi(rs::core::rectF32{0.25,0,0.2,1});//center only
      
//      if(st != rs::core::status_no_error)
//	return st;
	  
//      st = or_configuration->apply_changes();
//      */
//      return st;
//  }
  
//  rs::core::status ORUtils::ObjectRecognizer::process_sample(rs::core::correlated_sample_set& sample_set)
//  {
//    //return impl.process_sample_set_sync(&sample_set);
//    //return impl.process_sample_set(&sample_set);
//    rs::core::status st;
//    return st;
//  }
  
//  std::string ORUtils::ObjectRecognizer::get_object_name()
//  {
//    std::string objects_name = "";
//    int array_size;
//    if (or_data->query_single_recognition_result(&recognition_data, array_size) != rs::core::status_no_error)
//    {
//      std::cout<<"error while quering or data"<<std::endl;
//      return objects_name;
//    }
		   
//    if(recognition_data[0].probability>0.8)
//    {
//      objects_name = or_configuration->query_object_name_by_id(recognition_data[0].label);
//      std::cout<<"found an object with high probability : "<<objects_name<<" prob: "<<recognition_data[0].probability<<std::endl;
//      return objects_name;
//    }
//  }
  
//    rs::core::status ORUtils::ObjectRecognizer::initDevice()
//    {
//      //if(!playback)
//      //{
//	  ctx.reset(new rs::core::context);
//      //}
//      //else ctx.reset(new rs::playback::context(playback_file_name));
      
//      if (ctx == nullptr)
//	  return rs::core::status_process_failed;

//      int deviceCount = ctx->get_device_count();
      
//      if (deviceCount  == 0)
//      {
//	  std::cout<<"No RealSense device connected"<<std::endl;
//	  return rs::core::status_process_failed;
//      }

//      //get pointer the the camera
//      device = ctx->get_device(0);
      
//      /**********************************create and configure device********************************/
//      //*ctx.reset(new rs::playback::context("/home/maker/Desktop/project/rssdk.rssdk"));
//    // if (ctx->get_device_count() == 0)
//      //{
//	// printf("Error : cant find devices\n");
//	  //exit(EXIT_FAILURE);
//      //}

//      //device = ctx->get_device(0); //device memory managed by the context

//      //enable color and depth streams
//  }
//  void ORUtils::ObjectRecognizer::startCamera()
//  {
//      //device->enable_stream(rs::stream::color,rs::preset::best_quality);
//      //device->enable_stream(rs::stream::fisheye,rs::preset::best_quality);
//      //device->enable_stream(rs::stream::depth,rs::preset::best_quality);
//      //device->start();
//  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
     
