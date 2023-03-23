#pragma once
#include <map>
#include <functional>
#include <string>
#include <iostream>

template<class B>
class Factory {
    std::map<std::string, B*> s_creators;

public:
    ~Factory()
    {
        for (auto _item : s_creators)
        {
            delete _item.second;
        }
        s_creators.clear();
    }
    inline static Factory<B>& getInstance() {
        static Factory<B> s_instance;
        return s_instance;
    }

    template<class T>
    inline void registerClass(const std::string& name)
    {
        s_creators.insert(
            { name, new T() });
    }

    inline B* create(const std::string& name);

    void printRegisteredClasses()
    {
        for (const auto& creator : s_creators) {
            std::cout << creator.first << '\n';
        }
    }

    std::map<std::string, B*> GetFactory() { return s_creators; }
};
#define FACTORY(Class) Factory<Class>::getInstance()

template<class B, class T>
class Creator {
public:
    explicit Creator(const std::string& name)
    {
        FACTORY(B).registerClass<T>(name);
    }
};
#define REGISTERFACTORY(base_class, derived_class) \
__declspec(selectany) \
Creator<base_class, derived_class> s_##derived_class##Creator(#derived_class); \