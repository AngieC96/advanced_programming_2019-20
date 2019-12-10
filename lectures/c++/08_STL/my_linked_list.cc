//$ git checkout -b linked_list
//$ cd exercise/...

// FLAGS = -Wall -Wextra -std=c++14 -I ../../

// NAME FILE: as.linked_list.cc

#include <iostream>
#include <memory>  //unique_ptr
#include <iterator>
#include <vector>
#include <algorithmic>

#include "ap_error.h"

enum class method {push_back, push_front};

template <class T>  //it's the class List that is templated, the struct is NOT!
class List{
    struct node {
        std::unique_ptr<node> next; //it's templated only in the class List -> the two classes are linked
        // fully qualified name: List::node
        T value;
        node(const T& v, node * p): next{p}, value{v} {
            std::cout << "copy ctor" << std::endl;
        }
        //node(const T&& v, node * p): next{p}, value{std::move(v)} {}  // there is a possible font of warnings
		node(T&& v, node* p): next{p}, value{std::move(v)} {}
        explicit node(const std::unique_ptr<node>& p): value{p-> value} {
            if(p->next)
                next = std::make_unique<node>(p->next);
        }
    };

    std::unique_ptr<node> head;

    template <class OT>
    void push_back(OT&& v);
    //void push_back(const T& v);
    //void push_bacj(T&& v);

    //void push_front(const T& v) {  //all equivalent!
        //auto h = head.release();
        //auto new_node = new node{v, h};
        //head.reset(new_node);

        //head.reset(new node{v, head.release()});

    //    head = std::make_unique<node>(v, head.release());
    //}
    //void push_front(T&& v);
    template <class OT>  // they are discovered to be Turing-complete, but they were not programmed to be!
    void push_front(OT&& v) {
        head = std::make_unique<node>(std::forward<OT>(v), head.release());
    }

    node* tail() noexcept;

    public:
    List() noexcept = default;
    List(List&& l) noexcept = default;  // they don't throws exceptions!
    List& operator = (List&& l) noexcept = default;

    List(const List& l); // copy ctor
    List& operator=(const List& l); //copy assignment -> copry semantic can throw exceptions!!!! (In the exam put them in the right places!)

    template <class OT>  // this fit
    void insert(OT&& v, const method m);
    //void insert(const T& v, const method m);
    //void insert(T&& v, const method m);  //uses the move semantic
    //but now I cannot use std::mode inside it: std::move(d) doesn't work -> solution: perfect forward -> std::forward<T>(d)
    //prefect forward has to be done on the same type!!!

    template <class O> // you cannot use T beacuse it goes in conflict
    friend std::ostream& operator<<(std::ostream&, const List<O>&);

    template <typename O>
    calss __iterator;

    using iterator = __iterator<T>;
    using cont_iterator = __iterator<const T>;

    iterator begin() noexcept { return iterator{head.get()}; }  // returns the begin of the list
    iterator end() { return iterator{nullptr}; }  // returns one past the last element
    const_iterator begin() const { return const_iterator{head.get()}; }  // it returns a const reference, all the rest is the same
    const_iterator end() const { return const_iterator{nullptr}; }
    const_iterator cbegin() const { return const_iterator{head.get()}; }  // optional, but all the container have it
    const_iterator cend() const { return const_iterator{nullptr}; }
};

template <typename T>  // tempalte of the calss list
template <typename O>// template of the class iterator
class List<T>::__iterator{
    using node = typename List<T>::node;
    node* current;
public:
    explicit __iterator(node* x) noexcept: current{x} {}  // it's better use explicit, ecapet because we're not aquiring memory here

    using value_type = 0;// value type of the calss iterator
    using difference_type = std::ptrdiff_t;
    using iterator_category = std::forward_iterator_tag;
    using reference = value_type&;
    using pointer = value_type*;

    reference operator*() const noexcept { return current->value; }
    pointer operator->() const noexcept { return &(*(*this)); }  // pharenthesis are not really

    __iterator& operator++() noexcept {  // pre-increment
        current = current->next.get(); // we used unique pointers!
        return *this;
    }

    __iterator operator++(int) noexcept {  // post-increment -> by value because ....  USE PRE-INCREMENT because it's faster! You don't need to do all this stuff:
        __iterator tmp {current};  // we didn't implement a copy constructor
        ++(*this);
        current = current->next.get(); // we used unique pointers!
        return tmp;
    }

    friend // they're not part of the calss
    bool operator==(const __iterator& a, const __iterator& b){
        return ;
    }
    bool operator==(__iterator&& a, __iterator&& b){
        return ;
    }
};

template <class T>
typename List<T>::node* List<T>::tail() noexcept {
        auto tmp = head.get();

        while(tmp->next)
            tmp = tmp->next.get();  //if the list is empty this will cause a segmentation fault
        
        return tmp;
}

//fully qualified name:
template <class T>
template <class OT>
//void List<T>::insert(const T& v, const method m) {
void List<T>::insert(OT&& v, const method m) {
    if(!head) {
        //head.reset(new node{v, nullptr});  // I reset the unique_ptr to a new value
        //head = std::make_unique<node> (v, nullptr);  // I generate a volatile object and then use the move semantic
		head = std::make_unique<node>(std::forward<OT>(v), nullptr);
        return;
    }
    switch(m){
        case method::push_back:
            //push_back(v);
			push_back(std::forward<OT>(v));
            break;
        case method::push_front:
            //push_front(v);
			push_front(std::forward<OT>(v));
            break;
        default:
            AP_ERROR(false) << "Unkonwn insertion method";
            break;
    };
}
/* There is something better!!!! The type can be deduced: template <class T> void f(T&& d)
template <class T>
void List<T>::insert(T&& v, const method m) {
    if(!head) {
        //head.reset(new node{v, nullptr});  // I reset the unique_ptr to a new value
        head = std::make_unique<node> (std::move(v), nullptr);  // I generate a volatile object and then use the move semantic
        return;
    }
    switch(m){
        case method::push_back:
            push_back(std::move(v));
            break;
        case method::push_front:
            push_front(std::move(v));
            break;
        default:
            AP_ERROR(false) << "Unkonwn insertion method";
            break;
    }
}*/

template <class T>
template <class OT>
//void List<T>::push_back(const T& v){
void List<T>::push_back(OT&& v) {
    node* last = tail();
    //last->next.reset(new node{v, nullptr});
    //last->next = std::make_unique<node>(v, nullptr);
	last->next = std::make_unique<node>(std::forward<OT>(v), nullptr);
}

template <class T>
std::ostream& operator<<(std::ostream& os, const List<T>& l){
    auto tmp = l.head.get();
    while(tmp){  //equal to: tmp != nullptr
        os << tmp->value << " ";
        // now I need to go on:
        tmp = tmp->next.get();
    }
    return os;
}

template <class T>
//template <class OT>
List<T>::List(const List& l){  //you're friend of yoursel: the frienship is on types not on objects
    //deep copy
    /*
    auto tmp = l.head.get();
    while(tmp) {
        //push_back(tmp->value);
        //insert(v, method::push_back);
        insert(tmp->value, method::push_back);
        tmp = tmp->next.get();
    }*/
    //head = std::make_unique<node>(v, head.release());
    //head = std::make_unique<node>(v, l.head());
	head = std::make_unique<node>(l.head);
}

int main() {
    try{
        List<int> l{};

        l.insert(4, method::push_back);
        l.insert(5, method::push_back);
        l.insert(3, method::push_front);  

        std::cout << l << std::endl;

        std::vector<int> v(3);

        std::copy(l.begin(), l.end(), v.begin());
        std::copy(l.cbegin(), l.cend(), v.begin());

        for(auto x : v)
            std::cout << x << std::endl;
        

        auto ol = l; //copy ctor  
        int a = 9;
        l.insert(14, method::push_front); 
        l.insert(a, method::push_front); 

        std::cout << l << std::endl;
        std::cout << ol << std::endl;

    } catch(std::exception& e) {
        std::cerr << e.what() << std::endl;
    } catch(...) {
        std::cerr << "Unknown exception" << std::endl;
    }

    return 0;
}
