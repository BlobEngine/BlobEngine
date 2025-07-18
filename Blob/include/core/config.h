#pragma once
#include <iostream>

// Configuration for the main game window.
struct GameWindow {

	std::string WINDOW_TITLE = "Blob Engine"; 	// Title of the window displayed in the title bar
	unsigned int WINDOW_WIDTH = 1400; 			// Width of the window in pixels
	unsigned int WINDOW_HEIGHT = 800;			// Height of the window in pixels
	bool VERTICAL_SYNC = true; 					// Enable or disable vertical sync (prevents screen tearing)
	float FRAME_RATE = 60;						// Maximum frame rate limit (in frames per second)
	int ANTI_ALIASING = 8; 						// Level of anti-aliasing for smoother edges (higher = better quality, slower performance)
};

// Configuration Random value ranges.
struct RandomValue {

	float MIN_POSITION = 100.0f;				// Minimum distance from edge of screen for positioning
	float MAX_VELOCITY = 20.0f;					// Maximum velocity for random movement generation
	float MIN_VELOCITY = 5.0f;					// Minimum velocity for random movement generation
};



