#include "SensorHCSR04.h"
#include "Timer.h"
#include "FadedLed.h"
#include "Blinker.h"
#include "SensorHCSR04.h"

//Blinker ledBlinker(new FadedLed(11), 2000, 2000);

SensorHCSR04 sensor(13, 12);
FadedLed greenLed(11, 10);
FadedLed blueLed(10, 10);
FadedLed yellowLed(6, 10);
Led buzzer(8);

const int maxDistance = 40;
bool prevBuzzOn = false;

const int oneLedDistance = maxDistance / 3;

void setup() {
	Serial.begin(9600);
}

void loop() {
	greenLed.Loop();
	blueLed.Loop();
	yellowLed.Loop();

	long distance = sensor.GetCmDistance();
	
	//if (distance <= maxDistance && distance >= 0)
	//{
	//	int brightness = (distance * 255) / maxDistance;
	//	greenLed.SetBrightness(255 - brightness);
	//	blueLed.SetBrightness(255 - brightness);
	//	yellowLed.SetBrightness(255 - brightness);

	//	/*Serial.print(255 - brightness);
	//	Serial.print(" ");
	//	Serial.println(distance);*/
	//}
	//else
	//{
	//	greenLed.SetBrightness(0);
	//	blueLed.SetBrightness(0);
	//	yellowLed.SetBrightness(0);
	//	/*Serial.print(0);
	//	Serial.print(" ");
	//	Serial.println(distance);*/
	//}

	Serial.println(distance);

	greenLed.SetBrightness(0);
	blueLed.SetBrightness(0);
	yellowLed.SetBrightness(0);

	if (distance <= maxDistance && distance >= 0)
	{
		if (distance < oneLedDistance)
		{
			yellowLed.SetBrightness(255);
		}

		if (distance < oneLedDistance * 2)
		{
			blueLed.SetBrightness(255);
		}

		if (distance < maxDistance)
		{
			greenLed.SetBrightness(255);
		}

		/*Serial.print(255 - brightness);
		Serial.print(" ");
		Serial.println(distance);*/
	}

	PlayBuzzer(distance);

	delay(10);
}

void PlayBuzzer(int distance)
{
	if (distance < maxDistance / 5 && distance >= 0)
	{
		if (prevBuzzOn)
		{
			buzzer.On();
		}
		else
		{
			prevBuzzOn = true;
		}
	}
	else
	{
		buzzer.Off();
		prevBuzzOn = false;
	}
}