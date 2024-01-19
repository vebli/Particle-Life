#include "../include/SpatialHashGrid.hpp"

SpatialHashGrid::SpatialHashGrid(){};

void SpatialHashGrid::insert(const Particle& particle){
    sf::Vector2f cellIndex(static_cast<int>(particle.getPosition().x),  static_cast<int>(particle.getPosition().y));
    const int cellX = static_cast<int>(particle.getPosition().x / cellSize);
    const int cellY = static_cast<int>(particle.getPosition().y / cellSize);

    const sf::Color color = particle.getColor();
    std::string colorKey = colorToStr(color);

    grid[{cellX, cellY}][colorKey].push_back(particle);
}

const std::vector<Particle>& SpatialHashGrid::getCellParticles(sf::Color color, int cellX, int cellY){
    std::string colorKey = colorToStr(color);
    return grid.at({cellX, cellY}).at(colorKey);
}

