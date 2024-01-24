#include "../include/SpatialHashGrid.hpp"

SpatialHashGrid::SpatialHashGrid(){};

void SpatialHashGrid::insert(const Particle& particle){
    const int cellX = static_cast<int>(particle.getPosition().x / cellSize);
    const int cellY = static_cast<int>(particle.getPosition().y / cellSize);

    const std::string colorKey = particle.getColor();

    grid[{cellX, cellY}][colorKey].push_back(particle);
}

std::vector<Particle>& SpatialHashGrid::getCellParticles(std::string color, int cellX, int cellY){
    return grid.at({cellX, cellY}).at(color);
}

