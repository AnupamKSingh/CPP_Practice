/*
 * Spawning multiple threads, storing all threads in a vector
 *
 * Checking possible multiple threads using hardware_concurrency
 *
 */
#include<iostream>
#include<string>
#include<thread>
#include<vector>
#include<algorithm> // For for_each 
using namespace std;

class Anupam {
	private:
		string& s;
	public:
		Anupam(string& s_):s(s_) {
			cout<<"Constructor is called with s ="<<s<<endl;
		}

		~Anupam() {
			cout<<"Destructor is called with s = "<<s<<endl;
		}

		void operator() () {
			cout<<"In Operator with s = "<<s<<endl;
		}

//		Anupam(Anupam const&) = delete;

		Anupam operator= (Anupam const&) = delete;
};

int main() {
	vector<thread> vec;
	string s = "Anupam";
	for (unsigned i = 0;i<10;i++) {
		vec.push_back(thread (Anupam(ref(s))));
	}

	for_each(vec.begin(), vec.end(), mem_fn(&thread::join));

	cout<<thread::hardware_concurrency()<<endl;
}
