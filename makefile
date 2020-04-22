make: assignment4.c Motor.c Encoder.c
	gcc -Wall assignment4.c Motor.c -o assignment4 -lwiringPi -lpthread
	gcc -Wall Encoder.c -o encoder -lwiringPi 

clean:
	rm assignment4
