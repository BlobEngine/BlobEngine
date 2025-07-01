#pragma once
#include <iostream>

struct GameWindow {

    std::string WINDOW_TITLE = "Blob Engine";     
    unsigned int WINDOW_WIDTH = 1400;            
    unsigned int WINDOW_HEIGHT = 800;            
    bool VERTICAL_SYNC = true;                   
    float FRAME_RATE = 60;                       
    int ANTI_ALIASING = 8;                        
};

struct RandomValue {

    float MIN_POSITION = 100.0f;                 
    float MAX_VELOCITY = 20.0f;                   
    float MIN_VELOCITY = 5.0f;                    
};
