#include "Particle.hpp"
#include "Rule.hpp"
#include "config.hpp"
#include "findDistance.hpp"
#include "SpatialHashGrid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>


class Particles{
private:
    std::vector<Rule> rules;
    SpatialHashGrid grid;
    bool rulesApply;
public:
    Particles();
    void addVector(const std::vector<Particle> &particleVector);
    void addRule(Rule rule);
    void draw();
    void update();
    void applyRules();
};
