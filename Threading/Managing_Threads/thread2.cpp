#include<iostream>
#include<thread>
#include<string>
using namespace std;

class Anupam {
	private:
		string& s;
	public:
		Anupam(string& t_):s(t_) {
			cout<<"Constructor is called with s = "<<s<<endl;
		}
		
		~Anupam() {
			cout<<"Destructor is called with s - "<<s<<endl;
		}
	
		void operator() () {
			cout<<"Operator is called with s = "<<s<<endl;
		}

		void do_something() {
			cout<<"Value of s = "<<s<<endl;
		}

		Anupam operator= (Anupam const&) = delete;
};

class Deepoo {
	public:
		Deepoo() {
			cout<<"Deepoo Constructor is called"<<endl;
		}

		~Deepoo() {
			cout<<"Deepoo Destructor is called"<<endl;
		}

		void do_something() {
			cout<<"I am trying to do something"<<endl;
		}
};

void smartArg(unique_ptr<Deepoo> A) {
	A->do_something();
}

void normalArg(Deepoo *A) {
	A->do_something();
}

int main() {
	string s="Anupam";
	thread t1 ((move(Anupam(move(ref(s))))));
	unique_ptr<Deepoo> dee(new Deepoo);
	Deepoo *dee1 = new Deepoo;
	dee->do_something();
	thread t2 (smartArg, move(dee));//Will not compile without move, since unique pointer cannot be copied, but can be always moved
	thread t3(normalArg,dee1);
	t1.join();
	t2.join();
	t3.join();
	delete dee1;//Deleting explicitly, otherwise dangling pointer
}
