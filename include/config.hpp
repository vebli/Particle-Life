#ifndef CONF
#define CONF 
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cmath>
#include <string>
#include <unordered_map>
//window

// Particles
inline sf::RenderWindow gameWindow(sf::VideoMode(800, 600), "Particle Life");
inline const float particleRadius = 2;
inline const float thresholdRadius = 50;
inline const float cellSize = 50;
inline const float particleEquilibrium = 0.3;
inline const float delta_t = 0.01;
inline const float friction = pow(0.5, delta_t / 1);
inline const float fpsCap = 60.f;
#endif // CONF
