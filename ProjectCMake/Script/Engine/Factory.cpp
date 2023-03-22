#include "Factory.h"
#include <memory>

template<class B>
inline B* Factory<B>::create(const std::string& name)
{
    const auto it = s_creators.find(name);
    if (it == s_creators.end()) return nullptr; // not a derived class
    return (it->second)();
}