Michael Allen-Bond
WSU ID: 011386199
Email: michael.allen-bond@wsu.edu
CS 460
02/19/2016
Dr. Zhang

README

This program will execute a pthread based version of the producer/consumer problem.

To Compile:

>"make"

To Execute:

>./procon <sleep time> <# of producers> <# of consumers>

For Sequential Output:

>./procon <sleep time> <# of producers> <# of consumers> d

I've capped the number of threads for producers and consumers at 200, but if you like, you can increase it in the .c file (THREAD_MAX).  

The sleep time for each thread will be rand()%<sleep time>

Archive Contents:

	README.txt
	procon.c
	buffer.h
	Makefile
	M.A.B_P2.pdf

Thank you very much for your time.