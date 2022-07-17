#include "pch.h"
#include "inherit.h"

TEST(inherit, normal)
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