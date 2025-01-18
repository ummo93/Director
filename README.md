## Director (Service locator) - single header library

A primitive implementation of the service locator pattern. Do not use it to access services directly, as this violates SOLID principles.

### Example of use

1. Copy Director.hpp to your project
2. Now you can do something like this:
```c++
struct IService
{
    virtual ~IService() = default;
    virtual int Calculate(int a, int b) = 0;
};

class ExampleService : public IService
{
public:
    inline ~ExampleService() override
    {
        std::cout << "~ExampleService" << std::endl;
    }
    inline int Calculate(int a, int b) override
    {
        std::cout << "Calculate method" << std::endl;
        return a + b;
    }
};

int main()
{
    // Initialisation
    auto service = std::make_shared<ExampleService>();
    Director::Register<IService>(service);
    // ...
    auto s = Director::GetContext<IService>();
    int res = s.Calculate(2, 2);

    return 0;
}

```

#### Currently only one instance per interface is supported.