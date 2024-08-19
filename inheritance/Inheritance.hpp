#ifndef		INHERITANCE_HPP
# define	INHERITANCE_HPP

# include <string>

class Base
{
	public:
		Base(): baseName("baseName") {}
		~Base() {}

		virtual std::string getName() const { return baseName; }
		void setName(std::string i) { baseName += i; }

	protected:
		std::string	baseName;
};

class Derived1: public virtual Base
{
	public:
		Derived1(): derived1Name("Derived1Name") {}
		~Derived1() {}

		std::string getName() const override { return derived1Name; }

	protected:
		std::string	derived1Name;
};

class Derived2: public virtual Base
{
	public:
		Derived2(): derived2Name("Derived2Name") {}
		~Derived2() {}

		std::string getName() const override { return derived2Name; }

	protected:
		std::string	derived2Name;
};

class Diamond: public Derived1, public Derived2
{
	public:
		Diamond(): DiamondName("DiamondName") {}
		~Diamond() {}

		std::string getName() const override { return DiamondName; }

	protected:
		std::string	DiamondName;
};

#endif