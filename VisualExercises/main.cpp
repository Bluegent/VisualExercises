#include <SFML/Graphics.hpp>
#include <SleepFixImpl.hpp>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
#include <random>

namespace constants
{
    const int32_t width = 800;
    const int32_t height = 600;
    const uint32_t frameRate = 60u;
}


std::random_device rd;
std::mt19937 mt;
std::uniform_int_distribution<int32_t> dist(0,255);

void setRandomColor(sf::RectangleShape & rect)
{
    uint8_t red = dist(mt);
    uint8_t green = dist(mt);
    uint8_t blue = dist(mt);

    rect.setFillColor(sf::Color(red, green, blue));
}


int main()
{
    ve::SleepFix& fix = ve::SleepFixImpl(1);
    mt.seed(rd());
    using namespace std::literals::string_literals;
    sf::RenderWindow window(
        sf::VideoMode(constants::width, constants::height)
        , "VEngine"s);
    // surface - a table of pixels characterized by a size and a position


    sf::RectangleShape horLine;
    horLine.setSize(sf::Vector2f(constants::width,1.f));
    horLine.setPosition(0.f,constants::height/2);

    sf::RectangleShape verLine;
    verLine.setSize(sf::Vector2f(1.f, constants::height));
    verLine.setPosition(constants::width / 2,0.f);


    sf::RectangleShape rect;
    sf::Vector2f rectPos;
    sf::Vector2f rectVelocity(3.f,3.f);
    rect.setFillColor(sf::Color::White);
    rect.setSize(sf::Vector2f(50.f,50.f));

    std::chrono::time_point last = std::chrono::steady_clock::now();
    uint32_t frameCount = 0;

    std::chrono::time_point beforeRender = std::chrono::steady_clock::now();
    std::chrono::time_point afterRender = std::chrono::steady_clock::now();

    const int64_t frameMaxDuration = 16; //16ms
    int64_t renderTimeSum = 0;

    while (window.isOpen())
    {      
        sf::Event evt;
        while (window.pollEvent(evt))
        {
            if (evt.type == sf::Event::Closed)
            {
                return 0;
            }
        }


        beforeRender = std::chrono::steady_clock::now();
        
        //clean the screen so that the new frame is not overlapping the old one
        window.clear();

        //do stuff with our objects

        //adjust the position by adding the velocity to it
        rectPos += rectVelocity;
        //check for bottom margin
        if (rectPos.y + rect.getSize().y >= constants::height)
        {
            rectVelocity.y *= -1.f; // we flip the y direction
            rectPos.y = constants::height - rect.getSize().y - 1.f; // position the rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(rect);
        }
        //check for top margin
        if (rectPos.y <= 0)
        {
            rectVelocity.y *= -1.f; // we flip the y direction
            rectPos.y = 1.f; // position the rectangle so we are sure it is no longer touching the bottom margin by moving it down by one pixel
            setRandomColor(rect);
        }

        //check for left margin
        if (rectPos.x <= 0.f )
        {
            rectVelocity.x *= -1.f; // we flip the x direction
            rectPos.x = 1.f; // position the rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(rect);
        }

        //check for right margin
        if (rectPos.x  + rect.getSize().x >= constants::width)
        {
            rectVelocity.x *= -1.f; // we flip the x direction
            rectPos.x = constants::width - rect.getSize().x - 1.f; // position the rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            setRandomColor(rect);
        }


        //finally set the position
        rect.setPosition(rectPos);

        //draw all our objects  
        //window.draw(horLine);
        //window.draw(verLine);
        window.draw(rect);

        //show the frame
        window.display();
        
        ++frameCount;
        afterRender = std::chrono::steady_clock::now();

        int64_t renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>(afterRender - beforeRender).count();

        int64_t sleepTime = frameMaxDuration - renderDuration;
        renderTimeSum += renderDuration;

        if (sleepTime > 0)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(sleepTime));
        }

        std::chrono::time_point now = std::chrono::steady_clock::now();
        if (std::chrono::duration_cast<std::chrono::seconds>(now - last).count() >= 5)
        {
            std::cout << "Rendered " << frameCount << " frames" << " avg render time = " << ((renderTimeSum / frameCount)/5) << "\n";
            renderTimeSum = 0;
            frameCount = 0;
            last = now;
        }
    }

    return 0;
}
