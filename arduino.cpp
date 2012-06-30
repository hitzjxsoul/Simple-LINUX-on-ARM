#include <DallasTemperature.h>
#include "MsTimer2.h"
DallasTemperature tempSensor;
int left_cnt,right_cnt;

void setup(void)
{
	Serial.begin(9600);
	tempSensor.begin(12); /*温度传感器连数字口12*/

	left_cnt = right_cnt = 0;
	attachInterrupt(0,rotateLeftAdd,RISING);/*设置中断，上升沿触发*/
	attachInterrupt(1,rotateRightAdd,RISING);

	/*设置计时器*/
	MsTimer2::set(500,calc());
	MsTimer2::start();
}

void calc(void)
{
    /*温度*/
	switch(tempSensor.isValid())
	{
		case 1:
			Serial.println("Invalid CRC");
			tempSensor.reset();
			return;
		case 2:
			Serial.println("Not a valid device");
			tempSensor.reset();
			return;
	}
	Serial.print(tempSensor.getTemperature());
	Serial.print("C");
	Serial.println();

	/*速度*/
	Serial.print("left : ");
	Serial.print(left_cnt);
	Serial.println();
	
	/*
	Serial.print("right : ");
	Serial.print(right_cnt);
	Serial.println();
	*/

	left_cnt = right_cnt = 0;
}

void rotateLeftAdd()
{
	left_cnt++;
}

void rotateRightAdd()
{
	right_cnt++;
}

