#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <unordered_map>
#include "../include/Particle.hpp"
#include "../include/Particles.hpp"
#include "../include/Field.hpp"
#include "../include/config.hpp"
#include "../include/initParticles.hpp"

Particle p1(sf::Color::Red, sf::Vector2f(2,2));
Particle p2(sf::Color::Red, sf::Vector2f(2,2));

// Particles particles;

sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Life");

int main(){
    Field field(sf::Vector2f(0,0), sf::Vector2f(500,500));
    Particles particles;
    particles.addVector((initParticles(sf::Color::Green, 100, field)));
    particles.addVector((initParticles(sf::Color::Yellow, 10, field)));
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //draw
        window.clear();
        particles.draw();
        window.display();
        //rule("red", "blue", 10);
        //std::cin.get();
        // applyRules();
    }
    return 0;
}
