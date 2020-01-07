#include <iostream>

int main(){
	std::string line;
	std::string line2;
	std::getline(std::cin,line);
	int k{1};
	while(std::getline(std::cin,line2)){
		if (line == line2){
			k += 1;
		}
		else {
			std::cout << k << " " << line << std::endl;
			k = 1;
			line = line2;
		}
	}
	std::cout << k << " " << line << std::endl;
	return 0;
}
