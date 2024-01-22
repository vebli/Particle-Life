#include "Particle.hpp"
#include "Rule.hpp"
#include "config.hpp"
#include "findDistance.hpp"
#include "SpatialHashGrid.hpp"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <unordered_map>
#include <iostream>

extern sf::RenderWindow window;

class Particles{
private:
    std::vector<Rule> rules;
    SpatialHashGrid grid;
    bool rulesApply;
    float force(float distance, float attraction);
public:
    Particles();
    void addVector(const std::vector<Particle> &particleVector);
    void addRule(Rule rule);
    void draw();
    void update();
    void applyRules();
    sf::Vector2f wrap(sf::Vector2f pos, sf::Vector2f trajectory); 
};
