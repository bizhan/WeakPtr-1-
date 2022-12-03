#include <iostream>
#include <memory>

// NOTES:
// 0. If we say unique_ptr is for unique ownership and shared_ptr is for shared ownership then
//    weak_ptr is for non-ownership smart pointer.
// 1. It actually reference to an object which is managed by shared_ptr.
// 2. A weak_ptr is created as a copy of shared_ptr.
// 3. We have to convert weak_ptr to shared_ptr in order to use the managed object.
// 4. It is used to remove cyclic dependency between shared_ptr.

using namespace std;
class Foo {
  int x;

public:
  explicit Foo(int x) : x{x} {}
  int getX() { return x; }
  ~Foo() { cout << "Foo Dest" << endl; }
};
class Foo2 {
int x;
public:

};

int main() {
  auto sp = make_shared<int>(100);
  weak_ptr<int> wp(sp);

  cout<<"Weak ptr use count: "<<wp.use_count()<<endl;
  cout<<"Share ptr use count: "<<sp.use_count()<<endl;
  cout<<"Weak ptr expired(): "<<wp.expired()<<endl;
  // Below line prints the value of the managed object sp points too.
  cout<<"Share ptr value: "<<*sp<<endl;
  // However this does not work for weak ptr
  //cout<<"Weak ptr value: "<<*wp<<endl;

  // NOTE: Below line surpises me ...
  auto spF = make_shared<Foo>(200);
  cout<<"Shared ptr FOO value: "<<*sp<<endl;
  
  
  // wp.lock check if the shared pointer that weak ptr copied from
  // is alive or not, if yes, it returns true.
  // since we can not deference wp, we need to create a shared ptr
  // from it.
  if(shared_ptr<int> sp2 = wp.lock()){
    cout<<"sp1 value: "<<*sp<<endl;
    cout<<"sp2 value: "<<*sp2<<endl;
    cout<<"sp2 use countr: "<<sp2.use_count()<<endl;
  }
  // reset make weak ptr expires.
  wp.reset();
  cout<<"Weak ptr expired(): "<<wp.expired()<<endl;
  
  if(shared_ptr<int> sp3 = wp.lock()){
    cout<< "we should never get here"<<endl;
    }
  
  
}