make: assignment4.c Motor.c Speed_Sensor.c
	gcc -Wall assignment4.c Motor.c Speed_Sensor.c -o assignment4 -lwiringPi -lpthread

clean:
	rm assignment4
