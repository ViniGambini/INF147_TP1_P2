
#include "Aleatoire.h"

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
	// n * randf()) donne un r�el dans (0, n-1)
	// le typecast (int) va le tronquer dans [0, n[
	return (n <= 0) ? 0 : ((int)(n * randf()));
}

//=========================================================
double randf_bornes(double b1, double b2) {
	// STRATEGIE
	// passer de l'intervalle r�el (0,1) � l'intervalle 
	// d�sign� par les param�tres
	// maths :  une dilatation de (0,1) par le facteur(b2 - b1)
	// suivie d'une translation de b1
	return b1 + ((b2 - b1) * randf());
}

//=========================================================
void srand_sys(void) {
	unsigned int secondes;
	int tmp; //pour �viter un warning
	// obtenir le d�calage secondes (Unix timestamp)
	secondes = (unsigned int)time(NULL);
	// init le generateur du C du temps obtenu
	srand(secondes);
	// qui par tradition est suivi d'un premier appel au generateur
	tmp = rand();
}
