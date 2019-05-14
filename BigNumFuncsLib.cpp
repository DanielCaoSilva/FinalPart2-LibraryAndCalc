#include "pch.h" 

#include "BigNumFuncsLib.h" 

#include <vector>
#include <iostream>

#include <stdexcept>

namespace BigNumFuncs
{
	BigNum::BigNum(std::vector<int>n) : num(n) {}
	BigNum BigNum::operator +(BigNum b)
	{
		int bigSz;
		if (num.size() >= b.num.size())
			bigSz = num.size();
		else
			bigSz = b.num.size();
		std::vector<int> c(bigSz, 0);
		std::vector<int> nA(bigSz, 0);
		std::vector<int> nB(bigSz, 0);
		//Copies old vect into new vect with 0s at the end
		for (int i = 0; i < num.size(); i++)
			nA[i] = (num[i]);
		for (int i = 0; i < b.num.size(); i++)
			nB[i] = (b.num[i]);
		std::reverse(nA.begin(), nA.end());
		std::reverse(nB.begin(), nB.end());
		int t = 0;
		for (int i = 0; i < bigSz; i++)
		{
			int j;
			j = nA[i] + nB[i] + t;
			//printf("\nj:%d\n",j);
			t = j / 10 % 10;
			//printf("\nt:%d\n", t);
			c[i] = j % 10;
		}
		if (t != 0)
			c.push_back(t);

		std::reverse(c.begin(), c.end());
		return BigNum(c);
	}
	BigNum BigNum::operator -(BigNum b)
	{
		int comp = compare(num, b.num);
		std::vector<int> diff;
		std::vector<int> nA(size, 0);
		std::vector<int> nB(size, 0);
		int check = 0;
		for (int i = 0; i < size; i++)
		{
			if (num[i] == b.num[i])
			{
				check++;
			}
		}
		if (check == size)
		{
			return BigNum(nA);
		}
		if (comp == 2)
		{
			for (int i = 0; i < num.size(); i++)
				nB[i] = (num[i]);
			for (int i = 0; i < b.num.size(); i++)
				nA[i] = (b.num[i]);
		}
		else
		{
			for (int i = 0; i < num.size(); i++)
				nA[i] = (num[i]);
			for (int i = 0; i < b.num.size(); i++)
				nB[i] = (b.num[i]);
		}
		int diffLen = num.size() - b.num.size();
		int t = 0;
		for (int i = b.num.size() - 1; i >= 0; i--)
		{
			int j;
			j = (nA[i + diffLen] - 0) - (nB[i] - 0) - t;
			if (j < 0)
			{
				j = j + 10;
				t = 1;
			}
			else
				t = 0;
			//t = j / 10 % 10;
			//diff.push_back(j % 10);
			diff.push_back(j + 0);
		}
		/*if (t != 0)
			diff.push_back(t);*/
		for (int i = num.size() - b.num.size() - 1; i >= 0; i--)
		{
			if (nA[i] == 0 && t)
			{
				diff.push_back(9);
				continue;
			}
			int sub = ((nA[i] - 0) - t);
			if (i > 0 || sub > 0) // remove preceding 0's 
				diff.push_back(sub + 0);
			t = 0;

		}
		std::reverse(diff.begin(), diff.end());
		return BigNum(diff);
	}
	BigNum BigNum::operator *(BigNum b)
	{
		std::vector<int> nA(size, 0);
		std::vector<int> nB(b.num.size(), 0);
		//Copies old vect into new vect with 0s at the end
		for (int i = 0; i < num.size(); i++)
			nA[i] = (num[i]);
		for (int i = 0; i < b.num.size(); i++)
			nB[i] = (b.num[i]);
		//std::reverse(nA.begin(), nA.end());
		//std::reverse(nB.begin(), nB.end());
		//std::reverse(num.begin(), num.end());
		int n1 = num.size();
		int n2 = b.num.size();
		if (n1 == 0 || n2 == 0)
			return b;// go back and fix

		// will keep the result number in vector 
		// in reverse order 
		std::vector<int> result(n1 + n2, 0);

		// Below two indexes are used to find positions 
		// in result.  
		int i_n1 = 0;
		int i_n2 = 0;

		// Go from right to left in num1 
		for (int i = n1 - 1; i >= 0; i--)
		{
			int carry = 0;
			int n1 = nA[i] - 0;

			// To shift position to left after every 
			// multiplication of a digit in num2 
			i_n2 = 0;

			// Go from right to left in num2              
			for (int j = n2 - 1; j >= 0; j--)
			{
				// Take current digit of second number 
				int n2 = nB[j] - 0;

				// Multiply with current digit of first number 
				// and add result to previously stored result 
				// at current position.  
				int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

				// Carry for next iteration 
				carry = sum / 10;

				// Store result 
				result[i_n1 + i_n2] = sum % 10;

				i_n2++;
			}

			// store carry in next cell 
			if (carry > 0)
				result[i_n1 + i_n2] += carry;

			// To shift position to left after every 
			// multiplication of a digit in num1. 
			i_n1++;
		}

		// ignore '0's from the right 
		int i = result.size() - 1;
		while (i >= 0 && result[i] == 0)
			i--;

		// If all were '0's - means either both or 
		// one of num1 or num2 were '0' 
		//if (i == -1)
			//return "0";

		// generate the result string 
		//string s = "";

		//while (i >= 0)
			//s += std::to_string(result[i--]);

		//return s;
		std::reverse(result.begin(), result.end());
		BigNum out(result);
		return out;
	}
	BigNum BigNum::operator /(BigNum b)
	{
		//std::vector<int>count;

		std::vector<int> nA(size, 0);
		std::vector<int> nB(b.num.size(), 0);
		//Copies old vect into new vect with 0s at the end
		for (int i = 0; i < num.size(); i++)
			nA[i] = (num[i]);
		for (int i = 0; i < b.num.size(); i++)
			nB[i] = (b.num[i]);
		//std::reverse(nA.begin(), nA.end());
		//std::reverse(nB.begin(), nB.end());
		//std::reverse(num.begin(), num.end());
		std::vector<int>q;
		std::vector<int> rez(num.size());
		rez = num;
		int comp = 1;
		std::vector<int> count(size, 0);
		std::vector<int> one(size, 0);
		one[0] = 1;
		std::reverse(one.begin(), one.end());
		BigNum rezz(rez);
		BigNum countt(count);
		BigNum onee(one);
		//printVec(nA);
		//printVec(nB);
		//onee.print();
		int check = 0;
		for (int i = 0; i < size; i++)
		{
			if (num[i] == b.num[i])
			{
				check++;
			}
		}
		//std::cout << check<<size;
		if (check == size)
		{
			return onee;
		}
		while (comp == 1)
		{
			//std::cout << "\n"; rezz.print();b.print(); std::cout << "\n";

			comp = compare(rezz.num, b.num);
			//std::cout << comp;
			if ((comp != 1) && (comp != 0))
			{
				//std::cout << "in here";
				break;
			}
			//std::reverse(rezz.num.begin(), rezz.num.end());
			rezz = rezz - (b);
			//rezz.print();
			countt = countt + (onee);
			//std::cout << "\n"; countt.print(); std::cout << "\n";
			//std::cout << "in while\n";
		}
		//countt = countt.add(onee);
		return countt;
	}
	BigNum BigNum::operator %(BigNum b)
	{
		std::vector<int> nA(size, 0);
		std::vector<int> nB(b.num.size(), 0);
		//Copies old vect into new vect with 0s at the end
		for (int i = 0; i < num.size(); i++)
			nA[i] = (num[i]);
		for (int i = 0; i < b.num.size(); i++)
			nB[i] = (b.num[i]);
		//std::reverse(nA.begin(), nA.end());
		//std::reverse(nB.begin(), nB.end());
		BigNum a(nA);
		BigNum bNew(nB);
		//std::cout << "a:"; a.print();
		//b.print();
		BigNum div = a / (bNew);
		//div.print();
		//std::reverse(div.num.begin(), div.num.end());
		BigNum x = div * (b);
		//x.print();
		std::reverse(x.num.begin(), x.num.end());
		int j = x.num.size() - 1;
		while (j >= 0 && x.num[j] == 0)
		{
			x.num.pop_back();
			j--;
		}
		std::reverse(x.num.begin(), x.num.end());
		//x.print();
		//a.print();
		BigNum r = a - (x);
		//a.print();
		//r.print();
		return r;
	}
	int BigNum::compare(std::vector<int> a, std::vector<int> b) 
	{
		if (a.size() > b.size())
			return 1;
		if (b.size() > a.size())
			return 2;
		int r = 0;
		for (int i = 0; i < a.size(); i++)
		{
			if (a[i] > b[i])
			{
				r = 1;
				break;
			}
			if (b[i] > a[i])
			{
				r = 2;
				break;
			}
		}
		return r;
	}
	void BigNum::print()
	{
		std::cout << "The vector elements are : ";

		for (int i = 0; i < num.size(); i++)
			std::cout << num.at(i) << ' ';
	}
}