#include "../include/Particles.hpp"
Particles::Particles(){rulesApply = false;};
void Particles::addVector(const std::vector<Particle> &particleVector){
    if(!particleVector.empty()){
        sf::Color color = particleVector[0].getColor(); 
        std::string colorKey = std::to_string(color.r) + "-" + std::to_string(color.g) + "-" + std::to_string(color.b); 
        std::cout << colorKey << std::endl;
        particles[colorKey] = particleVector;
    }
    else{
        std::cout << "Particles::addVector: vector is empty" << std::endl;
    }
}
void Particles::addRule(Rule rule){
    rules.push_back(rule);
}

void Particles::draw(){
    for(const auto &particleVector : particles){
        for(const Particle &particle: particleVector.second){
            particle.draw();
        }
    }
}
void Particles::applyRules(){
    rulesApply = true;
}
void Particles::update(){
    if(rulesApply){

    }
}
