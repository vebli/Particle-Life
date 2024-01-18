#include "../include/Particle.hpp"
Particle::Particle(){};
Particle::Particle(const sf::Color color, const sf::Vector2f StartingPosition){
    sprite.setFillColor(color);
    sprite.setRadius(particleRadius);
    sprite.setPosition(StartingPosition);
}

void Particle::setPosition(sf::Vector2f Position){
    sprite.setPosition(Position);
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

sf::Color Particle::getColor() const{
    return sprite.getFillColor();
}
