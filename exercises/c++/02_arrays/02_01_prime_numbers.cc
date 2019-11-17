#include <iostream>

int main(){
	
	//First method: allocation of one big array
	int primes[100];
	unsigned int number{100};
	unsigned int n_primes{0};
	unsigned int i{2};
    while (i < number){
    	unsigned int j=2;
        while(i%j){
        	j++;
        }
        if (j==i){
			primes[n_primes] = i;
            n_primes++;
        }
        i++;
    }

	std::cout << "The prime numbers less than " << number << " are:" << std::endl;
	for(std::size_t k{0}; k < n_primes; ++k) {
		std::cout << primes[k] << std::endl;
	}

	return 0;
}
