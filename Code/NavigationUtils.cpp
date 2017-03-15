#include "NavigationUtils.h"
#include "AudioManager.h"
#include "ObstacleManager.h"
#include <iostream>
#include <stdlib.h>

  /*NavigationUtils::Navigator::Navigator()
  {
    //audioMsg = AudioUtils::AudioManager::AudioManager();
  }*/
  
  //this is the main function to navigate the user, using rotate sensors and audio messages
  std::string NavigationUtils::Navigator::navigate(int* collisions_map)
  {
    std::cout<<"in navigate"<<std::endl;
    std::cout<< "layer 0: "<<collisions_map[0]<<std::endl;
    std::cout<< "layer 1: "<<collisions_map[1]<<std::endl;
    std::cout<< "layer 2: "<<collisions_map[2]<<std::endl;
    
    //rotateDir(collisions_map[0]);
    
    NavigationUtils::Constants::Direction dir = findDirection(collisions_map); //find the direction to where the user need to turn by examining 3 layers of the image
    
    if(dir == NavigationUtils::Constants::Direction::STOP)
    {
      //audioMsg.play("stop");
      return "STOP !!!";
    }
    if(dir == NavigationUtils::Constants::Direction::D_LEFT)
    {
      //audioMsg.play("move left");
      return "MOVE LEFT";
    }
    if(dir == NavigationUtils::Constants::Direction::D_RIGHT)
    {
      //audioMsg.play("move right");
      return "MOVE RIGHT";
    }
    else
        return "OPEN";

  }
  
  NavigationUtils::Constants::Direction NavigationUtils::Navigator::findDirection(int * collisions_map)
  {    
    if(collisions_map[0] == ObstacleUtils::Obstacle::ALL) //left,center and right are all blocked by obstacles
      return NavigationUtils::Constants::Direction::STOP;
    
    if((collisions_map[0] & ObstacleUtils::Obstacle::CENTER) == 0) //center is open
      return NavigationUtils::Constants::Direction::OPEN;//there is no obstacle in the center of first layer - no findDirection needed 
    
    for(int i = 0; i < NavigationUtils::Constants::LAYERS_NUM; i++)
    {
      if(checkLayer(collisions_map[i]) == NavigationUtils::Constants::Direction::D_RIGHT)
	return NavigationUtils::Constants::Direction::D_RIGHT;
      if(checkLayer(collisions_map[i]) == NavigationUtils::Constants::Direction::D_LEFT)
	return NavigationUtils::Constants::Direction::D_LEFT;
    }
    
    return randomDirection(); //all layers were checked and no blocked direction was found. couldn't get a decision since both left and right are open in all layers. choose direction randomaly
  }

  NavigationUtils::Constants::Direction NavigationUtils::Navigator::checkLayer(int layer)
  {
    //if((layerCollisionMap & Obstacle::RIGHT)!=0 && (layerCollisionMap & Obstacle::LEFT)==0)
    if((layer == ObstacleUtils::Obstacle::RIGHT) || (layer == ObstacleUtils::Obstacle::RIGHT_CENTER))//'right' is blocked and left is open
      return NavigationUtils::Constants::Direction::D_LEFT;//go to 'left' direction
    
    //if((layerCollisionMap & Obstacle::LEFT)!=0 && (layerCollisionMap & Obstacle::RIGHT)==0)
    if((layer == ObstacleUtils::Obstacle::LEFT) || (layer == ObstacleUtils::Obstacle::LEFT_CENTER))//'left' is blocked and right is open
      return NavigationUtils::Constants::Direction::D_RIGHT;//go to 'right' direction
  
    if(layer == ObstacleUtils::Obstacle::LEFT_RIGHT)  //both left and right are blocked will choose right/left randomaly. (arbitrary decision: turn right?)
    {
      //std::cout<<"in checkLayer, both right and left are blocked. random num is: "<< randomNum <<std::endl;
      return randomDirection();
    }
    return NavigationUtils::Constants::Direction::OPEN;//both 'right' and 'left' are free
  }
  
  NavigationUtils::Constants::Direction NavigationUtils::Navigator::randomDirection()
  {
    int randomNum = rand()%2;
    
    if(randomNum==0)
	return NavigationUtils::Constants::Direction::D_RIGHT;
      return NavigationUtils::Constants::Direction::D_LEFT;
  }
  
