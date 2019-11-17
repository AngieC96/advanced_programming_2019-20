#include <iostream>

int main(){
	int a{8}, k{-1};
	//std::cout << "Inserisci la lunghezza massima: "<< std::endl;
	//std::cin >> a;
	std::string line;
	while(std::getline(std::cin,line)){
		if(line.length() > a){
			for(int j=0; j < a; j++)
				if(line[j] == ' ')
					k = j;
			for(int j=0; j < k; j++)
				std::cout << line[j];
			if (k > 0) std::cout << std::endl;
			//I erase the space betwen the words
			for(int j=k+1; j <= line.length(); j++)
				std::cout << line[j];
			std::cout << std::endl;
		} else {
			std::cout << line << std::endl;
		}
	}
	std::cout << line << std::endl;
	return 0;
}
