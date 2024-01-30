#include "../include/Particle.hpp"
#include <limits>
Particle::Particle(){
    sprite.setRadius(particleRadius);
};
Particle::Particle(const sf::Color Color, const sf::Vector2f StartingPosition){
    sprite.setFillColor(Color);
    sprite.setRadius(particleRadius);
    sprite.setPosition(StartingPosition);
    position = StartingPosition;
    velocity = sf::Vector2f(0,0);  
    color = colorToStr(Color);
}

void Particle::setPosition(sf::Vector2f Position){
    sprite.setPosition(Position);
    position = Position;
}
sf::Vector2f Particle::getPosition() const{
    return position;
}
void Particle::draw () const{
    gameWindow.draw(sprite);
}

void Particle::setColor(sf::Color Color){
    sprite.setFillColor(Color);
    color = colorToStr(Color);
}

std::string Particle::getColor() const{
    return color;
}

void Particle::addVelocity(sf::Vector2f v){
    velocity.x += v.x;
    velocity.y += v.y;
}

void Particle::update(){
    sf::Vector2f newPosition(position.x + velocity.x * delta_t, position.y + velocity.y * delta_t);
    float windowX = gameWindow.getSize().x;
    float windowY = gameWindow.getSize().y;

    // std::cout << velocity.x << "," << velocity.y << std::endl;
    
    if(newPosition.x < 0){
        newPosition.x += windowX;
    }
    if(newPosition.y < 0){
        newPosition.y += windowY;
    }
    if(newPosition.x > windowX){
        newPosition.x -= windowX;
    }
    if(newPosition.y > windowY){
        newPosition.y -= windowY;
    }

    sprite.setPosition(newPosition);
    position = newPosition;

    velocity.x *= friction;
    velocity.y *= friction;
}

sf::Vector2f Particle::getVelocity(){
    return velocity;
}
