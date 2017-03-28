  #ifndef AUDIOMANAGER_H
  #define AUDIOMANAGER_H 
  
  #include <cstdlib> 
  #include <iostream>
  #include <map>
  #include <utility>


namespace AudioUtils
{
  //TODO:: add all object messages accoeding to or list
  enum Message{
      WELCOME = 0,
      MOVE_RIGHT,
      MOVE_LEFT,
      STOP
  };
  //void play(int msg, int frame_num);    
  
  class AudioManager
  {
    public:
      bool play(std::string message/*Message msg, int frame_num = 0*/);

    
  };
}

#endif
  
