#pragma once

#include <ve/engine/Entity.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <memory>

namespace vedev
{
    class BouncyRectangle : public ve::Entity, public sf::Drawable
    {
    private:
        sf::RectangleShape _rect;
        sf::Vector2f _rectPos;
        sf::Vector2f _rectVelocity;
        sf::Vector2f _frame;
    public:
        BouncyRectangle(const sf::Vector2f & frame);
        virtual void update(int32_t deltaT) override;
        void draw(sf::RenderTarget& target, sf::RenderStates state = sf::RenderStates::Default) const override;
        void setPosition(const sf::Vector2f& position);
    };

    using BouncyRectanglePtr = std::shared_ptr<BouncyRectangle>;
}