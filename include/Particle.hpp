#ifndef PARTICLE 
#define PARTICLE
#include "config.hpp"
#include "colorToStr.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <limits>
#include <iostream>

extern sf::RenderWindow window;

class Particle{
private:
    sf::CircleShape sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    std::string color;

public:
    Particle();
    Particle(sf::Color Color, sf::Vector2f StartingPosition);
    std::string getColor() const;
    void setColor(sf::Color color);
    sf::Vector2f getPosition() const; 
    void setPosition(sf::Vector2f Position);
    void draw() const;
    void addVelocity(sf::Vector2f velocity);
    void update();
    sf::Vector2f getVelocity();
};

#endif //PARTICLE
