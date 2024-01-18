#include "Particle.hpp"
#include "Rule.hpp"
#include "config.hpp"
#include <SFML/Graphics/Color.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>


class Particles{
private:
    std::unordered_map<std::string, std::vector<Particle>> particles;
    std::vector<Rule> rules;
    bool rulesApply;
public:
    Particles();
    void addVector(const std::vector<Particle> &particleVector);
    void addRule(Rule rule);
    void draw();
    void update();
    void applyRules();
};
