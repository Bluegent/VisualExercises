#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>

class Entity
{
public:
    virtual void update(const float frameRatio) = 0;
};

using DrawablePtr = std::shared_ptr<sf::Drawable>;
using EntityPtr = std::shared_ptr<Entity>;
using Drawables = std::vector<DrawablePtr>;
using Entities = std::vector<EntityPtr>;