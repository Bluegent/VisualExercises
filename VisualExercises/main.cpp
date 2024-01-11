#include <ve/Engine/Game.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#ifdef _WIN32
    #include <windows/WinSleepUnfucker.hpp>
#endif //  _WIN32

#include "src/Sparkler.hpp"

namespace constants
{
    const int32_t width = 1900;
    const int32_t height = 1000;
    const uint32_t frameRate = 60u;
}

class TestEntity : public ve::Entity
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

        velocity += 0.3f * frameRatio;
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

};


int main()
{

#ifdef _WIN32
    WinSleepUnfucker unfucker(4);
#endif //_WIN32

    using namespace std::literals::string_literals;
    //declare the window size

    sf::Vector2i windowSize(constants::width, constants::height);

    ve::Renderer renderer{ windowSize,"VisualExercises"s , constants::frameRate };

    auto spawner = std::make_shared<ve::SparklerSpawner>(sf::Vector2f(constants::width / 2, constants::height / 2-500));
    spawner->setDrawableManager(renderer.getDrawables());
    spawner->setManager(renderer.getEntities());
    renderer.getEntities()->add(spawner);

    
    renderer.loop();
    return 0;
}
