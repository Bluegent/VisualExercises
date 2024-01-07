#pragma once
#include <Engine/Base.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <memory>

namespace ve
{
    using SfDrawablePtr = std::shared_ptr<sf::Drawable>;

    class Drawable
    {
    private:
        SfDrawablePtr drawable;
        Id id;
    public:
        Drawable(const SfDrawablePtr& drawable)
            : drawable{ drawable }
            , id{0}
        {

        }
        const SfDrawablePtr& getSfDrawable() const
        {
            return drawable;
        }
        void setId(const Id id)
        {
            this->id = id;
        }

        Id getId() const
        {
            return id;
        }


    };
    using DrawablePtr = std::shared_ptr<Drawable>;
}