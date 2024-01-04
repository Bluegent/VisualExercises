#include <Renderer.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#ifdef _WIN32
#include <WinSleepUnfucker.hpp>
#endif //  _WIN32


class TestEntity : public Entity
{
public:
    std::shared_ptr<sf::CircleShape> shape;
    float x;
    float y;
    float radius;
    TestEntity()
        : shape{ std::make_shared<sf::CircleShape>(sf::CircleShape{ 10.0f }) }
        , x{10.f}
        , y{10.f}
        , radius{10.f}
    {
        shape->setFillColor(sf::Color::Black);
        shape->setOutlineColor(sf::Color::White);
        shape->setOutlineThickness(1.f);
        
    }
    void update(const float frameRatio) override
    {
        x += 5.f * frameRatio;
        shape->setPosition(x,y);
    }
};


int main()
{

#ifdef _WIN32
    WinSleepUnfucker unfucker(4);
#endif //_WIN32
    using namespace std::literals::string_literals;
    //declare the window size
    sf::Vector2i windowSize(1900, 1000);

    Renderer renderer{ windowSize,"VisualExercises"s ,60u};
    std::shared_ptr<TestEntity> shape = std::make_shared<TestEntity>();

    renderer.getDrawables().push_back(shape->shape);
    renderer.getEntities().push_back(shape);
    renderer.loop();
    return 0;
}
