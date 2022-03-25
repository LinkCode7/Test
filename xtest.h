

#ifdef _DEBUG

#define ASSERT_EQ(a,b) EXPECT_EQ(a,b)
#define ASSERT_NE(a,b) EXPECT_NE(a,b)

#endif



#define EXPECT_EQ(a,b) if((a) != (b)) \
    { \
		xtest::OutputRed("[     FAIL ] "); \
        std::cout << #a << " not equal " << #b << std::endl; \
    } else { \
		xtest::OutputGreen("[       OK ] "); \
        std::cout << std::endl; \
    }

#define EXPECT_NE(a,b) if((a) == (b)) \
    { \
		xtest::OutputRed("[     FAIL ] "); \
        std::cout << #a << " not equal " << #b << std::endl; \
    } else { \
		xtest::OutputGreen("[       OK ] "); \
        std::cout << std::endl; \
    }

#define MAKE_CLASS_NAME(test_case_name, test_name)  MAKI_CLASS_NAME_I(test_case_name, test_name)
#define MAKI_CLASS_NAME_I(test_case_name, test_name) XTest_##test_case_name##_##test_name##_Test
#define XTEST_TEST(test_case_name,test_name) class MAKE_CLASS_NAME(test_case_name, test_name): \
    public ::xtest::_Test { \
    public: \
        MAKE_CLASS_NAME(test_case_name, test_name)(): ::xtest::_Test(#test_case_name, #test_name) \
        { \
            ::xtest::UnitTest::regist(std::shared_ptr<::xtest::_Test>(this)); \
        } \
        virtual void testBody(); \
        static MAKE_CLASS_NAME(test_case_name, test_name) * instance; \
}; \
MAKE_CLASS_NAME(test_case_name, test_name) * MAKE_CLASS_NAME(test_case_name, test_name) ::instance \
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
		_Test(const std::string &n1, const std::string& n2);
		virtual void testBody() = 0;
		std::string test_case_name;
		std::string test_name;
	private:
		_Test(const _Test&) = delete;
		_Test& operator=(const _Test&) = delete;
	};

	class UnitTest
	{
		std::vector<std::shared_ptr<_Test>> all_tests12;
	public:
		static UnitTest& getInstance() {
			static UnitTest opr;
			return opr;
		}
		static void regist(std::shared_ptr<_Test> const& a) {
			getInstance().all_tests12.push_back(a);
		}
		void Run();
	};

	void OutputRed(const char* str);
	void OutputGreen(const char* str);
}

#define RUN_ALL_TESTS() xtest::UnitTest::getInstance().Run();




//#define COLOR(msg, code) "\033[0;" #code "m" msg "\033[0m"
//#define RED(msg)     COLOR(msg, 31)
//#define GREEN(msg)   COLOR(msg, 32)
//#define YELLOW(msg)  COLOR(msg, 33)
//#define BLUE(msg)    COLOR(msg, 34)
