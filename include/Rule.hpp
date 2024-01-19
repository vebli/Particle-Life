#include <vector>
#include "Particle.hpp"
class Rule{
private:
public:
    std::string color1;
    std::string color2;
    float magnitude;
    Rule() = delete;
    Rule(std::string Color1, std::string Color2, float Magnitude);
};
