#include<iostream>
#include<thread>
#include<unistd.h>
using namespace std;

class anu {
	private:
		int a;
	public:
		anu (int& i): a(i) {}
		void operator() () {
			cout<<"Operator overloading starts"<<endl;
			usleep(1000);
			cout<<"I am in operotor overloading: "<<a<<endl;
		}
};

int oops() {
	int a =  1;
	thread t1 {anu(a)};
	t1.detach();
}
int main() {
	oops();
	cout<<"I am waiting in main()"<<endl;
	usleep(1000000);
	cout<<"Main exited"<<endl;
}
