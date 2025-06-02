
/********************************************************************/
/* Fichier   : TP1 PARTIE 1                                         */
/* Noms		 : Renaud Lamonde et Vincent Goulet						*/
/* Date  de crÃ©ation : 12 mai 2025									*/
/* Description :  Ce fichier contient les fonctions et leurs tests	*/
/* unitaires permettant de vÃ©rifier les 6 principes imposÃ©s par		*/
/* l'Ã©quipe d'ingÃ©nieurs de L'AEAC. 								*/
/********************************************************************/


#include <assert.h>
#include "Aleatoire.h"
#include "Fonctions_bits.h"


//=========================================================//
//                     LES CONSTANTES                      //
//=========================================================//

#define MODE_TEST 0 // 1 = main des tests, 0 = main des parties 1 ou 2
#define MODE_PARTIE1 0  // 1 = Partie 1, 0 = Partie 2
#define MODE_MACRO 0    // 1 = active les macros, 0 = active les fonctions


#define MAX_ITER_P1 100 // ItÃ©ration max de la partie 1
#define MAX_ITER_P2 10000 // ItÃ©ration maximum pour la partie 2
#define PROB_BRIS 0.021 // ProbabilitÃ© de bris entre 0.0 et 1.0
#define PERIODE_REPARATION 30 // RÃ©pare les gÃ©nÃ©rateur tous les X itÃ©rations
#define NB_TESTS 100 // Nombre de test effectuer pour obtenir la moyenne d'itÃ©ration

#define N 30 //18 <= N <= 32
#define K 12 //0,28 * N <= K <= 0,48 * N


//=========================================================//
//                     LES PROTOTYPES                      //
//=========================================================//

//=========================================================
/*
	VÃ©rifie qu'il n'y a pas 3 bits Ã  1 de suite
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
	RETOUR : 1 si tout est beau, 0 si 3 bits ou plus se suivent
*/
int principe1(unsigned int etat_gen);

// Tests pour la fonction principe1()
void assert_principe1(void);

//=========================================================
/*
	Trouve les endroits oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
	RETOUR : nombre binaire oÃ¹ un 1 reprÃ©sente les endroits ou
			 un gÃ©nÃ©rateur peut Ãªtre activÃ©
*/
unsigned int get_bits_dispo(unsigned int etat_gen);

// Tests pour la fonction get_bits_dispo()
void test_get_bits_dispo(void);

//=========================================================
/*
	Choisi alÃ©atoirement un endroit oÃ¹ activer un gÃ©nÃ©rateur
	PARAMETRE : bit_possible, chaine de bit ou un 1 reprÃ©sente
				lÃ  oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©
	RETOUR : position du bit choisi (entre 0 et N-1)
*/
int choix_alea_bit1(unsigned int bit_possible);

// Tests pour la fonction choix_alea_bit1()
void assert_choix_alea_bit1(void);

//=========================================================
/*
	Initialisation des gÃ©nÃ©rateur : active alÃ©atoirement K gÃ©nÃ©rateurs
	PARAMETRE : void
	RETOUR : N bits avec K gÃ©nÃ©rateurs activÃ©s
*/
unsigned int init_gen(void);

//=========================================================
/*
	Permutation de deux gÃ©nÃ©rateur, en active alÃ©atoirement un et en dÃ©sactive un autre
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs
	RETOUR : Ã©tat des gÃ©nÃ©rateur aprÃ¨s la permutation
*/
unsigned int permuter_bits(unsigned int etat_gen);

//=========================================================
/*
	Valider qu'il y a exactement K gÃ©nÃ©rateur d'activÃ©
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs
	RETOUR : 1 si tout est beau, 0 s'il y a un problÃ¨me
*/
int valider_etatK(unsigned int etat_gen);

// Tests pour la fonction valider_etat_K()
void assert_valider_etatK(void);

//=========================================================
/*
	Valider qu'il n'y a pas de gÃ©nÃ©rateur brisÃ© qui sont activÃ©
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs, Ã©tat des bris
	RETOUR : 1 si tout est beau, 0 s'il y a un problÃ¨me
*/
int valider_bris(unsigned int etat_gen, unsigned int etat_bris);

// Tests pour la fonction valider_bris()
void assert_valider_bris(void);

//=========================================================
/*
	Trouve les endroits oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©, en considÃ©rant les bris
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
				etat_bris, endroit oÃ¹ les gÃ©nÃ©rateur sont brisÃ©s
	RETOUR : nombre binaire oÃ¹ un 1 reprÃ©sente les endroits oÃ¹ un 
			 gÃ©nÃ©rateur peut Ãªtre activÃ©
*/
unsigned int get_bits_dispo2(unsigned int etat_gen, unsigned int etat_bris);

//=========================================================
/*
	GÃ©nÃ¨re alÃ©atoirement des bris de gÃ©nÃ©rateur
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
				etat_bris, endroit oÃ¹ les gÃ©nÃ©rateur sont brisÃ©s
	RETOUR : 1 si tout est beau, 0 si il y a un Ã©chec
*/
int gestion_bris(unsigned int *etat_gen, unsigned int *etat_bris);

//=========================================================
/*
	Permutation de deux gÃ©nÃ©rateur, en prennant en compte les gÃ©nÃ©rateurs brisÃ©s
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs, Ã©tat des bris
	RETOUR : Ã©tat des gÃ©nÃ©rateur aprÃ¨s la permutation
*/
unsigned int permuter_bits2(unsigned int *etat_gen, unsigned int etat_bris);


double moyenne_tests(int tab_essais[], int nb_tests, int* min, int* max);


/*=========================================================*/
/*=========================================================*/
#if (MODE_TEST) 
int main(void) {
	printf("Tests des differentes fonctions : \n\n");

	assert_principe1();
	test_get_bits_dispo();
	assert_choix_alea_bit1();
	assert_valider_etatK();
	assert_valider_bris();

}
#elif(MODE_PARTIE1)

int main(void) {

	unsigned int etat_gen_ions = 0; // Ãtat des gÃ©nÃ©rateurs
	int i = 0;


	etat_gen_ions = init_gen(); // Initialise les gÃ©nÃ©rateurs

	printf("N : %d\nK : %d\n%s", N, K,
		"  Bits genere avec init_gen() : ");
	voir_bits(etat_gen_ions);

	//Permute 2 bits (nbr_validation) de fois
	for (i = 0; i < MAX_ITER_P1; i++) {
		etat_gen_ions = permuter_bits(etat_gen_ions);
		assert(test_surchauffe_gen(etat_gen_ions));

		//Enlever le commentaire ci-dessous pour voir chaque permutation
		//voir_bits(etat_gen_ions);
	}

	printf("Bits obtenus apres %d tests : ", MAX_ITER_P1);
	voir_bits(etat_gen_ions);

	system("pause");
	return EXIT_SUCCESS;
}
#else
int main(void)
{
	//Initialisation du génÃ©rateur alÃ©atoire
	srand_sys();


	int tab_essais[NB_TESTS];

	int min, max;


	unsigned int etat_gen_ions;

	unsigned int bris_gen_ions;

	int nb_passages = 0;


	//Compteur du nombre d'itÃ©ration
	int nb_tests = 0;

	//Boucle permettant 100 iterations de la boucle principale
	for (nb_tests = 0; nb_tests < NB_TESTS; nb_tests++) {

		etat_gen_ions = init_gen();

		bris_gen_ions = 0;


		// Boucle principale
		for (nb_passages = 0; nb_passages < MAX_ITER_P2; nb_passages++) {

			if (permuter_bits2(&etat_gen_ions, bris_gen_ions) == 0) {
				break;
			}

			if (gestion_bris(&etat_gen_ions, &bris_gen_ions) == 0)
				break;


			// Affiche des donnÃ©es tous les 100 itÃ©rations
			/*if (nb_passages % 100 == 0) {
				printf("%s%d\n%s",
					"Nombre d'iterations  : ", nb_passages,
					"Etat des generateurs : ");
				voir_bits(etat_gen_ions);
				printf("Etat des bris        : ");
				voir_bits(bris_gen_ions);
				printf("\n");
			}*/

			// Valide le principe 1
			if (principe1(etat_gen_ions) == 0)
				break;
			// Valide K
			if (valider_etatK(etat_gen_ions) == 0)
				break;
			// Valide les bris
			if (valider_bris(etat_gen_ions, bris_gen_ions) == 0)
				break;

			// RÃ©pare les gÃ©nrateurs pÃ©riodiquement
			if (nb_passages % PERIODE_REPARATION == 0)
				bris_gen_ions = 0;

		}

		// Affiche le nombre d'itÃ©ration
		/*printf("\n%s%d\n%s", "Nombre d'iteration   : ", nb_passages,
			"Etat des generateurs : ");
		voir_bits(etat_gen_ions);
		printf("Etat des bris        : ");
		voir_bits(bris_gen_ions);*/

		tab_essais[nb_tests] = nb_passages;
		if (nb_tests < 10)
		{
			printf(" %i : Arret apres %i passages\n", nb_tests, nb_passages);
		}
		else
			printf("%i : Arret apres %i passages\n", nb_tests, nb_passages);
	}

	// Fonction moyenne


	double moyenne = moyenne_tests(tab_essais, NB_TESTS, &min, &max);

	printf("\n*======== RESULTATS DE LA SIMULATION ========*\n");
	printf("Constantes utilisees:\n");
	printf("N = %d\n", N);
	printf("K = %d\n", K);
	printf("PROB_BRIS = %.3f\n", PROB_BRIS);
	printf("PERIODE_REPARATION = %d\n", PERIODE_REPARATION);
	printf("MAX_ITER = %d\n", MAX_ITER_P2);
	printf("NB_TESTS = %d\n", NB_TESTS);
	printf("\nStatistiques sur %d essais:\n", NB_TESTS);
	printf("Moyenne: %.2f iterations\n", moyenne);
	printf("Minimum: %d iterations\n", min);
	printf("Maximum: %d iterations\n", max);
  
	system("pause");
	return EXIT_SUCCESS;
}

#endif
/*=========================================================*/



//=========================================================//
//		       DÃFINITIONS DES FONCTIONS			       //
//=========================================================//

//=========================================================
/*
	VÃ©rifie qu'il n'y a pas 3 bits Ã  1 de suite
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
	RETOUR : 1 si tout est beau, 0 si 3 bits ou plus se suivent
*/
int principe1(unsigned int etat_gen) {
	int test = 1;

	// VÃ©rifie trois bits cÃ´te Ã  cÃ´te
	for (int i = 1; i < N - 1; i += 1) {

		test *= get_bit(etat_gen, i - 1);
		test *= get_bit(etat_gen, i);
		test *= get_bit(etat_gen, i + 1);

		// Si il y a trois 1
		if (test == 1) {
			return 0; // Retourne 0
		}
		//S'il y a un 0, continue les tests
		test = 1;
	}
	return 1;
}

//=========================================================
/*
	Trouve les endroits oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
	RETOUR : nombre binaire oÃ¹ un 1 reprÃ©sente les endroits ou
			 un gÃ©nÃ©rateur peut Ãªtre activÃ©
*/
unsigned int get_bits_dispo(unsigned int etat_gen) {
	unsigned int bits_possible = 0;

	// test chaque bit pour voir si le bit en question peut Ãªtre mis Ã  1
	for (int i = 0; i < N; i += 1) {

		// si le bit i est 0
		if (get_bit(etat_gen, i) == 0) {
			etat_gen = set_bit(etat_gen, i); //met le bit Ã  1

			// Test si la rÃ¨gle du principe 1 est respectÃ©e
			if (principe1(etat_gen)) {
				bits_possible = set_bit(bits_possible, i);
			}

			etat_gen = clear_bit(etat_gen, i); // remet le bit Ã  0
		}
	}

	return bits_possible;
}

//=========================================================
/*
	Choisi alÃ©atoirement un endroit oÃ¹ activer un gÃ©nÃ©rateur
	PARAMETRE : bit_possible, chaine de bit ou un 1 reprÃ©sente
				lÃ  oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©
	RETOUR : position du bit choisi (entre 0 et N-1)
*/
int choix_alea_bit1(unsigned int bit_possible) {

	int ordre = 0;
	int bit = 0;

	// Erreur si aucun bit possible
	if (bit_possible == 0) {
		return -1;
	}
	else {
		// Choisi un bit alÃ©atoire dans les bits possibles
		while (bit == 0) {
			ordre = randi(N);
			bit = get_bit(bit_possible, ordre);
		}
	}
	return ordre;
}

//=========================================================
/*
	Initialisation des gÃ©nÃ©rateur : active alÃ©atoirement K gÃ©nÃ©rateurs
	PARAMETRE : void
	RETOUR : N bits avec K gÃ©nÃ©rateurs activÃ©s
*/
unsigned int init_gen(void) {

	unsigned int config_initiale = 0; // Variable Ã  remplir pour les gÃ©nÃ©rateurs
	unsigned int bits_dispo = 0; // Variable temporaire pour les bits dispo
	int ordre = 0; // Variable temporaire pour contenir l'ordre d'un bit

	// Choisi K bits alÃ©atoirement Ã  activer tout en respectant le principe 1
	for (int i = 0; i < K; i++) {
		bits_dispo = get_bits_dispo(config_initiale);
		ordre = choix_alea_bit1(bits_dispo);
		//printf("%d ", ordre);

		//VÃ©rifie que l'ordre est bon
		assert(ordre < N && ordre >= 0);

		config_initiale = set_bit(config_initiale, ordre);

	}

	//test du principe 1
	assert(principe1(config_initiale) == 1);

	return config_initiale;
}

//=========================================================
/*
	Permutation de deux gÃ©nÃ©rateur, active alÃ©atoirement 1 et en dÃ©sactive un autre
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs
	RETOUR : Ã©tat des gÃ©nÃ©rateur aprÃ¨s la permutation
*/
unsigned int permuter_bits(unsigned int etat_gen) {

	int ordre_a_eteindre = 0;
	int ordre_a_allumer = 0;

	//choisi alÃ©atoirement un bit Ã  Ã©teindre
	ordre_a_eteindre = choix_alea_bit1(etat_gen);
	//Trouve les bits disponible et en choisi un alÃ©atoirement pour l'allumer
	ordre_a_allumer = choix_alea_bit1(get_bits_dispo(etat_gen));

	//VÃ©rification des ordres
	assert(ordre_a_allumer < N && ordre_a_allumer >= 0);
	assert(ordre_a_eteindre < N && ordre_a_eteindre >= 0);

	//Ã©change les valeurs des 2 bits
	etat_gen = flip_bit(etat_gen, ordre_a_eteindre);
	etat_gen = flip_bit(etat_gen, ordre_a_allumer);

	//Validation du principe 1
	assert(principe1(etat_gen) == 1);

	return etat_gen;
}

//=========================================================
/*
	Valider qu'il y a exactement K gÃ©nÃ©rateur d'activÃ©
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs
	RETOUR : 1 si tout est beau, 0 s'il y a un problÃ¨me
*/
int valider_etatK(unsigned int etat_gen) {
	int compteur_de_1 = 0;

	// VÃ©rifie le principe 1
	if (principe1(etat_gen) == 0) 
		return 0;
	
	// Compte le nombre de gÃ©nÃ©rateur actif
	for (int i = 0; i < N; i++) {
		if (get_bit(etat_gen, i) == 1) {
			compteur_de_1 += 1;
		}
	}
	//printf("Bit compte : %d\n", compteur_de_1); // Affiche le nbr de bit comptÃ©

	// VÃ©rifie si compteur == K
	if (compteur_de_1 != K) 
		return 0;
	
	// VÃ©rifie les bit entre 31 et N
	for (int i = 31; i >= N; i--) {
		if (get_bit(etat_gen, i) == 1)
			return 0;
	}

	// Si tout est beau
	return 1;
	
}

//=========================================================
/*
	Valider qu'il n'y a pas de gÃ©nÃ©rateur brisÃ© qui sont activÃ©
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs, Ã©tat des bris
	RETOUR : 1 si tout est beau, 0 s'il y a un problÃ¨me
*/
int valider_bris(unsigned int etat_gen, unsigned int etat_bris) {
	// VÃ©rifie si les 2 variables ont des bits commun
	if ((etat_bris & etat_gen) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//=========================================================
/*
	Trouve les endroits oÃ¹ un gÃ©nÃ©rateur peut Ãªtre activÃ©, en considÃ©rant les bris
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
				etat_bris, endroit oÃ¹ les gÃ©nÃ©rateur sont brisÃ©s
	RETOUR : nombre binaire oÃ¹ un 1 reprÃ©sente les endroits oÃ¹ un
			 gÃ©nÃ©rateur peut Ãªtre activÃ©
*/
unsigned int get_bits_dispo2(unsigned int etat_gen, unsigned int etat_bris) {
	unsigned int bits_possible = 0;

	// test chaque bit pour voir si le bit en question peut Ãªtre mis Ã  1
	for (int i = 0; i < N; i += 1) {

		// si le bit i est 0
		if (get_bit(etat_gen, i) == 0 && get_bit(etat_bris, i) == 0) {
			etat_gen = set_bit(etat_gen, i); //met le bit Ã  1

			// Test si la rÃ¨gle du principe 1 est respectÃ©e
			if (principe1(etat_gen)) {
				bits_possible = set_bit(bits_possible, i);
			}

			etat_gen = clear_bit(etat_gen, i); // remet le bit Ã  0
		}
	}

	return bits_possible;
}

//=========================================================
/*
	GÃ©nÃ¨re alÃ©atoirement des bris de gÃ©nÃ©rateur
	PARAMETRE : etat_gen, nombre binaire a vÃ©rifier
				etat_bris, endroit oÃ¹ les gÃ©nÃ©rateur sont brisÃ©s
	RETOUR : 1 si tout est beau, 0 si il y a un Ã©chec
*/
int gestion_bris(unsigned int *etat_gen, unsigned int *etat_bris) {
	
	int ordre = 0;

	// Pour chaque bit entre 0 et N-1
	for (int i = 0; i < N; i++) {
		
		// Si le gÃ©nÃ©rateur est activÃ© et qu'il n'est pas brisÃ©
		if (get_bit(*etat_gen, i) == 1 && get_bit(*etat_bris, i) == 0) {
			// ProbabilitÃ© de bris
			if (randf() < PROB_BRIS) {
				*etat_gen = clear_bit(*etat_gen, i);
				*etat_bris = set_bit(*etat_bris, i);

				// Active un bit alÃ©atoire
				ordre = choix_alea_bit1(get_bits_dispo2(*etat_gen, *etat_bris));
				if (ordre < 0 || ordre >= N)
					return 0;

				*etat_gen = set_bit(*etat_gen, ordre);

				if (valider_bris(*etat_gen, *etat_bris) == 0)
					return 0;
			}
		}
	}
	return 1;

}

//=========================================================
/*
	Permutation de deux gÃ©nÃ©rateur, en prennant en compte les gÃ©nÃ©rateurs brisÃ©s
	PARAMETRE : Ã©tat des gÃ©nÃ©rateurs, Ã©tat des bris
	RETOUR : Ã©tat des gÃ©nÃ©rateur aprÃ¨s la permutation
*/
unsigned int permuter_bits2(unsigned int *etat_gen, unsigned int etat_bris) {

	int ordre_a_eteindre = 0;
	int ordre_a_allumer = 0;

	//choisi alÃ©atoirement un bit Ã  Ã©teindre
	ordre_a_eteindre = choix_alea_bit1(*etat_gen);
	//Trouve les bits disponible et en choisi un alÃ©atoirement pour l'allumer
	ordre_a_allumer = choix_alea_bit1(get_bits_dispo2(*etat_gen, etat_bris));

	//VÃ©rification des ordres
	if (ordre_a_allumer >= N || ordre_a_allumer < 0) {
		return 0;
	}
	if (ordre_a_eteindre >= N || ordre_a_eteindre < 0) {
		return 0;
	}

	//Ã©change les valeurs des 2 bits
	*etat_gen = flip_bit(*etat_gen, ordre_a_eteindre);
	*etat_gen = flip_bit(*etat_gen, ordre_a_allumer);

	//Validation du principe 1
	if (principe1(*etat_gen) == 0) {
		return 0;
	}
	// Validation des bris
	if (valider_bris(*etat_gen, etat_bris) == 0) {
		return 0;
	}

	return 1;
}


//=========================================================
/*
	Permutation de deux gÃ©nÃ©rateur, en prennant en compte les gÃ©nÃ©rateurs brisÃ©s
	PARAMETRE : tableau contenant les essais, le nombre de tests a faire, 
				la valeur minimale et la valeur maximale
	RETOUR : moyenne des test totaux
*/
double moyenne_tests(int tab_essais[], int nb_tests, int* min, int* max)
{
	if (nb_tests <= 0) return 0;

	*min = tab_essais[0];
	*max = tab_essais[0];
	int somme = tab_essais[0];

	for (int i = 0; i < nb_tests - 1; i++)
	{
		somme = tab_essais[i] + somme;
		if (tab_essais[i] < *min) *min = tab_essais[i];
		if (tab_essais[i] > *max) *max = tab_essais[i];
	}

	return (double)somme / nb_tests;


//=========================================================
void assert_principe1(void) {

	// Test plusiseurs cas diffÃ©rent pour s'assurer que tout fonctionne bien
	unsigned int bin = 42;
	assert(principe1(bin) == 1);

	bin = 0b00011010110110;
	assert(principe1(bin) == 1);

	bin = 0b110111001101101;
	assert(principe1(bin) == 0);

	bin = 0b11111111111111111111;
	assert(principe1(bin) == 0);

	bin = 0b0000000000000000000001;
	assert(principe1(bin) == 1);

	bin = 0b0000000000000000000011;
	assert(principe1(bin) == 1);

	bin = 0b0000000000000000000111;
	assert(principe1(bin) == 0);

	printf("principe1() : OK\n");
}

//=========================================================
void test_get_bits_dispo(void) {

	unsigned int etat_gen_ions = 0b0011001001000101101011001;

	// Validation manuelle pour les bits possibles
	printf("%s\n%s%d\n%s",
		"     get_bits_dispo() : Verification manuelle",
		" Nombre de generateur : ", N,
		"        Etat_gen_ions : ");
	voir_bits(etat_gen_ions);
	printf("         Bit_possible : ");
	voir_bits(get_bits_dispo(etat_gen_ions));

}

//=========================================================
void assert_choix_alea_bit1(void) {

	// test si 0 bit possible
	assert(choix_alea_bit1(0) == -1);

	int resultat = 0;
	const int nbr_test = 20;

	// test la sÃ©lection alÃ©atoire 20 fois
	for (int i = 0; i < nbr_test; i++) {
		resultat = choix_alea_bit1(0b000110010010010110);
		//printf("%d\n", test);
		assert(resultat == 1 || resultat == 2 || resultat == 4 || resultat == 7 ||\
			   resultat == 10 || resultat == 13 || resultat == 14);
	}

	printf("    choix_alea_bit1() : OK\n");
}

//=========================================================
void assert_valider_etatK(void) {
	unsigned int etat_test = 0;

	etat_test = init_gen();
	assert(valider_etatK(etat_test) == 1);

	etat_test = set_bit(etat_test, 31);
	assert(valider_etatK(etat_test) == 0);

}

//=========================================================
void assert_valider_bris(void) {
	unsigned int var1 = 0b10001110100100;
	unsigned int var2 = 0b01100001000000;
	assert(valider_bris(var1, var2) == 1);

	var1 = 0b10001110100100;
	var2 = 0b01101001000000;
	assert(valider_bris(var1, var2) == 0);

	var1 = 0b010001110100100;
	var2 = 0b101110001011111;
	assert(valider_bris(var1, var2) == 0);

	var1 = 0b010001110100100;
	var2 = 0b101110001011011;
	assert(valider_bris(var1, var2) == 1);

}

/*=========================================================*/
/*=========================================================*/