#include <unordered_map>
#include <string>
#include <vector>
#include <functional>
#include <ve/Dependency/InterfaceName.hpp>
#include <ve/Dependency/Interface.hpp>

namespace ve
{
    class DependencyContainer;
    using InstanceList = std::vector<InterfacePtr>;
    using Instances = std::unordered_map<std::string, InstanceList>;

    using CreateFunc = std::function<InterfacePtr(DependencyContainer&)>;
    using CreateFuncs = std::unordered_map<std::string, CreateFunc>;


    class DependencyContainer
    {
    private:
        Instances instances;
        CreateFuncs functions;

        size_t put(const std::string& name, const InterfacePtr& instance);
        InterfacePtr get(const std::string& name, const size_t index = 0);
        InterfacePtr create(const std::string& name);
        void registerFunc(const std::string& name, const CreateFunc& function);


    public:
        template <typename Type>
        size_t registerInstance(const InterfacePtr& instance);

        template <typename Type>
        void registerFunction(const CreateFunc& function);

        template <typename Type>
        std::shared_ptr<Type> retrieveInstance(const size_t index = 0);

        template <typename Type>
        std::shared_ptr<Type> createInstance();

        template <typename Type>
        std::shared_ptr<Type> retrieveOrCreate(const size_t index = 0);
        ~DependencyContainer();

    };

    template<typename Type>
    size_t DependencyContainer::registerInstance(const InterfacePtr& instance)
    {
        return put(InterfaceName<Type>::get(), instance);
    }

    template<typename Type>
    std::shared_ptr<Type> DependencyContainer::retrieveInstance(const size_t index)
    {
        return Interface::downCast<Type>(get(InterfaceName<Type>::get(),index));
    }

    template<typename Type>
    std::shared_ptr<Type> DependencyContainer::createInstance()
    {
        return Interface::downCast<Type>(create(InterfaceName<Type>::get()));
    }

    template <typename Type>
    void DependencyContainer::registerFunction(const CreateFunc& function)
    {
        registerFunc(InterfaceName<Type>::get(),function);
    }

    template<typename Type>
    std::shared_ptr<Type> DependencyContainer::retrieveOrCreate(const size_t index)
    {
        auto instance = get(InterfaceName<Type>::get(), index);
        if (!instance)
        {
            instance = create(InterfaceName<Type>::get());
        }
        return instance;
    }

}