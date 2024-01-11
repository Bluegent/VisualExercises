#pragma once
#include <ve/Engine/Entity.hpp>
#include <unordered_map>
#include <vector>

namespace ve
{
    using Entities = std::unordered_map<Id, EntityPtr>;

    class EntityManager
    {
    private:
        Entities entities;
        std::vector<Id> removals;
        Id idGenerator;
    public:
        EntityManager();
        void add(const EntityPtr& entity);
        void remove(const Id id);
        void update(const float tickRatio);
        const Entities& getEntities() const;
        void removePass();
        size_t getEntityCount();

    };

    using EntityManagerPtr = std::shared_ptr<EntityManager>;
}