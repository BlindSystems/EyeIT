#include "AudioManager.h"
#include <limits>
#include <sstream>


/*AudioUtils::AudioManager::AudioManager()
{
  mr = ml = st = d  =0; //all flags start from frame zero
  last_play = 0;
}*/
void AudioUtils::AudioManager::init()
{

}



void AudioUtils::AudioManager::play(std::string msg/*Message msg, int frame_num*/)
{ 
    //=============text to speach option=====================================================//

    if(!is_OR_playing)
    {
        std::string sound_message =  "espeak -v en '"+msg+"'";
        const char * sound = sound_message.c_str();
        system(sound);
    }
    else is_OR_playing = false;






    //=============recorded audio option========================================================//

//    if(!is_OR_playing)
//    {
  
//  if(msg == "move left")
//  {
    
//    //if( ((frame_num - ml) > max_delay) /*|| (abs(mr - ml) > min_delay) || (abs(st - ml) > min_delay)*/ || ml==0)
//    //if(AudioManager::findSmallestInterval() > min_delay || ml == 0)
//    {
//      system("gst-play-1.0 move_left.wav &");
//      //ml = frame_num;
//      return;
//    }
//  }
  
//  if(msg == "move_right")
//  {
//    std::cout<<" in play for: right"<<std::endl;
//    //if( ((frame_num - mr) > max_delay) /*|| (abs(ml - mr) > min_delay) || (abs(st - mr) > min_delay)*/ || mr == 0)
//    //if(AudioManager::findSmallestInterval() > min_delay || mr == 0)
//    {
//      system("gst-play-1.0 move_right.wav &");
//      //mr = frame_num;
//      return;
//    }
//  }
//  if(msg == "stop")
//  {
//    //if( ((frame_num - st) > max_delay) /*|| (abs(ml - st) > min_delay) || (abs(mr - st) > min_delay)*/ || st == 0)
//    //if(AudioManager::findSmallestInterval() > min_delay || st == 0)
//    {
//      std::cout<<" in play for: stop"<<std::endl;
//      system("gst-play-1.0 stop.wav &");
//      //st = frame_num;
//      return;
//    }
//  }
//  if(msg == "welcome")
//  {
//      system("gst-play-1.0 welcome.wav &");

//  }
//    }
//    else is_OR_playing = false;
  //last_play = frame_num;
}

/*oid  voiceORObject(std::string object_name)
{
  if (object_name=="bag")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
    system("gst-play-1.0 bag.wav &");
  }
  if (object_name=="bed")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 bed.wav &");
  }
  if (object_name=="cabinet")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 cabinet.wav &");
  }
  if (object_name=="cat")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 cat.wav &");
  }
  if (object_name=="dog")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 dog.wav &");
  }
  if (object_name=="chair")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 chair.wav &");
  }
  if(abs(mr-st)<diff)
  if (object_name=="open_door")
  {
    std::cout<<"There is a "<<object_name<<std::endl;//should be in voice
     system("gst-play-1.0 opened_door.wav &");
  }
}*/




//   std::cout<<" in play func"<<std::endl;
//   std::istringstream command;
//   command >> "gst-play-1.0 " >> m_messages[msg] >> ".wav &";
//   system (command);




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
