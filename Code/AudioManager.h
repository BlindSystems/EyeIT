  #ifndef AUDIOMANAGER_H
  #define AUDIOMANAGER_H 
  
  #include <cstdlib> 
  #include <iostream>


namespace AudioUtils
{
  
  enum Message{MOVE_RIGHT=0, MOVE_LEFT, STOP};
  //void play(int msg, int frame_num);    
  
  class AudioManager
  {
    public:
      
      //AudioManager();
      void play(int msg, int frame_num);
      int findSmallestInterval();
      int ml, mr, st, d  = 0;
      int last_play = 0;
      int min_delay = 100;
      int max_delay = 150;
    
  };
}

#endif
  