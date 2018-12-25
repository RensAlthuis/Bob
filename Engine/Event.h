#pragma once
#include "functional"

template <typename... T>
class Event
{
  private:
    std::vector<void(*)(T...)> registry;

    inline void registerFunc(void (*f)(T...))
    {
        registry.push_back(f);
    }

    void deRegisterFunc(void (*func)(T...))
    {
        for (int i = 0; i < registry.size(); i++)
        {
            if(func == registry[i]){
                registry[i] = registry[registry.size()-1];
                registry.pop_back();
                return;
            }
        }
    }
  public:

    inline void operator+=(void(*f)(T...)){
        registerFunc(f);
    }

    inline void operator-=(void(*f)(T...)){
        deRegisterFunc(f);
    }

    void emit(T... args)
    {
        for (auto f : registry)
        {
            f(args...);
        }
    }
};