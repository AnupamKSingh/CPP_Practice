#include<iostream>
#include<thread>

using namespace std;

void hello() {
	cout<<"Hello World !!"<<endl;
}

int main() {
	thread t(hello);
	//t.join();
	t.detach();
	//hello();
	cout<<"Main thread exited";
}
