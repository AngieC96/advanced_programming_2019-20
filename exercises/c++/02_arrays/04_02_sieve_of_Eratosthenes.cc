#include <iostream>
#include <cmath>
#include <vector>

int main(){

	std::cout << "Please insert the array length: ";
	std::size_t n;
	std::cin >> n;
	std::vector<int> primes;

	for(std::size_t k{2}; k <= n; ++k) {
		primes.push_back(k);
	}

	std::cout << "The prime numbers less than " << n << " are:" << std::endl;
	for(std::size_t k{2}; k < ((int)std::sqrt(n)) + 1; ++k) {
		if (primes.at(k - 2) != 0) {
			for(std::size_t z{k}; k*z - 2 < primes.size(); ++z) {
				primes.at(k*z - 2) = 0;
			}
		}
	}

	for(std::size_t k{0}; k < primes.size(); ++k) {
		if (primes.at(k) != 0)
			std::cout << primes.at(k) << std::endl;
		//else
			//primes.erase(primes.begin()+k);
	}

	return 0;
}
