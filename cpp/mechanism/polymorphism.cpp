#include "polymorphism.h"

TEST(polymorphism, normal)
{
    using namespace polymorphism;

    std::cout << "\n基类对象Geometry:" << std::endl;
    Geometry geometry;
    geometry.draw();

    std::cout << "\n子类对象Segment:" << std::endl;
    Segment line;
    line.drawLine();

    std::cout << "\n基类指针指向自身:" << std::endl;
    Geometry* pGeo = new Geometry();
    pGeo->draw();

    std::cout << "\n基类指针指向子类:" << std::endl;
    Geometry* pGeoLine = new Segment();
    pGeoLine->draw();

    delete pGeo;
    delete pGeoLine;
}

TEST(polymorphism, clone)
{
    using namespace test_clone;

    std::cout << "\n\n";
    Entity* pLine1 = new Segment({0, 0}, {1, 1});
    Entity* line1  = pLine1->clone(); // Entity* Entity::clone() const
    delete pLine1;
    delete line1;

    Segment* pLine2 = new Segment({0, 0}, {1, 1});
    Segment* line2  = pLine2->clone(); // Segment* Segment::clone() const
    delete pLine2;
    delete line2;
}
