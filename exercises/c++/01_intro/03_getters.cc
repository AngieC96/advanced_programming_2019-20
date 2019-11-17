#include <iostream>
int get_int(){
	float i, flt;
	while(!(std::cin >> i)){ //PROBLEMA: se prende un float poi è a posto e non fa il while ma esce
		std::cout << "Insert an integer!" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		flt = (int) i;
		if (flt != i) {
			continue;
		}
	}
	return i;
}

int get_int4(){
	float i;
	int x,y;
	while((std::cin >> i)){
		std::cout << "Insert an integer!" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		x = (int) i;
		x = x*10;
		y = (int)(i * 10);
		if (x != y) {
			std::cout << "It's NOT an integer!" << std::endl;
			continue;
		} else {
			break;
		}
	}
	return i;
}

int get_int3(){
	float i, flt;
	do{
		std::cout << "Insert an integer!" << std::endl;
		std::cin >> i;
		std::cin.clear();
		std::cin.ignore();
		flt = (int) i;
		if (flt != i) {
			continue;
		}
	} while(!(std::cin));
	return i;
}

int get_int(){
	int flt;
	float i;
	while(!(std::cin >> i)){
		std::cout << "Insert an integer number!\n" << std::endl;
		std::cin.clear();
		std::cin.ignore();
		
			
		if (flt) continue
	}
	return i;
}

int get_int2(){
	int in, flt;
	float i;
	while(!(in) || flt){
		in = (std::cin >> i)
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Insert an integer number!\n" << std::endl;
	}
	return i;
}

int get_double(){
	double i;
	while(!(std::cin >> i)){
		std::cin.clear();
		std::cin.ignore();
		std::cout << "Insert an integer number!\n" << std::endl;
	}
	return i;
}

int main(){

	//int i;
	//std::cin >> i;
	//std::cout << boolalpha << static_cast<bool>(std::cin>>a) << std::endl;
	//std::cout << (bool)(std::cin >> i) << std::endl;	
	
//	int a;
//	std::cout << "Insert an integer 1:" << std::endl;
//	a = get_int();
//	std::cout << "Your integer is " << a << std::endl;
//	std::cin.clear();

	int a2;
	a2 = get_int2();
	std::cout << "Your integer is " << a2 << std::endl;
	std::cin.clear();

//	int a3;
//	std::cout << "Insert an integer 3:" << std::endl;
//	a3 = get_int3();
//	std::cout << "Your integer is " << a3 << std::endl;
//	std::cin.clear();

	double b;
	std::cout << "Insert a double:" << std::endl;
	b = get_double();
	std::cout << "Your double is " << b << std::endl;
	return 0;
}
