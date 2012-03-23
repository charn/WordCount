#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dynchar.h"

char* extendChar(char *sana, int pituus, int kasvatuspituus) {
	
	char *pidempisana;

	if (sana == NULL || pituus < 0 || kasvatuspituus < 0)
		return NULL;

	if((pidempisana=calloc((pituus + kasvatuspituus),sizeof(char))) == NULL ) {
		fprintf(stderr,"Muistinvaraus pidemmälle merkkijonotaulukolle epäonnistui.\n");
		return NULL;
	}
	
	memcpy(pidempisana, sana,(pituus*sizeof(char)));
	free(sana);
	return pidempisana;
}

