#pragma once
#include <EntityManager.h>
#include <DrawableManager.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <chrono>

namespace ve
{

    class Renderer
    {
    private:
        sf::Vector2i size;
        sf::RenderWindow window;

        std::chrono::high_resolution_clock::time_point loopStart;
        std::chrono::high_resolution_clock::time_point lastLoopStart;
        std::chrono::high_resolution_clock::time_point updateEnd;
        std::chrono::high_resolution_clock::time_point renderEnd;
        std::chrono::high_resolution_clock::time_point loopEnd;

        uint64_t frameCount;
        const int64_t frameSleepMax;
        const uint32_t reportTime;
        std::vector <int64_t> frameDurations;
        std::vector <int64_t> renderDurations;
        std::vector <int64_t> sleepTimes;
        EntityManagerPtr entityManager;
        DrawableManagerPtr drawableManager;




    public:
        Renderer(const sf::Vector2i& size, const std::string& name, const uint32_t frameRate = 60U, const uint32_t reportTimeSeconds = 2U);
        const EntityManagerPtr& getEntities();
        const DrawableManagerPtr& getDrawables();
        void drawFrame();
        void updateEntities();
        void handleEvents();
        void loop();
        void calculateAndPrintFrameTimes();
        void addDrawableEntity(const EntityPtr& entity);
    };
}