#include "overflow.h"

ComponentBaseSp getComponent(ModelBaseSp model)
{
    if (auto sub = dynamic_cast<ModelA*>(model.get()); sub)
        return std::make_shared<ComponentA>(sub);

    return nullptr;
}

TEST(shared_ptr, wild_pointer)
{
    if (0)
    {
        ModelBaseSp model     = std::make_shared<ModelA>();
        auto        component = getComponent(model);
    }
}