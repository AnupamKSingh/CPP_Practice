#include<iostream>
#include<list>
#include<thread>
#include<algorithm>
#include<mutex>
using namespace std;

list<int> anuList;
mutex mu;

void ListAdd(int a) {
	lock_guard<mutex> g(mu);
	anuList.push_back(a);
}

void ListShow() {
	lock_guard<mutex> g(mu);
	for(int a : anuList) {
		cout<<a<<endl;
	}
}

void thread1() {
	ListAdd(1);
	ListAdd(3);
	ListAdd(5);
	ListAdd(7);
	ListAdd(9);
}

void thread2() {
	ListAdd(2);
	ListAdd(4);
	ListAdd(6);
	ListAdd(8);
	ListAdd(10);
}

int main() {
	thread t1(thread1);
	thread t2(thread2);

	ListShow();
	t1.join();
	ListShow();
	t2.join();
	ListShow();
}
