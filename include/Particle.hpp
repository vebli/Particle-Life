#ifndef PARTICLE 
#define PARTICLE
#include "config.hpp"
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

extern sf::RenderWindow window;

class Particle{
private:
    sf::CircleShape sprite;

public:
    Particle();
    Particle(sf::Color Color, sf::Vector2f StartingPosition);
    sf::Color getColor() const;
    void setColor(sf::Color color);
    sf::Vector2f getPosition() const; 
    void setPosition(sf::Vector2f Position);
    void draw() const;
};

#endif //PARTICLE
