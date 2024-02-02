#include <SFML/Graphics/Color.hpp>
#include <functional>
#include <unordered_map>
#include <map>
#include <vector>
#include <list>
#include "config.hpp"
#include "Particle.hpp"
#include "colorToStr.hpp"
class SpatialHashGrid{
private:

public:
    // std::vector<std::vector< std::unordered_map<float*, std::vector<Particle>>>> grid;
    std::vector<std::vector< std::unordered_map<const float*, std::vector<Particle>, std::hash<const float*>>>> grid;

    SpatialHashGrid();
    void insert(const Particle& particle);
    std::vector<Particle>& getCellParticles(float* color, int cellX, int cellY);
};
