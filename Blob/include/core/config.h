#pragma once
#include <iostream>

struct GameWindow {
  std::string WINDOW_TITLE = "Blob Engine";
  unsigned int WINDOW_HEIGHT = 800;
  unsigned int WINDOW_WIDTH = 800;
  bool VERTICAL_SYNC = true;
  float FRAME_RATE = 60;
  int ANTI_ALIASING = 8;
};
