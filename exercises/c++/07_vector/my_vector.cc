//git checkout -b vector

//mkdir 07_vector

//cd 07_vector

//cp ../06_linked...

#include <iostream>
#include <memory> // for unique_ptr
#include <utility> // for the move semantic
#include <vector>

// Should wemake a class or a struct? A class, because we should keep secret some members that represent the state of the object. E.g. if the vector has 7 objects the number 7 should be keept hidden, because the user shouldn't be able to directly modify it by hands
template <typename T> // is transalted in actual types (int, double ) during compilation time
// requires T
class Vector {
	// I initialize the elements with the default value of that type: 0 for size_t, NULL for unique_ptr
	std::size_t _size{};  // how many elements does the array contains
	// the vector should live in the heap because we don't know the size of the vector!
	std::unique_ptr<T[]> elem{}; // pointer to the real array
	std::size_t _capacity{}; // how big is the actual array

	void check_and_increase_capacity(){
		if (_capacity == 0)
			reserve(8); // reserve(1); -> memory allocation is expensive! At the beginning in thei case I have to make a lot of re-allocations!

		if (_size == _capacity)
			reserve(2 * _size); // we postpone the creation of this function (don't do today what you can do tomorrow)
	}

public:
	auto size() const noexcept { return _size; }  // I'm returning by value so there is no possibility that the user modity the value of _size
	auto capacity() const noexcept { return _capacity; }  // const is a stataement that I will not modity the value of the variable inside the function

	// here I can change the value of the vector
	T& operator[](const std::size_t i) noexcept{ // this function DOESN'T check the boundaries of the array!
		// preconditions: elem != nullptr and i < _size
		return elem[i];
	}

	// here I can only read the value of the element!
	// T& operator[](const std::size_t i) const noexcept { -> here the compiler check that in the function you don't modify the value of the element, but the function returns a reference so you can modfy the value of the element
	const T& operator[](const std::size_t i) const noexcept { // this function DOESN'T check the boundaries of the array!
		// preconditions: elem != nullptr and i < _size
		return elem[i];
	}

	Vector() = default; // I use the default void constructor

	//custom ctor
	// convention: things you pass to the constructor are const and referece
	explicit Vector(const std::size_t& lenght): // we should make this constructo explicit! -> avoid implicit conversion form size_t to Vector
	_size{lenght}, // if we initialize here it directly assign this value to the variable -> we do only one step!
	elem{new T[lenght]{}},  // each element will be initialized calling the constructor of the type
	_capacity{lenght}
	{// _size = lenght -> the compiler has already constructed the elements, with random numbers -> so it makes two things: it initializate the variable with a random number and then it assigns to it the right value lenght
	}

	// we should also make a constructor that takes two values: the size and a value to put in all the elements of the vector
	
	// here there is no need of a reference (also in the custom ctor but it's a convention)
	void reserve(const std::size_t new_size){ // public because if by chance you know in advance the size of your array you can reserve the memory immediately
		if(_capacity < new_size) {
			// for this line std::Vector is better that ours! For the built-in types are equivalent, but for type Data will call the default constructor of every element
			T* new_array = new T[new_size];
			for(std::size_t i{0}; i < _size; ++i){
				// we have outperformed the real Vector because it makes a copy!
				new_array[i] = std::move(elem[i]); // we can steal the values because we will not use old_array=elem anymore!
			}
			elem.reset(new_array);
			_capacity = new_size;
		}
	}

	// in std::Vector takes T and Allocator
	void push_back(const T& x){ // const is for not modifying x in the function, the reference & is because I don't know is size, while a pointer is big 8bytes
		check_and_increase_capacity(); // I will have to implement this function! Delay as much as possible!
		elem[_size] = x;
		++_size; //let's start from the end -> we need a variable _size!
	}

	void push_back(T&& x){ // since c++11
		check_and_increase_capacity();
		elem[_size] = std::move(x); // coll the move semantic of your type if it exists, otherwise passes to copy
		++_size;
	}
	/* // With this function you don't need the other two!!!
	template <typename OT>
	void push_back(OT&& x){ // forwarded reference -> you have to put another template! 
		check_and_increase_capacity();
		elem[_size] = std::forward<OT>(x); // coll the move semantic of your type if it exists, otherwise passes to copy
		++_size;
	} */

	template <typename... Types> // variadic templates: it can be anything! -> your're packing all the variables type into one!
	void emplace_back(Types&&... args) { // args contains all the arguments I have of that type
		// doesn't work!
		// elem[_size] = T{std::forward<Types>(args)...};  // I'm accepting all the types by value so I'm using a forwarded reference -> and I'm also using the move semantic
		elem[_size] = T{std::forward<Types>(args)...};
		++_size;
	}
};

	template <typename T>
	std::ostream& operator <<(std::ostream& os, const Vector<T>& x){
		os << "size " << x.size() << "\n"
		   << "capacity " << x.capacity() << "\n";
		for (std::size_t i = 0; i < x.size(); ++i) {
			os << x[i] << " ";
		}
		os << std::endl;

		return os;
	}

	template <typename T>
	std::ostream& operator <<(std::ostream& os, const std::vector<T>& x){
		os << "size " << x.size() << "\n"
		   << "capacity " << x.capacity() << "\n";
		for (std::size_t i = 0; i < x.size(); ++i) {
			os << x[i] << " ";
		}
		os << std::endl;

		return os;
	}

struct Date{
	int d, m, y;
	// the compiler creates default constructor, copy ctor, copy semantic, move ctor, move semantic
	Date() { std::cout << "default ctor" << std::endl;}
	Date(int d, int m, int y): d{d}, m{m}, y{y} {} // there is no confusion between the two d, m, y!
};


std::ostream& operator<<(std::ostream& os, const Date& x){
	os << x.d << "/" << x.m << "/" << x.y << std::endl;
	return os;
}

int main() {
	//Vector<value_type> v;
	//value_type x;
	Vector<int> v;
	int x = 8;
	

	v.push_back(x); //what do we need to be able of executing this? // push_back with const T&
	v.push_back(99); // push_back with l-value
	
	std::cout << v << std::endl;

	Vector<Date> w;
	Date y{1,2,3};
	w.push_back(y);
	//w.push_back(Date{4, 5, 6}); // we are s
	w.emplace_back(4, 5, 6); // he creates 
	w.emplace_back();

	std::cout << w << std::endl;

	std::vector<Date> u;
	Date z{1,2,3};
	u.push_back(z);
	u.emplace_back(4, 5, 6);
	u.emplace_back();

	std::cout << u << std::endl;

	return 0;
}
