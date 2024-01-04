#include <Renderer.h>
#include <cstdio>
#include <SFML/Window/Event.hpp>


static float ratio = 0.f;
static int64_t deltaT = 0;

Renderer::Renderer(const sf::Vector2i& size, const std::string& name, const uint32_t frameRate, const uint32_t reportTimeSeconds)
    : size{ size }
    , window{ sf::VideoMode(size.x,size.y),name }
    , loopStart{ std::chrono::steady_clock::now() }
    , updateEnd{ std::chrono::steady_clock::now() }
    , renderEnd{ std::chrono::steady_clock::now() }
    , loopEnd{ std::chrono::steady_clock::now() }
    , frameCount{ 0 }
    , frameSleepMax{ 1000L/ frameRate }
    , reportTime{ reportTimeSeconds * frameRate}
{
    frameDurations.reserve(100);
    renderDurations.reserve(100);
    sleepTimes.reserve(100);
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
    deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(loopEnd - lastLoopStart).count();

    ratio = static_cast<float>(deltaT) / frameSleepMax;

    for (auto entity : entities)
    {
        entity->update(ratio);
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
    loopStart = std::chrono::steady_clock::now();
    loopEnd = std::chrono::steady_clock::now();
    lastLoopStart = loopStart;
    while (window.isOpen())
    {
        loopStart = std::chrono::steady_clock::now();
        handleEvents();
        updateEntities();
        drawFrame();
     
        int64_t renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>((renderEnd - loopStart)).count();
        int64_t sleepTime = frameSleepMax - renderDuration;
        renderDurations.push_back(renderDuration);
        if (sleepTime > 0)
        {
            sleepTimes.push_back(sleepTime);
            //std::unique_lock<std::mutex> lock(mtx);
            //auto sleepUntil = std::chrono::steady_clock::now() + std::chrono::milliseconds(sleepTime);
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }
        lastLoopStart = loopStart;
        loopEnd = std::chrono::steady_clock::now();
        frameDurations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>((loopEnd - loopStart)).count());
        calculateAndPrintFrameTimes();
    }
}

int64_t calcAvg(std::vector<int64_t> & values)
{
    int64_t avg = 0;
    for (const auto value : values)
    {
        avg += value;
    }
    return avg / values.size();
}

void Renderer::calculateAndPrintFrameTimes()
{
    ++frameCount;
    if (frameCount % reportTime == 0)
    {
        int64_t renderAvg = calcAvg(renderDurations);
        renderDurations.clear();
        int64_t frameAvg = calcAvg(frameDurations);
        frameDurations.clear();
        int64_t sleepAvg = calcAvg(sleepTimes);
        sleepTimes.clear();
        printf("FR#: %llu r:%lld f:%lld s:%lld \n",frameCount,renderAvg,frameAvg,sleepAvg);
    }
}
