#pragma once
#include <Entity.h>
#include <SFML/Graphics/RectangleShape.hpp>

namespace ve
{
    class Sparkler : public Entity
    {
    private:
        std::shared_ptr<sf::RectangleShape> shape;
        DrawablePtr drawable;
        sf::Vector2f origin;
        float length;
        const float targetLength;
        std::shared_ptr<EntityManager> entityManager;
        std::shared_ptr<DrawableManager> drawableManager;
        bool spawnChild;
        sf::Color color;

    public:
        Sparkler(const sf::Vector2f& origin, const float targetLength, float angle, bool spawnChild = false)
            : shape{ std::make_shared<sf::RectangleShape>() }
            , origin{ origin }
            , length{ 0.f }
            , targetLength{ targetLength }
            , spawnChild{ spawnChild }
            , color{ sf::Color::White }
            , drawable{std::make_shared<Drawable>(shape)}
        {
            shape->setPosition(origin);
            shape->setFillColor(color);
            shape->setRotation(angle);

        }

        virtual void update(const float frameRatio)
        {
            if (length >= targetLength)
            {
                if (color.a >= 10u)
                {
                    color.a -= 3.f * frameRatio;
                    shape->setFillColor(color);
                }
                else
                {
                    color.a = 0;
                    shape->setFillColor(color);

                    entityManager->remove(id);
                    drawableManager->remove(drawable->getId());
                }
                return;
            }

            length += 30.f * frameRatio;
            shape->setSize(sf::Vector2f(2, length));

            if (spawnChild && length >= targetLength)
            {

                std::shared_ptr<Sparkler> childSpark1 = std::make_shared<Sparkler>(sf::Vector2f(origin.x, origin.y - shape->getSize().y), 50, shape->getRotation() + 45.f);
                std::shared_ptr<Sparkler> childSpark2 = std::make_shared<Sparkler>(sf::Vector2f(origin.x, origin.y - shape->getSize().y), 50, shape->getRotation() - 45.f);
                entityManager->add(childSpark1);
                entityManager->add(childSpark2);
                drawableManager->add(childSpark1->getDrawable());
                drawableManager->add(childSpark2->getDrawable());
                childSpark1->setDrawableManager(drawableManager);
                childSpark2->setDrawableManager(drawableManager);
                childSpark1->setManager(entityManager);
                childSpark2->setManager(entityManager);

            }
        }

        virtual const DrawablePtr getDrawable() const
        {
            return drawable;
        }

        virtual void setManager(const std::shared_ptr<EntityManager>& manager)
        {
            entityManager = manager;
        }

        virtual void setDrawableManager(const std::shared_ptr<DrawableManager>& manager)
        {
            drawableManager = manager;
        }

        ~Sparkler()
        {
        }

    };
}