#ifndef SANALASKURI_H
#define SANALASKURI_H

#define SANALASKURI_VERSION "1.1"
/* Lyhyin pituus hyväksyttävälle sanalle */

#define SANAN_MIN_PITUUS 2

/* Function: lueSanoja
 * Purpose: Lukee osoittimen "fp" osoittamasta streamista sanoja ja laittaa niitä binääripuuhun "puu".
 * Inputs: Osoitin auki olevaan streamiin ja alustettuun binääripuuhun, johon sanat laitetaan.
 * Returns: EXIT_SUCCESS, jos lukeminen onnistui ja EXIT_FAILURE jos ei onnistunut.
 * Modifies: Lisää annettuun binääripuuhun silmuja.
 * Error checking: Tarkistaa, että tiedosto on olemassa.
 * Sample call: lueTiedostosta(puu, "text.txt");
 */

int lueSanoja(FILE *fp, BinTree *puu);

/* Function: tulostaSanat
 * Purpose: Tulostaa löytyneet sanat käyttäen apunaan binääripuun inorderTreeWalk -funktiota annettuun streamiin.
 * Inputs: Osoitin puuhun, joka halutaan tulostaa.
 * Returns: EXIT_SUCCESS
 * Modifies: Ei mitään.
 * Error checking: Tarkistaa ettei annettu puu ole NULL.
 * Sample call: tulostaSanat(puu);
 */

int tulostaSanat(FILE *fp, BinTree *puu);

/* Function: tulostaOhjeet
 * Purpose: Tulostaa käyttöohjeet ohjelmalle.
 * Inputs: Osoitin merkkijonoon, jolla ohjelmaa kutsuttiin.
 * Returns: Ei mitään.
 * Modifies: Ei mitään.
 * Error checking: Ei mitään.
 * Sample call: tulostaOhjeet(argv[0]);
 */

void tulostaOhjeet(const char *komento);

#endif
