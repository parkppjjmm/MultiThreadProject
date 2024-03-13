/* Code Explain
This code demonstrates the use of inter-process communication (IPC) using shared memory and Windows semaphores to synchronize two threads in C++.
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

HANDLE sem1;

const std::string currentDateTime() {
	time_t     now = time(0); 
	//struct tm  tstruct;
	char       Buffer[80];
	//tstruct = *localtime(&now);
	//strftime(Buffer, sizeof(Buffer), "%Y-%m-%d_%H:%M:%S", &tstruct); 
	return Buffer;
}

void thread_1() {

	// local variable 
	bool start;
	string user_input;
	clock_t start_time;
	clock_t end_time;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 0. Shared Memory 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "Please read it before running the code. " << endl;
	cout << "The order of project execution is as follows. " << endl;
	cout << "Run in the order of server_v2.cpp for the first, BasicThread_v0.cpp for the second, and client_v4.cpp for the third. " << endl;
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

		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		////    0. �����޸� ���� �� local variable ����	
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////
		//////////////////////////////////////////////////////////////////////////////////////////////////////////

		HANDLE HanValue1;
		HanValue1 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(char) * 16, "IPCValue1");
		if (HanValue1 == NULL) { std::cout << currentDateTime() << " -- " << "Could not read HanCoilID : " << GetLastError() << endl;	exit(0); }

		HANDLE HanValue2;
		HanValue2 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int32_t), "IPCValue2");
		if (HanValue2 == NULL) { std::cout << currentDateTime() << " -- " << "Could not read HanLength : " << GetLastError() << endl;	exit(0); }

		HANDLE HanValue3;
		HanValue3 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int32_t), "IPCValue3");
		if (HanValue3 == NULL) { std::cout << currentDateTime() << " -- " << "Could not read HanCoilStatus : " << GetLastError() << endl;	exit(0); }

		HANDLE HanValue4;
		HanValue4 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(int32_t), "IPCValue4");
		if (HanValue4 == NULL) { std::cout << currentDateTime() << " -- " << "Could not read HanCoilSpeed : " << GetLastError() << endl;	exit(0); }

		char* recvValue1 = (char*)MapViewOfFile(HanValue1, FILE_MAP_WRITE, 0, 0, 0);
		int32_t* recvValue2 = (int32_t*)MapViewOfFile(HanValue2, FILE_MAP_WRITE, 0, 0, 0);
		int32_t* recvValue3 = (int32_t*)MapViewOfFile(HanValue3, FILE_MAP_WRITE, 0, 0, 0);
		int32_t* recvValue4 = (int32_t*)MapViewOfFile(HanValue4, FILE_MAP_WRITE, 0, 0, 0);


		printf("recvValue1 : %s\n", recvValue1);
		printf("recvValue2 : %d\n", *recvValue2);
		printf("recvValue3 : %d\n", *recvValue3);
		printf("recvValue4 : %d\n", *recvValue4);

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
		��� �߰�
		*/
		end_time = clock();
		printf("Thread_2 is worked......... Processed Time : %d......... \n", end_time - start_time);
	}
}

int main() {

	// Initialize the semaphores
	sem1 = CreateSemaphore(NULL, 0, 1, NULL);

	// Create the threads
	thread t1(thread_1);
	thread t2(thread_2);

	t1.join();
	t2.join();

	CloseHandle(sem1);

	return 0;
}

