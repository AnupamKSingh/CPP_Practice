/* Transfering ownership of threads */
#include<iostream>
#include<thread>
#include<string>
using namespace std;

class Anupam {
	private:
		string& s;
	public:
		Anupam(string& t):s(t) {
			cout<<"Constructor is called s = "<<s<<endl;
		}

		~Anupam() {
			cout<<"Destructor is called ith s = "<<s<<endl;
		}

		void operator() () {
			cout<<"Operator is being called"<<endl;
		}

		Anupam operator= (Anupam const&) = delete;
};

int main() {
	string s = "Anupam";
	thread t1 {Anupam(ref(s))};
	thread t2 = move(t1);
	s = "Deepoo";
	thread t3 {Anupam(ref(s))};
//	t2 = move(t3);
	/*
	 * terminate called without an active exception
	 * Aborted (core dumped)
	 *
	 * std::terminate() will be called to terminate the program
	 *
	 * The message comes in runtime , when we are trying to move the ownership of thread 
	 * to non-empty thread object
	 *
	 * The same will happen , in case the thread object goes out of scope,
	 * without calling detach() or join() on that object
	 *
	 */

	if(t2.joinable()) {
		cout<<"t2 is joinable"<<endl;
		t2.join();
	}
	if(!t1.joinable()) {
		cout<<"t1 is no longer joinable"<<endl;
	}
	t3.join();
}
