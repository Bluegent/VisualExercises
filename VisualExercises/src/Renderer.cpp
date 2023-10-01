#include <Renderer.h>
#include <cstdio>
#include <SFML/Window/Event.hpp>

Renderer::Renderer(const sf::Vector2i& size, const std::string& name, const uint32_t frameRate, const uint32_t reportTimeSeconds)
    : size{ size }
    , window{ sf::VideoMode(size.x,size.y),name }
    , loopStart{ std::chrono::steady_clock::now() }
    , updateEnd{ std::chrono::steady_clock::now() }
    , renderEnd{ std::chrono::steady_clock::now() }
    , loopEnd{ std::chrono::steady_clock::now() }
    , frameCount{ 0 }
    , frameSleepMax{ 1000L / frameRate }
    , reportTime{ reportTimeSeconds * frameRate}
{
    printf("Sleep max: %lld\n", frameSleepMax);
}

Drawables& Renderer::getDrawables()
{
    return drawables;
}

Entities& Renderer::getEntities()
{
    return entities;
}

void Renderer::drawFrame()
{
    window.clear();
    for (auto drawme : drawables)
    {
        window.draw(*drawme);
    }
    window.display();
    renderEnd = std::chrono::steady_clock::now();
}

void Renderer::updateEntities()
{
    auto deltaT = (loopEnd - loopStart).count();

    for (auto entity : entities)
    {
        entity->update(deltaT);
    }
    updateEnd = std::chrono::steady_clock::now();
}

void Renderer::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }
    }
}

void Renderer::loop()
{
    uint64_t loopTime = 0;
    while (window.isOpen())
    {
        loopStart = std::chrono::steady_clock::now();
        handleEvents();
        updateEntities();
        drawFrame();
     
        int64_t sleepTime = frameSleepMax - std::chrono::duration_cast<std::chrono::milliseconds>((renderEnd - loopStart)).count();
        if (sleepTime > 0)
        {
            std::unique_lock<std::mutex> lock(mtx);
            cv.wait_for(lock, std::chrono::milliseconds(sleepTime));
        }

        loopEnd = std::chrono::steady_clock::now();
        calculateAndPrintFrameTimes();
    }
}

void Renderer::calculateAndPrintFrameTimes()
{
    auto loopTime = std::chrono::duration_cast<std::chrono::milliseconds>(loopEnd - loopStart).count();
    auto renderTime = std::chrono::duration_cast<std::chrono::milliseconds>(renderEnd - updateEnd).count();
    auto updateTime = std::chrono::duration_cast<std::chrono::milliseconds>(updateEnd - loopStart).count();
    ++frameCount;
    if (frameCount % reportTime == 0)
    {
        printf("FR#: %llu UT: %llums RT: %llums LT: %llums\n",frameCount,updateTime,renderTime,loopTime);
    }
}
