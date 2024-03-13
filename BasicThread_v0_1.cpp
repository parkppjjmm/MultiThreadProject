/* Code Explain
This code demonstrates the use of Windows semaphores to synchronize three threads in C++.
It simulates a simple pipeline, where each thread performs some work and then signals the next thread to start.
*/

#include <iostream>
#include <thread>
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctime>
#include <vector>
#include <stdio.h>

// namespace
using namespace std;

HANDLE sem1, sem2, sem3;

void thread_1() {

	// local variable 
	bool start;
	string user_input;
	clock_t start_time;
	clock_t end_time;

	cout << "If you ready, enter 'start' in the cmd: ";
	cin >> user_input;

	if (user_input == "start") {
		start = true;
	}
	else
	{
		cout << "Invalid input. Please enter 'start' to run the other threads." << std::endl;
	}

	while (start)
	{
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(100)); // Sleep for 100 milliseconds to simulate work
		/*
		기능 추가
		*/
		end_time = clock();
		printf("Thread_1 is worked......... Processed Time : %d......... \n", end_time - start_time);

		ReleaseSemaphore(sem1, 1, NULL);
	}

}

void thread_2() {
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem1, INFINITE);
		start_time = clock();
		/*
		기능 추가
		*/
		end_time = clock();
		printf("Thread_2 is worked......... Processed Time : %d......... \n", end_time - start_time);

		ReleaseSemaphore(sem2, 1, NULL);
	}
}

void thread_3() {
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem2, INFINITE);
		start_time = clock();
		/*
		기능 추가
		*/
		end_time = clock();
		printf("Thread_3 is worked......... Processed Time : %d......... \n", end_time - start_time);
	}
}

int main() {

	// Initialize the semaphores
	sem1 = CreateSemaphore(NULL, 0, 1, NULL);
	sem2 = CreateSemaphore(NULL, 0, 1, NULL);

	// Create the threads
	thread t1(thread_1);
	thread t2(thread_2);
	thread t3(thread_3);

	t1.join();
	t2.join();
	t3.join();

	CloseHandle(sem1);
	CloseHandle(sem2);

	return 0;
}

