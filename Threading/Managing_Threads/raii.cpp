/*Resource Acquisition Is Initialization */
#include<iostream>
#include<thread>
#include<unistd.h>

using namespace std;

class thread_guard {
	private:
		thread &t;
	public:
		thread_guard(thread& t_): t(t_) {
			cout<<"Thread_guard constructor is called"<<endl;
		}
		~thread_guard() {
			cout<<"Thread_guard destructor is called"<<endl;
			if (t.joinable()) {
				cout<<"Thread_guard join is called"<<endl;
				t.join();
			}
		}
		thread_guard(thread_guard const&) = delete; /* Copy constructor disabled */
		thread_guard& operator= (thread_guard const&) = delete; /*Copy assignment operator disabled*/
};

class anu {
	private:
		string& s;
	public:
		anu(string str):s(str) {
			cout<<"anu constructor is being called for s = "<<s<<endl;
		}
		~anu() {
			cout<<"anu destructor is being called for s = "<<s<<endl;
		}
		void do_something() const {
			cout<<"Print for s = " <<s<<endl;
		}
};

void anuchanarg(string& s) {
	s = "Changed";
	cout<<"Anuchanarg is being called"<<endl;
}

void anuarg(int a, string const& b) {
	cout<<"We are in anuarg"<<endl;
	usleep(100000);
	cout<<a<<endl<<b<<endl;
	cout<<"Anuarg is exited"<<endl;
}

void anu() {
	cout<<"Anupam is being called"<<endl;
	usleep(100000);
	cout<<"Anupam is exited"<<endl;
}

int main() {
	char buffer[1000] = "Anupam Kumar Singh";
	string s ="Anupam";
	anu a1(string("Deepoo1"));
	anu a2(string("Deepoo2"));
	thread t1(anu);
	thread t2(anuarg, 2,"Anupam");
	thread t3(anuarg, 3, string(buffer)); //string(buffer) avoids the dangling pointer if char a got out of scope 
	thread t4(anuchanarg, ref(s));  //To pass the reference to the thread use std::ref
//	thread t5(&anu::do_something,ref(a1));
//	thread t6(&anu::do_something,ref(a2));
	t4.join();

	thread_guard tg1(t1);
	thread_guard tg2(t2);
	thread_guard tg3(t3);
//	thread_guard tg5(t5);
//	thread_guard tg6(t6);
	
	cout<<s<<endl;

	cout<<"Main thread exits"<<endl;
}
