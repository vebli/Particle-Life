#include "../include/colorToStr.hpp"

std::string colorToStr(sf::Color color){
    std::string colorKey = std::to_string(color.r) + "-" + std::to_string(color.g) + "-" + std::to_string(color.b);
    return colorKey;
}

