#include <iostream>
#include <thread>
#include <Windows.h>
#include <stdlib.h>
#include <stdint.h>
#include <ctime>
#include <vector>
#include <stdio.h>

// generated Header
#include "structure.h"
#include "global.h"

// namespace
using namespace std;

HANDLE sem1, sem2, sem3, sem4, sem5;

const std::string currentDateTime() {
	time_t     now = time(0); //현재 시간을 time_t 타입으로 저장
	struct tm  tstruct;
	char       Buffer[80];
	tstruct = *localtime(&now);
	strftime(Buffer, sizeof(Buffer), "%Y-%m-%d_%H:%M:%S", &tstruct); // YYYY-MM-DD.HH:mm:ss 형태의 스트링

	return Buffer;
}

void input_thread(MAIN_FORMAT* ts) {

	// local variable 
	int input_count = 0;
	int exitCode = 0; // The exit code of the sample application.
	bool start;
	string user_input;
	clock_t start_time;
	clock_t end_time;

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 0. Shared Memory 
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	cout << "Enter 'start' to run the other threads: ";
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
		////    0. 공유메모리 선언 및 local variable 선언	
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

		memcpy(&ts->input_format.g_input_CoilID[input_count][0], recvValue1, sizeof(char) * 16);
		memcpy(&ts->input_format.g_input_Length[input_count], recvValue3, sizeof(recvValue3));
		memcpy(&ts->input_format.g_input_Status[input_count], recvValue2, sizeof(recvValue2));
		memcpy(&ts->input_format.g_input_Speed[input_count], recvValue4, sizeof(recvValue4));

		printf("Input's CoilID : %s\n", &ts->input_format.g_input_CoilID[input_count][0]);
		printf("Input's Length : %d\n", ts->input_format.g_input_Length[input_count]);
		printf("Input's Status : %d\n", ts->input_format.g_input_Status[input_count]);
		printf("Input's Speed : %d\n", ts->input_format.g_input_Speed[input_count]);

		ts->input_format.g_input_Parity[input_count] = PO;
		ts->input_format.g_input_Count[input_count] = input_count;
		end_time = clock();
		printf("%d INPUT Thread is worked......... Processed Time : %d......... \n", input_count, end_time - start_time);
		input_count += 1;
		if (input_count > 15) { input_count = 0; }
		else {}
		ReleaseSemaphore(sem1, 1, NULL);
	}

}

void edge_thread(MAIN_FORMAT* ts) {
	int edge_count = 0;
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem1, INFINITE);
		start_time = clock();
		ts->input_format.g_input_Parity[edge_count] = PF;

		end_time = clock();
		printf("%d EDGE Thread is worked......... Processed Time : %d......... \n", edge_count, end_time - start_time);
		edge_count += 1;
		if (edge_count > 15) { edge_count = 0; }
		else {}
		ReleaseSemaphore(sem2, 1, NULL);
	}
}

void convert_thread(MAIN_FORMAT* ts) {
	int convert_count = 0;
	clock_t start_time;
	clock_t end_time;
	while (TRUE) {
		WaitForSingleObject(sem2, INFINITE);
		start_time = clock();
		ts->edge_format.g_edge_Parity[convert_count] = PF;

		end_time = clock();
		printf("%d CONVERT Thread is worked......... Processed Time : %d......... \n", convert_count, end_time - start_time);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		convert_count += 1;
		if (convert_count > 15) { convert_count = 0; }
		else {}
		ReleaseSemaphore(sem3, 1, NULL);
	}
}

void fitting_thread(MAIN_FORMAT* ts) {
	int fitting_count = 0;
	clock_t start_time = 0;
	clock_t end_time = 0;
	while (TRUE) {
		WaitForSingleObject(sem3, INFINITE);
		start_time = clock();
		ts->convert_format.g_convert_Parity[fitting_count] = PF;

		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		
		end_time = clock();
		printf("%d FITTING Thread is worked......... Processed Time : %d......... \n", fitting_count, end_time - start_time);
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		fitting_count += 1;
		if (fitting_count > 15) { fitting_count = 0; }
		else {}
		ReleaseSemaphore(sem4, 1, NULL);
	}
}

void result_thread(MAIN_FORMAT* ts) {
	int result_count = 0;
	
	
	clock_t start_time;
	clock_t end_time;
	
	
	while (TRUE) {
		WaitForSingleObject(sem4, INFINITE);
		start_time = clock();
		ts->fitting_format.g_fitting_Parity[result_count] = PF;


		end_time = clock();
		printf("%d RESULT Thread is worked......... Processed Time : %d......... \n", result_count, end_time - start_time);
		result_count += 1;

		if (result_count > 15) { result_count = 0; }
		else {}
		//ReleaseSemaphore(sem5, 1, NULL);
	}
}

int main() {
	
	// Initialize the semaphores
	sem1 = CreateSemaphore(NULL, 0, 16, NULL); // input -> eda
	sem2 = CreateSemaphore(NULL, 0, 16, NULL); // eda -> edge
	sem3 = CreateSemaphore(NULL, 0, 16, NULL); // edge -> convert
	sem4 = CreateSemaphore(NULL, 0, 16, NULL); // convert -> fitting

	// declare structure
	MAIN_FORMAT main_data;
	memset(&main_data, 0, sizeof(main_data));

	// Create the threads
	thread t1(input_thread, &main_data);
	thread t2(edge_thread, &main_data);
	thread t3(convert_thread, &main_data);
	thread t4(fitting_thread, &main_data);
	thread t5(result_thread, &main_data);

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

