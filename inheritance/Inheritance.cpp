#include <iostream>

#include "Inheritance.hpp"

int main() {
	Base p1;
	std::cout << p1.getName() << std::endl;

	std::cout << std::endl;

	Derived1 p2;
	std::cout << p2.Base::getName() << std::endl;
	std::cout << p2.getName() << std::endl;

	std::cout << std::endl;

	Derived2 p3;
	std::cout << p3.Base::getName() << std::endl;
	std::cout << p3.getName() << std::endl;

	std::cout << std::endl;

	Diamond p4;
	p4.Derived2::Base::setName("2");
	p4.Derived1::Base::setName("1");
	std::cout << p4.Derived1::Base::getName() << std::endl;
	std::cout << p4.Derived2::Base::getName() << std::endl;
	std::cout << p4.Derived2::getName() << std::endl;
	std::cout << p4.getName() << std::endl;
}
