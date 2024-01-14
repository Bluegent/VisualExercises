#include <gtest/gtest.h>
#include <ve/Dependency/InterfaceName.hpp>
#include <ve/Dependency/DependencyContainer.hpp>


class Type : public ve::Interface
{
private:
    int32_t value;
public:
    Type(const int32_t value) : value{ value } {}
    int getValue()
    {
        return value;
    }
};
using TypePtr = std::shared_ptr<Type>;
MAKE_INTERFACE(Type);

TEST(DependencyTest, InterfaceName)
{
    std::string typeName = ve::InterfaceName<Type>::get();
    ASSERT_EQ(typeName, "Type");
}


TEST(DependencyTest, RetrieveNull)
{
    ve::DependencyContainer container;
    TypePtr inital = container.retrieveInstance<Type>();
    ASSERT_EQ(inital.get(), nullptr);
}


TEST(DependencyTest, RetrieveReal)
{
    ve::DependencyContainer container;

    int32_t realValue = 12;
    TypePtr real = std::make_shared<Type>(realValue);

    container.registerInstance<Type>(real);

    TypePtr retrieved = container.retrieveInstance<Type>();

    ASSERT_NE(retrieved.get(),nullptr);
}

TEST(DependencyTest, RetrieveRealIndex2)
{
    ve::DependencyContainer container;

    int32_t realValue = 12;
    int32_t real2Value = 42;
    TypePtr real = std::make_shared<Type>(realValue);
    TypePtr real2 = std::make_shared<Type>(real2Value);
    container.registerInstance<Type>(real);
    container.registerInstance<Type>(real2);

    TypePtr retrieved = container.retrieveInstance<Type>(1);
    ASSERT_EQ(retrieved->getValue(), real2Value);
}


TEST(DependencyTest, RetrieveWrongIndex)
{
    ve::DependencyContainer container;

    int32_t realValue = 12;
    TypePtr real = std::make_shared<Type>(realValue);

    container.registerInstance<Type>(real);

    TypePtr retrieved = container.retrieveInstance<Type>(100);
    ASSERT_EQ(retrieved.get(), nullptr);
}


TypePtr makeType(ve::DependencyContainer &)
{
    return std::make_shared<Type>(20);
}


TEST(DependencyTest, RegisterAndCreateViaFunction)
{
    ve::DependencyContainer container;
    container.registerFunction<Type>(&makeType);

    TypePtr ptr = container.createInstance<Type>();

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr->getValue(), 20);
}