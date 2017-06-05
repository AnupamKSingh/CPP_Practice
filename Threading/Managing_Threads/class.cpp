#include<iostream>
#include<thread>
using namespace std;

class anu {
	private:
		int a;
		string& s;
	public:
		anu(int i, string str):a(i),s(str) {
			cout<<"Constructor is called with a = "<<a<<endl;
			cout<<"Constructor is called with s = "<<s<<endl;
		}
		~anu() {
			cout<<"Destructor is called with a = "<<a<<endl;
			cout<<"Destructor is called with s = "<<s<<endl;
		}
		void print() {
			cout<<"Print for a = "<<a<<endl;
			cout<<"Print for s = "<<s<<endl;
		}
		void change(int i, string str) {
			a = i;
			s = str;
			cout<<"Change the value of a to "<<a<<endl;
			cout<<"Change the value of s to "<<s<<endl;
		}
/*		void operator() () const {
			cout<<"In operator overloading"<<endl;
		}*/
};


class dee {
	private:
		string& s;
	public:
		dee(string const& str):s(move((str))) {}
		~dee(){}
		void print() const {
			cout<<"I am in dee where s = "<<this->s<<endl;
		}
};

int main() {
	string s = "Anupam";
	cout<<s<<endl;
	dee d1(ref("Anupam"));
	d1.print();
	anu a1 (2,string("deepoo"));
	anu* a = new anu(3, string("Anupam"));
	a->print();
	delete a;
}
