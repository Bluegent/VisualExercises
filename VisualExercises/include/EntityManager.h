#pragma once
#include <Entity.h>
#include <unordered_map>


namespace ve
{
    using Entities = std::unordered_map<Id, EntityPtr>;

    class EntityManager
    {
    private:
        Entities entities;
        Id idGenerator;
    public:
        EntityManager();
        void add(const EntityPtr& entity);
        void remove(const Id id);
        void update(const float tickRatio);
        const Entities& getEntities() const;

    };

    using EntityManagerPtr = std::shared_ptr<EntityManager>;
}