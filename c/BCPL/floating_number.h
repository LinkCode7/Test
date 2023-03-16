#ifndef FLOATING_NUMBER_H
#define FLOATING_NUMBER_H
#include <vector>

std::vector<int> get_every_digit(int num)
{
	if (num == 0)
		return {0};

	std::vector<int> result;
	while (num != 0)
	{
		result.emplace_back(num % 10);
		num /= 10;
	}
	return result;
}

template<typename T>
bool is_same_container(const std::vector<T>& result, const std::vector<T>& expect)
{
	auto size = expect.size();
	if (size != result.size())
		return false;
	for (auto i = 0; i < size; ++i)
	{
		if (expect[i] != result[i])
			return false;
	}
	return true;
}

#endif // !FLOATING_NUMBER_H