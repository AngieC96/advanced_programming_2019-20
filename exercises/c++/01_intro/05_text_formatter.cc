//NON VA BENE perchè spezza le parole

#include <iostream>

int main(){
	int a = 8;
	//std::cout << "Inserisci la lunghezza massima: "<< std::endl;
	//std::cin >> a;
	std::string line;
	while(std::getline(std::cin,line)){
		if(line.length() > a){
			for(int i=0; i < a; i++)
				std::cout << line[i];
			std::cout << std::endl;
			for(int i=a; i <= line.length(); i++)
				std::cout << line[i];
			std::cout << std::endl;
		} else{
			std::cout << line << std::endl;
		}
	}
	std::cout << line << std::endl;
	return 0;
}
