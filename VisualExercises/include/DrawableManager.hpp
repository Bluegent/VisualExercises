#pragma once
#include <Entity.h>
#include <map>
#include <unordered_map>
#include <SFML/Graphics/RenderWindow.hpp>

using ZIndex = int32_t;
using Layer = std::unordered_map<EntityId, DrawablePtr>;
using Layers = std::map <ZIndex, Layer>;

class DrawableManager
{
private:
    Layers layers;
    EntityId idGenerator;
    sf::RenderWindow & window;
public:
    DrawableManager(sf::RenderWindow & window);
    EntityId add(const DrawablePtr& entity, const ZIndex zIndex = 0);
    void remove(const EntityId id);
    void remove(const EntityId id, const ZIndex zIndex);
    void draw();
};

using DrawableManagerPtr = std::shared_ptr<DrawableManager>;