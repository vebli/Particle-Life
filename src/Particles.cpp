#include "../include/Particles.hpp"
#include <stdexcept>
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
        std::map<std::string, std::vector<Particle>>::iterator it1;
        std::pair<int,int> cellIndex;
        float newPositionX;
        float newPositionY;
        float distance;
        sf::Vector2f trajectory;
        for(auto& positionMap : grid.grid){
            for(Rule& rule : rules){
                auto& cell = positionMap.second;
                cellIndex = positionMap.first;
                for(int i = -1; i < 1; i++){
                    for(int j = -1; j < 1; j++){
                        try{
                            it1 = grid.grid.at({cellIndex.first + i, cellIndex.second + i}).find(rule.color2);
                        }
                        catch(const std::out_of_range& e){
                            continue; 
                        }
                        if(it1 != cell.end()){
                            auto it2 = cell.find(rule.color2);
                            if(it2 != cell.end()){
                                std::vector<Particle>& coloredParticles1 = (*it1).second;
                                std::vector<Particle>& coloredParticles2 = (*it2).second;
                                for(Particle& p1 : coloredParticles1){
                                    for(Particle& p2 : coloredParticles2){
                                        trajectory = sf::Vector2f(p2.getPosition().x - p1.getPosition().x, p2.getPosition().y - p1.getPosition().y);
                                        distance = std::sqrt(std::pow(trajectory.x,2) + std::pow(trajectory.y,2));
                                        trajectory.x = trajectory.x * rule.magnitude / distance;
                                        trajectory.y = trajectory.y * rule.magnitude / distance; 
                                        p2.setPosition(sf::Vector2f(p2.getPosition().x + trajectory.x, p2.getPosition().y + trajectory.y));
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}
