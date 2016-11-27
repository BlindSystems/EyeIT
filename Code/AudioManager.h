  #ifndef AUDIOMANAGER_H
  #define AUDIOMANAGER_H 
  
  #include <cstdlib> 
  #include <iostream>



class AudioManager
{
public:
  
  enum Message{MOVE_RIGHT=0, MOVE_LEFT, STOP};
  
  AudioManager();
  void play(int msg, int frame_num);
  int ml, mr, st;
  int min_delay = 100;
  int max_delay = 200;
};

#endif
  