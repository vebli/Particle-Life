#include "../include/Particle.hpp"
Particle::Particle(){};
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
    return sprite.getPosition();
}
void Particle::draw () const{
    window.draw(sprite);
}

void Particle::setColor(sf::Color color){
    sprite.setFillColor(color);
}

std::string Particle::getColor() const{
    return color;
}

void Particle::addVelocity(sf::Vector2f v){
    velocity.x += v.x;
    velocity.y += v.y;
}

void Particle::update(){
    position = sf::Vector2f(position.x + velocity.x * delta_t, position.y + velocity.y * delta_t);
    sprite.setPosition(position);
}

sf::Vector2f Particle::getVelocity(){
    return velocity;
}
