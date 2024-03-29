#pragma once
#include <cstdint>
#include <vector>
#include <memory>
#include <ve/Rendering/Drawable.hpp>


namespace ve
{
    class DrawableManager;
    class EntityManager;

    class Entity
    {
    protected:
        Id id;
    public:
        virtual void update(const float frameRatio) = 0;
        virtual void setManager(const std::shared_ptr<EntityManager>& manager) {}
        virtual void setDrawableManager(const std::shared_ptr<DrawableManager>& manager) {}
        virtual const DrawablePtr getDrawable() const
        {
            return {};
        }
        virtual Id getId() const
        {
            return id;
        }
        virtual void setId(const Id id)
        {
            this->id = id;
        }
    };

    class DrawableEntity : public Entity
    {
    protected:
        std::shared_ptr<EntityManager> manager;
        std::shared_ptr<DrawableManager> drawableManager;
    public:
        virtual void setManager(const std::shared_ptr<EntityManager>& manager) 
        {
            this->manager = manager;
        }
        virtual void setDrawableManager(const std::shared_ptr<DrawableManager>& manager)
        {
            this->drawableManager = manager;
        }
    };


    using EntityPtr = std::shared_ptr<Entity>;
}