#pragma once


/*
日期：年月日、星期
时间：
*/

/*
时长类：years,months,days(weeks)


boost::progress_timer是计时类
*/



namespace TestDate
{
	// date以天为单位的日期核心类
	// 时长类：年、月、日
	// 辅助类：日期区间、日期迭代器

	// 日期
	void test_date();

	// 日期时长，长度
	void test_date_duration();
	// 日期运算
	void calculate_date();

	// 日期区间
	void _date_period();

	// 日期迭代器
	void date_iterator();

	void static_function();

} // namespace TestDate









namespace TestTimeAndPTime
{
	// 时间长度
	void _time_duration();


	// 时间点
	void _p_time();
	// 时间区间
	void _time_period();

	// 时间迭代器
	void _time_iterator();

	// 格式化时间
	void format_time();

} // namespace TestTimeAndPTime