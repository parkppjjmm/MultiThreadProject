### Multi-Thread Flow Chart
![multithread](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/f26fed4f-6490-49bf-a5ae-112c4ffe719e)
![image](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/5b38d1c8-0a22-4b26-bdc8-97775786036f)
■ 때로는 영상처리에서 Time과 Accuracy 중 어떤 것이 더 중요한지 갈린다. 이번에 진행했던 영상처리의 경우 Time이 무조건적으로 중요했기 때문에 적당한 Accuracy를 유지하며, 무조건적으로 Time이 초당 10 frame을 처리할 수 있도록 설계하는 것이 중요했다.

■ 이를 위해 CPU에선 Thread 처리 방법이 있었다. 기본적으로 프로그램은 위에서 아래로 Sequencial 방식으로 진행한다. 영상 처리를 수행하게 될 경우 2중 for loop가 여러 번 수행하게 될 것이고(이거는 빈번), 심할 경우 3중 for loop가 있을 수도 있다(이거는 최악!!).

■ 이럴 경우 초당 10 frame을 절대 수행하지 못하게 된다. 왜냐하면, 대표적으로 1920 by 1080 화면의 픽셀을 2중 for만 수행하는데 얼마나 많은 시간이 걸리겠는가? 상상만 해도 처리 후 나오는 이미지가 "버벅 버벅"할 것이다. 이를 보완하기 위해 Multi-Thread 개념을 도입하게 되었고, 전체 시스템을 부분 부분으로 나누어 각각의 Thread로 구성시켰다.

## C++ 멀티스레딩(multi-thread) 기본 개념: (파일 이름 : BasicThread_v0_1.cpp)
### 세마포어(semaphore)와 while() loop를 사용한 프로세스 병렬 처리 이해하기
### https://easycode.tistory.com/25

![image](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/e0e85631-c14d-40ac-9056-b068c5079bac)

멀티스레딩은 여러 실행 스레드가 단일 프로세스 내에서 동시에 실행될 수 있도록 하는 프로그래밍 개념입니다. 

스레드는 프로세스 내에서 가장 작은 실행 단위이며 가볍고 독립적인 명령 시퀀스로 생각할 수 있습니다. 

각 스레드는 자체 스택 및 프로그램 카운터를 갖지만 동일한 프로세스의 다른 스레드와 메모리 및 파일 핸들과 같은 동일한 주소 공간 및 리소스를 공유합니다.

### File name : BasicThread_v0_1.cpp
/* Code Explain
This code demonstrates the use of Windows semaphores to synchronize three threads in C++. 
It simulates a simple pipeline, where each thread performs some work and then signals the next thread to start. 
*/

###
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
### 코드 설명 (BasicThread_v0_1.cpp)
이 코드는 Windows 세마포어를 사용하여 C++에서 세 개의 스레드를 동기화하는 방법을 보여줍니다. 각 스레드가 일부 작업을 수행한 다음 시작하도록 다음 스레드에 신호를 보내는 간단한 파이프라인을 시뮬레이트합니다. 코드를 단계별로 분석해 보겠습니다.

### ▶ Header files and namespace:
코드에는 iostream, thread, Windows.h, stdlib.h, stdint.h, ctime, vector 및 stdio.h와 같은 필수 헤더 파일이 포함되어 있습니다. 또한 std 네임스페이스의 사용을 선언합니다.

### ▶ Global variables:
3개의 세마포어 핸들 sem1, sem2 및 sem3이 전역 변수로 정의됩니다. 스레드를 동기화하는 데 사용됩니다.

### ▶ Thread functions:

★ thread_1(): 이 함수는 100밀리초 동안 휴면하여 작업을 시뮬레이트합니다. 작업을 완료한 후 작업을 시작하기 위해 thread_2()에 신호를 보내기 위해 sem1을 해제합니다. 이 스레드는 사용자 입력이 "시작"인 동안 루프에서 계속 작동합니다.
 
★ thread_2(): 이 함수는 thread_1()에 의해 sem1이 해제되기를 기다립니다. 해제되면 thread_2()가 작업을 수행한 다음(현재 비어 있지만 원하는 기능으로 확장할 수 있음) sem2를 해제하여 thread_3()에 신호를 보내 작업을 시작합니다.
 
★ thread_3(): thread_2()와 유사하게 이 함수는 작업을 수행하기 전에 thread_2()에 의해 sem2가 해제될 때까지 기다립니다(현재 비어 있지만 원하는 기능으로 확장할 수 있음).
 

### ▶ Main function:

★ Initializes semaphores: sem1과 sem2는 초기 카운트 0과 최대 카운트 1로 생성됩니다. 두 번째 세마포어인 sem2는 카운트 0으로 초기화되어 첫 번째 스레드가 신호를 보낼 때까지 두 번째 스레드가 대기하도록 합니다.
 
★ Creates threads: t1, t2 및 t3은 각각 thread_1(), thread_2() 및 thread_3() 함수에 대해 생성됩니다.
 
★ Joins threads: 각 스레드에 대해 join() 함수가 호출되어 기본 함수가 종료하기 전에 모든 스레드가 완료될 때까지 대기하는지 확인합니다.
 
★ Closes semaphore handles: 프로그램이 종료되기 전에 sem1 및 sem2에 대한 핸들이 닫힙니다.
	 
이 코드는 각 스레드 함수(thread_1(), thread_2() 및 thread_3())에 기능을 추가하여 확장할 수 있습니다. 현재 구조는 스레드가 동기화된 방식으로 작동하도록 보장합니다. 하나의 스레드가 파이프라인을 시뮬레이트하면서 작업을 시작하도록 다음 스레드에 신호를 보냅니다.

### 결과
![image](https://github.com/parkppjjmm/MultiThreadProject/assets/56201670/c020993b-0709-4f28-abb1-16b32088bf59)



## C++ 멀티스레딩(multi-thread) 응용 개념: (파일 이름 : BasicThread_v0.cpp)
### 멀티쓰레드 속에 공유메모리 적용
### https://easycode.tistory.com/23

공유 메모리는 여러 프로세스가 데이터를 읽고 쓰기 위해 공통 메모리 공간에 액세스하고 공유할 수 있도록 하는 IPC(프로세스 간 통신) 방법입니다.
C++에서 공유 메모리는 다양한 라이브러리와 메커니즘을 사용하여 얻을 수 있습니다. 
여러 프로세스 또는 스레드가 함께 작업하여 문제를 해결하거나 작업을 보다 효율적으로 수행하는 병렬 프로그래밍에서 특히 유용합니다.

▶ Windows shared memory:
Windows는 메모리 매핑된 파일과 CreateFileMapping(), MapViewOfFile() 및 UnmapViewOfFile() 함수를 사용하여 고유한 공유 메모리 메커니즘을 제공합니다. 
이를 통해 Windows에서 실행되는 프로세스 간에 공유 메모리를 생성하고 관리할 수 있습니다.


### ■ 프로세스1: Shared memory: char-type data 

	// Declare a HANDLE variable for the shared memory object
	HANDLE HanValue1;
	
	// Open the shared memory object named "IPCValue1" with read and write access
	HanValue1 = OpenFileMapping(FILE_MAP_ALL_ACCESS, FALSE, "IPCValue1");
	
	// Check if the shared memory object was opened successfully
	if (HanValue1 == NULL) {
	    // If not, print an error message and exit the program
	    std::cout << currentDateTime() << " -- " << "Could not read HanValue1 : " << GetLastError() << std::endl;
	    exit(0);
	}
	
	// Map the shared memory object into the address space of the current process
	char* chkValue1 = (char*)MapViewOfFile(HanValue1, FILE_MAP_WRITE, 0, 0, 0);

### [코드 설명]

이 코드는 Windows 시스템에서 공유 메모리를 사용하는 프로세스 간 통신(IPC)용입니다. 여기에는 OpenFileMapping() 및 MapViewOfFile()의 두 가지 주요 기능이 포함됩니다. 이 코드의 목적은 공유 메모리 개체를 열고 현재 프로세스의 주소 공간에 매핑하여 프로세스가 공유 메모리를 읽거나 수정할 수 있도록 하는 것입니다.

▶ Declaration of HANDLE HanValue1 (HANDLE HanValue1 선언):
HANDLE은 파일, 프로세스 또는 공유 메모리와 같은 운영 체제 리소스에 대한 "핸들"을 나타내는 Windows 데이터 유형입니다. 이 경우 파일 매핑 개체(공유 메모리)에 대한 핸들을 나타냅니다.

▶ Opening the file mapping object (파일 매핑 개체 열기):
OpenFileMapping() 함수는 FILE_MAP_ALL_ACCESS 액세스 권한이 있는 "IPCValue1"이라는 기존 공유 메모리 개체를 열기 위해 호출됩니다. 즉, 프로세스가 공유 메모리에 대한 읽기 및 쓰기 액세스 권한이 있음을 의미합니다. 함수가 실패하면 NULL을 반환하고 후속 오류 검사에서 오류 메시지를 인쇄하고 프로그램을 종료합니다.

▶ Mapping the shared memory object into the process's address space (공유 메모리를 프로세스의 주소 공간에 매핑):
MapViewOfFile() 함수는 공유 메모리 객체(HanValue1)를 현재 프로세스의 주소 공간에 매핑하기 위해 호출됩니다. 이 함수는 매핑된 보기의 시작 주소에 대한 포인터를 반환하고 코드 조각은 이 포인터를 char* chkValue1 변수에 저장합니다. 매핑이 성공하면 이제 chkValue1을 사용하여 공유 메모리에서 데이터를 읽고 쓸 수 있습니다.

[관련 문서]

https://learn.microsoft.com/ko-kr/windows/win32/memory/creating-named-shared-memory

### □ 프로세스2: Shared memory: char-type data 

	// Declare a HANDLE variable for the shared memory object
	HANDLE HanValue1;
	
	// Create a new shared memory object named "IPCValue1" with read and write access and a size of 16 bytes
	HanValue1 = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(char) * 16, "IPCValue1");
	
	// Check if the shared memory object was created successfully
	if (HanValue1 == NULL) {
	    // If not, print an error message and exit the program
	    std::cout << currentDateTime() << " -- " << "Could not read HanCoilID : " << GetLastError() << std::endl;
	    exit(0);
	}
	
	// Map the shared memory object into the address space of the current process
	char* recvValue1 = (char*)MapViewOfFile(HanValue1, FILE_MAP_WRITE, 0, 0, 0);

### [코드 설명]

이 코드의 목적은 공유 메모리 개체를 만든 다음 현재 프로세스의 주소 공간에 매핑하여 프로세스가 공유 메모리를 읽거나 수정할 수 있도록 하는 것입니다.

▶ Declaration of HANDLE HanValue1 (HANDLE HanValue1 선언):
HANDLE은 파일, 프로세스 또는 공유 메모리와 같은 운영 체제 리소스에 대한 "핸들"을 나타내는 Windows 데이터 유형입니다. 이 경우 파일 매핑 개체(공유 메모리)에 대한 핸들을 나타냅니다.

▶ Creating the file mapping object (파일 매핑 개체 만들기):
CreateFileMapping() 함수는 PAGE_READWRITE 액세스 권한이 있는 "IPCValue1"이라는 새 공유 메모리 개체를 만들기 위해 호출됩니다. 즉, 공유 메모리를 읽고 쓸 수 있습니다. 공유 메모리의 크기는 sizeof(char) * 16으로 지정되며 각 문자는 1바이트의 메모리를 차지하므로 16바이트입니다. 함수가 실패하면 NULL을 반환하고 후속 오류 검사에서 오류 메시지를 인쇄하고 프로그램을 종료합니다.

▶ Mapping the shared memory object into the process's address space (공유 메모리 프로세스의 주소 공간에 매핑):
MapViewOfFile() 함수는 공유 메모리 객체(HanValue1)를 현재 프로세스의 주소 공간에 매핑하기 위해 호출됩니다. 이 함수는 매핑된 보기의 시작 주소에 대한 포인터를 반환하고 코드 조각은 이 포인터를 char* recvValue1 변수에 저장합니다. 매핑이 성공하면 이제 recvValue1을 사용하여 공유 메모리에 데이터를 읽고 쓸 수 있습니다.

이 코드는 현재 프로세스가 공유 메모리 객체 "IPCValue1"을 생성 및 액세스하고 포인터 recvValue1을 사용하여 데이터를 읽거나 쓸 수 있도록 합니다. UnmapViewOfFile() 및 CloseHandle() 함수를 각각 사용하여 완료되면 공유 메모리를 올바르게 닫고 매핑 해제해야 합니다.

[관련 문서]
https://learn.microsoft.com/en-us/windows/win32/api/winbase/nf-winbase-createfilemappinga
