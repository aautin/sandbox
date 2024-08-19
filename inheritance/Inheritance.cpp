#include <iostream>

#include "Inheritance.hpp"

int main() {
	Base p1;
	std::cout << p1.getNumber1() << std::endl;
	std::cout << p1.getNumber2() << std::endl;

	std::cout << std::endl;

	Derived1 p2;
	std::cout << p2.getNumber1() << std::endl;
	std::cout << p2.getNumber2() << std::endl;

	std::cout << std::endl;

	Derived2 p3;
	std::cout << p3.getNumber1() << std::endl;
	std::cout << p3.getNumber2() << std::endl;

	std::cout << std::endl;

	Diamond p4;
	std::cout << p4.getNumber1() << std::endl;
	std::cout << p4.getNumber2() << std::endl;
}
