#pragma once
#include <ve/Engine/Entity.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <ve/Helper/Math.hpp>
#include <random>

namespace ve
{
    class Sparkler : public DrawableEntity
    {
    private:
        std::shared_ptr<sf::RectangleShape> shape;
        DrawablePtr drawable;
        sf::Vector2f origin;
        float length;
        const float targetLength;
        bool spawnChild;
        sf::Color color;
        float angle;

    public:
        Sparkler(const sf::Vector2f& origin, const float targetLength, float angle, bool spawnChild = false)
            : shape{ std::make_shared<sf::RectangleShape>() }
            , origin{ origin }
            , length{ 0.f }
            , targetLength{ targetLength }
            , spawnChild{ spawnChild }
            , color{ sf::Color::White}
            , drawable{std::make_shared<Drawable>(shape)}
            , angle{angle}
        {
            shape->setPosition(origin);
            shape->setFillColor(color);
            shape->setRotation(angle-90.f);

        }

        virtual void update(const float frameRatio)
        {
            if (length >= targetLength)
            {
                if (color.a >= 10u)
                {
                    color.a -= 15.f * frameRatio;
                    shape->setFillColor(color);
                }
                else
                {
                    color.a = 0;

                    shape->setFillColor(color);

                    manager->remove(id);
                    drawableManager->remove(drawable->getId());
                }
                return;
            }

            length += 15.f * frameRatio;
            shape->setSize(sf::Vector2f(2, length));

            if (spawnChild && length >= targetLength)
            {

                float angleInRadians = toRadians(angle);
                sf::Vector2f childOrigin;
                float currentLength = shape->getSize().y;
                childOrigin.x = origin.x + cos(angleInRadians) * currentLength;
                childOrigin.y = origin.y + sin(angleInRadians) * currentLength;

                int32_t childCount = getRandom(2, 8);
                for (int32_t i = 0; i < childCount; ++i)
                {
                    std::shared_ptr<Sparkler> childSpark = std::make_shared<Sparkler>(childOrigin, getRandomF(10.f,50.f), angle + getRandomF(-180.f,180.f));
                    manager->add(childSpark);
                    drawableManager->add(childSpark->getDrawable());
                    childSpark->setDrawableManager(drawableManager);
                    childSpark->setManager(manager);
                }

     

            }
        }

        virtual const DrawablePtr getDrawable() const
        {
            return drawable;
        }

    };

    class SparklerSpawner : public DrawableEntity
    {
    private:
        sf::Vector2f origin;
        float counter;
    public:
        SparklerSpawner(const sf::Vector2f& origin)
            : origin{ origin }
            , counter{0.f}
        {

        }

        void update(const float tickRatio)
        {
            counter += tickRatio;
            origin.y += 0.9f * tickRatio;
            std::vector<int> a;
            if (counter >= 1.f)
            {
                counter = 0.f;
                int32_t childCount = getRandom(3, 5);
                for (int32_t i = 0; i < childCount; ++i)
                {
                    std::shared_ptr<Sparkler> childSpark = std::make_shared<Sparkler>(origin, getRandomF(10.f, 350.f), getRandomF(45.f, -225.f), true);
                    manager->add(childSpark);
                    childSpark->setManager(manager);

                    drawableManager->add(childSpark->getDrawable());
                    childSpark->setDrawableManager(drawableManager);
                }
            }
        }

    };

}