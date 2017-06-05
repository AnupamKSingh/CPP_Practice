/*
 * Deadlock prevention, by taking two locks at the same time
 * Using lock(), unique_lock() and defer_lock()
 */
#include<iostream>
#include<thread>
#include<string>
#include<mutex>
using namespace std;


class StrClass;

void swap(StrClass& s1, StrClass& s2);

class StrClass {
	private:
		string& s;
	public:
		StrClass(string& s_):s(s_) {
			cout<<"StrClass Constructor is called with s = "<<s<<endl;
		}

		~StrClass() {
			cout<<"StrClass Destructor is called with s = "<<s<<endl;
		}

		string& getString() {
			return s;
		}
};

class Swap {
	private:
		StrClass& s;
		mutex mu;
	public:
		Swap(StrClass& s_):s(s_) {
			cout<<"Swap Constructor is called"<<endl;
		}

		~Swap() {
			cout<<"Swap Destructor is called"<<endl;
		}

		friend void frswap(Swap& s1, Swap& s2) {
			unique_lock<mutex> u1(s1.mu, std::defer_lock);
			unique_lock<mutex> u2(s2.mu, std::defer_lock);
			std::lock(u1, u2);
			/*
			 * unique_lock does'nt own the mutex, since defer_lock tells just to associate not to lock.
			 * lock will now not use mutex to lock the mutexes, but instead it will take unique_locks
			 *
			 * std::adopt_lock tell the lock_guard object, that no need to try the lock again.
			 * Just need to take the ownership of the lock, since lock is already
			 * acquired by std::lock.
			 *
			 */
			swap(s1.s, s2.s);
		}
};


void swap(StrClass& s1, StrClass& s2) {
	string  s = s1.getString();
	s1.getString() = s2.getString();
	s2.getString() = s;
}

int main() {
	string s1 = "Anupam";
	string s2 = "Deepoo";
	StrClass str1(s1);
	StrClass str2(s2);
	cout<<"Str1 = "<<str1.getString()<<endl;
	cout<<"Str2 = "<<str2.getString()<<endl;
	Swap sw1(str1);
	Swap sw2(str2);
	frswap(sw1, sw2);
	cout<<"Str1 = "<<str1.getString()<<endl;
	cout<<"Str2 = "<<str2.getString()<<endl;
}
