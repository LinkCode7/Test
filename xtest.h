#ifndef XTEST_H
#define XTEST_H
#include <string>

#ifdef _DEBUG
#define ASSERT_EQ(a,b) EXPECT_EQ(a,b)
#define ASSERT_NE(a,b) EXPECT_NE(a,b)
#endif



#define EXPECT_TRUE(a) if(!(a)) \
    { \
		xtest::OutputRed("[     FAIL ] "); \
		xtest::OutputRed(std::to_string(a)+" is false "); \
		std::cout << std::endl; \
    } else { \
		xtest::OutputGreen("[       OK ] "); \
		xtest::OutputGreen(std::to_string(a)+" is true "); \
		std::cout << std::endl; \
	}

#define EXPECT_EQ(a,b) if((a) != (b)) \
    { \
		xtest::OutputRed("[     FAIL ] "); \
		xtest::OutputRed(std::to_string(a)+" != " + std::to_string(b)); \
		std::cout << std::endl; \
    } else { \
		xtest::OutputGreen("[       OK ] "); \
		xtest::OutputGreen(std::to_string(a)+" = " + std::to_string(b)); \
		std::cout << std::endl; \
	}

#define EXPECT_NE(a,b) if((a) == (b)) \
    { \
		xtest::OutputRed("[     FAIL ] "); \
		xtest::OutputRed(std::to_string(a)+" != " + std::to_string(b)); \
		std::cout << std::endl; \
    } else { \
		xtest::OutputGreen("[       OK ] "); \
		xtest::OutputGreen(std::to_string(a)+" = " + std::to_string(b)); \
		std::cout << std::endl; \
	}

#define MAKE_CLASS_NAME(test_case_name, test_name)  MAKI_CLASS_NAME_I(test_case_name, test_name)
#define MAKI_CLASS_NAME_I(test_case_name, test_name) XTest_##test_case_name##_##test_name##Test
#define XTEST_TEST(test_case_name,test_name) class MAKE_CLASS_NAME(test_case_name, test_name): public ::xtest::_Test \
{ \
    public: \
        MAKE_CLASS_NAME(test_case_name, test_name)(): ::xtest::_Test(#test_case_name, #test_name) \
        { \
            ::xtest::UnitTest::regist(std::shared_ptr<::xtest::_Test>(this)); \
        } \
        void testBody() override; \
        static MAKE_CLASS_NAME(test_case_name, test_name) * instance; \
}; \
MAKE_CLASS_NAME(test_case_name, test_name) * MAKE_CLASS_NAME(test_case_name, test_name)::instance \
    = new MAKE_CLASS_NAME(test_case_name, test_name) ();\
void MAKE_CLASS_NAME(test_case_name, test_name)::testBody()

#define TEST(test_case_name, test_name) XTEST_TEST(test_case_name, test_name)


namespace xtest
{
	class UnitTest;

	class _Test
	{
		friend class UnitTest;
	public:
		_Test(const std::string& n1, const std::string& n2);
		virtual void testBody() = 0;
		std::string test_case_name;
		std::string test_name;
	private:
		_Test(const _Test&) = delete;
		_Test& operator=(const _Test&) = delete;
	};

	class UnitTest
	{
		std::vector<std::shared_ptr<_Test>> all_case;
	public:
		static UnitTest& getInstance() {
			static UnitTest opr;
			return opr;
		}
		static void regist(std::shared_ptr<_Test> const& a) {
			getInstance().all_case.push_back(a);
		}
		void Run();
	};

	void OutputRed(const std::string& str);
	void OutputGreen(const std::string& str);
}

#define RUN_ALL_TESTS() xtest::UnitTest::getInstance().Run();





#define _LOOK_GOOGLE_TEST_MECHANISM

#ifdef _LOOK_GOOGLE_TEST_MECHANISM
#define TEST_MECHANISM(test_case_name, test_name) class _mechanism_ : public ::xtest::_Test\
{\
public:\
	_mechanism_() : ::xtest::_Test(#test_case_name, #test_name)\
	{\
		::xtest::UnitTest::regist(std::shared_ptr<::xtest::_Test>(this));\
	}\
	static _mechanism_* _instance;\
	void testBody() override;\
};\
_mechanism_* _mechanism_::_instance = new _mechanism_();\
void _mechanism_::testBody()
// 这下面就是函数体了{...}
// key:静态对象的初始化在main之前
#endif

#endif // !XTEST_H
