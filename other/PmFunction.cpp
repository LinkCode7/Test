#include "PmFunction.h"

namespace PmFunction
{
bool Pow(double value, int num, double& result)
{
    if (num < 0)
        return false;
    else if (num == 0)
    {
        if (value != 0)
            result = 1;
        else
            result = 0;
        return true;
    }
    else
    {
        result = value;
        for (int i = 1; i < num; i++)
        {
            result *= value;
        }

        //
        return true;
    }
}

} // namespace PmFunction
