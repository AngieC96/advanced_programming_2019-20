#include <iostream>
#include <iomanip>
#include <utility>

template <std::size_t N>
void print_ma(std::array<double,N>& p, int r, int c) {
  for (int i = 0; i < r; ++i) {
    for (int j = 0; j < c; ++j)
      std::cout << std::setw(2) << p[i * c + j] << " ";
    std::cout << std::endl;
  }
}

//template <class T>
//T transpose(T& p, int r, int c) {
//	auto transposed = p;
//	for (int i = 0; i < c; ++i) {
//		for (int j = 0; j < r; ++j)
//			transposed[i * r + j] = p[j * c + i];
//	}
//	return transposed;
//}

template <class T>
void transpose(T& p, int r, int c) {
	auto transposed = p;
	for (int i = 0; i < c; ++i) {
		for (int j = 0; j < r; ++j)
			transposed[i * r + j] = p[j * c + i];
	}
	std::swap(p,transposed);
}

template <class T>
void transpose2(T& p, int r, int c) {
	//in-place algorithm for matrix transpose inspired by:
	//https://gitlab.com/conradsnicta/armadillo-code/blob/9.800.x/include/armadillo_bits/fn_inplace_strans.hpp
    if ( r == 1 || c == 1 ) return;
	bool visited[r * c]; //array that stores whether I have already changed a value or not
	for (int n = 0; n < r*c; ++n) //initializing the array
		visited[n] = false;
	int pos, curr_pos, i_new, j_new = 0;
	double val, tmp = 0;
	for (int i = 0; i < r; ++i) {
		for (int j = 0; j < c; ++j){
			pos = i * c + j;  //linearize the position of the matrix
			if(visited[pos] == false) {  //I go on only if I have never visited this position
				curr_pos = pos; //initializing the current position
				val = p[curr_pos]; //storing the matrix element at the current position
				while(visited[curr_pos] == false){  //I follow the permutation path until I go back to the
													//starting point at the initial value of curr_pos
					visited[curr_pos] = true;
					i_new = curr_pos / c; j_new = curr_pos % c; //calculating i_new and j_new such that curr_pos = i_new*c + j_new
					curr_pos = j_new * r + i_new; //calculating the new linearized position (next step in the permutation)
					tmp = p[curr_pos]; //saving the value in the new position
					p[curr_pos] = val; //assigning the value of the previous matrix element to this one
					val = tmp; //the value in tmp becomes the "previous" matrix element in the next step
				}
			}
		}
	}
}

int main(){
	
	const int row{5}, col{4};
    std::array<double,row*col> A{row*col}; 
	for (int i = 0; i < row*col; ++i) {
      		A[i] = i;
	}

 	print_ma(A, row, col);
	std::cout << std::endl;

//	std::array<double,row*col> transposed{col*row};
//	transposed = transpose(A, row, col);
//	print_ma(transposed, col, row);
//	std::cout << std::endl;

//	transpose(A,row,col);
//	print_ma(A, col, row);
//    std::cout << std::endl;
	
	transpose2(A,row,col);
	print_ma(A, col, row);
    std::cout << std::endl;

	return 0;
}
