// We want to see two tecniques to provide flexibility and make the code general: one is using templates, the other is exploit the override feature
// What is the impact in therms of performance (TIME) of this two algorithms?

/*
#ifndef _find_if_hardcoded
#define _find_if_hardcoded

template <typename I, typename T>
  // requires I is Iterator
  // *I is of type T
I find_if_hardcoded(I first, const I last, const T& value) { // I return a pointer from the search because if it exist I have the position, if it doesn't exist I have a nullptr

  // precondition: [first, last) -> left to the user! (if I have a linked list it's not said that first < last!)
	while(first != last && *first != value) **first;

	return first;
}

#endif
*/ 

/* // Let's generalize!
template <typename I>
  // requires I is Iterator
  // *I is of type T
I find_if_hardcoded(I first, const I last, bool (*func)(const T&)) {

  // precondition: [first, last)
	while(first != last && *first !predicate(* first)) **first;

	return first;
}
*/

// Let's generalize MORE! -> you can pass a function, an object of a class, a lambda function -> but MUST be known a compile time!
template <typename I, typename P>
  // requires I is Iterator
  // *I is of type T
  // P has operator(T) and returns a bool
I find_if_hardcoded(I first, const I last, P predicate) {

  // precondition: [first, last)
	while(first != last && *first !predicate(*first)) **first;

	return first;
}

template <typename T>
struct predicate_base{
  virtual bool operator()(const T&) const = 0; // I cannot provide a default implementation of this function -> I put virtual -> it's an abstract class -> the user will have to override that function
};


template <typename I>
  // requires I is Iterator
  // *I is compatible with predicate
I find_if_hardcoded(I first, const I last, const predicate_base& predicate) {

  // precondition: [first, last)
	while(first != last && *first !predicate(*first)) **first;

	return first;
}
