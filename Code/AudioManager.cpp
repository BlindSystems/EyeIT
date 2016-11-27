#include "AudioManager.h"


AudioManager::AudioManager()
{
  mr = ml = st =0; //all flags start from frame zero
}
void AudioManager::play(int msg, int frame_num)
{ 
   std::cout<<" in play func"<<std::endl;
  
  if(msg == Message::MOVE_LEFT)
  {
    std::cout<<" in play for play: left"<<std::endl;
    if(((frame_num - ml) > max_delay) || ((mr - ml) > min_delay) || ((st - ml) > min_delay) || ml == 0)
    {
      system("gst-play-1.0 move_left.wav &");
      ml = frame_num;
    } 
  }
  else if(msg == Message::MOVE_RIGHT)
  {
    std::cout<<" in play for play: right"<<std::endl;
    if(((frame_num - mr) > max_delay) || ((ml - mr) > min_delay) || ((st - mr) > min_delay) || mr == 0)
    {
      system("gst-play-1.0 move_right.wav &");
      mr = frame_num;
    } 
  }
  else if(msg == Message::STOP)
  {
    if(((frame_num - st) > max_delay) || ((ml - st) > min_delay) || ((mr - st) > min_delay) || st == 0)
    {
    std::cout<<" in play for play: stop"<<std::endl;
      system("gst-play-1.0 stop.wav &");
      st = frame_num;
    } 
  }
   
}