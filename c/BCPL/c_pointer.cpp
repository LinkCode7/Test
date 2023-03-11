#include "pch.h"
#include <any>

enum TestAlignType : uint8_t
{
	eTAT_Left,
	eTAT_Center,
	eTAT_Right,
};

TEST(c_pointer, convert_void_star)
{
	void* pEnum = (void*)eTAT_Center;
	TestAlignType enumValue = (TestAlignType)reinterpret_cast<uint64_t>(pEnum);

	void* pBool = (void*)true;
	//bool boolValue = reinterpret_cast<bool>(pBool);
	//bool boolValue = reinterpret_cast<bool>((int*)pBool);
	bool boolValue = (bool)reinterpret_cast<uint64_t>(pBool); // 较好的转换

	void* pInt = (void*)10001;
	uint64_t intValue = reinterpret_cast<uint64_t>(pInt);

	// C++的方式
	std::any anyValue = std::make_any<int>(100);
	if (anyValue.has_value())
		std::cout << std::any_cast<int>(anyValue) << std::endl;
}