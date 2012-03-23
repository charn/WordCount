#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "bintree.h"
#include "sanalaskuri.h"
#include "dynchar.h"

BinTree *puu;
BinSilmu *silmu;


int main(int argc, char **argv) {
	
	FILE *mista, *minne;
	int i;

	mista = stdin;
	minne = stdout;

	/* Tarkistetaan jos halutaan tulostaa ohjeet. h -vipu */
	for(i=1; i < argc; i++) {
		if(strstr(argv[i],"-h") || strstr(argv[i],"--help")) {
			tulostaOhjeet(argv[0]);
			return EXIT_SUCCESS;
		}
	}

	/* Tarkistetaan jos tulostiedosto on määritelty. o -vipu */
	for(i=1; i < argc; i++) {
		if(strstr(argv[i],"-s") || strstr(argv[i],"--source")) {
			if((i+1) < argc) {
				if((mista=fopen(argv[i+1], "r")) == NULL) {
					fprintf(stderr, "Tiedoston %s avaaminen ei onnistunut.\n", argv[i+1]);
					return EXIT_FAILURE;
				}
			}
			else {
				tulostaOhjeet(argv[0]);
				return EXIT_FAILURE;
			}
			break;
		}
	}

	/* Tarkistetaan jos tulostiedosto on määritelty. o -vipu */
	for(i=1; i < argc; i++) {
		if(strstr(argv[i],"-o") || strstr(argv[i],"--out")) {
			if((i+1) < argc) {
				if((minne=fopen(argv[i+1], "w")) == NULL) {
					fprintf(stderr, "Tiedoston %s avaaminen ei onnistunut.\n", argv[i+1]);
					return EXIT_FAILURE;
				}
			}
			else {
				tulostaOhjeet(argv[0]);
				return EXIT_FAILURE;
			}
			break;
		}
	}	

	/* Rakennetaan puu, luetaan sinne sanoja ja tulostetaan sanat. */
	puu = buildTree();	
	lueSanoja(mista,puu);
	tulostaSanat(minne,puu);
	free(puu); /* vapautetaan, kun ei enää tarvita */

	/* Suljetaan streamit. */
	if(fclose(mista) == EOF || fclose(minne) == EOF) {
		fprintf(stderr, "Tiedoston sulkeminen ei onnistunut.\n");
		return EXIT_FAILURE;
	}
	
	return EXIT_SUCCESS;
}

int lueSanoja(FILE *fp, BinTree *puu) {
	
	char *sana;
	int pituus = 50;
	int kasvatuspituus = 50;
	char merkki;
	int i = 0;

	if((sana=calloc(pituus,sizeof(char))) == NULL ) {
		fprintf(stderr,"Muistinvaraus merkkijonolle epäonnistui.\n");
		return EXIT_FAILURE;
	}

	while(1) {
		merkki=fgetc(fp);
		
		if(!(isspace(merkki)) && merkki != EOF) {
			/* Kasvatetaan taulukon pituutta jos tila meinaa loppua kesken.
			 * varaa tarvittaessa tilan myös viimeiselle '\0' -merkille
			 * */
			if(i >= pituus) {
				sana = extendChar(sana,pituus,kasvatuspituus);
				pituus += kasvatuspituus;
			}
			/* Asetetaan merkki paikalleen ja kasvatetaan i:tä seuraavaa merkkiä varten. */
			sana[i] = merkki;
			i++;
		}
	
		/* Lisätään sana puuhun jos pituus on oikea,
		 * nollataan sananpituutta laskeva muuttuja i,
		 * lopetetaan lukeminen jos viimeinen luettu merkki oli EOF
		 * */
		else {	
			if(i >= SANAN_MIN_PITUUS) {
				/* Sanan viimeinen merkki on aina '\0' */
				sana[i] = '\0';
				if( (silmu=search(puu->root,sana)) == NULL )
					addSilmu(puu,sana);
				else
					(silmu->count)++;
			}
			
			i = 0;
			if(merkki == EOF) {
				free(sana);
				break;
			}
		}

	}	

	return EXIT_SUCCESS;
}

int tulostaSanat(FILE *fp, BinTree *puu) {

	if(puu == NULL)
		printf("Puuta ei ole alustettu.");
	else {
		fprintf(fp,"\nSanat: lkm\n");
		fprintf(fp,"******************************\n");
		inorderTreeWalk(fp,puu->root);
		fprintf(fp,"******************************\n");
		fprintf(fp,"Eri sanoja yhteenä: %d\n",puu->items);
	}	

	return EXIT_SUCCESS;
}

void tulostaOhjeet( const char *komento ) {
	printf("Sanalaskuri versio %s\n", SANALASKURI_VERSION);
	printf("Ohjelman käyttö: %s [-s tiedosto] [-o tulostiedosto] \n", komento);	
	printf("\nOhjelman mahdolliset parametrit:\n");
	printf("%-30s%s","-h / --help","Tulostaa tämän ohjeen.\n");
	printf("%-30s%s","-s / --source <tiedosto>","Tiedosto, josta sanoja luetaan.\n");
	printf("%-30s%s","-o / --out <tiedosto>","Tiedosto, johon tulokset tallennetaan.\n");
	printf("\nJos parametrejä -s tai -o ei anneta, olettaa ohjelma syötteen tulevan standarista syöttövirrasta\ntai tulostuksen menevän standardiin tulostusvirtaan.\n");
	printf("Jos syötettä annetaan näppäimistöllä, voidaan sanojen antaminen lopettaa painamalla CTRL-D\n");

}
