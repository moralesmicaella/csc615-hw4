make: assignment4.c Motor.c v2.c
	gcc -Wall assignment4.c Motor.c -o assignment4 -lwiringPi -lpthread
	gcc -Wall v2.c -o v2 -lwiringPi 

clean:
	rm assignment4
