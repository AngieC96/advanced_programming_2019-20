#include <iostream>

enum month { jan = 1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec }; //after jan=1 the others are incremented by one: feb=2, mar=3, ....

//using namespace std;
using std::cout;
using std::endl; //I can use 'endl' alone
//But for all the other function of std I have to use the fully qualified name

int main() {

  cout << nov << endl;
  // cout << dec << endl;  //this scope doesn't compile. Why? Because dec is a function of std! -> name crashing! -> never use 'using namespace' for big namespaces, expecially in headers and ... Or put them inside a scopes

  return 0;
}
