#include <ve/Dependency/DependencyContainer.hpp>

namespace ve
{
    size_t DependencyContainer::put(const std::string& name, const InterfacePtr& instance)
    {
        auto& list = instances.find(name);
        if (list == instances.end())
        {
            list = instances.emplace(name, InstanceList()).first;
        }
        list->second.emplace_back(instance);
        return list->second.size() - 1;
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
    InterfacePtr DependencyContainer::create(const std::string& name)
    {
        auto& func = functions.find(name);
        if (func == functions.end())
        {
            return InterfacePtr();
        }
        return func->second(*this);
    }
    void DependencyContainer::registerFunc(const std::string& name, const CreateFunc& function)
    {
        functions.emplace(name, function);
    }


    DependencyContainer::~DependencyContainer()
    {
        instances.clear();
        functions.clear();
    }
}
