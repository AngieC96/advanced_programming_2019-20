#include <iomanip>
#include <iostream>

void print_ma(int m[][5], int dim1);  // ugly and not flexible -> the size of the column MUS BE KNOWN! It can print only the matrices that have 5 columns! Here Ican use the ma[i][j]  syntax
// void print_ma(int m[][], int dim1, int dim2); // error second
// dimension must be
// knwon at compile time

void print_ma(int* p, int row, int col);  // the only possible solution: pass the rows and comlums length

int main() {
  int ma[6][5];  // definition of a matrix in the stack: 6 rows, 5 columns each

  for (int i = 0; i < 6; ++i)
    for (int j = 0; j < 5; ++j)
      ma[i][j] = 10 * i + j;

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
      std::cout << std::setw(3) << ma[i][j];
    std::cout << std::endl;
  }

  for (int i = 0; i < 6; ++i) {
    for (int j = 0; j < 5; ++j)
      std::cout << &ma[i][j] << " ";  //we want to see how it is stored in the memory! It is a rectangular? NO, it's a long array
    std::cout << std::endl;
  }

  // int *pma {ma}; 		// error
  // int *pma[5] {ma};		// error
  int* p{reinterpret_cast<int*>(ma)}; //to make the pointer to the first element of the matrix
  // int* p {&ma[0][0]};

  // print_ma(ma, 6, 5); 	// error
  print_ma(p, 6, 5);

  //only way to define a matrix on the heap
  auto d_ma = new int[6 * 5]{}; //allocates a matrix with 30 elements and then I have to remember to access them with d_ma[i * col + j]

  std::cout << std::endl;

  print_ma(d_ma, 6, 5);
  delete[] d_ma;

  return 0;
}

void print_ma(int* p, int row, int col) { //this is how the compiler access the elements of the matrix, because they are on a single line!
  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j)
      std::cout << std::setw(2) << p[i * col + j] << " ";
    std::cout << std::endl;
  }
}

//these are BUILT-IN arrays -> the std library offers something better! See next file
