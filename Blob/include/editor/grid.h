#pragma once
#include "../../include/core/config.h"
#include <SFML/Graphics.hpp>

struct Grid
{
    GameWindow gameWindow;

    const int cellSize = 30;
    const int cols = gameWindow.WINDOW_WIDTH / cellSize + 1;
    const int rows = gameWindow.WINDOW_HEIGHT / cellSize + 1;

    void Initialize(sf::RenderWindow& window);
};