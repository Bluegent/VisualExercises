#include <memory>


namespace ve
{

    class Interface;
    using InterfacePtr = std::shared_ptr<Interface>;

    class Interface
    {
    public:
        template <typename Derived>
        static std::shared_ptr<Derived> downCast(const InterfacePtr& ptr);
        virtual ~Interface() 
        {
        }
    };

    template <typename Derived>
    static std::shared_ptr<Derived> Interface::downCast(const InterfacePtr& ptr)
    {
        return std::dynamic_pointer_cast<Derived>(ptr);
    }

    
}