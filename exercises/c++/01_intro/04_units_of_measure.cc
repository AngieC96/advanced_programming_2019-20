#include <iostream>

int main(){
	
	int a;
	std::string strg;
	std::cout << "Insert a number with its unit of measure" << std::endl;
	std::cin >> a >> strg;
	
	std::cout << "The number according to the SI units is:" << std::endl;
	if(strg == "inch")
	{
		std::cout << a * 0.0254 << " m" << std::endl;
	} else if (strg == "atm") {
		std::cout << a*101325 << " Pa" << std::endl;
	} else if (strg == "bar") {
		std::cout << a*100000 << " Pa" << std::endl;
	}else if (strg == "Bhor") {
		std::cout << a*0.529177208*1e-10<<" m"<< std::endl;
	} else if (strg == "oz") { //oz = once
		std::cout << a*0.0295735<<" l"<< std::endl;
	} else {
		std::cout << "Unit of measure not supported for the conversion" << std::endl;
	}
	
	return 0;
}
