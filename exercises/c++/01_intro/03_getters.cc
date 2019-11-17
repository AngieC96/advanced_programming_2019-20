#include <iostream>

int get_int(){
	bool check_cin, check_int;
	int x,y;
	float i;
	do{
		std::cout << "Insert an integer:" << std::endl;
		check_cin = (bool)(std::cin >> i);
		std::cin.clear();
		std::cin.ignore();
		check_int = true;
		if(check_cin){
			x = (int) i;
			x = x*10;
			y = (int)(i * 10);
			if (x != y) {
				check_int = false;
			}
		}
	} while(!(check_cin && check_int));
	return i;
}

double get_double(){
	double i;
	while(!(std::cin >> i)){
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Insert a  double!" << std::endl;
	}
	return i;
}

int main(){	

	int a;
	a = get_int();
	std::cout << "Your integer is " << a << std::endl;

	double b;
	std::cout << "Insert a double:" << std::endl;
	b = get_double();
	std::cout << "Your double is " << b << std::endl;
	
	return 0;
}
