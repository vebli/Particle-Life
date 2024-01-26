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
    window.draw(sprite);
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
    float windowX = window.getSize().x;
    float windowY = window.getSize().y;

    // std::cout << velocity.x << "," << velocity.y << std::endl;
    if(newPosition.x >= 0 && newPosition.y >= 0 && newPosition.x <= windowX && newPosition.y <= windowY){
        sprite.setPosition(newPosition);
        position = newPosition;
    }
    
    else{ // wrap around window 
        // std::cout << "out of bound" << std::endl;
        sf::Vector2f trajectory(newPosition.x - position.x, newPosition.y - position.y);
        float* scalars = new float[4];
        float float_min = std::numeric_limits<float>::min();
        //scalars to calculate window border position
        scalars[0] = (trajectory.x != 0) ? -position.x / trajectory.x : float_min;
        scalars[1] = (trajectory.y != 0) ? -position.y / trajectory.y : float_min; 
        scalars[2] = (trajectory.x != 0) ? (windowX - position.x) / trajectory.x : float_min; 
        scalars[3] = (trajectory.y != 0) ? (windowY - position.y) / trajectory.y : float_min;

        float smallestScalar = scalars[0];
        float secondSmallestScalar = std::numeric_limits<float>::min();
        for(int i = 0; i < 4; i++){
            if(smallestScalar > scalars[i] ){
                smallestScalar = scalars[i];
            }
        }
        for(int i = 0; i < 4; i++){
            if(scalars[i] > smallestScalar && scalars[i] < secondSmallestScalar){
                secondSmallestScalar = scalars[i];
            }
        }
        
        sf::Vector2f newPosition(position.x + trajectory.x * secondSmallestScalar, position.y + trajectory.y * secondSmallestScalar);
        newPosition.x += trajectory.x * delta_t;
        newPosition.y += trajectory.y * delta_t;
        delete[] scalars;

        sprite.setPosition(newPosition);
        position = newPosition;

    }
    velocity.x *= friction;
    velocity.y *= friction;
}

sf::Vector2f Particle::getVelocity(){
    return velocity;
}
