#include "pch.h"
#include "PmFunction.h"


namespace PmFunction
{
	bool Pow(double value, int num, double & result)
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


	template<class T>
	std::string CStrCut0(const T& value)
	{
		std::string strValue = PmFunction::CStr(value);

		int position = strValue.Find(_T("."));
		if (position >= 0)
		{
			// 去除浮点字符串右边无效的0：SC20.0100 -> SC20.01
			int length = strValue.GetLength();
			for (int i = 0; i < length - position; ++i)
			{
				// 从右边开始取字符，看是不是 0 或 . 
				std::string strTemp = strValue.Right(i + 1);

				// 取左边第一个，因为strTemp右边的已经比较过了
				if (strTemp.Left(1) != _T("0"))
				{
					strValue = strValue.Left(length - i);
					break;
				}
			}

			if (strValue.Right(1) == _T("."))
				strValue = strValue.Left(strValue.GetLength() - 1);
		}

		return strValue;
	}
}
