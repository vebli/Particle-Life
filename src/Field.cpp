#include "Field.hpp"

void Field::spawnRandom(std::vector<Particle> &Particles){
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> distributionX(p1.x,p2.x); 
    std::uniform_real_distribution<float> distributionY(p1.y, p2.y);
    for(Particle &particle : Particles){
        int newX = distributionX(gen);
        int newY = distributionY(gen);
        particle.setPosition(sf::Vector2f(newX, newY));
    }
}
