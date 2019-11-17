#include <iostream>

template <typename T> T* array(const std::size_t m){
	
	T val;
	T* arr{new T[m]};
	std::cout << "Insert the values of the array: " << std::endl;
	for (std::size_t i{0}; i < m; ++i){
		std::cin >> val;
    	arr[i] = val;
	}

	return arr;
}

template <typename T> void print_arr(T* array, const std::size_t m){
	std::cout << "The array is: " << std::endl;
	for (std::size_t i{0}; i < m; ++i)
		std::cout << "arr[" << m-1-i << "] = " << array[m-1-i] <<std::endl;
}

int main(){
	
	std::cout << "Insert the length of the array: " ;
	std::size_t n_1;
	std::cin >> n_1;

	int* a{array<int>(n_1)};
	print_arr(a, n_1);
	
	std::cout << "Insert the length of the array: " ;
	std::size_t n_2;
	std::cin >> n_2;

	auto b = array<double>(n_2);
	print_arr(b, n_2);

	delete [] a;
	delete [] b;

	return 0;
}
