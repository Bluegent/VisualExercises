#pragma once
#include <Entity.h>
#include <unordered_map>

using Entities = std::unordered_map<EntityId, EntityPtr>;

class EntityManager
{
private:
    Entities entities;
    EntityId idGenerator;
public:
    EntityManager();
    void add(const EntityPtr& entity);
    void remove(const EntityId id);
    void update(const float tickRatio);
    const Entities& getEntities() const;

};

using EntityManagerPtr = std::shared_ptr<EntityManager>;