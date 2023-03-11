#include "pch.h"
#include "SkiaSharedPtr.h"

class TestSkiaObject : public SkRefCnt
{
public:
	TestSkiaObject() {}
	~TestSkiaObject() {}
};

TEST(SkiaSharedPtr, basic)
{
	sk_sp<TestSkiaObject> pInt(new TestSkiaObject());

}