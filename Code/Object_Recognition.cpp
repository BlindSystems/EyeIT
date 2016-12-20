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
	device->enable_stream(rs::stream::color, cfg.image_streams_configs[(int)rs::stream::color].min_size.width,
		                                  cfg.image_streams_configs[(int)rs::stream::color].min_size.height,
		                                  rs::format::bgr8,
		                                  cfg.image_streams_configs[(int)rs::stream::color].minimal_frame_rate);

	device->enable_stream(rs::stream::depth, cfg.image_streams_configs[(int)rs::stream::depth].min_size.width,
		                                  cfg.image_streams_configs[(int)rs::stream::depth].min_size.height,
		                                  rs::format::z16,
		                                  cfg.image_streams_configs[(int)rs::stream::depth].minimal_frame_rate);
	//device->enable_stream(rs::stream::color,rs::preset::best_quality);
	//device->enable_stream(rs::stream::depth,rs::preset::best_quality);

	//handling color image info (for later using)
	rs::core::image_info colorInfo ;
	colorInfo.height = cfg.image_streams_configs[(int)rs::stream::color].min_size.height;
	colorInfo.width = cfg.image_streams_configs[(int)rs::stream::color].min_size.width;
	colorInfo.format = rs::core::pixel_format::bgr8;
	colorInfo.pitch = colorInfo.width * 3;
	
	//handling depth image info (for later using)
	rs::core::image_info depthInfo;
	depthInfo.height = cfg.image_streams_configs[(int)rs::stream::depth].min_size.height;
	depthInfo.width = cfg.image_streams_configs[(int)rs::stream::depth].min_size.width;
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
	
        return st;
  }
  
  rs::core::status ORUtils::ObjectRecognizer::set_rect(int thirdlayer)
  {
    
    rs::core::status st;
      if((thirdlayer & ObstacleUtils::Obstacle::ALL)!=0)
	st = or_configuration->set_roi(rs::core::rectF32{0,0,1,1});//all image
      else if((thirdlayer & ObstacleUtils::Obstacle::CENTER)!=0) //center only
	st = or_configuration->set_roi(rs::core::rectF32{0.25,0,0.2,1});
      else if((thirdlayer & ObstacleUtils::Obstacle::LEFT)!=0)  //Left only
	st = or_configuration->set_roi(rs::core::rectF32{0,0,0.25,1});
      else if((thirdlayer & ObstacleUtils::Obstacle::RIGHT)!=0) //Right only
	st = or_configuration->set_roi(rs::core::rectF32{0.75,0,0.25,1});
      else if((thirdlayer & ObstacleUtils::Obstacle::LEFT_CENTER)!=0)//Left & center
	st = or_configuration->set_roi(rs::core::rectF32{0,0,0.75,1});
      else if((thirdlayer & ObstacleUtils::Obstacle::RIGHT_CENTER)!=0)//Right & center
	st = or_configuration->set_roi(rs::core::rectF32{0.25,0,0.75,1});
      else
	st = or_configuration->set_roi(rs::core::rectF32{0.25,0,0.2,1});//center only
      
      if(st != rs::core::status_no_error)
	return st;
	  
      st = or_configuration->apply_changes();
      return st;  
  }
  
  rs::core::status ORUtils::ObjectRecognizer::process_sample(rs::core::correlated_sample_set& sample_set)
  {
    return impl.process_sample_set_sync(&sample_set);
  }
  
  std::string ORUtils::ObjectRecognizer::get_object_name()
  {
    std::string objects_name = "";
    int array_size;
    if (or_data->query_single_recognition_result(&recognition_data, array_size) != rs::core::status_no_error)
    {
      std::cout<<"error while quering or data"<<std::endl;
      return objects_name;
    }
		   
    if(recognition_data[0].probability>0.8)
    {
      objects_name = or_configuration->query_object_name_by_id(recognition_data[0].label);
      std::cout<<"found an object with high probability : "<<objects_name<<" prob: "<<recognition_data[0].probability<<std::endl;
      return objects_name;
    }
  }
  
    rs::core::status ORUtils::ObjectRecognizer::initDevice()
    {
      //if(!playback)
      //{
	  ctx.reset(new rs::core::context);  
      //}
      //else ctx.reset(new rs::playback::context(playback_file_name));
      
      if (ctx == nullptr)
	  return rs::core::status_process_failed;

      int deviceCount = ctx->get_device_count();
      
      if (deviceCount  == 0)
      {
	  std::cout<<"No RealSense device connected"<<std::endl;
	  return rs::core::status_process_failed;
      }

      //get pointer the the camera
      device = ctx->get_device(0);
      
      /**********************************create and configure device********************************/
      //*ctx.reset(new rs::playback::context("/home/maker/Desktop/project/rssdk.rssdk"));
    // if (ctx->get_device_count() == 0)
      //{
	// printf("Error : cant find devices\n");
	  //exit(EXIT_FAILURE);
      //}

      //device = ctx->get_device(0); //device memory managed by the context 

      //enable color and depth streams
  }
  void ORUtils::ObjectRecognizer::startCamera()
  {
      //device->enable_stream(rs::stream::color,rs::preset::best_quality);
      //device->enable_stream(rs::stream::fisheye,rs::preset::best_quality);
      //device->enable_stream(rs::stream::depth,rs::preset::best_quality);
      //device->start();
  }
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
     
