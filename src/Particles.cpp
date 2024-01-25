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
        std::map<std::string, std::vector<Particle>>::iterator itColor2VecPair;
        std::map<std::string, std::vector<Particle>>::iterator itColor1VecPair;
        std::pair<int,int> cellIndex;
        sf::Vector2f direction;
        sf::Vector2f acceleration;
        int comparisons = 0;
        for(auto& positionMapPair : grid.grid){
            auto& colorParticlesPair = positionMapPair.second;
            cellIndex = positionMapPair.first;
            for(Rule& rule : rules){
                itColor1VecPair = colorParticlesPair.find(rule.color1);
                if(itColor1VecPair == colorParticlesPair.end()){continue;}

                for(int i = -1; i <= 1; i++){
                    for(int j = -1; j <= 1; j++){
                        try{
                            itColor2VecPair = grid.grid.at({cellIndex.first + j, cellIndex.second + i}).find(rule.color2);
                        }
                        catch(const std::out_of_range& e){
                            continue; 
                        }
                        if(itColor2VecPair == grid.grid.at({cellIndex.first + j, cellIndex.second + i}).end()){continue;}

                        std::vector<Particle>& coloredParticles1 = (*itColor1VecPair).second;
                        std::vector<Particle>& coloredParticles2 = (*itColor2VecPair).second;
                        for(Particle& p1 : coloredParticles1){
                            for(Particle& p2 : coloredParticles2){
                                if(&p1 == &p2){continue;}
                                comparisons++;
                                // std::cout << grid.grid.size() << std::endl;
                                // std::cout << coloredParticles1.size() << std::endl;
                                // std::cout << coloredParticles2.size() << std::endl;
                                distance = std::sqrt(
                                        std::pow(p2.getPosition().x - p1.getPosition().x,2) + 
                                        std::pow(p2.getPosition().y - p1.getPosition().y,2)
                                        );

                                if(distance <= thresholdRadius){
                                    direction.x = (distance != 0) ? (p1.getPosition().x- p2.getPosition().x) / distance :
                                        0;
                                    direction.y = (distance != 0) ? (p1.getPosition().y- p2.getPosition().y) / distance :
                                        0;
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
        // std::cout << "comparison " << comparisons << std::endl;
        // size_t size = 0;
        for(auto& positionMapPair: grid.grid){
            for(auto& colorParticlesPair : positionMapPair.second){
                auto& particles = colorParticlesPair.second;
                for(int i = 0; i < particles.size(); i++){
                    // size++;
                    Particle& particle = particles[i];
                    if(
                            static_cast<int>(particle.getPosition().x) == positionMapPair.first.first &&
                            static_cast<int>(particle.getPosition().y) == positionMapPair.first.second
                      ){
                        continue;
                    }
                    particle.update(); 
                    grid.insert(particle);
                    particles.erase(particles.begin() + i);
                }
            } 
        }
        // std::cout << "size:\t "<< size << std::endl;
    }
}
