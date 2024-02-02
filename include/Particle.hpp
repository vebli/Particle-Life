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

class Particle{
public:
    Particle();
    ~Particle();
    Particle(float* Color, sf::Vector2f StartingPosition);
    float* getColor() const;
    void updateColor();
    sf::Vector2f getPosition() const; 
    void setPosition(sf::Vector2f Position);
    void draw() const;
    void addVelocity(sf::Vector2f velocity);
    void update();
    sf::Vector2f getVelocity();

private:
    sf::CircleShape sprite;
    sf::Vector2f position;
    sf::Vector2f velocity;
    float* color;

};

#endif //PARTICLE
