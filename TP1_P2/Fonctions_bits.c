
#include "Fonctions_bits.h"

//=========================================================
/* get_bit(): un test qui dit si un (and) entre la valeur re�ue
	et un train de bits tout � 0 sauf un bit 1 en position voulue,
	obtenu avec l'op�rateur <<, est diff�rent de 0.  */
int get_bit(unsigned int nombre, int ordre) {
	return (nombre & (1 << ordre)) != 0;
}

//=========================================================
/* set_bit(): un (or) suffit entre la valeur re�ue et un train de bits
	tout � 0 sauf pour un bit 1 en position voulue,	obtenu avec l'op�rateur <<. */
unsigned int set_bit(unsigned int nombre, int ordre) {
	unsigned int masque = (1 << ordre);
	unsigned int nombre_ou_masque = (nombre | masque);

	return nombre_ou_masque;
}

//=========================================================
/* clear_bit():	un (and) suffit entre la valeur re�ue et un train de
	bits tout � 1 sauf un bit 0 � la position voulue, obtenu avec les op�rateurs <<, ~. */
unsigned int clear_bit(unsigned int nombre, int ordre) {
	unsigned int masque_inv = ~(1 << ordre);
	unsigned int nombre_et_masque = (nombre & masque_inv);

	return nombre_et_masque;
}

//=========================================================
/* flip_bit(): r�utilisation des deux fonctions pr�c�dentes
	si le bit est 1, on retourne clear_bit(), sinon, on retourne set_bit(). */
unsigned int flip_bit(unsigned int nombre, int ordre) {
	return get_bit(nombre, ordre) ? clear_bit(nombre, ordre)
		: set_bit(nombre, ordre);
}

//=========================================================
/* voir_bits(): avec r�utilisation de get_bit()
	 on affiche le r�sultat de get_bit() pour chaque position de 31 � 0. */
void voir_bits(unsigned int nombre) {
	// pour respecter l'ordre naturel des bits on les
	// affiche du plus repr�sentatif en descendant (ordre 31 � 0)
	for (int i = INT_BIT - 1; i > -1; i -= 1)
		printf("%d", get_bit(nombre, i));
	printf("\n");		//affiche un ENTER apr�s la fin de la boucle for()
}