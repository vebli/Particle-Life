#ifndef CONF
#define CONF 
#include <SFML/Graphics/Color.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <array>
// ImGui flags
#define customColorEditFlags ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha

inline const float fpsCap = 60.f;
// Particles
inline sf::RenderWindow sfWindow(sf::VideoMode(1920, 1080), "Particle Life", sf::Style::Fullscreen);
inline float delta_t = 0.025;
inline const float particleRadius = 2;
inline const float thresholdRadius = 50;
inline const float cellSize = 50;
inline const float particleEquilibrium = 0.3;
inline const float friction = pow(0.5f, delta_t / 0.6f);

//default colors
inline constexpr int matrixSize = 6;
inline constexpr int tableSize= 7;
inline constexpr int colorDimensions = 4; 
inline static float color1[] = {255.f, 0.f, 0.f ,255.f};
inline static float color2[] = {0.f, 255.f, 0.f, 255.f};
inline static float color3[] = {0.f, 0.f, 255.f, 255.f};
inline static float color4[] = {255.f, 255.f, 0.f, 255.f};
inline static float color5[] = {0.f, 255.f, 255.f, 255.f};
inline static float color6[] = {100.f, 255.f, 100.f, 255.f};
inline constexpr std::array<float*, matrixSize> defaultColors = {color1, color2, color3, color4, color5, color6};
inline static int defaultAmountOfParticleColors = 0; 
inline int defaultAmountOfColoredParticles[6] = {200, 200, 200, 200, 200, 200};
#endif // CONF
