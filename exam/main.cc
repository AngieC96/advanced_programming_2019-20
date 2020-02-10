#include <iostream>


template <typename KT, typename VT, typename cmp = std::less<KT>>
class bst{
	cmp op; // operator of comparison
  public:
    bst(cmp x): op{x} {} // constructor

	using node_type = Node<std::pair<const KT, VS>>;

	std::pair<iterator, bool> insert(const pair_type& x);
	std::pair<iterator, bool> insert(pair_type&& x);

	template<class... Types>
	std::pair<iterator,bool> emplace(Types&&... args);
	
	void clear();

	iterator begin();
	const_iterator begin() const;
	const_iterator cbegin() const;

	iterator end();
	const_iterator end() const;
	const_iterator cend() const;

	iterator find(const key_type& x); // find a node and eventually change the value
	const_iterator find(const key_type& x) const; // find if a node just exists: there is if the iterator is different from the end!

	void balance();

	value_type& operator[](const key_type& x);  // copy semantic
	value_type& operator[](key_type&& x);  // move semantic

	insert({x, VT{}}) // default constructor of type VT: VT{} is the default value!

  friend
	std::ostream& operator<<(std::ostream& os, const bst& x);

	void erase(const key_type& x);
}

template <typename T>
struct Node{
	T value;
	left, right; // unique_ptr!
	Node* parent; // a simply row pointer: you need it to navigate the three
}

template <typename node_t>
class iterator{
	node_t* current;
  public:
  	using value_type=typename node_t::value_type;
  	using reference = value_type&;
  	using pointer = value_type*
  	using iterator_category;
  	using difference_type=std::ptrdiff_t // two iterators are equal if they point tot he same node
    reference operator*() const{
        return .....;
    }
}

template <typename node_t>
class const_iterator{
	node_t* current;
  public:
  	using value_type = const typename node_t::value_type;
  	using reference = value_type&;
  	using pointer = value_type*
  	using iterator_category;
  	using difference_type=std::ptrdiff_t // two iterators are equal if they point tot he same node
    reference operator*() const{
        return .....;
    }
}


