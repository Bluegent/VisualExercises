#include <Renderer.h>
#include <SFML/Graphics/RectangleShape.hpp>

float arrX[] = { 1.f, 2.f, 4.f, 5.f, 6.f, 6.f, 5.f, 1.f, 0.f, 0.f };
float arrY[] = { -1.f, 1.f, 1.f, -1.f, 1.f, 4.f, 5.f, 5.f, 4.f, 1.f };
sf::Vector2f bow[] = { {0.f,0.f},{2.f,1.f},{4.f,0.f},{4.f,2.f},{2.f,1.f},{0.f,2.f} };

class TestEntity : public Entity
{
public:
    std::shared_ptr<sf::RectangleShape> rect;
    float x;
    float y;
    TestEntity()
        : rect{ std::make_shared<sf::RectangleShape>(sf::RectangleShape{ {20,20} }) }
        , x{0.f}
        , y{0.f}
    {
        rect->setFillColor(sf::Color::Red);
    }
    void update(const int64_t deltaT) override
    {
        x += 0.5f;
        y += 0.5f;
        rect->setPosition(x,y);
    }
};


int main()
{
    using namespace std::literals::string_literals;
    //declare the window size
    sf::Vector2i windowSize(800, 600);

    Renderer renderer{ windowSize,"VisualExercises"s ,60u};
    std::shared_ptr<TestEntity> rect = std::make_shared<TestEntity>();

    renderer.getDrawables().push_back(rect->rect);
    renderer.getEntities().push_back(rect);
    renderer.loop();

    return 0;
}
