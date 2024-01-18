#include "../include/initParticles.hpp"

std::vector<Particle> initParticles(const sf::Color color,const int amount, Field field){
    std::vector<Particle> particles;
    particles.reserve(amount);
    for(int i = 0; i < amount; i++){
        Particle particle(color, sf::Vector2f(0,0));
        particles.push_back(particle);
    }
    field.spawnRandom(particles);
    return particles;
}


