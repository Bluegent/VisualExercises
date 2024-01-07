#include <Game.h>
#include <cstdio>
#include <SFML/Window/Event.hpp>
#include <thread>


namespace ve
{

    static float ratio = 0.f;
    static int64_t deltaT = 0;

    void Renderer::addDrawableEntity(const EntityPtr& entity)
    {
        entityManager->add(entity);
        drawableManager->add(entity->getDrawable());
        entity->setDrawableManager(drawableManager);
        entity->setManager(entityManager);
    }

    Renderer::Renderer(const sf::Vector2i& size, const std::string& name, const uint32_t frameRate, const uint32_t reportTimeSeconds)
        : size{ size }
        , window{ sf::VideoMode(size.x,size.y),name }
        , loopStart{ std::chrono::steady_clock::now() }
        , updateEnd{ std::chrono::steady_clock::now() }
        , renderEnd{ std::chrono::steady_clock::now() }
        , loopEnd{ std::chrono::steady_clock::now() }
        , frameCount{ 0 }
        , frameSleepMax{ 1000L / frameRate }
        , reportTime{ reportTimeSeconds * frameRate }
        , entityManager{ std::make_shared<EntityManager>() }
        , drawableManager{ std::make_shared<DrawableManager>(window) }
    {
        frameDurations.reserve(reportTimeSeconds * 100u);
        renderDurations.reserve(reportTimeSeconds * 100u);
        sleepTimes.reserve(reportTimeSeconds * 100u);
        printf("Sleep max: %lld\n", frameSleepMax);
    }

    const EntityManagerPtr& Renderer::getEntities()
    {
        return entityManager;
    }

    const DrawableManagerPtr& Renderer::getDrawables()
    {
        return drawableManager;
    }

    void Renderer::drawFrame()
    {
        window.clear();
        drawableManager->draw();
        window.display();
        renderEnd = std::chrono::steady_clock::now();
    }

    void Renderer::updateEntities()
    {
        deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(loopEnd - lastLoopStart).count();
        ratio = static_cast<float>(deltaT) / frameSleepMax;

        entityManager->update(ratio);
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
        int64_t renderDuration = 0;
        int64_t sleepTime = 0;
        while (window.isOpen())
        {
            loopStart = std::chrono::steady_clock::now();
            handleEvents();
            updateEntities();
            drawFrame();

            renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>((renderEnd - loopStart)).count();
            sleepTime = frameSleepMax - renderDuration;
            sleepTimes.push_back(sleepTime);
            renderDurations.push_back(renderDuration);
            if (sleepTime > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
            lastLoopStart = loopStart;
            loopEnd = std::chrono::steady_clock::now();
            frameDurations.push_back(std::chrono::duration_cast<std::chrono::milliseconds>((loopEnd - loopStart)).count());
            calculateAndPrintFrameTimes();
        }
    }

    int64_t calcAvg(std::vector<int64_t>& values)
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
            printf("FR#: %llu b:%lld + s:%lld =  f:%lld d:%lld u:%lld\n", frameCount, renderAvg, sleepAvg, frameAvg,drawableManager->getDrawablesCount(),entityManager->getEntityCount());
        }
    }
}