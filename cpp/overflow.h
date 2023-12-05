#ifndef OVERFLOW_H
#define OVERFLOW_H
#include <memory>

class ModelBase
{
public:
    virtual ~ModelBase() { std::cout << "~ModelBase()\n"; }
};
using ModelBaseSp = std::shared_ptr<ModelBase>;

class ModelA : public ModelBase
{
public:
    ~ModelA() { std::cout << "~ModelA()\n"; }
};
using ModelASp = std::shared_ptr<ModelA>;

////////////////////////////////////////////////////////////////////////

class ComponentBase
{
public:
    virtual ~ComponentBase() { std::cout << "~ComponentBase()\n"; }
};
using ComponentBaseSp = std::shared_ptr<ComponentBase>;

class ComponentA : public ComponentBase
{
    ModelASp _model;

public:
    // 智能指针陷阱，这里会导致两个shared_ptr对象管理model指向的内存
    ComponentA(ModelA* model) : _model(model) {}

    ~ComponentA() { std::cout << "~ComponentA()\n"; }
};

#endif // !OVERFLOW_H
