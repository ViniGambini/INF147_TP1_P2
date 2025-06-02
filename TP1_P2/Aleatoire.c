
#include "Aleatoire.h"
#include "Fonctions_bits.h"

//=============================================================================
double randf(void) {
	// STRATEGIE
	// calcul du rapport de la valeur issue de rand au 
	// maximum emissible + epsilon  
	return (1.0 * rand()) / (RAND_MAX + EPSILON);
}

//=========================================================
int randi(int n) {
	// STRATEGIE
	// si n <= 0 retour 0 
	// n * randf()) donne un réel dans (0, n-1)
	// le typecast (int) va le tronquer dans [0, n[
	return (n <= 0) ? 0 : ((int)(n * randf()));
}

//=========================================================
double randf_bornes(double b1, double b2) {
	// STRATEGIE
	// passer de l'intervalle réel (0,1) à l'intervalle 
	// désigné par les paramètres
	// maths :  une dilatation de (0,1) par le facteur(b2 - b1)
	// suivie d'une translation de b1
	return b1 + ((b2 - b1) * randf());
}

//=========================================================
void srand_sys(void) {
	unsigned int secondes;
	int tmp; //pour éviter un warning
	// obtenir le décalage secondes (Unix timestamp)
	secondes = (unsigned int)time(NULL);
	// init le generateur du C du temps obtenu
	srand(secondes);
	// qui par tradition est suivi d'un premier appel au generateur
	tmp = rand();
}


unsigned int valeur_aleatoire(void)
{
	
	unsigned int val_alea = 0;

	for (int i = 0; i < 32; i++)
	{
		if (randi(2) == 0)
		
			val_alea = clear_bit(val_alea, i);
		else
			val_alea = set_bit(val_alea, i);
	}
	return val_alea;
}