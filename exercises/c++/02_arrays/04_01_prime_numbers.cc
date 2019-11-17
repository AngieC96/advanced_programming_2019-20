#include <iostream>
#include <vector>

int main(){
	
	//First method: allocation of one big array
	std::vector<int> primes;
	unsigned int number{100};
	unsigned int i{2};
    while (i < number){
    	unsigned int j=2;
        while(i%j){
        	j++;
        }
        if (j==i){
			primes.push_back(i);
        }
        i++;
    }

	std::cout << "The prime numbers less than " << number << " are:" << std::endl;
	for(auto k = 0u; k < primes.size(); ++k) {
		std::cout << primes.at(k) << std::endl;
	}

	return 0;
}
