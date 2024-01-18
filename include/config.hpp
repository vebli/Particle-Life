#ifndef CONF
#define CONF 
#include <SFML/Graphics/Color.hpp>
#include <string>
#include <unordered_map>
#include "../include/config.hpp"

// Particles
extern const float particleRadius;
extern const float threshholdRadius;

extern const std::unordered_map<std::string, sf::Color> strTosfColor;

#endif // CONF
