#ifndef		INHERITANCE_HPP
# define	INHERITANCE_HPP

# include <string>

class Base
{
	public:
		Base(): number1(0), number2(0) {}
		Base(int n1, int n2): number1(n1), number2(n2) {}
		~Base() {}

		int 				getNumber1() const { return number1; }
		int 				getNumber2() const { return number2; }

	protected:
		int			number1;
		int			number2;
};

class Derived1: public virtual Base
{
	public:
		Derived1() { Base::number1 = 1; }
		~Derived1() {}
};

class Derived2: public virtual Base
{
	public:
		Derived2() { }
		~Derived2() {}
};

class Diamond: public Derived1, public Derived2
{
	public:
		Diamond() {}
		~Diamond() {}
};

#endif