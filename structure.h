#pragma once
#include "global.h"
#include <iostream>

/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////
// Thread struct -- Total 각 thread는 120 Mbytes로 통일 
/////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////

typedef struct _INPUT_FORMAT {

	char g_input_CoilID[OUT][16]; // 1*16 *16 bytes = 256
	char g_input_Cspare00[OUT][16];
	char g_input_Cspare01[OUT][16];
	char g_input_Cspare02[OUT][16];
	//1,024 bytes

	int32_t g_input_Parity[OUT]; //64 bytes
	int32_t g_input_Alarm[OUT];
	int32_t g_input_Count[OUT];
	int32_t g_input_Speed[OUT];
	int32_t g_input_Status[OUT];
	int32_t g_input_Length[OUT];
	int32_t g_input_Runningtime[OUT];
	int32_t g_input_DS[OUT];
	int32_t g_input_WS[OUT];
	int32_t g_input_Ispare01[OUT];
	int32_t g_input_Ispare02[OUT];
	int32_t g_input_Ispare03[OUT];
	int32_t g_input_Ispare04[OUT];
	int32_t g_input_Ispare05[OUT];
	int32_t g_input_Ispare06[OUT];
	int32_t g_input_Ispare07[OUT];
	int32_t g_input_Ispare08[OUT];
	int32_t g_input_Ispare09[OUT];
	int32_t g_input_Ispare10[OUT];
	int32_t g_input_Ispare11[OUT];
	int32_t g_input_Ispare12[OUT];
	int32_t g_input_Ispare13[OUT];
	int32_t g_input_Ispare14[OUT];
	int32_t g_input_Ispare15[OUT];
	int32_t g_input_Ispare16[OUT];
	int32_t g_input_Ispare17[OUT];
	int32_t g_input_Ispare18[OUT];
	int32_t g_input_Ispare19[OUT];
	int32_t g_input_Ispare20[OUT];
	int32_t g_input_Ispare21[OUT];
	int32_t g_input_Ispare22[OUT];
	int32_t g_input_Ispare23[OUT];
	int32_t g_input_Ispare24[OUT];
	int32_t g_input_Ispare25[OUT];
	int32_t g_input_Ispare26[OUT];
	int32_t g_input_Ispare27[OUT];
	int32_t g_input_Ispare28[OUT];
	int32_t g_input_Ispare29[OUT];
	//2,432 bytes
	int32_t g_input_XArray[OUT][XP]; //1920*16*4 = 122,880 bytes
	int32_t g_input_YArray[OUT][XP];
	//245,760 bytes

	double g_input_Dspare00[OUT][XP]; //16*8*1920 = 245,760 bytes
	double g_input_Dspare01[OUT][XP];
	double g_input_Dspare02[OUT][XP];
	double g_input_Dspare03[OUT][XP];
	//983,040 bytes

	uint8_t g_input_Buffer[OUT][XP * YP * RGB]; // 1byte -> 6,220,800 bytes * 16개 = 99,532,800 bytes  XP*YP*RGB  1920*1080*3
	uint8_t g_input_ROIBuffer[OUT][XP * RY]; // 1byte -> 122,880 bytes * 16개 = 1,966,080 bytes
	//101,498,880 bytes
	//uint8_t g_input_UAspare00[8634432];
	//uint8_t g_input_UAspare01[8634432];

}INPUT_FORMAT;
//Input(except SAspare) = 102,731,136 bytes 


typedef struct _EDGE_FORMAT {

	char g_edge_CoilID[OUT][16]; // 1*16 *16 bytes = 256
	char g_edge_Cspare01[OUT][16];
	char g_edge_Cspare02[OUT][16];
	char g_edge_Cspare03[OUT][16];
	//1,024 bytes

	int32_t g_edge_Parity[OUT]; //64 bytes
	int32_t g_edge_Alarm[OUT];
	int32_t g_edge_Count[OUT];
	int32_t g_edge_Speed[OUT];
	int32_t g_edge_Status[OUT];
	int32_t g_edge_Length[OUT];
	int32_t g_edge_Runningtime[OUT];
	int32_t g_edge_DS[OUT];
	int32_t g_edge_WS[OUT];
	int32_t g_edge_Ispare01[OUT];
	int32_t g_edge_Ispare02[OUT];
	int32_t g_edge_Ispare03[OUT];
	int32_t g_edge_Ispare04[OUT];
	int32_t g_edge_Ispare05[OUT];
	int32_t g_edge_Ispare06[OUT];
	int32_t g_edge_Ispare07[OUT];
	int32_t g_edge_Ispare08[OUT];
	int32_t g_edge_Ispare09[OUT];
	int32_t g_edge_Ispare10[OUT];
	int32_t g_edge_Ispare11[OUT];
	int32_t g_edge_Ispare12[OUT];
	int32_t g_edge_Ispare13[OUT];
	int32_t g_edge_Ispare14[OUT];
	int32_t g_edge_Ispare15[OUT];
	int32_t g_edge_Ispare16[OUT];
	int32_t g_edge_Ispare17[OUT];
	int32_t g_edge_Ispare18[OUT];
	int32_t g_edge_Ispare19[OUT];
	int32_t g_edge_Ispare20[OUT];
	int32_t g_edge_Ispare21[OUT];
	int32_t g_edge_Ispare22[OUT];
	int32_t g_edge_Ispare23[OUT];
	int32_t g_edge_Ispare24[OUT];
	int32_t g_edge_Ispare25[OUT];
	int32_t g_edge_Ispare26[OUT];
	int32_t g_edge_Ispare27[OUT];
	int32_t g_edge_Ispare28[OUT];
	int32_t g_edge_Ispare29[OUT];
	//2,432 bytes
	int32_t g_edge_XArray[OUT][XP]; //1920*16*4 = 122,880 bytes
	int32_t g_edge_YArray[OUT][XP];
	//245,760 bytes

	double g_edge_Dspare00[OUT][XP]; //16*8*1920 = 245,760 bytes
	double g_edge_Dspare01[OUT][XP];
	double g_edge_Dspare02[OUT][XP];
	double g_edge_Dspare03[OUT][XP];
	//983,040 bytes

	uint8_t g_edge_Buffer[OUT][XP * YP * RGB]; // 1byte -> 6,220,800 bytes * 16개 = 99,532,800 bytes
	uint8_t g_edge_ROIBuffer[OUT][XP * RY]; // 1byte -> 122,880 bytes * 16개 = 1,966,080 bytes
	//101,498,880 bytes
	//uint8_t g_edge_UAspare00[8634432];
	//uint8_t g_edge_UAspare01[8634432];

}EDGE_FORMAT;
//Edge(except SAspare) =  102,731,136 bytes

typedef struct _CONVERT_FORMAT {

	char g_convert_CoilID[OUT][16]; // 1*16 *16 bytes = 256
	char g_convert_Cspare01[OUT][16];
	char g_convert_Cspare02[OUT][16];
	char g_convert_Cspare03[OUT][16];
	//1,024 bytes

	int32_t g_convert_Parity[OUT]; //64 bytes
	int32_t g_convert_Alarm[OUT];
	int32_t g_convert_Count[OUT];
	int32_t g_convert_Speed[OUT];
	int32_t g_convert_Status[OUT];
	int32_t g_convert_Length[OUT];
	int32_t g_convert_Runningtime[OUT];
	int32_t g_convert_DS[OUT];
	int32_t g_convert_WS[OUT];
	int32_t g_convert_DATASIZE[OUT];
	int32_t g_convert_Ispare01[OUT];
	int32_t g_convert_Ispare02[OUT];
	int32_t g_convert_Ispare03[OUT];
	int32_t g_convert_Ispare04[OUT];
	int32_t g_convert_Ispare05[OUT];
	int32_t g_convert_Ispare06[OUT];
	int32_t g_convert_Ispare07[OUT];
	int32_t g_convert_Ispare08[OUT];
	int32_t g_convert_Ispare09[OUT];
	int32_t g_convert_Ispare10[OUT];
	int32_t g_convert_Ispare11[OUT];
	int32_t g_convert_Ispare12[OUT];
	int32_t g_convert_Ispare13[OUT];
	int32_t g_convert_Ispare14[OUT];
	int32_t g_convert_Ispare15[OUT];
	int32_t g_convert_Ispare16[OUT];
	int32_t g_convert_Ispare17[OUT];
	int32_t g_convert_Ispare18[OUT];
	int32_t g_convert_Ispare19[OUT];
	int32_t g_convert_Ispare20[OUT];
	int32_t g_convert_Ispare21[OUT];
	int32_t g_convert_Ispare22[OUT];
	int32_t g_convert_Ispare23[OUT];
	int32_t g_convert_Ispare24[OUT];
	int32_t g_convert_Ispare25[OUT];
	int32_t g_convert_Ispare26[OUT];
	int32_t g_convert_Ispare27[OUT];
	int32_t g_convert_Ispare28[OUT];
	//2,432 bytes
	int32_t g_convert_XArray[OUT][XP]; //1920*16*4 = 122,880 bytes
	int32_t g_convert_YArray[OUT][XP];
	//245,760 bytes

	double g_convert_Dspare00[OUT][XP]; //16*8*1920 = 245,760 bytes
	double g_convert_Dspare01[OUT][XP];
	double g_convert_Dspare02[OUT][XP];
	double g_convert_Dspare03[OUT][XP];
	//983,040 bytes

	uint8_t g_convert_Buffer[OUT][XP * YP * RGB]; // 1byte -> 6,220,800 bytes * 16개 = 99,532,800 bytes
	uint8_t g_convert_ROIBuffer[OUT][XP * RY]; // 1byte -> 122,880 bytes * 16개 = 1,966,080 bytes
	//101,498,880 bytes
	//uint8_t g_convert_UAspare00[8634432];
	//uint8_t g_convert_UAspare01[8634432];

}CONVERT_FORMAT;
//Convert(except SAspare) =  102,731,136 bytes

typedef struct _FITTING_FORMAT {

	char g_fitting_CoilID[OUT][16]; // 1*16 *16 bytes = 256
	char g_fitting_Cspare01[OUT][16];
	char g_fitting_Cspare02[OUT][16];
	char g_fitting_Cspare03[OUT][16];
	//1,024 bytes

	int32_t g_fitting_Parity[OUT]; //64 bytes
	int32_t g_fitting_Alarm[OUT];
	int32_t g_fitting_Count[OUT];
	int32_t g_fitting_Speed[OUT];
	int32_t g_fitting_Status[OUT];
	int32_t g_fitting_Length[OUT];
	int32_t g_fitting_Runningtime[OUT];
	int32_t g_fitting_DS[OUT];
	int32_t g_fitting_WS[OUT];
	int32_t g_fitting_DATASIZE[OUT];
	int32_t g_fitting_Ispare01[OUT];
	int32_t g_fitting_Ispare02[OUT];
	int32_t g_fitting_Ispare03[OUT];
	int32_t g_fitting_Ispare04[OUT];
	int32_t g_fitting_Ispare05[OUT];
	int32_t g_fitting_Ispare06[OUT];
	int32_t g_fitting_Ispare07[OUT];
	int32_t g_fitting_Ispare08[OUT];
	int32_t g_fitting_Ispare09[OUT];
	int32_t g_fitting_Ispare10[OUT];
	int32_t g_fitting_Ispare11[OUT];
	int32_t g_fitting_Ispare12[OUT];
	int32_t g_fitting_Ispare13[OUT];
	int32_t g_fitting_Ispare14[OUT];
	int32_t g_fitting_Ispare15[OUT];
	int32_t g_fitting_Ispare16[OUT];
	int32_t g_fitting_Ispare17[OUT];
	int32_t g_fitting_Ispare18[OUT];
	int32_t g_fitting_Ispare19[OUT];
	int32_t g_fitting_Ispare20[OUT];
	int32_t g_fitting_Ispare21[OUT];
	int32_t g_fitting_Ispare22[OUT];
	int32_t g_fitting_Ispare23[OUT];
	int32_t g_fitting_Ispare24[OUT];
	int32_t g_fitting_Ispare25[OUT];
	int32_t g_fitting_Ispare26[OUT];
	int32_t g_fitting_Ispare27[OUT];
	int32_t g_fitting_Ispare28[OUT];
	//2,432 bytes
	int32_t g_fitting_XArray[OUT][XP]; //1920*16*4 = 122,880 bytes
	int32_t g_fitting_YArray[OUT][XP];
	//245,760 bytes

	double g_fitting_Array[OUT][XP]; //16*8*1920 = 245,760 bytes
	double g_fitting_Dspare00[OUT][XP];
	double g_fitting_Dspare01[OUT][XP];
	double g_fitting_Dspare02[OUT][XP];
	//983,040 bytes

	uint8_t g_fitting_Buffer[OUT][XP * YP * RGB]; // 1byte -> 6,220,800 bytes * 16개 = 99,532,800 bytes
	uint8_t g_fitting_ROIBuffer[OUT][XP * RY]; // 1byte -> 122,880 bytes * 16개 = 1,966,080 bytes
	//101,498,880 bytes
	//uint8_t g_fitting_UAspare00[8634432];
	//uint8_t g_fitting_UAspare01[8634432];

}FITTING_FORMAT;
//Fitting(except SAspare) =  102,731,136 bytes


typedef struct _RESULT_FORMAT {

	char g_result_CoilID[OUT][16]; // 1*16 *16 bytes = 256
	char g_result_Cspare01[OUT][16];
	char g_result_Cspare02[OUT][16];
	char g_result_Cspare03[OUT][16];
	//1,024 bytes

	int32_t g_result_Parity[OUT]; //64 bytes
	int32_t g_result_Alarm[OUT];
	int32_t g_result_Count[OUT];
	int32_t g_result_Speed[OUT];
	int32_t g_result_Status[OUT];
	int32_t g_result_Length[OUT];
	int32_t g_result_Runningtime[OUT];
	int32_t g_result_DS[OUT];
	int32_t g_result_WS[OUT];
	int32_t g_result_DATASIZE[OUT];
	int32_t g_result_Ispare01[OUT];
	int32_t g_result_Ispare02[OUT];
	int32_t g_result_Ispare03[OUT];
	int32_t g_result_Ispare04[OUT];
	int32_t g_result_Ispare05[OUT];
	int32_t g_result_Ispare06[OUT];
	int32_t g_result_Ispare07[OUT];
	int32_t g_result_Ispare08[OUT];
	int32_t g_result_Ispare09[OUT];
	int32_t g_result_Ispare10[OUT];
	int32_t g_result_Ispare11[OUT];
	int32_t g_result_Ispare12[OUT];
	int32_t g_result_Ispare13[OUT];
	int32_t g_result_Ispare14[OUT];
	int32_t g_result_Ispare15[OUT];
	int32_t g_result_Ispare16[OUT];
	int32_t g_result_Ispare17[OUT];
	int32_t g_result_Ispare18[OUT];
	int32_t g_result_Ispare19[OUT];
	int32_t g_result_Ispare20[OUT];
	int32_t g_result_Ispare21[OUT];
	int32_t g_result_Ispare22[OUT];
	int32_t g_result_Ispare23[OUT];
	int32_t g_result_Ispare24[OUT];
	int32_t g_result_Ispare25[OUT];
	int32_t g_result_Ispare26[OUT];
	int32_t g_result_Ispare27[OUT];
	int32_t g_result_Ispare28[OUT];
	//2,432 bytes
	int32_t g_result_XArray[OUT][XP]; //1920*16*4 = 122,880 bytes
	int32_t g_result_YArray[OUT][XP];
	//245,760 bytes

	double g_result_Array[OUT][XP]; //16*8*1920 = 245,760 bytes
	double g_result_Dspare00[OUT][XP];
	double g_result_Dspare01[OUT][XP];
	double g_result_Dspare02[OUT][XP];
	//983,040 bytes

	uint8_t g_result_Buffer[OUT][XP * YP * RGB]; // 1byte -> 6,220,800 bytes * 16개 = 99,532,800 bytes
	uint8_t g_result_ROIBuffer[OUT][XP * RY]; // 1byte -> 122,880 bytes * 16개 = 1,966,080 bytes
	//101,498,880 bytes
	//uint8_t g_result_UAspare00[8634432];
	//uint8_t g_result_UAspare01[8634432];

}RESULT_FORMAT;
//Result(except SAspare) =  102,731,136 bytes

typedef struct _MAIN_FORMAT {
	INPUT_FORMAT input_format;
	//EDA_FORMAT eda_format;
	EDGE_FORMAT edge_format;
	CONVERT_FORMAT convert_format;
	FITTING_FORMAT fitting_format;
	RESULT_FORMAT result_format;
}MAIN_FORMAT;

#pragma once