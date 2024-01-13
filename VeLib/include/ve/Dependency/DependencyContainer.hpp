#include <unordered_map>
#include <string>
#include <vector>
#include <ve/Dependency/InterfaceName.hpp>
#include <ve/Dependency/Interface.hpp>

namespace ve
{
    using InstanceList = std::vector<InterfacePtr>;
    using Instances = std::unordered_map<std::string, InstanceList>;
    class DependencyContainer
    {
    private:
        Instances instances;

        void put(const std::string& name, const InterfacePtr& instance);
        InterfacePtr get(const std::string& name, const size_t index = 0);

    public:
        template <typename Type>
        void registerInstance(const InterfacePtr& instance);

        template <typename Type>
        std::shared_ptr<Type> retrieveInstance(const size_t index = 0);
    };

    template<typename Type>
    void DependencyContainer::registerInstance(const InterfacePtr& instance)
    {
        put(InterfaceName<Type>::get(), instance);
    }

    template<typename Type>
    std::shared_ptr<Type> DependencyContainer::retrieveInstance(const size_t index)
    {
        return Interface::downCast<Type>(get(InterfaceName<Type>::get(),index));
    }
}