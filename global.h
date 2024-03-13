#pragma once

#define	BUFFER_SIZE		25628300
#define	TRUE			1 // True
#define	FALSE			0 // False
// Frame 관련 Define.
#define		XP		1920	// Video Width 1920 1600
#define		YP		1080	// Video Height 1080 1000
#define		RGB		3		// RGB
#define		FS		XP*YP*RGB // XP * YP * RGB
#define		RY		64		// ROI Video Height  64 ->32
#define		HY		530	//원본이미지 높이 보정.
#define		FPS		10		// FPS

// Buffer Define
#define		BS		1800	// A,B Buffer Frame Count
#define		AU		0		// A Buffer Used.
#define		BU		1		// B Buffer Used
#define		OUT		16		// Buffer 개수

// Parity, Alarm, Flag define
#define		PO		1		//Parity on
#define		PF		0		//parity off
#define		AO		1		//Alarm on
#define		AF		0		//Alarm off
#define		CF		1		//Coil Finish
#define		CW		0		//Coil Working

// Time define
#define		MIN		60		// 1분
#define		SMIN	3		// 3분

// Data Type Define		
#define		INT		4	// 4byte
#define		UINT	1	// 1byte
#define		PIXEL	1	// 1pixel
#define		SHORT	2	//	2byte
#define		DOUBLE	2	// 2byte

// Status Define
#define	RECV0		0	//Recv STS 0
#define	RECV1		1	//Recv STS 1
#define	RECV2		2	//Recv STS 2
#define	RECV4		4	//Recv STS 4
#define	RECV10		10	//Recv STS 10

// format define 
#define	DB_Format		".csv"
#define TXT_Format		".txt"
#define	AVI_Format		".avi"

//location Define
#define	THIS			"C:\\This\\"	// 3분치 동영상 저장 로케이션
#define	PRESENT			"D:\\Present\\"	// 하루치 저장 로케이션
#define PROCESSING		"C:\\Processing"	// save 작업시 This 폴더에서 이동 할 폴더

//edge define
#define IMAGE_X_START 0
#define IMAGE_Y_START 950
#define IMAGE_X_RANGE 1920
#define IMAGE_Y_RANGE RY

//convert define
#define FITTING_ARRAY_SIZE XP*1
#define IMAGE_PIXEL_THREASHOLD 50

//fitting define
#define POLYNOMINAL_DEGREE 6

