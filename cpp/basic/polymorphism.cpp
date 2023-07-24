#include "polymorphism.h"

TEST(polymorphism, normal)
{
    using namespace polymorphism;

    std::cout << "\n基类对象Geometry:" << std::endl;
    Geometry geometry;
    geometry.draw();

    std::cout << "\n子类对象Line:" << std::endl;
    Line line;
    line.drawLine();

    std::cout << "\n基类指针指向自身:" << std::endl;
    Geometry* pGeo = new Geometry();
    pGeo->draw();

    std::cout << "\n基类指针指向子类:" << std::endl;
    Geometry* pGeoLine = new Line();
    pGeoLine->draw();

    delete pGeo;
    delete pGeoLine;
}
