/************************************************************************/
/* Fichier    : CHRONO.H                                                */
/* References : Philippe Drix, chapitre VIII                            */
/*				Harbison & Steele, chapitre 4                           */
/*                                                                      */
/* Objectifs : Ce module permet de gerer un chronometre.                */
/*			   Elle presente la dissimulation de l'implantation de      */
/*			   la structure ce qui amene vers la representation objet.  */
/*             (i.e. la représentation cachée)                          */
/*                                                                      */
/* Il touche aux notions suivantes :                                    */
/*		- Compilation separee (Drix, chapitre VIII)                     */
/************************************************************************/

/********************************************************************/
/*                      DEFINITION DU TYPE                          */
/********************************************************************/

/* Type-POINTEUR vers un enregistrement privé (dans le "Chrono.c"). */
typedef struct t_chrono * t_ptr_chrono;

/********************************************************************/
/*                    DECLARATIONS DE FONCTIONS                     */
/********************************************************************/
t_ptr_chrono init_chrono(void);
/* Cette fonction permet d'initialiser un chronometre.              */
/* Elle l'initialise au temps 0 et celui-ci est arrete.             */
/* La fonction crée et retourne un nouveau chronomètre dynamique.   */


void demarrer_chrono(t_ptr_chrono);
/* Cette fonction met le chronometre en marche et associe le temps	*/
/* present au moment de depart.                                     */
/* Elle suppose que le chronometre a ete initialise grace a la      */
/* fonction	creer_chrono et qu'il n'a pas ete libere.               */


void arreter_chrono(t_ptr_chrono);
/* Cette fonction arrete le chronometre et associe au temps         */
/* accumule la difference entre le temps present et celui de depart.*/
/* Elle suppose que le chronometre a ete initialise grace a la      */
/* fonction	creer_chrono et qu'il n'a pas ete libere.               */


void reinitialiser_chrono(t_ptr_chrono);
/* Cette fonction associe au temps accumule la valeur 0. De plus,   */
/* si le chronometre est deja en marche, elle met le temps de       */
/* depart au temps present.                                         */
/* Elle suppose que le chronometre a ete initialise grace a la      */
/* fonction	creer_chrono et qu'il n'a pas ete libere.               */


double lire_chrono(const t_ptr_chrono);
/* Cette fonction lit le temps accumule par le chronometre a        */
/* maintenant. Elle suppose que le chronometre a ete initialise     */
/* grace a la fonction creer_chrono et qu'il n'a pas ete libere.    */


void detruire_chrono(t_ptr_chrono *);
/* Cette fonction permet de détruire (libérer) un chronometre.      */
/* NOTE: Le pointeur-chronomètre doit être reçu en RÉFÉRENCE ici.   */