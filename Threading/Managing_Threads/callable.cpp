#include<iostream>
#include<thread>
using namespace std;

class anu {
	private:
		int a;
	public:
		anu(int i) :a(i){}
		void operator() () const {
			do_something();
			do_something_else();
		}
		void do_something() const {
			cout<<"I am in do_something: "<<a<<endl;
		}
		void do_something_else() const{
			cout<<"I am in do_something_else: "<<a<<endl;
		}
};
/* Thread constructor decides the execution of threads and it follows stack (First come first serve) */
int main() {
	anu a(1);
	anu b(4);
	thread t1(a);
//	thread t2 (anu()); // C++'s most vexing parse
	thread t2((anu(2))); //Extra parentheis prevents the prevents the function declaration syntax
	thread t3 {anu(3)}; //New uniform initialization syntax
	thread t4 ([] {b.do_something(); b.do_something_else()});
	t2.join();
	t3.join();
	t1.join();
	t4.join();
	cout<<"Main thread exited!!"<<endl;
}
