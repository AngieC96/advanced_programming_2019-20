# Exercises - session 04

## Class Date
Implement a class `Date`. This class must meet the following requirements:
- it has three **private** attributes to represent day, month and year -> they are private by default! DATA HIDING: you hide the data of the class from the user -> 
- use a scoped enum for month -> Date d{1,3,2019} it's ambiguous! The month is jenuary or march? Date d{1, month::march, 2019} is NOT ambiguous. Maybe two constructors for doing also Date d{month::march, 1, 2019}
- it has the following **public** functions:
	- constructor that takes as arguments a day, a month and a year. (Forget about the validation for now)
	- `day()` function that returns the day
	- `month()` function that returns the month
	- `year()` function that returns the year
	- `add_days(const unsigned int n)` which adds `n` days. You have to take care to increment months and years accordingly (neglect leap years)

*Hints*:
- you can add more functions, maybe private, to simplify the implementation of the above (e.g., you can implement a function that adds 1 single day) -> make them private because only you will use them
- remember to properly mark the member functions that do not modify the class as `const`
```c++
void f(const Date& d) {
	d.day();
}

class Date{
	int _day;
	public:
		int day() const{
			return _day;
		}
}
```
- you should think where to implement the member functions, i.e. inside the class declaration or outside
```c++
class Foo{
public:

int foo() const {return an_int;} // note no ; at the end -> written all inside the class because it's simple

int bar(); //just declared inside the function because it's complicated

private:
int an_int;
}; // note the ; at the end of class declaration

int Foo::bar(){
...
} // note no ; at the end of function implementation

```

Member functions that are *defined* inside the class are **inlined**
meaning that the compiler will replace the function call to its implementation (thus the executable becomes bigger because whenever the class is called the compiler puts the body of the function there instead of writing it only one time). A good rule of thumb is that functions that are simple (e.g. a simple return or fewlines of code) should be inlined. Bigger functions are recommended to be implemented outside the class. Remember that the name of the function is prefixed with the class name (see the implementation of
`bar()` above).

- In a switch-case statement you can use several `case` labels for a single case
```c++
int a;
...
switch (a){
	case 0: case 2: case 4:	//If it fits more cases
	case 6: case 8: case 10:
		std::cout << "a is even\n";
		break;

	case 1: case 3: case 5:
	case 7: case 9:
		std::cout << "a is odd\n";
		break;
	default:
		std::cout << "a > 10\n";
		break;
}
```

## Helper functions
Implement the following external helper functions (i.e., they are not part of the class):
- `bool operator==(const Date& lhs, const Date& rhs);`
- `bool operator!=(const Date& lhs, const Date& rhs);`
	//-> returns !(d.day() == f.day())
- `std::ostream& operator<<(std::ostream& os, const Date& d);`
- **optional** `bool is_leap(const int y);`

*Hints*:
- a year is a leap year if it is divisible by 4. If it is also divisible by 100 is not a leap year. However, it is a leap year if it is divisible by 400.
- try to avoid code duplication




## C++14

Modify the class `Vector<typename T>` presented during the lecture exploiting all the of C++14 features you know. Can you see any benefit?

 - The return type of a function can be 'auto'

*Hints*:

- remember to compile with `-std=c++14`



## Smart usage of `enums`
Study and try to understand the file [multiple_flags.cc](./multiple_flags.cc)



## Optional: range-for-loop

Implement the range-for-loop for the class `Vector<class T>` we have written.
```c++
for (auto;)
...
