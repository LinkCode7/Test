#pragma once

namespace TestPoint
{
// 第三方库使用的Point
struct Point2d
{
public:
    float x;
    float y;
};

// 派生出一个Point，强制实现构造函数，避免浮点数没初始化
class MyPoint2d : public Point2d
{
public:
    MyPoint2d(float _x, float _y) /*: Point2d::x(_x), y(_y)*/
    {
        x = _x;
        y = _y;
    }
    MyPoint2d(const Point2d& pt)
    {
        x = pt.x;
        y = pt.y;
    }

    MyPoint2d& operator=(const Point2d& pt)
    {
        x = pt.x;
        y = pt.y;
        return *this; // 支持连等：a = b = c;
    }
};

void callPoint(Point2d pt);
void callPoint2(Point2d& pt);
void callPoint3(const Point2d& pt);
} // namespace TestPoint

struct SkRect
{
    float fLeft;   //!< smaller x-axis bounds
    float fTop;    //!< smaller y-axis bounds
    float fRight;  //!< larger x-axis bounds
    float fBottom; //!< larger y-axis bounds
};

class PxRect : public SkRect
{
public:
    PxRect(float width, float height) : SkRect{0, 0, width, height} {}
    PxRect(float x, float y, float width, float height) : SkRect{x, y, width, height} {}
    PxRect(const SkRect& other) : SkRect{other.fLeft, other.fTop, other.fRight, other.fBottom} {}
    PxRect& operator=(const SkRect& other)
    {
        fLeft   = other.fLeft;
        fTop    = other.fTop;
        fRight  = other.fRight;
        fBottom = other.fBottom;
        return *this;
    }
};

class DbEntity
{
public:
};