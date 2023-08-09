#pragma once
#include <iostream>

// 多态测试
namespace polymorphism
{
class Geometry
{
public:
    virtual ~Geometry() {}

    void draw()
    {
        std::cout << "Geometry::draw()" << std::endl;
        preDraw();
        // ...
        postDraw();
    }

    virtual void preDraw() { std::cout << "virtual Geometry::preDraw()" << std::endl; }
    virtual void postDraw() { std::cout << "virtual Geometry::postDraw()" << std::endl; }
};

class Segment : public Geometry
{
public:
    void drawLine()
    {
        // do something
        std::cout << "Segment::drawLine()" << std::endl;
        draw();
        postDraw();
    }

    void preDraw() override { std::cout << "Segment::preDraw() override" << std::endl; }
    void postDraw() override { std::cout << "Segment::postDraw() override" << std::endl; }
};

class StaticPolymorphismTest
{
public:
    Segment get() {}

    // 返回值不能成为重载决议
    // const Segment get() {} // error 2373: 重定义；不同的类型修饰符
    // const Segment& get() {} // error2556: 重载函数与“...”只是在返回类型上不同

    // 申明函数为const后，可以重载。如："T& operator[](size_t i)"和"const T& operator[](size_t i) const"
#ifndef GET_FUNCTION_RETURN_CONST_REFERENCE
    const Segment get() const {}
#else
    const Segment& get() const {}
#endif // DEBUG
};
} // namespace polymorphism

#define CLONE_ENTITY(ClassName)                                                          \
    ClassName* clone() const                                                             \
    {                                                                                    \
        std::cout << #ClassName << "* " << #ClassName << "::clone() const" << std::endl; \
        return static_cast<ClassName*>(subCreate());                                     \
    }

//#define USING_CLONE_MACRO

namespace test_clone
{
class Point
{
public:
    double x = 0.0;
    double y = 0.0;
};

class Entity
{
    int _flag = 0;

public:
    virtual ~Entity() {}

    virtual Entity* subCreate() const = 0
    {
        std::cout << "virtual Entity* Entity::subCreate() const" << std::endl;
        return nullptr;
    }

#ifdef USING_CLONE_MACRO
    CLONE_ENTITY(Entity)
#else
    Entity*        clone() const
    {
        std::cout << "Entity* Entity::clone() const" << std::endl;
        return subCreate();
    }
#endif
};

class Segment : public Entity
{
    Point _begin;
    Point _end;

public:
    Segment(Point const& begin, Point const& end) : _begin(begin), _end(end) {}

    Entity* subCreate() const override
    {
        std::cout << "virtual Entity* Segment::subCreate() const" << std::endl;
        return new Segment(_begin, _end);
    }

#ifdef USING_CLONE_MACRO
    CLONE_ENTITY(Segment)
#else
    Segment* clone() const
    {
        std::cout << "Segment* Segment::clone() const" << std::endl;
        return static_cast<Segment*>(subCreate());
    }
#endif
};

class Arc : public Entity
{
    Point _begin;
    Point _end;
    Point _center;

public:
    Arc(Point const& begin, Point const& end, Point const& center) : _begin(begin), _end(end), _center(center) {}

    Entity* subCreate() const override
    {
        std::cout << "virtual Entity* Arc::subCreate() const" << std::endl;
        return new Arc(_begin, _end, _center);
    }

#ifdef USING_CLONE_MACRO
    CLONE_ENTITY(Arc)
#else
    Arc* clone() const
    {
        std::cout << "Arc* Arc::clone() const" << std::endl;
        return static_cast<Arc*>(subCreate());
    }
#endif
};

// 实现带继承体系的克隆函数
class Pipe : public Segment
{
    double _thickness = 1.0;

public:
};

} // namespace test_clone
