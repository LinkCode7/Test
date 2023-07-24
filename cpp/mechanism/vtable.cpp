#include "vtable.h"

using namespace std;

namespace test_vtable
{
} // namespace test_vtable

void test_vtbl()
{
    return;

    using namespace test_vtable;

    Base    b;
    Derived d;

    unsigned long* pAddr = nullptr;

    pAddr = reinterpret_cast<unsigned long*>(&b);
    cout << "Address of vtable of Base is 0x" << (void*)*pAddr << endl;

    pAddr = reinterpret_cast<unsigned long*>(&d);
    cout << "Address of vtable of Derived is 0x" << (void*)*pAddr << endl;

    // SHOW_FUNC_ADDRESS(Base::f1);
    ShowVtableContent("Base", &b, 0);

    // SHOW_FUNC_ADDRESS(Base::f2);
    ShowVtableContent("Base", &b, 1);

    // SHOW_FUNC_ADDRESS(Base::f3);
    ShowVtableContent("Base", &b, 2);

    // SHOW_FUNC_ADDRESS(Derived::f1);
    ShowVtableContent("Derived", &d, 0);

    // SHOW_FUNC_ADDRESS(Derived::f2);
    ShowVtableContent("Derived", &d, 1);

    // SHOW_FUNC_ADDRESS(Derived::f3);
    ShowVtableContent("Derived", &d, 2);

    // SHOW_FUNC_ADDRESS(Derived::f4);
    ShowVtableContent("Derived", &d, 3);
}
