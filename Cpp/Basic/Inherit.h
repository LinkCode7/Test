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
			x = _x; y = _y;
		}
	};

	void callPoint(Point2d pt);
	void callPoint2(Point2d& pt);
	void callPoint3(const Point2d& pt);
}
