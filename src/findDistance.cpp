#include "../include/findDistance.hpp"

const float findDistance(Particle p1, Particle p2){
    sf::Vector2f p1Vec = p1.getPosition();
    sf::Vector2f p2Vec = p2.getPosition();
    float distanceX = p2Vec.x - p1Vec.x;
    float distanceY = p2Vec.y - p1Vec.y;
    float distance = std::sqrt(std::pow(distanceX, 2) + std::pow(distanceY,2));
    return distance; 
}
