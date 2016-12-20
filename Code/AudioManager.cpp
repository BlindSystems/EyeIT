#include "AudioManager.h"
#include <limits>


/*AudioUtils::AudioManager::AudioManager()
{
  mr = ml = st = d  =0; //all flags start from frame zero
  last_play = 0;
}*/

void AudioUtils::AudioManager::play(int msg, int frame_num)
{ 
   std::cout<<" in play func"<<std::endl;
  
  if(msg == MOVE_LEFT)
  {
    
    //if( ((frame_num - ml) > max_delay) /*|| (abs(mr - ml) > min_delay) || (abs(st - ml) > min_delay)*/ || ml==0)
    //if(AudioManager::findSmallestInterval() > min_delay || ml == 0)
    {
      system("gst-play-1.0 move_left.wav &");
      ml = frame_num;
      return;
    } 
  }
  
  if(msg == MOVE_RIGHT)
  {
    std::cout<<" in play for: right"<<std::endl;
    //if( ((frame_num - mr) > max_delay) /*|| (abs(ml - mr) > min_delay) || (abs(st - mr) > min_delay)*/ || mr == 0)
    //if(AudioManager::findSmallestInterval() > min_delay || mr == 0)
    {
      system("gst-play-1.0 move_right.wav &");
      mr = frame_num;
      return;
    } 
  }
  if(msg == STOP)
  {
    //if( ((frame_num - st) > max_delay) /*|| (abs(ml - st) > min_delay) || (abs(mr - st) > min_delay)*/ || st == 0)
    //if(AudioManager::findSmallestInterval() > min_delay || st == 0)
    {
      std::cout<<" in play for: stop"<<std::endl;
      system("gst-play-1.0 stop.wav &");
      st = frame_num;
      return;
    } 
  }
  last_play = frame_num;
}

int AudioUtils::AudioManager::findSmallestInterval()
{
  int diff = std::numeric_limits< int >::max();
  if(abs(mr-ml)<diff)
    diff = abs(mr-ml);
  if(abs(mr-st)<diff)
    diff = abs(mr-st);
  if(abs(st-ml)<diff)
    diff = abs(st-ml);
  return diff;
}
