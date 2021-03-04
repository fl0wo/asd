#ifndef COPERTURA_H
#define COPERTURA_H

typedef struct{
	int start;
	int end;
} Intervallo;

Intervallo * copertura(Intervallo v[], int dimV, int *dimout);

#endif