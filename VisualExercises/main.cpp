#include <ve/Engine/Game.hpp>
#include <SFML/Graphics.hpp>
#include <SleepFixImpl.hpp>
#include <iostream>
#include "src/Sparkler.hpp"

namespace constants
{
    const int32_t width = 1900;
    const int32_t height = 1000;
    const uint32_t frameRate = 60u;
}


int main()
{
    ve::SleepFix& fix = ve::SleepFixImpl(1);
    
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
