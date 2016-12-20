#pragma once
#ifndef NAVIGATIONUTILS_H
#define NAVIGATIONUTILS_H 

#include "AudioManager.h"

namespace NavigationUtils{
    
    //int frame_to_process_or = 50;
    
    namespace Constants{
    
    const int LAYERS_NUM = 3;
    
    enum Direction{D_RIGHT=0, D_LEFT, STOP, OPEN};
    
    }
    
    class Navigator{
    public:
      
       //Navigator();
       void navigate(int* collisions_map);
       NavigationUtils::Constants::Direction findDirection(int * collisions_map);
       NavigationUtils::Constants::Direction checkLayer(int layer);
       NavigationUtils::Constants::Direction randomDirection();
       
       AudioUtils::AudioManager audioMsg;

       
    };
}

  
#endif // NAVIGATIONUTILS_H