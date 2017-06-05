/*
 * Used to demonstrate the condition_variable (wait() and notify_one())
 * wait is blocking call for a thread, which release the acquired lock and blocks the thread
 * notify_one will notify the blocking thread due to wait()
 *
 * This code will block two threads spawned in block/wait mode.
 *
 */
#include<iostream>
#include<memory>
#include<thread>
#include<mutex>
#include<queue>
#include<condition_variable>
using namespace std;

template<typename T>
class threadsafe_queue {
	private:
		queue<T> data_queue;
		mutex mu;
		condition_variable data_cond;

	public:
		threadsafe_queue() {}

		threadsafe_queue(threadsafe_queue const& other_queue) {
			lock_guard<mutex> lg(mu);
			data_queue = other_queue.data_queue;
		}

		void wait_and_pop(T& a) {
			unique_lock<mutex> ul(mu);
			data_cond.wait(ul, [this] {return !data_queue.empty(); });
			/*
			 * Use of lambda function in wait(), to tell the condition for wait to unblock.
			 * Using unique_lock(), since we need to release the lock, when the condtion in wait lambda
			 * finction is not satisfied, this feature is not supported in lock_guard()
			 *
			 */
			a = data_queue.front();
			data_queue.pop();
		}

		void push(T& a) {
			lock_guard<mutex> lg(mu);
			data_queue.push(a);
			data_cond.notify_one();
		}

		shared_ptr<T> wait_and_pop() {
			unique_lock<mutex> ul(mu);
			data_cond(ul, [this] {return !data_queue.empty(); });
			shared_ptr<T> shptr (make_shared<T> (data_queue.front()));
			data_queue.pop();
			return shptr;
		}

		shared_ptr<T> try_pop() {
			lock_guard<mutex> lg(mu);
			if (data_queue.empty()) {
				cout<<"Data Queue is Empty"<<endl;
				return NULL;
			}
			shared_ptr<T> shptr (make_shared<T> (data_queue.front()));
			data_queue.pop();
			return shptr;
		}
};

void thread_1(threadsafe_queue<string> ts, bool wait) {
	string s1 = "Anupam1";
	string s2 = "Anupam2";
	string s3 = "Anupam3";
	string s4 = "Anupam4";
	string s;
	ts.push(s1);
	ts.push(s2);
	ts.push(s3);
	ts.push(s4);
	if (wait) {
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
	} else {
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
	}
}
	
void thread_2(threadsafe_queue<string> ts, bool wait) {
	string s1 = "Deepoo1";
	string s2 = "Deepoo2";
	string s3 = "Deepoo3";
	string s4 = "Deepoo4";
	string s;
	ts.push(s1);
	ts.push(s2);
	ts.push(s3);
	ts.push(s4);
	if (wait) {
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
		ts.wait_and_pop(s);
		cout<<s<<endl;
	} else {
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
		cout<<*ts.try_pop()<<endl;
	}
}
int main() {
	threadsafe_queue<string> ts;
	
	thread t1(thread_1, ts, 1);
	thread t2(thread_2, ts, 1);
	
	/*
	thread t1(thread_1, ts, 0);
	thread t2(thread_2, ts, 0);
	*/

	/*
	 * wait() will block the thread and release the mutex till the condition in the lambda function in wait 
	 * passes. But the try_lock will not block, it will execute all the operation an unlock the thread
	 * thereby will not be blocking
	 *
	 */
	t1.join();
	t2.join();
}
