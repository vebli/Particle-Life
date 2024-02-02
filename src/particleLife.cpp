#include "../include/particleLife.hpp"
#include "config.hpp"
#include "imgui.h"
#include <stdexcept>
#include <string>
#define customColorEditFlags ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha
void particleLife(){
    static int amountOfParticleColors = defaultAmountOfParticleColors;
    sf::Clock deltaClock;
    sf::Clock fpsClock;
    int frameCount = 0;
    int averageFps = 0.0f;
    sf::CircleShape dot;
    std::vector<sf::CircleShape> visualgrid;
    window.setFramerateLimit(fpsCap);
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    bool some_bool_idk_about = ImGui::SFML::Init(window);
    dot.setRadius(0.4);
    std::array<std::array<float,colorDimensions>, matrixSize - 1> previousColors; 
    for(int i = 0; i < defaultColors.size(); i++){
        for(int j = 0; j < colorDimensions; j++){
            previousColors[i][j] = defaultColors[i][j];
        }
    }
    for(int i = 0; i < window.getSize().x; i+= thresholdRadius){
        for(int j = 0; j < window.getSize().y; j += thresholdRadius){
            dot.setPosition(sf::Vector2f(i,j));
            visualgrid.push_back(dot);
        }
    }
    // Field field(sf::Vector2f(thresholdRadius*3, thresholdRadius*3), sf::Vector2f(thresholdRadius*4,thresholdRadius*4));
    Field field(sf::Vector2f(0, 0), sf::Vector2f(window.getSize().x, window.getSize().y));
    Particles particles;
    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed){
                window.close();
            }
        }

        ImGui::SFML::Update(window, sf::seconds(1.0f / fpsCap));
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);

        ImGui::Begin("Matrix Editor", nullptr, ImGuiWindowFlags_DockNodeHost | ImGuiWindowFlags_NoResize);

        static float matrix[matrixSize][matrixSize];
        int particleAmount = 12;
        
        ImGui::ShowDemoWindow();

        ImGui::SetNextItemWidth(20);
        ImGui::Text("%d fps", averageFps);

        ImGui::SliderFloat("delta_t", &delta_t,  0.01f, 1);
        ImGui::Separator();


        ImGui::Separator();

        if(ImGui::Button("restart")){
            //Restart Simulation
        }

        ImGui::SameLine();
    
        if(ImGui::Button("pause")){
            //pause simulation
        }

        ImGui::Spacing();
        ImGui::Separator();

        if(ImGui::Button("randomize")){
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> distribution(-1,1); 
            for(int x = 0; x < amountOfParticleColors; x++){
                for(int y = 0; y < amountOfParticleColors; y++){
                    float randomValue = distribution(gen);
                    matrix[x][y] = randomValue;
                }
            }
        }
        ImGui::Spacing();
        ImGui::Separator();

        if(amountOfParticleColors < 6){
            if(ImGui::Button("Add")){
                particles.addVector((initParticles(defaultColors[amountOfParticleColors], defaultAmountOfColoredParticles[amountOfParticleColors] , field)));
                amountOfParticleColors++;
            }
        }
        ImGui::SameLine();
        if(amountOfParticleColors > 0){
            if(ImGui::Button("remove")){
                particles.removeVector(defaultColors[amountOfParticleColors - 1]);
                amountOfParticleColors--;
            }
        }

        ImGui::Separator();

        ImGui::Text("Particle Amount");
        for(int row = 0; row < amountOfParticleColors; row++){
            char label[32];
            sprintf(label, "## %d", row);
            ImGui::ColorEdit4(label, defaultColors[row], customColorEditFlags);
            ImGui::SameLine();
            ImGui::InputInt(label, &defaultAmountOfColoredParticles[row], ImGuiInputTextFlags_CharsDecimal);
        }

        ImGui::Separator();
        ImGui::Text("Attraction Factor Matrix");
        // ImGui::SameLine();
        // ImGui::Text("(?)");
        //   if (ImGui::IsItemHovered(ImGuiHoveredFlags_AllowWhenDisabled))
        //   {
        //     ImGui::SetTooltip("");
        //   }
        for(int i = 0; i < defaultColors.size(); i++){
            for(int j = 0; j < colorDimensions; j++){
                if(defaultColors[i][j] != previousColors[i][j]){
                    particles.updateColor(defaultColors[i]);
                    previousColors[i][j] = defaultColors[i][j];
                }
            }
        }
        if(ImGui::BeginTable("Matrix", matrixSize, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit)){
            for (int row = 0 ; row <= amountOfParticleColors; row++) {
                ImGui::TableNextRow();
                for (int col = 0; col <= amountOfParticleColors; col++) {
                    char label[amountOfParticleColors*amountOfParticleColors];
                    sprintf(label, "## %d %d", row, col);
                    if(col == 0 && row == 0)
                        continue;
                    if(col != 0 && row != 0){
                        ImGui::TableSetColumnIndex(col);
                        ImGui::SetNextItemWidth(40.f);
                        ImGui::InputFloat(label, &matrix[row - 1][col - 1]);
                    }
                    else if(col == 0){
                        ImGui::TableSetColumnIndex(col);
                        ImGui::ColorEdit4(label, defaultColors[row - 1], customColorEditFlags);
                    }
                    else if(row == 0){
                        ImGui::TableSetColumnIndex(col);
                        ImGui::ColorEdit4(label, defaultColors[col - 1], customColorEditFlags);
                    }

                }
            }

            ImGui::EndTable();
        }

        ImGui::End();
        
        //matrix 
        for(int i = 0; i < matrixSize; i++){
            for(int j = 0; j < matrixSize; j++){
                particles.addRule(Rule(defaultColors[i], defaultColors[j], matrix[i][j]));
            }
        }
        //draw
        particles.update();
        window.clear();
        for(auto& dot: visualgrid){
            window.draw(dot);
        }
        particles.draw();
        particles.applyRules();
        
        ImGui::SFML::Render(window);
        window.display();

        float deltaTime = deltaClock.restart().asSeconds();
        frameCount++;
        if(fpsClock.getElapsedTime().asSeconds() >= 5.0f){
            averageFps = frameCount / 5.0f;
            frameCount = 0;
            fpsClock.restart();
        }
    }
    ImGui::DestroyContext();
    ImGui::SFML::Shutdown();
}
