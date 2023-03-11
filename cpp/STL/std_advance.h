#pragma once

// 迭代器相应型别之 iterator_category
/*
根据移动特性与施行操作，迭代器分为：
// ++
InputIterator：只读
OutputIterator：只写
FarwardIterator：允许写入型算法（replace）在次迭代器指向的空间上读写
// ++,--
BidirectionalIterator：双向移动（如：逆向拷贝某个范围内的元素）
// 
RandomAccessIterator：涵盖所有指针算数能力（++,--,p+n,p-n,p[n],p1-p2,p1<p2,p1!=p2,p1==p2）

*/


// 1.这些类只做标记用
struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag :public forward_iterator_tag {};
struct random_access_iterator_tag :public bidirectional_iterator_tag {};


// 2.重载不同版本的 advance()
template<class InputIterator, class Distance>
void __advance(InputIterator it, Distance n, input_iterator_tag) // 不指定形参，用来激活函数重载
{
	// 单向，逐一前进
	while (n--) ++it;
}

template<class BidIrectionalIterator, class Distance>
void __advance(BidIrectionalIterator it, Distance n, forward_iterator_tag)
{
	// 调用
	__advance(it, n, input_iterator_tag());
}

template<class BidIrectionalIterator, class Distance>
void advance_BI(BidIrectionalIterator it, Distance n, bidirectional_iterator_tag)
{
	// 双向，逐一前进
	if (n >= 0)
		while (n--) ++it;
	else
		while (n++) --it;
}

template<class RandomAccessIterator, class Distance>
void __advance(RandomAccessIterator it, Distance n, random_access_iterator_tag)
{
	// 双向，跳跃前进
	it += n;
}




// 4.利用trait添加一个型别
template<class I>
struct iterator_trait
{
	typedef typename I::iterator_category iterator_category;
};

// 为“原生指针”设计的偏特化(partial specialization)
template<class T>
struct iterator_trait<T*>
{
	// “原生指针”属于Random Access Iterator,应属于最强范围的
	typedef random_access_iterator_tag iterator_category;
};

// 为“原生指针”const版(point-to-const)设计的偏特化
template<class T>
struct iterator_trait<const T*>
{
	typedef random_access_iterator_tag iterator_category;
};



// 3.提供一个对外使用的接口
template<class InputIterator, class Distance>
void MyAdvance(InputIterator it, Distance n)
{
	// iterator_category()产生一个关于迭代器类型临时对象
	__advance(it, n, iterator_trait<InputIterator>::iterator_category());
}
