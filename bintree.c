#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bintree.h"

BinTree* buildTree( void ) {
	
	BinTree *puu = NULL;

	if((puu=malloc(sizeof(BinTree))) != NULL) {
		puu->items = 0;
		puu->root = NULL;
	}
	else
		fprintf(stderr,"Muistinvaraus puulle epäonnistui.\n");	

	return puu;
}

BinSilmu* buildSilmu(const char *data) {
	
	BinSilmu *silmu;
	char *string;

	if(data == NULL) {
		fprintf(stderr,"Ei annettu kelvollista dataa silmulle.\n");
		return NULL;
	}
	
	if((silmu=malloc(sizeof(BinSilmu))) == NULL) {
		fprintf(stderr,"Muistinvaraus silmulle epäonnistui.\n");
		return NULL;
	}
	
	if((string=calloc((strlen(data) + 1),sizeof(char))) == NULL ) { /* varataan myös sanan lopettavalle '\0' -merkille tilaa */
		fprintf(stderr,"Muistinvaraus stringille epäonnistui.\n");
		return NULL;
	}
	
	memcpy(string, data,((strlen(data))*sizeof(char)));
	silmu->string = string;
	silmu->left = NULL;
	silmu->right = NULL;
	silmu->parent = NULL;
	silmu->count = 1; /* There has been one occurrence. */

#ifdef DEBUG
	printf("buildSilmu: %s\n",silmu->string);
#endif
	
	return silmu;
}

int addSilmu(BinTree *puu, const char *string) {
	
	BinSilmu *silmu, *apusilmu, *vanhempi;
	silmu = buildSilmu(string);

	if(silmu==NULL) {
		fprintf(stderr,"Silmua ei onnistuttu luomaan.\n");
		return EXIT_FAILURE;
	}

	if(puu == NULL) {
		fprintf(stderr,"Ei voida laittaa silmua puuhun, jota ei ole olemassa.\n");
		return EXIT_FAILURE;
	}
	
	/* Normaali silmun lisäys  */

	if(puu->root == NULL)
		puu->root = silmu;
	else {
		apusilmu = puu->root;
		
		while(apusilmu != NULL) {
			vanhempi = apusilmu;
			if((strcmp(string, apusilmu->string)) < 0)
				apusilmu = apusilmu->left;
			else
				apusilmu = apusilmu->right;
		}

		silmu->parent = vanhempi;
		if((strcmp(string, vanhempi->string)) < 0)
			vanhempi->left = silmu;
		else
			vanhempi->right = silmu;
	
	}	
	
	(puu->items)++;

#ifdef DEBUG
	printf("addSilmu: %s\n",silmu->string);
#endif

	return EXIT_SUCCESS;
}

BinSilmu* search(BinSilmu *silmu, char *mjono) {
	if(mjono != NULL) {
		while(silmu != NULL && (strcmp(mjono, silmu->string)) != 0 ) {
			if( (strcmp(mjono, silmu->string)) < 0 )
               			silmu = silmu->left;
			else
               			silmu = silmu->right;
		}
	}
	else
		silmu = NULL;
	return silmu;
}

void inorderTreeWalk(FILE *fp, BinSilmu *silmu) {
	if(silmu != NULL) {
		inorderTreeWalk(fp,silmu->left);
		fprintf(fp,"%s  : %d\n",silmu->string,silmu->count);
		inorderTreeWalk(fp,silmu->right);
		free(silmu->string);
		free(silmu); /* vapautetaan, kun ei enää tarvita */
	}
}
