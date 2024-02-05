#include "colorButtonRGB.hpp"
//Conversion from RGB values to percentages due to ColorEdit4
void colorButtonRGB( char* label, float* color, ImGuiColorEditFlags flags){
    color[0] /= 255.0f;
    color[1] /= 255.0f;
    color[2] /= 255.0f;
    ImGui::ColorEdit4(label, color, flags);
    color[0] *= 255.0f;
    color[1] *= 255.0f;
    color[2] *= 255.0f;
}
