#include <ve/Dependency/DependencyContainer.hpp>

namespace ve
{
    void DependencyContainer::put(const std::string& name, const InterfacePtr& instance)
    {
        auto& list = instances.find(name);
        if (list == instances.end())
        {
            list = instances.emplace(name, InstanceList()).first;
        }
        list->second.push_back(instance);
    }
    
    InterfacePtr DependencyContainer::get(const std::string& name, const size_t index)
    {
        auto& list = instances.find(name);
        if (list == instances.end() || list->second.size() < index)
        {
            return InterfacePtr();
        }
        return list->second[index];
    }
}
