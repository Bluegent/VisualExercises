
#include <SleepFixImpl.hpp>
#include <ve/render/Renderer.hpp>
namespace constants
{
    const int32_t width = 800;
    const int32_t height = 600;
    const uint32_t frameRate = 60u;
}


int main()
{
    ve::SleepFix& fix = ve::SleepFixImpl(1);
    ve::Renderer renderer(sf::VideoMode(constants::width, constants::height), "VeEngine");
    renderer.renderloop();
    return 0;
}
