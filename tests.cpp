#include "Director.hpp"
#include <cassert>

struct IService1
{
    virtual ~IService1() = default;
    virtual int Calculate(int a, int b) = 0;
};

class FirstService : public IService1
{
public:
    inline ~FirstService() override
    {
        std::cout << "~FirstService" << std::endl;
    }
    inline int Calculate(int a, int b) override
    {
        std::cout << "Calculate method" << std::endl;
        return a + b;
    }
};

class SecondService : public IService1
{
public:
    inline ~SecondService() override
    {
        std::cout << "~SecondService" << std::endl;
    }
    inline int Calculate(int a, int b) override
    {
        std::cout << "Calculate method 2" << std::endl;
        return a - b;
    }
};

void TestUseDirector()
{
    auto service1 = Director::GetContext<IService1>();
    assert(service1);
    int result = service1->Calculate(2, 2);
    assert(result == 0);
}

void BeforeTests()
{
    auto service1 = std::make_shared<FirstService>();
    auto service2 = std::make_shared<SecondService>();
    Director::Register<IService1>(service1);
    Director::Register<IService1>(service2);
}

int main(void)
{
    BeforeTests();
    TestUseDirector();
    return 0;
}