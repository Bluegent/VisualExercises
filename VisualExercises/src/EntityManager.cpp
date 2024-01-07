#include <EntityManager.h>

namespace ve
{

    EntityManager::EntityManager()
        : entities{}
        , idGenerator{ 0 }
    {
    }

    void EntityManager::add(const EntityPtr& entity)
    {
        entities.emplace(idGenerator, entity);
        entity->setId(idGenerator++);
    }

    void EntityManager::remove(const Id id)
    {
        entities.erase(id);
    }

    void EntityManager::update(const float tickRatio)
    {
        for (auto entity : entities)
        {
            entity.second->update(tickRatio);
        }
    }

    const Entities& EntityManager::getEntities() const
    {
        return entities;
    }
}
