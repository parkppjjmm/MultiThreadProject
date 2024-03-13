/* 2023.03.14
This is a program that creates five threads and implements synchronization between them using semaphores.
The program starts by initializing five semaphores with the CreateSemaphore function. 
The first semaphore sem1 is initialized with an initial count of 0 and a maximum count of 16 (it means 16 frames). 
The same is done for the other semaphores sem2, sem3, sem4, and sem5.
Each of the five threads performs a specific task, which is currently indicated by the comment 역할 (Role in English). 
The tasks are performed in the order of the threads, with each thread waiting for the previous thread to release a semaphore before starting its own task.
Each thread also measures and outputs the time it took to perform its task. 
The time is measured using the clock() function from the ctime library.
After creating the threads, the main function waits for each of them to finish with the join() function. 
Finally, the program closes the handles to the semaphores with the CloseHandle function.
*/

#include <iostream>
#include <thread>
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctime>
#include <stdio.h>

// generated Header
#include "header_v1.h"

// Define
#define CNT 15 //it can set up frame num.

// namespace
using namespace std;

HANDLE sem1, sem2, sem3, sem4, sem5;

void thread_1(MAIN_FORMAT* ts) {
	// local variable 
	int thread_1_count = 0;
	int runningtime = 0;

	clock_t start_time;
	clock_t end_time;

	while (true) {
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(100)); // Sleep for 100 milliseconds to simulate work
		/*
		Add function performed by the thread
		*/
		end_time = clock();
		runningtime = end_time - start_time;
		printf("%d thread_1 is worked..... Running Time : %d..... \n", thread_1_count, runningtime);
		thread_1_count += 1;
		if (thread_1_count > CNT)
		{
			thread_1_count = 0;
		}
		else {}
		ReleaseSemaphore(sem1, 1, NULL);
	}
}

void thread_2(MAIN_FORMAT* ts) {
	int thread_2_count = 0;
	int runningtime = 0;
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem1, INFINITE);
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(10)); // Sleep for 10 milliseconds to simulate work
		/*
		Add function performed by the thread
		*/
		end_time = clock();
		runningtime = end_time - start_time;
		printf("%d thread_2 is worked..... Running Time : %d..... \n", thread_2_count, runningtime);
		thread_2_count += 1;
		if (thread_2_count > CNT)
		{
			thread_2_count = 0;
		}
		else {}
		ReleaseSemaphore(sem2, 1, NULL);
	}
}

void thread_3(MAIN_FORMAT* ts) {
	int thread_3_count = 0;
	int runningtime = 0;
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem2, INFINITE);
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(10)); // Sleep for 10 milliseconds to simulate work
		/*
		Add function performed by the thread
		*/
		end_time = clock();
		runningtime = end_time - start_time;
		printf("%d thread_3 is worked..... Runnig Time : %d..... \n", thread_3_count, runningtime);
		thread_3_count += 1;
		if (thread_3_count > CNT)
		{
			thread_3_count = 0;
		}
		else {}
		ReleaseSemaphore(sem3, 1, NULL);
	}
}

void thread_4(MAIN_FORMAT* ts) {
	int thread_4_count = 0;
	int runningtime = 0;
	clock_t start_time = 0;
	clock_t end_time = 0;
	while (TRUE) {
		WaitForSingleObject(sem3, INFINITE);
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(10)); // Sleep for 10 milliseconds to simulate work
		/*
		Add function performed by the thread
		*/
		end_time = clock();
		runningtime = end_time - start_time;
		printf("%d thread_4 is worked..... Running Time : %d..... \n", thread_4_count, runningtime);

		thread_4_count += 1;
		if (thread_4_count > CNT)
		{
			thread_4_count = 0;
		}
		else {}
		ReleaseSemaphore(sem4, 1, NULL);
	}
}

void thread_5(MAIN_FORMAT* ts) {
	int thread_5_count = 0;
	int runningtime = 0;
	clock_t start_time;
	clock_t end_time;

	while (TRUE) {
		WaitForSingleObject(sem4, INFINITE);
		start_time = clock();
		this_thread::sleep_for(chrono::milliseconds(10)); // Sleep for 10 milliseconds to simulate work
		/*
		Add function performed by the thread
		*/
		end_time = clock();
		runningtime = end_time - start_time;
		printf("%d thread_5 is worked..... Running Time : %d..... \n", thread_5_count, runningtime);
		thread_5_count += 1;

		if (thread_5_count > CNT)
		{
			thread_5_count = 0;
		}
		else {}
	}
}

int main() {
	// Initialize the semaphores
	sem1 = CreateSemaphore(NULL, 0, 16, NULL); //(기본보안 속성, 세마포어 초기카운터, 최대 카운터, 세마포터의 이름 지정하는 문자열 포인터)
	sem2 = CreateSemaphore(NULL, 0, 16, NULL);
	sem3 = CreateSemaphore(NULL, 0, 16, NULL);
	sem4 = CreateSemaphore(NULL, 0, 16, NULL);

	// declare structure
	MAIN_FORMAT main_data;
	memset(&main_data, 0, sizeof(main_data));

	// Create the threads
	thread t1(thread_1, &main_data);
	thread t2(thread_2, &main_data);
	thread t3(thread_3, &main_data);
	thread t4(thread_4, &main_data);
	thread t5(thread_5, &main_data);

	t1.join();
	t2.join();
	t3.join();
	t4.join();
	t5.join();

	CloseHandle(sem1);
	CloseHandle(sem2);
	CloseHandle(sem3);
	CloseHandle(sem4);
	CloseHandle(sem5);

	return 0;
}