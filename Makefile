#Fichier Makefile avec ou sans macros (a votre choix)

code: main.o fonctions.o affichage.o
	gcc -fPIC -ansi -Wall main.o fonctions.o affichage.o `pkg-config --cflags --libs gtk+-3.0` -o code
	
main.o : header.h main.c 
	gcc -ansi -Wall -c main.c `pkg-config --cflags --libs gtk+-3.0` -o main.o

fonctions.o : header.h fonctions.c
	gcc -ansi -Wall -c fonctions.c `pkg-config --cflags --libs gtk+-3.0` -o fonctions.o
	
affichage.o : header.h affichage.c
		gcc -ansi -Wall -c affichage.c `pkg-config --cflags --libs gtk+-3.0` -o affichage.o
	
	
clean: 
	rm * .o code
