/* Scoped thread 
 * So even when the thread object passed goes out of 
 * scope, the thread is joinable till the scope for scope_thread objext exists
 * and the scope_thread object took the ownership for passed thread object
 *
 */
#include<iostream>
#include<thread>
#include<string>
using namespace std;

class scope_thread {
	private:
		thread t;
		string& s;
	public:
		scope_thread(thread t_,string& s_):t(move(t_)),s(s_) { //Moving the thread ownership from temporary to the class members
			if(!t.joinable()) {
				cout<<"Not joinable thread"<<endl;
				terminate();
			} else {
				cout<<"Constructor is called with joinable thread and s = "<<s<<endl;
			}
		}

		~scope_thread() {
			t.join();
			cout<<"Destructor is called with s = "<<s<<endl;
		}
		
		scope_thread (scope_thread const&) = delete;
		
		scope_thread operator= (scope_thread const&) = delete;
};

void do_something(string& s) {
	cout<<"Do Something s ="<<s<<endl;
}

int main() {
	string s = "Anupam";
	string s1 = "Deepoo";
	scope_thread(thread(do_something,ref(s)),ref(s1));
}	
