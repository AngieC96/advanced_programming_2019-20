#include <iostream>

template <typename T> T* array(const std::size_t n){
	
	T val;
	T* arr{new T[n]};
	for (std::size_t i{0}; i < n; ++i){
		std::cin >> val;
    	arr[i] = val;
	}

	return arr;
}

template <typename T> T print_arr(T* array, const std::size_t n){
	for (std::size_t i{n}; i > 0; --i)
		std::cout << "arr[" << i-1 << "] = " << array[i-1] << std::endl;
//	  while(n)
//	  std::cout << array[--n] << std::endl;
//	while(n--)
//		std::cout << array[n] << std::endl;

	delete[] array;
}

int main(){
	
	std::size_t n;
	std::cin >> n;

	//int arr[n];
	//print_arr<int>(arr, n);

	//int * a{array<int>(n)};
	//double a = array<double>(n);

	//auto a = array<double>(n);
	//print_arr(a, n);

	print_arr(array<double>(n), n);

	//delete [] a;



	return 0;
}
