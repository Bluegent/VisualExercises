#pragma once
#include <stdint.h>
#include <memory>

namespace ve
{
    class Entity
    {
    public:
        virtual void update(int32_t deltaT) = 0;
    };
    using EntityPtr = std::shared_ptr<Entity>;
}