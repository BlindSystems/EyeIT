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

      void init();
      void createMsgVec();
      void play(std::string message/*Message msg, int frame_num = 0*/);
      void  voiceORObject(std::string object_name);
      int findSmallestInterval();
      int ml, mr, st, d  = 0;
      int last_play = 0;
      int min_delay = 100;
      int max_delay = 150;

      bool is_OR_playing = false;

      std::map<Message, std::string> m_messages;
    
  };
}

#endif
  
