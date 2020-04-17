make: assignment4.c Motor.c
	gcc -Wall assignment4.c Motor.c -o assignment4 -lwiringPi -lpthread

clean:
	rm assignment4
