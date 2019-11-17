#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm> //for std::remove

int main(){

	std::cout << "Please insert the array length: ";
	std::size_t n;
	std::cin >> n;
	std::vector<int> primes;

	for(std::size_t k{2}; k <= n; ++k) {
		primes.push_back(k);
	}

	std::cout << "The prime numbers less than " << n << " are:" << std::endl;
	for(std::size_t k{2}; k < ((std::size_t)std::sqrt(n)) + 1; ++k) {
		for(std::size_t z{k}; k*z - 2 < primes.size(); ++z) {
			primes.erase(std::remove(primes.begin(), primes.end(), k*z), primes.end());
		}
	}

	for(std::size_t k{0}; k < primes.size(); ++k) {
			std::cout << primes.at(k) << std::endl;
	}

	return 0;
}
