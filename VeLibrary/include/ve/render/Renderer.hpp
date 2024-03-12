#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>

namespace ve
{
    class Renderer
    {
    private:
        sf::VideoMode _mode;
        sf::RenderWindow _window;
        sf::RectangleShape _rect;
        sf::Vector2f _rectPos;
        sf::Vector2f _rectVelocity;
        const int64_t _frameMaxDuration;
       

    public:
        Renderer(const sf::VideoMode& mode, const std::string& name, int64_t frameMaxDuration = 16);       
        void renderloop();
    private:
        int64_t draw();
        int64_t update();
        bool pollevents();
    };
    
}