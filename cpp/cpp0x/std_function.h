#ifndef STD_FUNCTION_H
#define STD_FUNCTION_H

class TestFunction
{
    std::function<int()> _fun;

public:
    TestFunction(std::function<int()> const& fun) : _fun(fun) {}

    bool valid() const { return _fun != nullptr; }
    int  result() const { return _fun(); }
};

#endif // !STD_FUNCTION_H
