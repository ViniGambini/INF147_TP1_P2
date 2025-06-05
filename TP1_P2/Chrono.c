/********************************************************************/
/* Fichier    : CHRONO.C                                            */
/* References : Philippe Drix, chapitre VIII                        */
/*				Harbison & Steele, chapitre 4                             */
/*                                                                  */
/* Objectifs : Ce module permet de gerer un chronometre.            */
/*			   Elle presente la dissimulation de l'implantation de      */
/*			   la structure ce qui amene vers la representation objet.  */
/*                                                                  */
/* Il touche aux notions suivantes :                                */
/*		- Compilation separee (Drix, chapitre VIII)                   */
/********************************************************************/

#include <stdlib.h>
#include <time.h>
#include "chrono.h"

/********************************************************************/
/*                    DÉCLARATION DU TYPE PRIVÉ                     */
/********************************************************************/
/* Type-struct PRIVÉ (représentation cachée) pour un chronoimètre.  */
struct t_chrono {
	double heure_depart;
	double temps_cumul;
	int    en_marche;
};

/********************************************************************/
/*                       CORPS DE FONCTIONS                         */
/********************************************************************/
t_ptr_chrono init_chrono(void)
{
	t_ptr_chrono chronometre = (t_ptr_chrono)malloc(sizeof(struct t_chrono));

    chronometre->en_marche = 0;
	reinitialiser_chrono(chronometre);

	return chronometre;
}

/********************************************************************/
void demarrer_chrono(t_ptr_chrono chronometre)
{
	chronometre->heure_depart = clock();
	chronometre->en_marche = 1;
}

/********************************************************************/
void arreter_chrono(t_ptr_chrono chronometre)
{
	if (chronometre->en_marche)
		chronometre->temps_cumul += 
		  ((clock() - chronometre->heure_depart)/CLOCKS_PER_SEC);
	chronometre->en_marche = 0;
}

/********************************************************************/
void reinitialiser_chrono(t_ptr_chrono chronometre)
{
	chronometre->heure_depart = clock();
	chronometre->temps_cumul = 0;
}

/********************************************************************/
double lire_chrono(const t_ptr_chrono chronometre)
{
	if (chronometre->en_marche)
		return chronometre->temps_cumul + 
		       ((clock() - chronometre->heure_depart)/CLOCKS_PER_SEC);
	else
		return chronometre->temps_cumul;
}

/********************************************************************/
void detruire_chrono(t_ptr_chrono *chrono)
{
	free(*chrono);   *chrono = NULL;
}
/********************************************************************/
/********************************************************************/