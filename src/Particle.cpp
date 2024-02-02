#include "Particle.hpp"
#include <limits>
#include <string>
Particle::Particle(){
    sprite.setRadius(particleRadius);
};
Particle::Particle(float* Color, const sf::Vector2f StartingPosition){
    sf::Color sfColor(Color[0], Color[1], Color[2], Color[3]);
    sprite.setFillColor(sfColor);
    sprite.setRadius(particleRadius);
    sprite.setPosition(StartingPosition);
    position = StartingPosition;
    velocity = sf::Vector2f(0,0);  
    color = Color;
}
Particle::~Particle(){
    // delete[] color;
}

void Particle::setPosition(sf::Vector2f Position){
    sprite.setPosition(Position);
    position = Position;
}
sf::Vector2f Particle::getPosition() const{
    return position;
}
void Particle::draw () const{
    window.draw(sprite);
}

void Particle::updateColor(){
    sf::Color sfColor(color[0]*255, color[1]*255, color[2]*255, color[3]);
    sprite.setFillColor(sfColor);
}

float* Particle::getColor() const{
    return color;
}

void Particle::addVelocity(sf::Vector2f v){
    velocity.x += v.x;
    velocity.y += v.y;
}

void Particle::update(){
    sf::Vector2f newPosition(position.x + velocity.x * delta_t, position.y + velocity.y * delta_t);
    float windowX = window.getSize().x;
    float windowY = window.getSize().y;

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
