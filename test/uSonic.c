#include <stdio.h>
#include <wiringPi.h>

#define TRIG	27
#define	ECHO	28

void Trigger()
{
	digitalWrite(TRIG, HIGH);
	delayMicroseconds(10);
	digitalWrite(TRIG, LOW);
	delayMicroseconds(200);	// wait for Burst end
}

double Distance()
{
	while(1)	// Burst over, count start
	{
		int e = digitalRead(ECHO);
		if(e == 1) break;
	}
	int t1 = micros();
	while(1)	// wait until echo receive
	{
		int e = digitalRead(ECHO);
		if(e == 0) break;
	}
	int t2 = micros();
	
	double dist = (t2 - t1) * 0.017;
	
	return dist;
}

int main()
{
	wiringPiSetup();
	pinMode(TRIG, OUTPUT);
	pinMode(ECHO, INPUT);
	digitalWrite(TRIG, LOW); delay(10);  // 초기 pin 상태 0
	while(1)
	{
		// Trigger signal
		Trigger();		
		double dist = Distance();
		printf("Distance : %.2f\n\n",dist);	
		delay(200);	// delay for next trigger
	}
	return 1;
}

