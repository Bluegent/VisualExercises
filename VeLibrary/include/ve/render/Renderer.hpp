#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <string>
#include <SFML/Graphics/Drawable.hpp>
#include <ve/engine/Entity.hpp>
#include <memory>
#include <vector>
#include <chrono>

namespace ve
{
    using DrawablePtr = std::shared_ptr<sf::Drawable>;
    class Renderer
    {
    private:
        sf::VideoMode _mode;
        sf::RenderWindow _window;
        const int64_t _frameMaxDuration;
        std::vector<DrawablePtr> _drawables;
        std::vector<EntityPtr> _entities;
        std::chrono::time_point<std::chrono::steady_clock> _lastUpdate;

    public:
        Renderer(const sf::VideoMode& mode, const std::string& name, int64_t frameMaxDuration = 16);       
        void renderloop();

        void addEntity(const EntityPtr& entity);
        void addDrawable(const DrawablePtr& drawable);

    private:
        int64_t draw();
        int64_t update();
        bool pollevents();
    };
    
}