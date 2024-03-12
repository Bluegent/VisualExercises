#include <ve/dev/BouncyRectangle.hpp>
#include <random>
#include <SFML/Graphics/RenderTarget.hpp>
#include <iostream>

namespace vedev
{
    void setRandomColor(sf::RectangleShape& rect)
    {
        static std::random_device rd;
        static std::mt19937 mt;
        static std::uniform_int_distribution<int32_t> dist(0, 255);
        uint8_t red = dist(mt);
        uint8_t green = dist(mt);
        uint8_t blue = dist(mt);

        rect.setFillColor(sf::Color(red, green, blue));
    }

    BouncyRectangle::BouncyRectangle(const sf::Vector2f& frame)
        : _rect(sf::Vector2f(50.f, 50.f))
        , _rectPos(0.f, 0.f)
        , _rectVelocity(0.1f, 0.1f)
        , _frame{frame}
    {
        //_rect.setFillColor(sf::Color::White);
        setRandomColor(_rect);
    }

    void BouncyRectangle::update(int32_t deltaT)
    {
        _rectPos += _rectVelocity * static_cast<float>(deltaT);

        if (_rectPos.y + _rect.getSize().y >= _frame.y)
        {
            _rectVelocity.y *= -1.f; // we flip the y di_rection
            _rectPos.y = _frame.y - _rect.getSize().y - 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            //setRandomColor(_rect);
        }
        //check for top margin
        if (_rectPos.y <= 0)
        {
            _rectVelocity.y *= -1.f; // we flip the y di_rection
            _rectPos.y = 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it down by one pixel
            //setRandomColor(_rect);
        }

        //check for left margin
        if (_rectPos.x <= 0.f)
        {
            _rectVelocity.x *= -1.f; // we flip the x di_rection
            _rectPos.x = 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            //setRandomColor(_rect);
        }

        //check for right margin
        if (_rectPos.x + _rect.getSize().x >= _frame.x)
        {
            _rectVelocity.x *= -1.f; // we flip the x di_rection
            _rectPos.x = _frame.x - _rect.getSize().x - 1.f; // position the _rectangle so we are sure it is no longer touching the bottom margin by moving it up by one pixel
            //setRandomColor(_rect);
        }


        //finally set the position
        _rect.setPosition(_rectPos);
    }

    void BouncyRectangle::draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        target.draw(_rect,state);
    }
    void BouncyRectangle::setPosition(const sf::Vector2f& position)
    {
        _rectPos = position;
    }
}