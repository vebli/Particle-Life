#include "../include/Particles.hpp"
#include <SFML/System/Vector2.hpp>
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

sf::Vector2f Particles::wrap(sf::Vector2f pos, sf::Vector2f trajectory){
    const sf::Vector2f posOOB(sf::Vector2f(pos.x + trajectory.x, pos.y + trajectory.y));
    if(posOOB.x > 0 && posOOB.x < window.getSize().x && posOOB.y > 0 && posOOB.y < window.getSize().y){
        return posOOB; 
    }
    float sy_left= -pos.x / trajectory.x;
    float sx_up = -pos.y / trajectory.y;
    float sy_right = (window.getSize().x -pos.x) / trajectory.x;
    float sx_down = (window.getSize().y -pos.y) / trajectory.y;

    sf::Vector2f newPos;
    sf::Vector2f borderPos;

    if(sx_up >= 0){
        if(sx_up < sy_left){
            borderPos = sf::Vector2f(pos.x + trajectory.x * sx_up, pos.y + trajectory.y * sx_up); 
        }
        else{
            borderPos = sf::Vector2f(pos.x + trajectory.x * sy_left, pos.y + trajectory.y * sy_left);
        }
    }
    else{
        if(sx_down < sy_right){
            borderPos = sf::Vector2f(pos.x + trajectory.x * sx_down, pos.y + trajectory.y * sx_down);
        }
        else{
            borderPos = sf::Vector2f(pos.x + trajectory.x * sy_right, pos.y + trajectory.y * sy_right);
        }
    }
    newPos = sf::Vector2f(
            -(borderPos.x - window.getSize().x / 2.f) + window.getSize().x / 2.f, 
            -(borderPos.y - window.getSize().y / 2.f) + window.getSize().y / 2.f 
            ); 
    return newPos;
}
float Particles::force(float distance, float attraction){
    sf::Vector2f acceleration;
    if(distance < particleEquilibrium){
        return distance/particleEquilibrium - 1;
    }
    else if(particleEquilibrium < distance && distance < 1){
        return attraction * (1 - (std::abs(2.85 * distance - 1 - 2.85 * particleEquilibrium))/(1-particleEquilibrium));
    }
    else{
        return 0;
    }
}
void Particles::update(){
    if(rulesApply){
        float newPositionX;
        float newPositionY;
        float distance;
        std::map<std::string, std::vector<Particle>>::iterator it1;
        std::pair<int,int> cellIndex;
        sf::Vector2f direction;
        sf::Vector2f acceleration;
        for(auto& positionMap : grid.grid){
            for(Rule& rule : rules){
                auto& cell = positionMap.second;
                cellIndex = positionMap.first;
                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        try{
                            it1 = grid.grid.at({cellIndex.first + i, cellIndex.second + i}).find(rule.color1);
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
                                        if(&p1 == &p2){continue;}
                                        distance = std::sqrt(
                                                std::pow(p2.getPosition().x - p1.getPosition().x,2) + 
                                                std::pow(p2.getPosition().y - p1.getPosition().y,2)
                                                );

                                        if(distance <= thresholdRadius){
                                            direction.x = (distance != 0) ? (p1.getPosition().x- p2.getPosition().x) / distance :
                                                -1;
                                            direction.y = (distance != 0) ? (p1.getPosition().y- p2.getPosition().y) / distance :
                                                -1;
                                            acceleration.x = direction.x * thresholdRadius * force(distance/thresholdRadius, rule.magnitude);
                                            acceleration.y = direction.y * thresholdRadius *force(distance/thresholdRadius, rule.magnitude);
                                            p2.addVelocity(sf::Vector2f(acceleration.x * delta_t, acceleration.y * delta_t));
                                            // std::cout << "distance: " << distance << std::endl;
                                            // std::cout  << "force: " << force(distance, rule.magnitude) << std::endl;
                                            // std::cout << "direction: " << direction.x << "," << direction.y << std::endl;
                                            // std::cout << "acceleration: " << acceleration.x << "," << acceleration.y << std::endl;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        for(auto& mapPair : grid.grid){
            for(auto& mapPair2 : mapPair.second){
                for(auto& particle : mapPair2.second){
                   particle.update(); 
                   std::cout << particle.getColor() << ": " << particle.getVelocity().x << "," << particle.getVelocity().y << std::endl;
                }
            } 
        }
    }
}
