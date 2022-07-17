#pragma once
#include <iostream>



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
}
