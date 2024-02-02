#include "Particle.hpp"
#include "Rule.hpp"
#include "config.hpp"
#include "findDistance.hpp"
#include "SpatialHashGrid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <optional>
#include <iostream>
#include <functional>
#include <stdexcept>

class Particles{
public:
    Particles();
    void addVector(const std::vector<Particle> &particleVector);
    void removeVector(float*);
    void addRule(Rule rule);
    int findRuleIndex(float* color1, float* color2);
    void updateColor(float* color);
    // void manipulateParticlesOfSameColor(float* Color, std::function<void(std::vector<Particle>)> lambda);
    void draw();
    void update();
    void applyRules();
public:
    bool rulesApply;
    std::vector<Rule> rules;
private:
    float force(float distance, float attraction);
private:
    SpatialHashGrid grid;
};
