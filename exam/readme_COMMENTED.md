# Advanced Programming Exam

The exam consists of a written project followed by an oral discussion. 
The written project is due to February 14, 2020, at 11:59 PM.
Orals take place on 19th and 20th of February.

- Work in groups make of two/three people.
- Use a separate git repository (also the one of the course is fine, but tell exactly the folder to the professor). 
- You have to upload all and only the **source files** you wrote, with a **Makefile** and a **readme.md** where you describe how to compile, run your code, and a short report on what you have done, understood, and, eventually, benchmarked.
- Your code must have no memory leaks.
- No warnings must appear if compiled with the flags `-Wall -Wextra`.
- Don't change the name of the functions!
- Document the code (for you, because Casagrande will extend this one with his project)
- Once finished, send me either the link to the repository or a `tar.gz` with the files (`.git` folder included).

## Binary search tree

The project consists of the implementation of a **template** binary search tree (BST) (simplified version of `std::map`). A BST is a hierarchical (ordered) data structure where each **node** can have at most two children, namely, **left** and **right** child. Each node stores a **pair** of a **key** and the associated **value** (the figure can be misleading because only the keys are reported!). The binary tree is ordered according to the keys. 
If we assume that we sort the keys in ascending order (i.e., we use the less than `<` operator), then given a node `N`, all the nodes having keys **smaller** than the key of the node `N` are on the **left**. All the nodes with a key **greater** than the key of the node `N` are on the **right**.

![](./.aux/binary.png)


Practically speaking, given the binary tree in the picture, if you need to insert a new node with `key=5`, you start from the root node `8`, you go left since `5<8`, you reach node `3`, then you go right, you land in `6`, you go left reaching node `4`. Node `4` has no right child, so the new node `5` becomes the right child of node `4`. If a key is already present in the tree, the associated value **is not** changed.

From the implementation point of view, a node has two pointers `left` and `right` pointing to the left and right child, respectively. The pointers point to `nullptr` if they have no children.

It is useful to add a pointer (head, root, whatever you like) pointing to the top node, called **root node**.

### Tree traversal

The tree must be traversed in order, i.e., if I "print" the tree in the picture, I expect to see on the screen the sequence
```
1 3 4 6 7 8 10 13 14
```
node `1` is the first node, and node `14` is the last one.

If I cannot go right, I go through the node of which I am child. Then I go to the right as far as I can. I go up until I arrive to a node for which I'm not greater.

### Assignments
You have to solve the following tasks using modern C++14 (C++17 is welcome as well).

- Implement a **template** binary search tree class, named `bst`.

- The class has three templates:
  - the key type
  - the value type associated with the key
  - the type of the comparison operator, which is used to compare two keys. `std::less<key_type>` should be used as default choice.
  
  ```c++
  template <typename KT, typename VT, typename cmp = std::less<KT>>
  class bst{
  	cmp op; // operator of comparison
    public:
      bst(cmp x): op{x} {} // constructor
  }
  ```
  
  where `if (K1 < K2)` becomes `if(op(K1,K2))` and where `if(K1>K2)` becomes `if(op(K2,K1))`, where `K1 \ge K2` becomes `!op(K1, K2)`, where `K1 \le K2` becomes `!op(K2,K1)` and `K1==K2` becomes `!op(K1, K2) && !op(K2, K1)`
  
  `cmp` default value: `std::less<KT>` functional object that compares two objects and is templated on the key type
  
- Implement proper iterators for your tree (i.e., `iterator` and `const_iterator`). Forward iterator is sufficient: keep it simple! (no extra mark for extra things: they add bugs!).

- Mark `noexcept` the right functions.

- Remember the KISS principle. 

- Implement at least the following public member functions.

##### Insert

```c++
std::pair<iterator, bool> insert(const pair_type& x);
std::pair<iterator, bool> insert(pair_type&& x);
```
They are used to insert a new node. The function returns a pair of an iterator (pointing to the node) and a bool. The bool is true if a new node has been allocated, false otherwise (i.e., the key was already present in the tree). `pair_type` can be for example `std::pair<const key_type, value_type>`. 

##### Emplace

```c++
template< class... Types >
std::pair<iterator,bool> emplace(Types&&... args);
```
Inserts a new element into the container constructed in-place with the given args if there is no element with the key in the container.

**Difference from Insert**: we can write

```c++
bst<int,int> t;
t.insert({1, 3});
// EQUIVALENT TO:
t.insert(std::pair<KT, VT>{1, 3})
t.emplace(5,4);
```

##### Clear

```c++
void clear();
```
Clear the content of the tree.

##### Begin

```c++
iterator begin();
const_iterator begin() const; / Difference between iterator and const_iterator: when you derefrence them!  → const iterator: you cannot change it! READ ONLY
const_iterator cbegin() const;
```

Return an iterator to the left-most node (which, likely, is not the root node).

##### End

```c++
iterator end();
const_iterator end() const;
const_iterator cend() const;
```

Return an iterator to one-past the last element.

##### Find

```c++
iterator find(const key_type& x); // find a node and eventually change the value
const_iterator find(const key_type& x) const; // find if a node just exists: there is if the iterator is different from the end!
```
Find a given key. If the key is present, returns an iterator to the proper node, `end()` otherwise.

##### Balance

```c++
void balance();
```

Balance the tree. A simple and naive implementation is fine. The aim of this exam is not producing a super-performant code, but learning c++. No extra points for complicated algorithms.

Easiest thing: copy the pairs into an `std::vector` then clear the tree, and start constructing a new tree. How? Take the half value and put it as root, at its right put the half of the right part of the vector, at its left the half of the left part of the vector, and so on...

##### Subscripting operator


```c++
value_type& operator[](const key_type& x);  // copy semantic
value_type& operator[](key_type&& x);  // move semantic
```

Returns a reference to the value that is mapped to a key equivalent to `x`, performing an insertion if such key does not already exist.

```c++
insert({x, VT{}}) // default constructor of type VT: VT{} is the default value!
```

##### Put-to operator


```c++
friend   // friend function
std::ostream& operator<<(std::ostream& os, const bst& x);
```

Implement the friend function **inside** the class, such that you do not have to specify the templates for `bst` (they are a lot! But inside the class they are known).

##### Copy and move

The copy semantics perform a deep-copy. Move semantics is as usual.

##### Erase

```c++
void erase(const key_type& x);
```

Removes the element (if one exists) with the key equivalent to key. Find a way to move the nodes from the function and not use `balance()`! (You can but you will have to recode this function with Casagrande)


### Hints
- **Big hint** use `std::pair<const key_type,value_type>`, which is defined in the header `utility`
- start coding and using the iterators ASAP.
- Sartori would expect to see 3 classes: bst, iterator, Node
- class Node:

```c++
struct Node{
	key_t k;
	val_t v;
} &#x274C; &#x274C; &#x274C;

std::pair<..> value;
```

- (const or not if iterator is const or not)

  The user don't have to know the class Node! It only have to know that there is the pair!

- If the two classes are templates with all and only the same templates make sense to put them one into another, otherwise NO! → Node can have just one template `T`, and not two (key and value)

  ```c++
  template <typename T>
  struct Node{
  	T value;
  }
  ```

  ```c++
  template <typename KT, typename VT, typename cmp = std::less<KT>>
  class bst{
  	cmp op; // operator of comparison
    public:
      bst(cmp x): op{x} {} // constructor
      using node_type = Node<std::pair<const KT, VS>>;
  }
  ```

- Iterator: if I want to go up in the three I need another pointer!

  ```c++
  template <typename T>
  struct Node{
  	T value;
  	left, right; // unique_ptr!
  	Node* parent; // a simply row pointer: you need it to navigate the three
  }
  ```

- Class iterator: outside `bst`! I have different templates!
  Two separate classes: iterator and const iterator! → iterator is templated on the node type it is pointing to
  Aim of iterator: jump through node → it's a generalized pointer! An iterator has a pointer to what it is pointing to
  An iterator doesn't have to know that a node exists! It only need the pair key-value
  Iterator:

  ```c++
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
  ```

  Const iterator:

  ```c++
  template <typename node_t>
  class iterator{
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
  ```

  Can we avoid to write two classes? YES! Put a templated iterator!

  ```c++
  template <typename node_t, typename T>
  class _iterator{
  	node_t* current;
    public:
    	using value_type = T;
    	using reference = value_type&;
    	using pointer = value_type*
    	using iterator_category;
    	using difference_type=std::ptrdiff_t // two iterators are equal if they point tot he same node
      reference operator*() const{
          return .....;
      }
  }
  ```

  Then the main class becomes:

  ```c++
  template <typename KT, typename VT, typename cmp = std::less<KT>>
  class bst{
  	cmp op; // operator of comparison
    public:
      bst(cmp x): op{x} {} // constructor
      using node_type = Node<std::pair<const KT, VS>>;
      using iterator = _iterator<node_type, typename node_type::value_type>
      using const_iterator = _iterator<node_type, const T>
  }
  ```

  signature of insert:

  ```c++
  std::pair<iterator, bool> insert (const KT& x);
  ```

  If we want to implement this funtion outside the class, we should write: first of all the three templates of the class

  ```c++
  template <typename KT, typename VT, typename cmp>
  std::pair<typename bst<KT, VT, cmp>::iterator, bool> bst<KT, VT, cmp>::insert(const KT& x) {
      // here node type is known!
      new node_type // where node_type=Node<std::pair<const KT, V>>
  }
  ```
If I want to define all the classes in a different file:
  ```c++
  #ifndef __bst_hpp // bst.hpp nome of the header
  #define __bst_hpp
  #endif
  ```

  bst.hpp:

  ```
  #ifndef __bst__
  #define __bst__
  template <....>
  class bst{
  ....
  };
  #endif
  #include "bits_bst.hpp"
  ```
```
  
  bits_bst.hpp
  
```
  #ifndef __bst__
  #define __bst__
  #include "bst.hpp"
  	insert ...
  #endif
  ```
  
  


  ```