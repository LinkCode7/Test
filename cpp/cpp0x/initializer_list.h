#pragma once






class Fool
{
public:
	Fool(int a, int b) : a_(a), b_(b) {}

private:

	int a_;
	int b_;
};




class MagicFool
{
public:
	MagicFool(std::initializer_list<int> list)
	{
		for (std::initializer_list<int>::iterator it = list.begin(); it != list.end(); ++it)
		{
			m_arr.push_back(*it);
		}
	}

private:
	std::vector<int> m_arr;
};