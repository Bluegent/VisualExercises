#include <ve/render/Renderer.hpp>
#include <SFML/Window/Event.hpp>
#include <chrono>
#include <random>
#include <thread>
#include <iostream>

namespace ve
{
    std::random_device rd;
    std::mt19937 mt;
    std::uniform_int_distribution<int32_t> dist(0, 255);

    void setRandomColor(sf::RectangleShape& rect)
    {
        uint8_t red = dist(mt);
        uint8_t green = dist(mt);
        uint8_t blue = dist(mt);

        rect.setFillColor(sf::Color(red, green, blue));
    }

    Renderer::Renderer(const sf::VideoMode& mode, const std::string& name, int64_t frameMaxDuration)
        : _mode{mode}
        , _window(_mode, name)
        , _rect(sf::Vector2f(50.f, 50.f))
        , _rectPos(0.f, 0.f)
        , _rectVelocity(3.f,3.f)
        , _frameMaxDuration{frameMaxDuration}
    {
        _rect.setFillColor(sf::Color::White);
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

    int64_t Renderer::draw()
    {
        std::chrono::time_point before = std::chrono::steady_clock::now();
        _window.clear();
        _window.draw(_rect);
        _window.display();
        std::chrono::time_point after = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::milliseconds>(after - before).count();
    }

    int64_t Renderer::update()
    {
        std::chrono::time_point before = std::chrono::steady_clock::now();
        
        //adjust the position by adding the velocity to it
        _rectPos += _rectVelocity;
        //check for bottom margin
        if (_rectPos.y + _rect.getSize().y >= _mode.height)
        {
            _rectVelocity.y *= -1.f; // we flip the y di_rection
            _rectPos.y = _mode.height - _rect.getSize().y - 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(_rect);
        }
        //check for top margin
        if (_rectPos.y <= 0)
        {
            _rectVelocity.y *= -1.f; // we flip the y di_rection
            _rectPos.y = 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it down by one pixel
            setRandomColor(_rect);
        }

        //check for left margin
        if (_rectPos.x <= 0.f)
        {
            _rectVelocity.x *= -1.f; // we flip the x di_rection
            _rectPos.x = 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(_rect);
        }

        //check for right margin
        if (_rectPos.x + _rect.getSize().x >= _mode.width)
        {
            _rectVelocity.x *= -1.f; // we flip the x di_rection
            _rectPos.x = _mode.width - _rect.getSize().x - 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(_rect);
        }


        //finally set the position
        _rect.setPosition(_rectPos);

        std::chrono::time_point after = std::chrono::steady_clock::now();
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