#include "../include/particleLife.hpp"

void particleLife(){
    sf::Clock deltaClock;
    sf::Clock fpsClock;
    int frameCount = 0;
    int averageFps = 0.0f;
    sf::CircleShape dot;
    std::vector<sf::CircleShape> visualgrid;
    gameWindow.setFramerateLimit(fpsCap);
    ImGui::CreateContext();
    ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    bool some_bool_idk_about = ImGui::SFML::Init(gameWindow);
    dot.setRadius(0.4);
    for(int i = 0; i < gameWindow.getSize().x; i+= thresholdRadius){
        for(int j = 0; j < gameWindow.getSize().y; j += thresholdRadius){
            dot.setPosition(sf::Vector2f(i,j));
            visualgrid.push_back(dot);
        }
    }
    // Field field(sf::Vector2f(thresholdRadius*3, thresholdRadius*3), sf::Vector2f(thresholdRadius*4,thresholdRadius*4));
    Field field(sf::Vector2f(0, 0), sf::Vector2f(gameWindow.getSize().x, gameWindow.getSize().y));
    Particles particles;
    Particle p1;
    // p1.setColor(sf::Color::Blue);
    // p1.setPosition(sf::Vector2f(thresholdRadius*3, thresholdRadius*3));
    // p1.addVelocity(sf::Vector2f(50,50));
    // std::vector<Particle> testvec;
    // testvec.push_back(p1);
    // p1.setPosition(sf::Vector2f(thresholdRadius*4, thresholdRadius*4));
    // p1.addVelocity(sf::Vector2f(-100,-100));
    // testvec.push_back(p1);
    // particles.addVector(testvec);
    particles.addVector((initParticles(sf::Color::Yellow, 1000, field)));
    particles.addVector((initParticles(sf::Color::Green, 1000, field)));
    particles.addVector((initParticles(sf::Color::Blue, 1000, field)));

    particles.addRule(Rule(colorToStr(sf::Color::Blue), colorToStr(sf::Color::Blue), 0.2));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Green), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Yellow), colorToStr(sf::Color::Green), -0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Yellow), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Green), colorToStr(sf::Color::Blue), 0.5));
    particles.addRule(Rule(colorToStr(sf::Color::Yellow), colorToStr(sf::Color::Blue), 0.2));

    while (gameWindow.isOpen()){
        sf::Event event;
        while (gameWindow.pollEvent(event)){
            ImGui::SFML::ProcessEvent(gameWindow, event);
            if (event.type == sf::Event::Closed){
                gameWindow.close();
            }
        }

        ImGui::SFML::Update(gameWindow, sf::seconds(1.0f / fpsCap));
        ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
        ImGui::Begin("Matrix Editor", nullptr, ImGuiWindowFlags_DockNodeHost);

        int selectedRow = -1;
        int selectedCol = -1;
        int matrixSize = 7;
        int matrixData[matrixSize][matrixSize];
        int amountOfOptions = 1;
        
        ImGui::ShowDemoWindow();

        static float temp_delta_t = 0;
        ImGui::SliderFloat("delta_t", &temp_delta_t,  0.01f, 1);

        static float color[] = {1.f,0.f,0.f,1.f};

        if(ImGui::Button("restart")){
            //Restart Simulation
        };

        ImGui::SameLine();
    
        if(ImGui::Button("pause")){
            //pause simulation
        };

        ImGui::Spacing();
        ImGui::Separator();

        if(ImGui::Button("randomize")){
            //random matrix 
        };

        ImGui::BeginTable("Matrix", matrixSize, ImGuiTableFlags_Borders | ImGuiTableFlags_SizingFixedFit);

        for (int row = 0 ; row < matrixSize; row++) {
            ImGui::TableNextRow();
            for (int col = 0; col < matrixSize; col++) {
                if(col == 0 && row == 0)
                    continue;
                if(col != 0 && row != 0){
                    ImGui::TableSetColumnIndex(col);
                    static float testf = 0;
                    ImGui::InputFloat("##", &testf);
                }
                else{
                    ImGui::TableSetColumnIndex(col);
                    ImGui::ColorEdit4("edit", color, ImGuiColorEditFlags_NoInputs | ImGuiColorEditFlags_NoLabel | ImGuiColorEditFlags_NoAlpha);
                }

            }
        }

        ImGui::EndTable();
        ImGui::End();
        
        //draw
        particles.update();
        gameWindow.clear();
        for(auto& dot: visualgrid){
            gameWindow.draw(dot);
        }
        particles.draw();
        particles.applyRules();
        
        ImGui::SFML::Render(gameWindow);
        gameWindow.display();

        float deltaTime = deltaClock.restart().asSeconds();
        frameCount++;

        if(fpsClock.getElapsedTime().asSeconds() >= 5.0f){
            averageFps = frameCount / 5.0f;
            frameCount = 0;
            fpsClock.restart();
            std::cout << averageFps << "fps" << std::endl;
        }
    }
    ImGui::DestroyContext();
    ImGui::SFML::Shutdown();
}
