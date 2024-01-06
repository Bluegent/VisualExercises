#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <SFML/Graphics/Drawable.hpp>

class EntityManager;
using EntityId = uint32_t;
using DrawablePtr = std::shared_ptr<sf::Drawable>;

class Entity
{
protected:
    EntityId id;

public:
    virtual void update(const float frameRatio) = 0;
    virtual void setManager(const std::shared_ptr<EntityManager>& manager) = 0;
    virtual const DrawablePtr getDrawable() const
    {
        return {};
    }
    virtual EntityId getId() const
    {
        return id;
    }
    virtual void setId(const EntityId id)
    {
        this->id = id;
    }
};

using EntityPtr = std::shared_ptr<Entity>;