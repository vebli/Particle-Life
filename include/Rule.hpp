#include <vector>
#include "Particle.hpp"
class Rule{
private:
public:
    float* color1;
    float* color2;
    float magnitude;
    Rule() = delete;
    Rule(float* Color1, float* Color2, float Magnitude);
};
