#include <ve/Engine/EntityManager.hpp>
#include <cstdio>
#include <ve/Helper/Log.hpp>

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
        removals.push_back(id);       
    }

    void EntityManager::update(const float tickRatio)
    {
        for (auto entity : entities)
        {
            entity.second->update(tickRatio);
        }
        removePass();
        
    }

    const Entities& EntityManager::getEntities() const
    {
        return entities;
    }
    void EntityManager::removePass()
    {
        for (const auto id : removals)
        {
            //LOG_DEBUG("Update: Removing entity %d", id);
            entities.erase(id);
        }
        removals.clear();
    }
    size_t EntityManager::getEntityCount()
    {
        return entities.size();
    }
}
