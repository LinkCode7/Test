#include "inherit.h"

TEST(inherit, point)
{
    using namespace TestPoint;

    Point2d pt;
    pt.x = 0;
    pt.y = 0;
    callPoint(pt);

    MyPoint2d pt2(1, 1);
    callPoint(pt2);
    callPoint2(pt2);
    callPoint3(pt2);

    pt2 = pt;

    Point2d   pt3 = {5, 5};
    MyPoint2d pt4 = pt3;
    MyPoint2d pt5 = pt4 = pt3;

    MyPoint2d pt6 = pt5;
    pt6           = pt2;
}

void TestPoint::callPoint(Point2d pt)
{
    Point2d pt2 = pt;
}

void TestPoint::callPoint2(Point2d& pt)
{
    pt.x = 222;
    pt.y = 222;
}
void TestPoint::callPoint3(const Point2d& pt)
{
    Point2d pt2 = pt;
}

TEST(inherit, rect)
{
    using namespace TestPoint;

    SkRect rect;
    rect.fLeft   = -1;
    rect.fTop    = -1;
    rect.fRight  = -1;
    rect.fBottom = -1;

    PxRect rect1(1, 1, 1, 1);
    PxRect rect2(1, 1, 20, 20);

    PxRect rect3 = rect1;
    rect3        = rect2;

    PxRect rect4 = rect;
    rect.fLeft   = -100;
    rect4        = rect;
}
