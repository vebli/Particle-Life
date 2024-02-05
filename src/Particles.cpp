#include "Particles.hpp"
#include "config.hpp"
Particles::Particles(){
    rulesApply = true;
    for(int i = 0; i < defaultColors.size(); i++){
        for(int j = 0; j < colorDimensions; j++){
            previousColors[i][j] = defaultColors[i][j];
        }
    }
    for(int i = 0; i < previousAmounts.size(); i++){
        previousAmounts[i] = defaultAmountOfColoredParticles[i]; 
    }
}

void Particles::addVector(const std::vector<Particle>& particleVector){
    for(const auto& particle : particleVector){
        grid.insert(particle);
    }
}
void Particles::removeVector(float* color){
    manipulateParticlesOfSameColor(color, [](std::vector<Particle>& particles){
            particles.clear();
        });
}

void Particles::manipulateParticlesOfSameColor(float* color, std::function<void(std::vector<Particle>&)> lambda){
     for (int x = 0; x < grid.grid.size(); x++){
        for(int y = 0; y < grid.grid[x].size(); y++){
            const auto& it = grid.grid[x][y].find(color);
            if(it != grid.grid[x][y].end()){    
                lambda((*it).second);
            }
        }
    }
}

void Particles::updateColors(){
   for(int i = 0; i < defaultColors.size(); i++){
        for(int j = 0; j < colorDimensions; j++){
            if(defaultColors[i][j] != previousColors[i][j]){
                manipulateParticlesOfSameColor(defaultColors[i], [](std::vector<Particle>& particles){
                    for(auto& particle : particles){
                        particle.updateColor(); 
                    }
                });
                for(int k = j; k < colorDimensions; k++){
                    previousColors[i][k] = defaultColors[i][k];
                }
                break;
            }
        }
   }
}
void Particles::updateAmount(){
    for(int i = 0; i < defaultColors.size(); i++){
        if(previousAmounts[i] != defaultAmountOfColoredParticles[i]){
            float* color = defaultColors[i];
            int sum = 0;
            manipulateParticlesOfSameColor(color, [&sum](std::vector<Particle>& particles){
                sum += particles.size();
            });
            int difference = sum - defaultAmountOfColoredParticles[i];
            bool addedParticles = difference < 0;
            bool removedParticles = difference > 0;
            if(addedParticles){
                std::vector<Particle> newParticles = initParticles(color, std::abs(difference), Field());
                for(auto& particle : newParticles){
                    grid.insert(particle);
                }
            }
            else if(removedParticles){
                std::random_device rd;
                std::mt19937 gen(rd());
                std::uniform_real_distribution<float> distributionX(0, sfWindow.getSize().x/cellSize); 
                std::uniform_real_distribution<float> distributionY(0, sfWindow.getSize().y/cellSize);
                for(int j = 0; j < difference; j++){
                    int x = static_cast<int>(distributionX(gen));
                    int y = static_cast<int>(distributionY(gen));
                    while(grid.grid[x][y][color].empty()){
                        x = static_cast<int>(distributionX(gen));
                        y = static_cast<int>(distributionY(gen));
                    }
                    grid.grid[x][y][color].pop_back();
                }
            }
            previousAmounts[i] = defaultAmountOfColoredParticles[i];
        }
    }
}

void Particles::addRule(Rule rule){
    bool foundRule = false;
    for(int i = 0; i < rules.size(); i ++){
        if(rule.color1 == rules[i].color1 && rule.color2 == rules[i].color2){
            if(rule.magnitude == 0){
                rules.erase(rules.begin() + i);
            }
            else if(rule.magnitude != rules[i].magnitude){
                rules[i].magnitude = rule.magnitude;
            }
            foundRule = true;
            break;
        }
    }
    if(!foundRule && rule.magnitude != 0){
        rules.push_back(rule);
    }
}
int Particles::findRuleIndex(float* color1, float* color2){
    for(int i = 0; i < rules.size(); i++){
        if(rules[i].color1 == color1 && rules[i].color2 == color2){
            return -1;
        }
    }
    return -1;
}

void Particles::draw(){
    for(auto& row : grid.grid){
        for(auto& column: row){
            for(auto& pairColorParticles : column){
                for(auto& particle : pairColorParticles.second){
                    particle.draw();
                }
            }
        }
    }
}

float Particles::force(float distance, float attraction){
    sf::Vector2f acceleration;
    if(distance < particleEquilibrium){
        return distance/particleEquilibrium - 1;
    }
    else if(distance > particleEquilibrium && distance < 1){
        return attraction * (1 - (std::abs(2 * distance - 1 - particleEquilibrium))/(1-particleEquilibrium));
    }
    else{
        return 0;
    }
}
void Particles::updatePosition(){
    float distance;
    std::unordered_map<std::string, std::vector<Particle>>::iterator itColor1VecPair;
    std::unordered_map<std::string, std::vector<Particle>>::iterator itColor2VecPair;
    sf::Vector2f direction;
    sf::Vector2f acceleration;
    for(int cellX = 0; cellX < grid.grid.size(); cellX++){
        for(int cellY = 0; cellY < grid.grid[cellX].size(); cellY++){
            for(auto& rule : rules){
                auto& map_colorParticles = grid.grid[cellX][cellY];
                const auto& it_pairColor1Particles = map_colorParticles.find(rule.color1);
                if(it_pairColor1Particles == map_colorParticles.end()){continue;}
                for(int x = -1; x <= 1; x++){
                    for(int y = -1; y <= 1; y++){
                        int cellX_offset = cellX + x;
                        int cellY_offset = cellY + y;
                        if(cellX_offset < 0 || cellY_offset < 0 || cellX_offset > grid.grid.size() || cellY_offset > grid.grid[cellX].size()){
                            continue;
                        }
                        const auto& it_pairColor2Particles = grid.grid[cellX_offset][cellY_offset].find(rule.color2);
                        if(it_pairColor2Particles == grid.grid[cellX_offset][cellY_offset].end()){
                            continue; 
                        }
                        auto& particlesOfColor1 = (*it_pairColor1Particles).second;
                        auto& particlesOfColor2 = (*it_pairColor2Particles).second;
                        for(auto& p1 : particlesOfColor1){
                            for(auto& p2 : particlesOfColor2){
                                if(&p1 == &p2){
                                    continue;
                                }
                                distance = std::sqrt(
                                        std::pow(p2.getPosition().x - p1.getPosition().x,2) + 
                                        std::pow(p2.getPosition().y - p1.getPosition().y,2)
                                        );

                                if(distance <= thresholdRadius){
                                    direction.x = (distance != 0) ? (p1.getPosition().x - p2.getPosition().x) / distance :
                                        0;
                                    direction.y = (distance != 0) ? (p1.getPosition().y - p2.getPosition().y) / distance :
                                        0;
                                    acceleration.x = direction.x * thresholdRadius * force(distance/thresholdRadius, rule.magnitude);
                                    acceleration.y = direction.y * thresholdRadius * force(distance/thresholdRadius, rule.magnitude);
                                    p2.addVelocity(sf::Vector2f(acceleration.x * delta_t, acceleration.y * delta_t));
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    for(int cellX = 0; cellX < grid.grid.size(); cellX++){
        for(int cellY = 0; cellY < grid.grid[cellX].size(); cellY++){
            for(auto& map_colorParticles : grid.grid[cellX][cellY]){
                auto& particles = map_colorParticles.second;
                for(int i = 0; i < particles.size(); i++){
                    Particle& particle = particles[i];
                    if(
                            static_cast<int>(particle.getPosition().x) == cellX &&
                            static_cast<int>(particle.getPosition().y) == cellY
                      ){
                        particle.updatePosition(); 
                        continue;
                    }
                    particle.updatePosition(); 
                    grid.insert(particle);
                    particles.erase(particles.begin() + i);
                }
            }
        } 
    }
}

void Particles::update(){
    updateColors();
    updateAmount();
    if(rulesApply){
        updatePosition();
    }
    // if(!rules.empty())
    //     std::cout<< "rules:\t" << rules.size() << std::endl; 
    // else{
    //     std::cout << "rules:\t" << "empty" << std::endl;
    // }
    // int sum = 0;
    // for(int x = 0; x < grid.grid.size(); x++){
    //     for(int y = 0; y < grid.grid[x].size(); y++){
    //         for(auto& color : grid.grid[x][y]){
    //             sum += color.second.size();
    //         }
    //     }
    // }
    // std::cout << "particles:\t" << sum << std::endl;
    // std::cout << std::endl;
}
