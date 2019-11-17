#include <iostream>

int main(){
	
	//Second method: every time it's found a new prime number the size of the previous `primes` array is increased
	unsigned int n_primes{1};
	int* primes{new int[n_primes]};
	unsigned int number{100};
	primes[n_primes-1] = 2;
	unsigned int i{3};

    while (i < number){
    	unsigned int j=2;
        while(i%j){
        	j++;
        }
        if (j==i){
			int* primes2{new int[n_primes+1]};
			for(std::size_t k{0}; k < n_primes; ++k)
				primes2[k] = primes[k];
			delete[] primes;
			primes=primes2;
			primes[n_primes] = i;
            n_primes += 1;

        }
        i++;
    }

	std::cout << "The prime numbers less than " << number << " are:" << std::endl;
	for(std::size_t k{0}; k < n_primes; ++k) {
		std::cout << primes[k] << std::endl;
	}

	delete[] primes;

	return 0;
}
