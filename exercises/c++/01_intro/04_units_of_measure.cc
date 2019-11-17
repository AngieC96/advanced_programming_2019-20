#include <iostream>

constexpr double inch2meter{0.0254};
constexpr double meter2inch{1./inch2meter};
constexpr int atm2Pa{101325};
constexpr int bar2Pa{100000};
constexpr double Bohr2meter{0.529177208*1e-10};
constexpr double ounces2liter{0.0295735};


int main(){
	
	int a;
	std::string strg;
	std::cout << "Insert a number with its unit of measure" << std::endl;
	std::cin >> a >> strg;
	
	std::cout << "The number according to the SI units is:" << std::endl;
	if(strg == "inch")
	{
		std::cout << a * inch2meter << " m" << std::endl;
	} else if (strg == "atm") {
		std::cout << a*atm2Pa << " Pa" << std::endl;
	} else if (strg == "bar") {
		std::cout << a*bar2Pa << " Pa" << std::endl;
	}else if (strg == "Bhor") {
		std::cout << a*Bohr2meter<<" m"<< std::endl;
	} else if (strg == "oz") { //oz = ounces = once
		std::cout << a*ounces2liter<<" l"<< std::endl;
	} else {
		std::cout << "Unit of measure not supported for the conversion" << std::endl;
	}
	
	return 0;
}
