#pragma once





// 也许是意料之外的
void Char_CharArray();

namespace TestSizeOf
{
	void Unexpected();

	namespace ByteAlignmentTest
	{
		void Test();

		// 一个位域必须存储在同一个字节中，不能跨两个字节。
		// 如一个字节所剩空间不够存储另一位域时，应从下一单元起存放该位域。
		// 也可以有意使某位域从下一单元（字节）开始
		typedef struct
		{
			char a : 3; // 3位
			char b : 3;
			char c : 3;
			char d : 3;
			char e : 3;
		}test1;
		typedef struct
		{
			char a : 3;
			char b : 4;
			char c : 5;
			char d : 6;
			char e : 7;
		}test2;
		typedef struct
		{
			char a : 1;
			char b : 2;
			char c : 3;
			char d : 4;
			char e : 5;
		}test3;

		typedef struct {
			int a;
			char b;
			char d;
			long c;
		}test4;
		typedef struct {
			int a;
			char b;
			long c;
			char d;
		}test5;

	} // namespace ByteAlignmentTest



	namespace VirtualFunctionTest
	{
		void Test();

		class A
		{
		public:
			virtual void Get()
			{
				std::cout << "class A Get()\n";
			}

		private:
			int m_iAValue;
		};

		class B
		{
		public:
			virtual void Set()
			{
				std::cout << "class B Set()\n";
			}

		private:
			int m_iBValue;
		};

		class C :public A, public B
		{
		public:
			void Get()
			{
				std::cout << "class C Get()\n";
			}

			void Set()
			{
				std::cout << "class C Set()\n";
			}

		private:
			int m_iCValue;
		};

	} // namespace VirtualFunctionTest



	// 20190914
	namespace VPtrTest
	{
		int g_i = 0;

		void Test();
		void TestNotAboutSizeOf();

		class NoVirtual
		{
			int m_i;

		public:

			NoVirtual()
			{
				m_i = ++g_i;
			}

			void fun()
			{
				std::cout << "class NoVirtual fun()" << std::endl;
			}
		};

		class HaveVirtual :public NoVirtual
		{
			int m_ii;
		public:
			HaveVirtual() :m_ii(0) {}

			virtual void fun()
			{
				std::cout << "class HaveVirtual fun()" << std::endl;
			}
		};

	} // VPtrTest

} // namespace TestSizeOf
