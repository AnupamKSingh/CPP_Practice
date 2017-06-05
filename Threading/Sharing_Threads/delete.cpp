#include<iostream>
#include<stack>
#include<mutex>
#include<thread>
#include<string>
using namespace std;

template<typename T>
class threadsafe_stack {
	private:
		stack<T> data;
		mutex mu;
	
	public:
		threadsafe_stack() {}
		
		threadsafe_stack(threadsafe_stack const& other) {
			lock_guard<mutex> lg(mu);
			data = other.data;
		}

		void push(T& a) {
			lock_guard<mutex> lg(mu);
			data.push(a);
		}

		shared_ptr<T> pop() {
			lock_guard<mutex> lg(mu);
			if(data.empty()) {
				cout<<"Data is empty"<<endl;
				return NULL;
			}
			shared_ptr<T> shptr (make_shared<T> (data.top()));
			data.pop();
			return shptr;
		}

		void pop(T& a) {
			lock_guard<mutex> lg(mu);
			if (data.empty()) {
				cout<<"Data is empty"<<endl;
				return NULL;
			}
			a = data.top;
			data.pop();
		}

		bool empty() {
			lock_guard<mutex> lg(mu);
			return data.empty();
		}
};

void thread_1(threadsafe_stack<string> ts) {
	string s1 = "Anupam1";
	string s2 = "Anupam2";
	string s3 = "Anupam3";
	string s4 = "Anupam4";
	ts.push(s1);
	ts.push(s2);
	ts.push(s3);
	ts.push(s4);
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<ts.pop()<<endl;
}

void thread_2(threadsafe_stack<string> ts) {
	string s1 = "Deepoo1";
	string s2 = "Deepoo2";
	string s3 = "Deepoo3";
	string s4 = "Deepoo4";
	ts.push(s1);
	ts.push(s2);
	ts.push(s3);
	ts.push(s4);
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<*ts.pop()<<endl;
	cout<<ts.pop()<<endl;
}

int main() {
	threadsafe_stack<string> ts;
	thread t1(thread_1, ts);
	thread t2(thread_2, ts);
	t1.join();
	t2.join();
}


