
#include "Fonctions_bits.h"

//=========================================================
/* get_bit(): un test qui dit si un (and) entre la valeur reçue
	et un train de bits tout à 0 sauf un bit 1 en position voulue,
	obtenu avec l'opérateur <<, est différent de 0.  */
int get_bit(unsigned int nombre, int ordre) {
	return (nombre & (1 << ordre)) != 0;
}

//=========================================================
/* set_bit(): un (or) suffit entre la valeur reçue et un train de bits
	tout à 0 sauf pour un bit 1 en position voulue,	obtenu avec l'opérateur <<. */
unsigned int set_bit(unsigned int nombre, int ordre) {
	unsigned int masque = (1 << ordre);
	unsigned int nombre_ou_masque = (nombre | masque);

	return nombre_ou_masque;
}

//=========================================================
/* clear_bit():	un (and) suffit entre la valeur reçue et un train de
	bits tout à 1 sauf un bit 0 à la position voulue, obtenu avec les opérateurs <<, ~. */
unsigned int clear_bit(unsigned int nombre, int ordre) {
	unsigned int masque_inv = ~(1 << ordre);
	unsigned int nombre_et_masque = (nombre & masque_inv);

	return nombre_et_masque;
}

//=========================================================
/* flip_bit(): réutilisation des deux fonctions précédentes
	si le bit est 1, on retourne clear_bit(), sinon, on retourne set_bit(). */
unsigned int flip_bit(unsigned int nombre, int ordre) {
	return get_bit(nombre, ordre) ? clear_bit(nombre, ordre)
		: set_bit(nombre, ordre);
}

//=========================================================
/* voir_bits(): avec réutilisation de get_bit()
	 on affiche le résultat de get_bit() pour chaque position de 31 à 0. */
void voir_bits(unsigned int nombre) {
	// pour respecter l'ordre naturel des bits on les
	// affiche du plus représentatif en descendant (ordre 31 à 0)
	for (int i = INT_BIT - 1; i > -1; i -= 1)
		printf("%d", get_bit(nombre, i));
	printf("\n");		//affiche un ENTER après la fin de la boucle for()
}