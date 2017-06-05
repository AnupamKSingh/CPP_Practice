#include<iostream>
#include<mutex>
#include<thread>
using namespace std;


class StrClass {
	private:
		string& s;
	public:
		StrClass() {}
		StrClass(string& s_):s(s_) {
			cout<<"StrClass Constructor is called with s= "<<s<<endl;
		}

		~StrClass() {
			cout<<"StrClass Destructor is called with s = "<<s<<endl;
		}

		string& getString() {
			return s;
		}

		void setString(string s_) {
			s = s_;
		}
};

void swap(StrClass&, StrClass&);

class SwapClass: public StrClass {
	private:
	    StrClass s;
		mutex mu;
	public:
		SwapClass(string& s_):StrClass(s_) {
			cout<<"SwapClass Constructor is called with s = "<<s_<<endl;
		}

		~SwapClass() {
			cout<<"SwapClass Destructor is called with s = "<<this->s.getString()<<endl;
		}

		friend void frswap(SwapClass& s1, SwapClass& s2) {
			lock(s1.mu, s2.mu);
			lock_guard<mutex> g1(s1.mu, adopt_lock);
			lock_guard<mutex> g2(s2.mu, adopt_lock);
			swap(s1.s, s2.s);
		}
};

void swap(StrClass& s1, StrClass& s2) {
	string& s = s1.getString();
	s1.setString(s2.getString());
	s2.setString(s);
}

int main() {
	string s1 = "Anupam";
	string s2 = "Deepoo";
	SwapClass sw1(s1);	
	SwapClass sw2(s2);
	frswap(sw1, sw2);
	cout<<"s1 = "<<s1;
	cout<<"s2 = "<<s2;
}
