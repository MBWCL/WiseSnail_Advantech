#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "WiseSnail.h"
#if defined(WIN32)
#pragma comment(lib, "WiseSnail.lib")
#endif

#define SERVER_URL		"127.0.0.1"
#define SERVER_PORT		1883
#define SENSOR_DEVICE1_MAC	"000E4C000000"

#define SAMPLE_RATE    1000  // target 1000
#define BUFFER_SIZE    (SAMPLE_RATE*4 + 20)


char datas[15][BUFFER_SIZE];
//  0, 1, 2 -> ecg
//  3, 4, 5 -> scg
//  6, 7, 8 -> gcg
//  9,10,11 -> mcg
// 12,13,14 -> ppg

char rssi[5];
char battery[5];


int Reset(WiseSnail_Data *data) {
	printf("\n###############Reset name %f\n\n",data->value);
}

WiseSnail_InfoSpec interface1[] = {
	{
		WISE_BOOL,
		"/Info/reset",
		"",
		0,
		0,
		1,
		"",
		Reset
	}
};

char SHName[128] = "123";
int SetSHName(WiseSnail_Data *mydata) {
	printf("###############Set SenHub name %s\n",mydata->string);
	strcpy(SHName, mydata->string);
}

int GetSHName(WiseSnail_Data *mydata) {
	printf("###############Get SenHub name %s\n",mydata->string);
	strcpy(mydata->string, SHName);
}

WiseSnail_InfoSpec infospec1[] = {
	{
		WISE_STRING,
		"/Info/Name",
		"",
		.string = "SenHub_libos",
		0,
		0,
		"",
		//SetSHName,
		.getValue = GetSHName
	}
};


WiseSnail_Data data[] = {
	{
        WISE_STRING,
        "AAAAAAAA/ECG_1",
        .string = datas[0],
    },
    {
        WISE_STRING,
        "AAAAAAAA/ECG_2",
        .string = datas[1],
    },
    {
        WISE_STRING,
        "AAAAAAAA/ECG_3",
        .string = datas[2],
    },
	{
        WISE_STRING,
        "AAAAAAAA/SCG_1",
        .string = datas[3],
    },
	{
        WISE_STRING,
        "AAAAAAAA/SCG_2",
        .string = datas[4],
    },
	{
        WISE_STRING,
        "AAAAAAAA/SCG_3",
        .string = datas[5],
    },
	{
        WISE_STRING,
        "AAAAAAAA/GCG_1",
        .string = datas[6],
    },
	{
        WISE_STRING,
        "AAAAAAAA/GCG_2",
        .string = datas[7],
    },
	{
        WISE_STRING,
        "AAAAAAAA/GCG_3",
        .string = datas[8],
    },
	{
        WISE_STRING,
        "AAAAAAAA/MCG_1",
        .string = datas[9],
    },
	{
        WISE_STRING,
        "AAAAAAAA/MCG_2",
        .string = datas[10],
    },
	{
        WISE_STRING,
        "AAAAAAAA/MCG_3",
        .string = datas[11],
    },
	{
        WISE_STRING,
        "AAAAAAAA/PPG_1",
        .string = datas[12],
    },
	{
        WISE_STRING,
        "AAAAAAAA/PPG_2",
        .string = datas[13],
    },
	{
        WISE_STRING,
        "AAAAAAAA/PPG_3",
        .string = datas[14],
    },
	{
        WISE_STRING,
        "AAAAAAAA/rssi",
        .string = rssi,
    },
	{
        WISE_STRING,
        "AAAAAAAA/battery",
        .string = battery,
    },
    {
        WISE_VALUE,
        "AAAAAAAA/sample_rate",
        SAMPLE_RATE
    }
};

void sleepOneSecond() {
	sleep(1);
}

int main (void)
{
	int count = 0;

	WiseSnail_Init("IotGW",NULL, NULL, NULL, 0);
	WiseSnail_RegisterInterface("000E4CAB1234", "Bluetooth", 0, interface1, 1);

	if(WiseSnail_Connect(SERVER_URL, SERVER_PORT, "", "", NULL, 0) == 0) {
		return -1;
	} else {
		sleep(1);
		WiseSnail_RegisterSensor(SENSOR_DEVICE1_MAC, "OnBoard", infospec1, sizeof(infospec1) / sizeof(WiseSnail_InfoSpec));
    }

	while(1) {
        memset(datas, 0, sizeof(datas) / sizeof(char));
		for(size_t i=0; i<15; i++) {
			for(size_t j=0; j<BUFFER_SIZE - 1; j++) {
            			datas[i][j] = (count%26) + 'a';
        		}
		}

		memset(rssi, 0, sizeof(rssi) / sizeof(char));
		for(size_t i=0; i<5-1; i++) {
			rssi[i] = (count%26) + 'a';
		}

		memset(battery, 0, sizeof(battery) / sizeof(char));
		for(size_t i=0; i<5-1; i++) {
			battery[i] = (count%26) + 'a';
		}

		printf("\r\n****** \033[33mSend update.\033[0m ******\r\n");
		WiseSnail_Update(SENSOR_DEVICE1_MAC, data, sizeof(data) / sizeof(WiseSnail_Data));
		WiseSnail_MainLoop(sleepOneSecond);
		count++;
	}
	return 0;
}
