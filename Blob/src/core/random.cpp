#include <random>
#include "../../include/core/random.h"
#include "../../include/core/config.h"

// Randomize position inside window
sf::Vector2f shape::Random::setPosition(const sf::RenderWindow& window) {
    RandomValue randomValue;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, window.getSize().x - randomValue.MIN_POSITION);
    std::uniform_real_distribution<float> distY(0.f, window.getSize().y - randomValue.MIN_POSITION);
    return sf::Vector2f{ distX(gen), distY(gen) };
}

// Randomize velocity
sf::Vector2f shape::Random::setVelocity() {
    RandomValue randomValue;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distX(0.f, randomValue.MAX_VELOCITY - randomValue.MIN_VELOCITY);
    std::uniform_real_distribution<float> distY(0.f, randomValue.MAX_VELOCITY - randomValue.MIN_VELOCITY);
    return sf::Vector2f{ distX(gen), distY(gen) };
}

// Randomize color
sf::Color shape::Random::setColor() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, 255);
    return sf::Color(dist(gen), dist(gen), dist(gen));
}