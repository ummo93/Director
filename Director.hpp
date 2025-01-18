#pragma once
#include <iostream>
#include <unordered_map>
#include <memory>
#include <typeindex>
#include <stdexcept>

namespace Director
{
    class DContainer
    {
    public:
        static DContainer& Instance()
        {
            static DContainer instance;
            return instance;
        }

        template<typename Interface, typename Implementation>
        void Register(std::shared_ptr<Implementation> service) {
            auto typeId = std::type_index(typeid(Interface));
            static_assert(std::is_base_of<Interface, Implementation>::value, "Implementation must derive from Interface");
            if (services.find(typeId) != services.end()) {
                std::cerr << "Warning: Service already registered, overwriting.\n";
            }
            services[typeid(Interface)] = service;
        }

        template<typename Interface>
        std::shared_ptr<Interface> GetContext() {
            auto it = services.find(typeid(Interface));
            if (it == services.end()) {
                throw std::runtime_error("Service not registered!");
            }
            return std::static_pointer_cast<Interface>(it->second);
        }

        void Clear()
        {
            std::cout << "Clearing services...\n";
            services.clear();
        }
    private:
        std::unordered_map<std::type_index, std::shared_ptr<void>> services;

        DContainer() = default;
        ~DContainer() = default;
    };

    template<typename T>
    static inline void Register(std::shared_ptr<T> service)
    {
        DContainer::Instance().Register<T>(service);
    }

    template<typename T>
    static inline std::shared_ptr<T> GetContext()
    {
        return DContainer::Instance().GetContext<T>();
    }

    static inline void Clear()
    {
        DContainer::Instance().Clear();
    }
}

