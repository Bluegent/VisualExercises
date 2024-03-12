
#include <SleepFixImpl.hpp>
#include <ve/render/Renderer.hpp>
#include <ve/dev/BouncyRectangle.hpp>
namespace constants
{
    const int32_t width = 800;
    const int32_t height = 600;
    const uint32_t frameRate = 60u;
}


int main()
{
    ve::SleepFix& fix = ve::SleepFixImpl(1);
    ve::Renderer renderer(sf::VideoMode(constants::width, constants::height), "VeEngine",8);

    //std::shared_ptr<sf::RectangleShape> rect = std::make_shared<sf::RectangleShape>();
    //rect->setSize(sf::Vector2f(100.f, 100.f));
    ///renderer.addDrawable(rect);

    vedev::BouncyRectanglePtr rect1 = std::make_shared<vedev::BouncyRectangle>(sf::Vector2f(constants::width, constants::height));
    vedev::BouncyRectanglePtr rect2 = std::make_shared<vedev::BouncyRectangle>(sf::Vector2f(constants::width, constants::height));
    vedev::BouncyRectanglePtr rect3 = std::make_shared<vedev::BouncyRectangle>(sf::Vector2f(constants::width, constants::height));
    vedev::BouncyRectanglePtr rect4 = std::make_shared<vedev::BouncyRectangle>(sf::Vector2f(constants::width, constants::height));
 

    rect2->setPosition(sf::Vector2f(constants::width - 50.f, 0.f));
    rect3->setPosition(sf::Vector2f(constants::width - 50.f, constants::height-50.f));
    rect4->setPosition(sf::Vector2f(0.f, constants::height - 50.f));


    renderer.addDrawable(rect1);
    renderer.addEntity(rect1);
    renderer.addDrawable(rect2);
    renderer.addEntity(rect2);
    renderer.addDrawable(rect3);
    renderer.addEntity(rect3);
    renderer.addDrawable(rect4);
    renderer.addEntity(rect4);
    
    renderer.renderloop();
    return 0;
}
