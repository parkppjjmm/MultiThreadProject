### Multi-Thread Flow Chart
![multithread](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/f26fed4f-6490-49bf-a5ae-112c4ffe719e)


### C++ 멀티스레딩(multi-thread) 기본 개념: 세마포어(semaphore)와 while() loop를 사용한 프로세스 병렬 처리 이해하기
![image](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/e0e85631-c14d-40ac-9056-b068c5079bac)
멀티스레딩은 여러 실행 스레드가 단일 프로세스 내에서 동시에 실행될 수 있도록 하는 프로그래밍 개념입니다. 스레드는 프로세스 내에서 가장 작은 실행 단위이며 가볍고 독립적인 명령 시퀀스로 생각할 수 있습니다. 각 스레드는 자체 스택 및 프로그램 카운터를 갖지만 동일한 프로세스의 다른 스레드와 메모리 및 파일 핸들과 같은 동일한 주소 공간 및 리소스를 공유합니다.

###
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
