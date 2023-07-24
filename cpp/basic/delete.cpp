
class Object
{
public:
    Object() { std::cout << "构造：Object()" << std::endl; }
    ~Object() { std::cout << "析构：~Object()" << std::endl; }
};

//////////////////////////////////////////////////////////////////////////

void testDelete()
{
    Object* pObject1 = new Object;
    Object* pObject2 = new Object[3];

    delete pObject1;
    delete[] pObject2; // []申明析构数组

    // 行为未知的错误析构方式
    // delete[] pObject1; // 程序循环delete
    // delete pObject2; // 异常
}