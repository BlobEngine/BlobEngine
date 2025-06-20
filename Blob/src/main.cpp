#include "../include/core/gameobjects/point.h"
//#include "../include/core/config.h"

int main()
{
   // GameWindow gameWindow;
    sf::ContextSettings settings;
    settings.antiAliasingLevel = 8;

    const int screenWidth = 800;
    const int screenHeight = 800;

    sf::RenderWindow window(sf::VideoMode({ screenWidth, screenHeight }), "Blob Engine");
    window.setFramerateLimit(60);

    Physics physics;
    int pointQuantity = 2;

    for (int i = 0; i < pointQuantity; ++i) {
        Points p;
        p.mass = 5;
        p.position = sf::Vector2f(100 + i * 40, 100);
        p.velocity = sf::Vector2f(20.0f, 40.0f);
        physics.points.push_back(p);
    }

    sf::Clock clock;

    // Main loop
    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        float dt = clock.restart().asSeconds();
        physics.Update(dt);

        window.clear(sf::Color::Black);

        for (const auto& p : physics.points) {
            sf::CircleShape shape(10.0f);
            shape.setFillColor(sf::Color::Green);
            shape.setPosition(p.position);
            window.draw(shape);
        }

        window.display();
    }

    return 0;
}
