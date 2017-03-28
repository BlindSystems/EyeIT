#include "AudioManager.h"
#include <limits>
#include <sstream>


/*AudioUtils::AudioManager::AudioManager()
{
  mr = ml = st = d  =0; //all flags start from frame zero
  last_play = 0;
}*/




bool AudioUtils::AudioManager::play(std::string msg/*Message msg, int frame_num*/)
{ 
    //=============text to speach option=====================================================//



//        std::string sound_message =  "espeak -v en '"+msg+"'";
//        const char * sound = sound_message.c_str();
//        system(sound);

//        return true;



    //=============recorded audio option========================================================//

    if(msg == "welcome")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/welcome.wav &");
        return true;

    }
    if(msg == "instructions")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/instructions.wav &");
        return true;
    }
    if(msg == "move_left")
    {
      system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/move_left.wav &");
      return true;
    }
    if(msg == "move_right")
    {
      system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/move_right.wav &");
      return true;
    }
    if(msg == "stop")
    {
      system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/stop.wav &");
      return true;
    }


    //======================OR_Objects==========================================================//

//    if(msg == "cabinet")
//    {
//        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/cabinet.wav &");
//        return true;
//    }
    if(msg == "bag")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/bag.wav &");
        return true;
    }
    if(msg == "bed")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/bed.wav &");
        return true;
    }
    if(msg == "bottle")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/buttle.wav &");
        return true;
    }
    if(msg == "chair")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/chair.wav &");
        return true;
    }
    if(msg == "closed_door")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/closed_door.wav &");
        return true;
    }
    if(msg == "cup")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/cup.wav &");
        return true;
    }
    if(msg == "laptop")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/laptop.wav &");
        return true;
    }
    if(msg == "light_switch")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/light_switch.wav &");
        return true;
    }
    if(msg == "open_door")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/open_door.wav &");
        return true;
    }
    if(msg == "picture")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/picture.wav &");
        return true;
    }
//    if(msg == "pillow")
//    {
//        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/pillow.wav &");
//        return true;
//    }
    if(msg == "shoes")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/shoes.wav &");
        return true;
    }
//    if(msg == "sink")
//    {
//        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/sink.wav &");
//        return true;
//    }
    if(msg == "smartphone")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/smartphone.wav &");
        return true;
    }
    if(msg == "sofa")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/sofa.wav &");
        return true;
    }
    if(msg == "table")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/table.wav &");
        return true;
    }
//    if(msg == "window")
//    {
//        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/window.wav &");
//        return true;
//    }
    if(msg == "garbage")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/garbage.wav &");
        return true;
    }
    if(msg == "houseplant")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/house_plant.wav &");
        return true;
    }
    if(msg == "light")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/lamp.wav &");
        return true;
    }

    //========================================================================================//

    if(msg == "on_your_left")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/on_your_left.wav &");
        return true;
    }
    if(msg == "on_your_right")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/on_your_right.wav &");
        return true;
    }
    if(msg == "in_front_of_you")
    {
        system("gst-play-1.0 /home/ntuser-chavy/Desktop/WAV/in_front_of_you.wav &");
        return true;
    }
    return false;

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





