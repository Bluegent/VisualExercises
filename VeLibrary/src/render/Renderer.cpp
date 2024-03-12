#include <ve/render/Renderer.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <thread>
#include <iostream>

namespace ve
{
  


    Renderer::Renderer(const sf::VideoMode& mode, const std::string& name, int64_t frameMaxDuration)
        : _mode{mode}
        , _window(_mode, name)
       // , _rect(sf::Vector2f(50.f, 50.f))
       // , _rectPos(0.f, 0.f)
       // , _rectVelocity(3.f,3.f)
        , _frameMaxDuration{frameMaxDuration}
        , _lastUpdate(std::chrono::steady_clock::now())
    {
       // _rect.setFillColor(sf::Color::White);
    }

    void Renderer::renderloop()
    {
        std::chrono::time_point last = std::chrono::steady_clock::now();
        int64_t frameCount = 0;
        int64_t renderTimeSum = 0;
        while (_window.isOpen())
        {
            if (!pollevents())
            {
                return;
            }

            int64_t totalTime = update();
            totalTime += draw();
            renderTimeSum += totalTime;
            int64_t sleepTime = _frameMaxDuration - totalTime;

            if (sleepTime > 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
            }
            ++frameCount;
            std::chrono::time_point now = std::chrono::steady_clock::now();
            if (std::chrono::duration_cast<std::chrono::seconds>(now - last).count() >= 5)
            {
                std::cout << "Rendered " << frameCount << " frames" << " avg render time = " << ((renderTimeSum / frameCount) / 5) << "\n";
                renderTimeSum = 0;
                frameCount = 0;
                last = now;
            }
           
        }
    }

    void Renderer::addEntity(const EntityPtr& entity)
    {
        _entities.push_back(entity);
    }

    void Renderer::addDrawable(const DrawablePtr& drawable)
    {
        _drawables.push_back(drawable);
    }

    int64_t Renderer::draw()
    {
        std::chrono::time_point before = std::chrono::steady_clock::now();
        _window.clear();

        for (const auto& drawable : _drawables)
        {
            _window.draw(*drawable);
        }

        _window.display();
        std::chrono::time_point after = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
    }

    int64_t Renderer::update()
    {
        std::chrono::time_point before = std::chrono::steady_clock::now();
        const int64_t deltaT = std::chrono::duration_cast<std::chrono::milliseconds>(before - _lastUpdate).count();

        for (auto& entity : _entities)
        {
            entity->update(deltaT);
        }

        std::chrono::time_point after = std::chrono::steady_clock::now();
        _lastUpdate = after;
        return std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
    }

    bool Renderer::pollevents()
    {
        sf::Event evt;
        while (_window.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                _window.close();
                return false;
            }
        }
        return true;
    }
}