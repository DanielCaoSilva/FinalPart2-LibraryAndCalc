/*!
 *  \brief     Big Number Class (BigNum)
 *  \details   This class is used to do basic arithmetic on large positive integers. 
 *  \author    Daniel Silva
 *  \version   1.0
 *  \date      2019
 *  \bug       In order to do the operations, the size of the big numbers must be the same. (ie 999*001)
 *  \warning   A work in progress...
 *  \copyright Cal Poly Pomona
 */
#pragma once
#include <vector>
#include <iostream>
namespace BigNumFuncs
{
	//!  Big Number class. Called BigNum. 
/*!
  This class is used to store large numbers that exceed the standard data types.
  It can handle arithmetic with only positve integers.
  The arithmetic functions include: 
	Addition, Subtraction, Mulitplication, Division and Modulos
  Addiontional functionality include:
	Printing the number on the console and comparing two vectors of type (int)
*/
	class BigNum
	{
	private:
		
	public:
		std::vector<int> num;/*!< The vector that the number is stored in. One digit per vector location. */
		int size = num.size();/*!< The size of the vector where the big number is stored.*/

		//! The constructor.
	/*!
	  The requires std::vector<int> as its parameter to initialize the member variables. 
	*/
		BigNum(std::vector<int>n);

		//! Adding two BigNum together. While operator overloading the + symbol.
	/*!
	  \param b a BigNum positive integer.
	  \return The sum of the two BigNum. 
	*/
		BigNum operator +(BigNum b);

		//! Subtracting two BigNum. While operator overloading the - symbol. 
	/*!
	  \param b a BigNum positive integer and must be smaller than the main BigNum.
	  \return The difference of the two BigNum.
	*/
		BigNum operator -(BigNum b);

		//! Multiplying two BigNum together. While operator overloading the * symbol.
	/*!
	  \param b a BigNum positive integer.
	  \return The product of the two BigNum.
	*/
		BigNum operator *(BigNum b);

		//! Dividing two BigNum together. While operator overloading the / symbol.
	/*!
	  \param b a BigNum positive integer.
	  \return The quotient of the two BigNum.
	*/
		BigNum operator /(BigNum b);

		//! Mod operation of two BigNum together. While operator overloading the % symbol.
	/*!
	  \param b a BigNum positive integer.
	  \return The remainder of the two BigNum when divided.
	*/
		BigNum operator %(BigNum b);

		//! Compares two vectors of type intger.
	/*!
	  \param a an integer vector.
	  \param b an integer vector.
	  \return 1 if vector a is larger, 2 if vector b is larger and 0 if neither.  
	*/
		int compare(std::vector<int> a, std::vector<int> b);

		//! Prints the BigNum to the console using std::cout<<
	/*!
	  \param none
	  \return Void. It prints to the console. 
	*/
		void print();
	};
}