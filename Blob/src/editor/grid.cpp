#include "../../include/editor/grid.h"

void Grid::Initialize(sf::RenderWindow& window) {

    sf::Color lightGray = sf::Color(80, 80, 80);

    for (int y = 0; y <= rows + 1; ++y) {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(0.f, y * cellSize);
        line[1].position = sf::Vector2f(cols * cellSize, y * cellSize);

        line[0].color = lightGray;
        line[1].color = lightGray;

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }

    for (int x = 0; x <= cols; ++x) {
        sf::Vertex line[2];
        line[0].position = sf::Vector2f(x * cellSize, 0.f);
        line[1].position = sf::Vector2f(x * cellSize, rows * cellSize);

        line[0].color = lightGray;
        line[1].color = lightGray;

        window.draw(line, 2, sf::PrimitiveType::Lines);
    }
}