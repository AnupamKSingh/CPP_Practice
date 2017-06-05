/*
 * Thread Safe stack
 *
 */
#include<iostream>
#include<thread>
#include<stack>
#include<mutex>
using namespace std;

template<typename T>
class threadsafe_stack {
	private:
		stack<T> data;
		mutex mu;
	public:
		threadsafe_stack() {}
		threadsafe_stack(threadsafe_stack const& other) {
			lock_guard<mutex> g(other.mu);
			data = other.data;
		}
		
		void push(T a) {
			lock_guard<mutex> g(mu);
			data.push(a);
		}

		void pop(T& a) {
			lock_guard<mutex> g(mu);
			if(data.empty()) {
				cout<<"Stack is Empty"<<endl;
				return;
			}
			a = data.top();
			data.pop();
		}

		shared_ptr<T> pop() {
			lock_guard<mutex> g(mu);
			if(data.empty()) {
				cout<<"Stack is Empty"<<endl;
				return NULL;
			}
			shared_ptr<T> shptr(make_shared<T>(data.top()));
			data.pop();
			return shptr;
		}

		bool empty() {
			lock_guard<mutex> g(mu);
			return data.empty();
		}
};

void thread1(threadsafe_stack<int> ts1) {
	int a;
	ts1.push(11);
	ts1.push(12);
	ts1.push(13);
	ts1.push(14);
	ts1.push(15);
	ts1.push(16);
	cout<<*ts1.pop()<<endl;
	cout<<*ts1.pop()<<endl;
	cout<<*ts1.pop()<<endl;
	ts1.pop(a);
	cout<<a<<endl;
	ts1.pop(a);
	cout<<a<<endl;
	ts1.pop(a);
	cout<<a<<endl;
}
	
void thread2(threadsafe_stack<int> ts1) {
	int a;
	ts1.push(21);
	ts1.push(22);
	ts1.push(23);
	ts1.push(24);
	ts1.push(25);
	ts1.push(26);
	cout<<*ts1.pop()<<endl;
	cout<<*ts1.pop()<<endl;
	cout<<*ts1.pop()<<endl;
	ts1.pop(a);
	cout<<a<<endl;
	ts1.pop(a);
	cout<<a<<endl;
	ts1.pop(a);
	cout<<a<<endl;
}

int main() {
	threadsafe_stack<int> ts;
	thread t1(thread1, ts);
	thread t2(thread2, ts);
	t1.join();
	t2.join();
}
