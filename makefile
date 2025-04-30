all:main

main: main.c
	gcc main.c -o main

clear:
	rm main
	rm /factures/*.txt