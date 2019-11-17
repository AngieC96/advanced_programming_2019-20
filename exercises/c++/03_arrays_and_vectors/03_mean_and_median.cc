#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){

	std::vector<double> numbers;
	std::string line;
    while(std::getline(std::cin, line)){
		numbers.push_back(std::stod(line));
	}
	
	std::size_t n = numbers.size();
	std::cout << "The number is " << n << std::endl;

	double sum{0};
	for(std::size_t i = 0; i < numbers.size(); ++i){
		sum += numbers.at(i);
	}
	
	double mean = sum/n;
	std::cout << "The mean is " << mean << std::endl;

	std::sort(numbers.begin(), numbers.end());

	for(std::size_t i = 0; i < numbers.size(); ++i){
		std::cout << numbers.at(i) << std::endl;
	}
	
	double median;
	if(n % 2) {
		median = numbers.at(((n+1)/2)-1);
	} else {
		median = (numbers.at((n/2)-1) + numbers.at(n/2))/2;
	}
	std::cout << "The median is " << median << std::endl;

//	(condizione) ? vero : falso;

	return 0;
}
