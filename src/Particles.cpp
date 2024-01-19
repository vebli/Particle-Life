#include "../include/Particles.hpp"
Particles::Particles(){
    rulesApply = false;
}

void Particles::addVector(const std::vector<Particle> &particleVector){
    for(const auto& particle : particleVector){
        grid.insert(particle);
    }
}
void Particles::addRule(Rule rule){
    rules.push_back(rule);
}

void Particles::draw(){
    for(auto& colorMap : grid.grid){
        for(auto& particleVector: colorMap.second){ 
            for(Particle& particle : particleVector.second){
                particle.draw();
            }
        }
    }
}
void Particles::applyRules(){
    rulesApply = true;
}
void Particles::update(){
    if(rulesApply){
        for(auto& positionMap : grid.grid){
            for(Rule& rule : rules){
                auto& cell = positionMap.second;
                auto it = cell.find(rule.color1);
                if(it != cell.end()){  // found particles with color of rule 1 inside cell
                    auto it2 = cell.find(rule.color2); 
                    if(it2 != cell.end()){ // found particles with color 2 inside same cell
                    // check distance -> apply physics 
                    }
                }
            }
        }
    }
}
