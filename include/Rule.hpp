#include <vector>
#include "Particle.hpp"
class Rule{
private:
public:
    sf::Color color1;
    sf::Color color2;
    float magnitude;
    Rule() = delete;
    Rule(sf::Color Color1, sf::Color Color2);
};
