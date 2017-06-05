#include<iostream>
#include<future>
#include<string>
#include<unistd.h>
using namespace std;

shared_ptr<string> string_in_future() {
	string s = "Anupam Future";
	shared_ptr<string> shptr(make_shared<string> (s));
	cout<<"Future 1"<<endl;
	usleep(10000);
	cout<<"Future 2"<<endl;
	return shptr;
}


struct X {
	
int main() {
/*	future<shared_ptr<string>> s = async(string_in_future);
	cout<<"Anupam"<<endl;
	cout<<*s.get()<<endl;
	usleep(100);
	cout<<"Deepoo"<<endl;
	*/

	
}
