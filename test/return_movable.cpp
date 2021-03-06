#include "poly_visitor/visitor.hpp"
#include <iostream>

struct D1;
struct D2;

using base_visitor = poly_visitor::base_visitor<D1, D2>;

struct B
{ PURE_VISITABLE(base_visitor) };

struct D1 : B
{ VISITABLE(base_visitor) };

struct D2 : B
{ VISITABLE(base_visitor) };

struct Movable
{
    Movable() = default;
    
    Movable(const Movable&)
    { std::cout << "Movable copy ctor" << std::endl;}
    
    Movable& operator=(const Movable&)
    {
        std::cout << "Movable copy assignment operator" << std::endl;
        return *this;
    }
    
    Movable(Movable&&)
    { std::cout << "Movable move ctor" << std::endl;}
    
    Movable& operator=(Movable&&)
    {
        std::cout << "Movable move assignment operator" << std::endl;
        return *this;
    }
};

struct Visitor
{
    using result_type = Movable;

    template<typename T>
    result_type operator()(T&&)
    {
        Movable m;
        return m;
    }
};

int main()
{
    D2 o;
    B& base = o;
    poly_visitor::apply_visitor(Visitor{}, base);
}
