#include<iostream>
#include<unistd.h>
#include<string>
#include<thread>
using namespace std;

class Anupam {
	private:
		int& a;
	public:
		Anupam(int& i):a(i) {cout<<"Constructor is called with "<<a<<endl;}
		
		~Anupam() {cout<<"Destructor is called with "<<a<<endl;}
		
		void operator() (){
			cout<<"Anupam1"<<endl;
			anupam();
			cout<<"Anupam2"<<endl;
		}
		
		void anupam() const{
			usleep(10000);
			cout<<"a = "<<a<<endl;
			a = 3;
		}
		
		void func(int d) {
			cout<<"d = "<<d<<endl;
		}

		Anupam(Anupam const&b):a(b.a) {
			cout<<"Copy constructor is called with "<<a<<endl;
		}
		
		Anupam& operator= (Anupam const&) = delete;
};

void anu1(int a,string s) {
	cout<<"a = "<<a<<endl;
	cout<<"s = "<<s<<endl;
}

void anu2(int a,string& s) {
	cout<<"a = "<<a<<endl;
	cout<<"s = "<<s<<endl;
	s = "Deepoo";
}
int main() {
	int a=2;
	int a1=12;
	Anupam A(a1);
	thread t1 {Anupam(a)};
	string s1= "Anupam";
	thread t2(anu1,4,"Anupam");
	thread t3(anu2,5,(ref(s1)));
	thread t4(&Anupam::func,&A,3);
//	t1.detach();
	t1.join();
	t2.join();
	t3.join();
	t4.join();
	cout<<"s1 = "<<s1;
}
