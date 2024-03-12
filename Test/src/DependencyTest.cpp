#include <gtest/gtest.h>
#include <ve/Dependency/InterfaceName.hpp>
#include <ve/Dependency/DependencyContainer.hpp>


class Type : public ve::Interface
{
private:
    int32_t value;
    bool& destructed;
public:
    Type(const int32_t value, bool & destructed) : value{ value } , destructed{destructed}
    {
        destructed = false; 
    }
    int getValue()
    {
        return value;
    }
    ~Type()
    {
        destructed = true;
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
    bool temp = false;
    ve::DependencyContainer container;
    TypePtr inital = container.retrieveInstance<Type>();
    ASSERT_EQ(inital.get(), nullptr);
}


TEST(DependencyTest, RetrieveReal)
{
    ve::DependencyContainer container;

    int32_t realValue = 12;
    bool temp = false;
    TypePtr real = std::make_shared<Type>(realValue, temp);

    container.registerInstance<Type>(real);

    TypePtr retrieved = container.retrieveInstance<Type>();

    ASSERT_NE(retrieved.get(),nullptr);
}

TEST(DependencyTest, RetrieveRealIndex2)
{
    ve::DependencyContainer container;
    bool temp = false;
    int32_t realValue = 12;
    int32_t real2Value = 42;
    TypePtr real = std::make_shared<Type>(realValue,temp);
    TypePtr real2 = std::make_shared<Type>(real2Value,temp);
    container.registerInstance<Type>(real);
    container.registerInstance<Type>(real2);

    TypePtr retrieved = container.retrieveInstance<Type>(1);
    ASSERT_EQ(retrieved->getValue(), real2Value);
}


TEST(DependencyTest, RetrieveWrongIndex)
{
    ve::DependencyContainer container;

    int32_t realValue = 12;
    bool temp = false;
    TypePtr real = std::make_shared<Type>(realValue,temp);

    container.registerInstance<Type>(real);

    TypePtr retrieved = container.retrieveInstance<Type>(100);
    ASSERT_EQ(retrieved.get(), nullptr);
}


TypePtr makeType(ve::DependencyContainer &)
{
    static bool temp = false;
    return std::make_shared<Type>(20,temp);
}


TEST(DependencyTest, RegisterAndCreateViaFunction)
{
    ve::DependencyContainer container;
    container.registerFunction<Type>(&makeType);

    TypePtr ptr = container.createInstance<Type>();

    ASSERT_NE(ptr.get(), nullptr);
    ASSERT_EQ(ptr->getValue(), 20);
}


TEST(DependencyTest, InstancesAreDestructed)
{
    bool temp = false;
    {
        ve::DependencyContainer container;

        TypePtr real = std::make_shared<Type>(23, temp);
        container.registerInstance<Type>(real);
        ASSERT_FALSE(temp);
    }
    ASSERT_TRUE(temp);
}