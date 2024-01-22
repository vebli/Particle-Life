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

Particle p1(sf::Color::White, sf::Vector2f(2,2));
Particle p2(sf::Color::Red, sf::Vector2f(2,2));

std::vector<Particle> visualgrid;

// Particles particles;

sf::RenderWindow window(sf::VideoMode(800, 600), "Particle Life");

int main(){
    for(int i = 0; i < window.getSize().x; i+= thresholdRadius){
        for(int j = 0; j < window.getSize().y; j += thresholdRadius){
            p1.setPosition(sf::Vector2f(i,j));
            visualgrid.push_back(p1);
        }
    }
    Field field(sf::Vector2f(thresholdRadius*2, thresholdRadius*2), sf::Vector2f(thresholdRadius*3,thresholdRadius*3));
    Particles particles;
    particles.addVector((initParticles(sf::Color::Green, 1, field)));
    particles.addVector((initParticles(sf::Color::Yellow, 1, field)));
    particles.addRule(Rule(colorToStr(sf::Color::Yellow), colorToStr(sf::Color::Green), 0.3));
    // particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Yellow), -0.6));
    // particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Yellow), 10));
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        //draw
        particles.update();
        window.clear();
        for(Particle& particle : visualgrid){
            particle.draw();
        }
        particles.draw();
        window.display();
        std::cin.get();
        particles.applyRules();
        //rule("red", "blue", 10);
        //std::cin.get();
        // applyRules();
        window.setFramerateLimit(30);
    }
    return 0;
}
