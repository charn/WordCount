#ifndef BINTREE_H
#define BINTREE_H

typedef struct BinSilmu {
	struct BinSilmu *left; /* left child */
	struct BinSilmu *right; /* right child */
	struct BinSilmu *parent; /* pointer to the parent */
	char *string; /* string */
        int count; /* how many times does the string occur */
} BinSilmu;

typedef struct BinTree {
	struct BinSilmu *root; /* Root of the bintree */
	int items; /* How many items does the bintree currently have */
} BinTree;

/* Function: buildTree
 * Purpose: Varaa muistia tyhjälle puulle ja palauttaa osoittimen siihen.
 * Inputs: ei mitään.
 * Returns: osoittimen tyhjään puuhun.
 * Modifies: alustaa items -kentän arvoksi 0 ja root -silmun NULL:ksi.
 * Error checking: palauttaa NULL, jos muistia ei pystytä varaamaan.
 * Sample call: tree = buildTree();
 */

BinTree* buildTree( void );

/* Function: buildSilmu
 * Purpose: Varaa muistia uudelle silmulle ja kopioi siihen parametrinä annetun merkkijonon.
 * Inputs: Osoitin merkkijonoon, joka kopioidaan uuden silmun string -kenttään.
 * Returns: Osoittimen uuteen silmuun.
 * Modifies: Uuden silmun count -kenttä alustetaan arvoon 1 ja string -kenttään kopioidaan parametrinä annettu merkkijono.
 * 	     Silmun parent, left, right -kentät asetetaan NULL:ksi.
 * Error checking: palauttaa NULL jos string osoittaa NULL:iin tai jos muistinvaraus ei onnistu.
 * Sample call: silmu = buildSilmu("merkkijono");
 */

BinSilmu* buildSilmu (const char *string);

/* Function: addSilmu
 * Purpose: Lue silmun annetulla merkkijonolla käyttäen buildSilmu -funktiota. Tämän jälkeen asettaa Silmun
 * 	    oikealle paikalleen vertailemalla sen sisältämää merkkijonoa muiden puissa olevien solmujen
 * 	    merkkijonoihin.
 * Inputs: osoitin puuhun johon silmu halutaan liittää ja osoitin merkkijonoon, joka lisättävään silmuun kopioidaan.
 * Returns: palautta EXIT_SUCCESS jos silmun lisäys puuhun onnistuu ja EXIT_FAILURE jos ei onnistu.
 * Modifies: Lisää puuhun puu silmun merkkijonolla string. puu items -kenttää kasvatetaan yhdellä.
 * 	     Lisättävän silmun parent, left, right kentät asetetaan oikeiksi.
 * Error checking: palauttaa EXIT_FAILURE samassa tilanteessa kuin buildSilmu epäonnistuisi tai jos puu on NULL.
 * Sample call: addSilmu(puu, "mjono");
 */

int addSilmu(BinTree *puu, const char *string);

/* Function: inorderTreeWalk
 * Purpose: Tulostaa silmun ja sen lapsien merkkijonot aakkosjärjestyksessä annettuun streamiin.
 * Inputs: Osoitin silmuun, josta tulostettava puu alkaa. Osoitin avattuun tiedostoon, johon on mahdollista kirjoittaa.
 * Returns: Ei mitään.
 * Modifies: Ei mitään.
 * Error checking: Tarkistaa ettei annettu silmu ole NULL, jos on, niin ei tehdä mitään.
 * Sample call: inorderTreeWalkTiedostoon(fp, node);
 */

void inorderTreeWalk(FILE *fp, BinSilmu *silmu);


/* Function: search
 * Purpose: Etsii tiettyä merkkijonoa silmusta ja kaikista sen lapsista.
 * Inputs: Osoitin silmuun, josta etsintä aloitetaan.
 * Returns: Osoittimeen silmuun, joka vastaa merkkijonoa. Palautetaan NULL jos merkkijonoa ei löydy.
 * Modifies: ei mitään.
 * Error checking: Tarkistaa ettei silmu tai mjono ole NULL, jos on niin ei tehdä mitään.
 * Sample call: search(silmu, "mjono");
 */

BinSilmu* search(BinSilmu *silmu, char *mjono);

#endif
