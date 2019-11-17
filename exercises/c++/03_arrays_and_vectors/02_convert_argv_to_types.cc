#include <iostream>
#include <iomanip>
#include <utility>
#include <sstream>
#include <vector>

template <class T>
void print_ma(T& p, int r, int c) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j)
      std::cout << std::setw(2) << p[i * c + j] << " ";
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

template <class T>
void transpose(T& p, int r, int c) {
	auto transposed = p;
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j)
			transposed[i * r + j] = p[j * c + i];
	}
	std::swap(p, transposed);
}


int main(int argc, char* argv[]){
	
	std::size_t row, col;
	{
		std::istringstream i1{argv[1]};
		i1 >> row;
	}
	{
		std::istringstream i2{argv[2]};
		i2 >> col;
	}
    std::vector<double> A;
	for (int i = 0; i < row*col; ++i) {
      		A.push_back(i);
	}

 	print_ma(A, row, col);

	transpose(A, row, col);

	print_ma(A, col, row);

	return 0;
}
