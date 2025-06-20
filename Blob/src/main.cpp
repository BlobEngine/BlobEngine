#include "SFML/Graphics.hpp"

int main() {
    // Window dimensions
    const int screenWidth = 800;
    const int screenHeight = 600;

    // Create the main window
    sf::RenderWindow window(sf::VideoMode({screenWidth, screenHeight }), "SFML Boilerplate");
    window.setFramerateLimit(60);

    // Main loop
    while (window.isOpen()) 
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        // Clear the screen
        window.clear(sf::Color::Black);


        window.display();
    }

    return 0;
}
