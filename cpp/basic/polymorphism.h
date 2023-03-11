#pragma once
#include <iostream>

// 多态测试
namespace polymorphism
{
	class Geometry
	{
	public:
		void draw() {
			std::cout << "Geometry::draw()" << std::endl;
			preDraw();
			// ...
			postDraw();
		}

		virtual void preDraw() { std::cout << "virtual Geometry::preDraw()" << std::endl; }
		virtual void postDraw() { std::cout << "virtual Geometry::postDraw()" << std::endl; }
	};

	class Line : public Geometry
	{
	public:
		void drawLine() {
			// do something
			std::cout << "Line::drawLine()" << std::endl;
			draw();
			postDraw();
		}

		void preDraw() override { std::cout << "Line::preDraw() override" << std::endl; }
		void postDraw() override { std::cout << "Line::postDraw() override" << std::endl; }
	};

	class StaticPolymorphismTest
	{
	public:
		Line get() {}

		// 返回值不能成为重载决议
		//const Line get() {} // error 2373: 重定义；不同的类型修饰符
		//const Line& get() {} // error2556: 重载函数与“...”只是在返回类型上不同

		// 申明函数为const后，可以重载。如："T& operator[](size_t i)"和"const T& operator[](size_t i) const"
#ifndef GET_FUNCTION_RETURN_CONST_REFERENCE
		const Line get() const {}
#else
		const Line& get() const {}
#endif // DEBUG
	};
}
