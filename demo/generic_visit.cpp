#include "poly_visitor/visitor.hpp"
#include <iostream>
#include <typeinfo>

struct Cat;
struct Cockatiel;

using base_visitor = poly_visitor::base_visitor<Cat, Cockatiel>;

struct Animal
{ PURE_VISITABLE(base_visitor) };

struct Cat : Animal
{ VISITABLE(base_visitor) };

struct Cockatiel : Animal
{ VISITABLE(base_visitor) };

struct TypeOf
{
    using result_type = void;
    
    template<typename Animal>
    void operator()(Animal&& animal)
    { std::cout << typeid(animal).name() << std::endl; }    
};

int main()
{
    Cockatiel bird;
    Animal& animal = bird;
    poly_visitor::apply_visitor(TypeOf{}, animal);
}
