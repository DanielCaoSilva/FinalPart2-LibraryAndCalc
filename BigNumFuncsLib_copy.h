#pragma once
#include <vector>
#include <iostream>
namespace BigNumFuncs
{
	class BigNum
	{
	private:
		std::vector<int> num;
		int size = num.size();
	public:
		BigNum(std::vector<int>n);// : num(n) {}
		BigNum operator +(BigNum b);
		BigNum operator -(BigNum b);
		BigNum operator *(BigNum b);
		BigNum operator /(BigNum b);
		BigNum operator %(BigNum b);
		int compare(std::vector<int> a, std::vector<int> b);
		void print();
	};
}