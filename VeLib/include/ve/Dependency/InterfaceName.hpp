#pragma once
#include <iostream>

namespace ve
{
    template <typename T>
    class InterfaceName
    {
    public:
        static const char* get()
        {
            static_assert(false, "Instantiating of undeclared InterfaceName is not allowed");
        }
    };
}


#define MAKE_INTERFACE(name)                       \
template <>                                        \
inline const char * ve::InterfaceName<name>::get() \
{                                                  \
    return #name;                                  \
}                                                  