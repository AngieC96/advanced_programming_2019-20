#include <iostream>
#include <cmath> 

int main(){

	std::cout << "Please insert the array length: ";
	std::size_t n;
	std::cin >> n;
	int* primes{new int[n - 1]};

	for(std::size_t k{2}; k <= n; ++k) {
		primes[k-2] = k;  //The numbers starts from 2 while the array starts from 0
	}

	std::cout << "The prime numbers less than " << n << " are:" << std::endl;
	for(std::size_t k{2}; k < ((int)std::sqrt(n)) + 1; ++k) {
		if (primes[k - 2] != 0) {
			for(std::size_t z{k}; k*z - 2 < n - 1; ++z) {
				primes[k*z - 2] = 0;
			}
		}
	}

	for(std::size_t k{0}; k < n - 1; ++k) {
		if (primes[k] != 0)
			std::cout << primes[k] << std::endl;
	}

	delete[] primes;

	return 0;
}
