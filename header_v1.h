/*
This code defines 5 different structures, each of which represent a different thread. 
Each structure contains an array of int32_t values with a length of OUT.
The MAIN_FORMAT structure contains an instance of each of these 5 structures.
*/

#pragma once
#include <iostream>

// Define
#define OUT 16

typedef struct _THREAD1_FORMAT {

	int32_t g_thrad1_Ispare01[OUT];

}THREAD1_FORMAT;

typedef struct _THREAD2_FORMAT {

	int32_t g_thrad2_Ispare01[OUT];

}THREAD2_FORMAT;

typedef struct _THREAD3_FORMAT {

	int32_t g_thrad3_Ispare01[OUT];

}THREAD3_FORMAT;

typedef struct _THREAD4_FORMAT {

	int32_t g_thrad4_Ispare01[OUT];

}THREAD4_FORMAT;

typedef struct _THREAD5_FORMAT {

	int32_t g_thrad5_Ispare01[OUT];

}THREAD5_FORMAT;

typedef struct _MAIN_FORMAT {
	THREAD1_FORMAT thread1_format;
	THREAD2_FORMAT thread2_format;
	THREAD3_FORMAT thread3_format;
	THREAD4_FORMAT thread4_format;
	THREAD5_FORMAT thread5_format;
}MAIN_FORMAT;

#pragma once