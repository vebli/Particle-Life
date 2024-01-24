#include <SFML/Graphics/Color.hpp>
#include <unordered_map>
#include <map>
#include <vector>
#include "config.hpp"
#include "Particle.hpp"
#include "colorToStr.hpp"
class SpatialHashGrid{
private:

public:
    std::map<std::pair<int, int>, std::map<std::string, std::vector<Particle>>> grid;
    SpatialHashGrid();
    void insert(const Particle& particle);
    std::vector<Particle>& getCellParticles(std::string color, int cellX, int cellY);
};
