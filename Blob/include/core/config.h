#pragma once
#include <iostream>

// Configuration for the main game window.
struct GameWindow {

	std::string WINDOW_TITLE = "Blob Engine"; 	// Title of the window displayed in the title bar
	unsigned int WINDOW_HEIGHT = 800;			// Height of the window in pixels
	unsigned int WINDOW_WIDTH = 800; 			// Width of the window in pixels
	bool VERTICAL_SYNC = true; 					// Enable or disable vertical sync (prevents screen tearing)
	float FRAME_RATE = 60;						// Maximum frame rate limit (in frames per second)
	int ANTI_ALIASING = 8; 						// Level of anti-aliasing for smoother edges (higher = better quality, slower performance)
};

// Configuration Random value ranges.
struct RandomValue {

	float MIN_POSITION = 100.0f;				// Minimum distance from edge of screen for positioning
	float MAX_VELOCITY = 200.0f;				// Maximum velocity for random movement generation
	float MIN_VELOCITY = 100.0f;				// Minimum velocity for random movement generation
};

// Configuration for physical properties.
namespace physics
{
	struct DefaultValue {
		int MASS = 5;							// Mass of the point, affects physics
		float GRAVITY_X = 0.0f;					// Constant downward force (X axis)
		float GRAVITY_Y = 100.0f;				// Constant downward force (Y axis)
		float RADIUS = 20.0f;					// Radius used for drawing and collisions
		float RESTITUTION = 0.95f;				// Bounciness (1 = fully elastic)
		float DAMPING = 10.0f;					// Slows down the motion over time
		int MAXPOINTS = 100;					// Maximum number of points allowed
	};

}


