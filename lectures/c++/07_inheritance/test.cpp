#include <iostream>

struct foo{
    //void bar() { std:: cout << "in foo\n";}
    virtual void bar() { std:: cout << "in foo\n";} // the children CAN (not must!) re-implement this function
    virtual void mm() { std:: cout << "in foo\n";}
}; // the size is always 8!

struct derived: public foo{

};

int main(){
    derived d;  // it contains a pointer to the virtual table
    std::cout << sizeof(foo) << std::endl;
    std::cout << sizeof(derived) << std::endl;
    //Output:
    //1
    //1
    // it's 1 because you cannot put two objects in the same memory address, otherwise you will pile them up
    // in this way each object has its own address


    // Output:
    // 8
    // 8
    // vitural table added by the compiler -> every time a new children is inserted, the virtual table has a row for sizeof the children
    // v+
    // foo  -> foo::bar()
    // derived -> derived::bar()

    // doesn't make virtual a function that is called many many times! -> you have to jump in the memory!!! And that's bad
}