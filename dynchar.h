/* Dynaaminen merkkijonotaulukon kasvatus */

#ifndef DYNCHAR_H
#define DYNCHAR_H

/* Function: extendChar
 * Purpose: kasvattaa annetun merkkijonotaulukon pituutta. 
 * Inputs: merkkijonotaulukko, jonka pituutta halutaan kasvattaa, nykyisen taulukon pituus ja kuinka paljon taulukkoa halutaan kasvattaa.
 * Returns: viite uuteen taulukkoon, joka sisältää samat merkit kuin alkuperäinen. Palauttaa NULL jos ei onnistu
 * Modifies: vapauttaa parametrinä annetun sanan muistin 
 * Error checking: tarkistaa ettei annettu sana ole NULL ja myös että annetut pituudet ovat positiivisia. Palauttaa NULL jos ehdot eivät täyty.
 * Sample call: extendChar();
 */

char* extendChar(char *sana, int pituus, int kasvatuspituus);

#endif
