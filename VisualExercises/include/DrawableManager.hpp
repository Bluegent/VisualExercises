#pragma once
#include <Engine/Drawable.hpp>
#include <map>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>

namespace ve
{
    using ZIndex = int32_t;
    using Layer = std::unordered_map<Id, DrawablePtr>;
    using Layers = std::map <ZIndex, Layer>;

    class DrawableManager
    {
    private:
        Layers layers;
        Id idGenerator;
        sf::RenderWindow& window;
    public:
        DrawableManager(sf::RenderWindow& window);
        void add(const DrawablePtr& entity, const ZIndex zIndex = 0);
        void remove(const Id id);
        void remove(const Id id, const ZIndex zIndex);
        void draw();
    };

    using DrawableManagerPtr = std::shared_ptr<DrawableManager>;
}