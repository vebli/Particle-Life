#ifndef FIELD 
#define FIELD

#include "Particle.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <random>
#include <iostream>

extern sf::RenderWindow window;

class Field{
    private:
    sf::Vector2f p1;
    sf::Vector2f p2;

    public:
    Field(sf::Vector2f P1, sf::Vector2f P2): p1(P1), p2(P2){}

    void spawnRandom(std::vector<Particle> &particles);
};
#endif
