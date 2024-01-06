#include <Game.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifdef _WIN32
#include <WinSleepUnfucker.hpp>
#endif //  _WIN32

namespace constants
{
    const int32_t width = 1900;
    const int32_t height = 1000;
    const uint32_t frameRate = 60u;
}

class TestEntity : public Entity
{
private:
    std::shared_ptr<sf::CircleShape> shape;
    float x;
    float y;
    float radius;
    bool landed;
    bool movingRight;
    float velocity;

public:
    TestEntity()
        : shape{ std::make_shared<sf::CircleShape>(sf::CircleShape{ 10.0f }) }
        , x{ constants::width / 2 }
        , y{ 0 }
        , radius{ 20.f }
        , landed{ false }
        , movingRight(true)
        , velocity{ 0.f }
    {
        shape->setFillColor(sf::Color::Black);
        shape->setOutlineColor(sf::Color::White);
        shape->setOutlineThickness(1.f);
        shape->setRadius(radius);
        shape->setPosition(x, y);

    }

    void moveRightAndLeft(const float frameRatio)
    {
        if (movingRight)
        {
            x += 5.f * frameRatio;
        }
        else
        {
            x -= 5.f * frameRatio;
        }

        shape->setPosition(x, y);

        if (x > constants::width - radius * 2)
        {
            movingRight = false;
        }
        else if (x < 0)
        {
            movingRight = true;
        }
    }

    void update(const float frameRatio) override
    {
        if (landed)
        {
            return;
        }

        velocity += 0.3 * frameRatio;
        y += velocity * frameRatio;

        shape->setPosition(x, y);

        if (y >= constants::height - radius * 2)
        {
            y = constants::height - radius * 2;
            shape->setPosition(x, y);
            landed = true;
        }

    }

    std::shared_ptr<sf::CircleShape> getShape()
    {
        return shape;
    }


    virtual void setManager(const std::shared_ptr<EntityManager>& manager)
    {

    }
    virtual const DrawablePtr getDrawable() const
    {
        return shape;
    }
};


int main()
{

#ifdef _WIN32
    WinSleepUnfucker unfucker(4);
#endif //_WIN32

    using namespace std::literals::string_literals;
    //declare the window size

    sf::Vector2i windowSize(constants::width, constants::height);

    Renderer renderer{ windowSize,"VisualExercises"s , constants::frameRate };



    std::shared_ptr<TestEntity> shape = std::make_shared<TestEntity>();

    renderer.getEntities()->add(shape);
    renderer.getDrawables()->add(shape->getDrawable());
    renderer.loop();
    return 0;
}
