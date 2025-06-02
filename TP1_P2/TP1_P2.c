
/********************************************************************/
/* Fichier   : TP1 PARTIE 1                                         */
/* Noms		 : Renaud Lamonde et Vincent Goulet						*/
/* Date  de création : 12 mai 2025									*/
/* Description :  Ce fichier contient les fonctions et leurs tests	*/
/* unitaires permettant de vérifier les 6 principes imposés par		*/
/* l'équipe d'ingénieurs de L'AEAC. 								*/
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


#define MAX_ITER_P1 100 // Itération max de la partie 1
#define MAX_ITER_P2 10000 // Itération maximum pour la partie 2
#define PROB_BRIS 0.021 // Probabilité de bris entre 0.0 et 1.0
#define PERIODE_REPARATION 30 // Répare les générateur tous les X itérations
#define NB_TESTS 100 // Nombre de test effectuer pour obtenir la moyenne d'itération

#define N 30 //18 <= N <= 32
#define K 12 //0,28 * N <= K <= 0,48 * N


//=========================================================//
//                     LES PROTOTYPES                      //
//=========================================================//

//=========================================================
/*
	Vérifie qu'il n'y a pas 3 bits à 1 de suite
	PARAMETRE : etat_gen, nombre binaire a vérifier
	RETOUR : 1 si tout est beau, 0 si 3 bits ou plus se suivent
*/
int principe1(unsigned int etat_gen);

// Tests pour la fonction principe1()
void assert_principe1(void);

//=========================================================
/*
	Trouve les endroits où un générateur peut être activé
	PARAMETRE : etat_gen, nombre binaire a vérifier
	RETOUR : nombre binaire où un 1 représente les endroits ou
			 un générateur peut être activé
*/
unsigned int get_bits_dispo(unsigned int etat_gen);

// Tests pour la fonction get_bits_dispo()
void test_get_bits_dispo(void);

//=========================================================
/*
	Choisi aléatoirement un endroit où activer un générateur
	PARAMETRE : bit_possible, chaine de bit ou un 1 représente
				là où un générateur peut être activé
	RETOUR : position du bit choisi (entre 0 et N-1)
*/
int choix_alea_bit1(unsigned int bit_possible);

// Tests pour la fonction choix_alea_bit1()
void assert_choix_alea_bit1(void);

//=========================================================
/*
	Initialisation des générateur : active aléatoirement K générateurs
	PARAMETRE : void
	RETOUR : N bits avec K générateurs activés
*/
unsigned int init_gen(void);

//=========================================================
/*
	Permutation de deux générateur, en active aléatoirement un et en désactive un autre
	PARAMETRE : état des générateurs
	RETOUR : état des générateur après la permutation
*/
unsigned int permuter_bits(unsigned int etat_gen);

//=========================================================
/*
	Valider qu'il y a exactement K générateur d'activé
	PARAMETRE : état des générateurs
	RETOUR : 1 si tout est beau, 0 s'il y a un problème
*/
int valider_etatK(unsigned int etat_gen);

void assert_valider_etatK(void);

//=========================================================
/*
	Valider qu'il n'y a pas de générateur brisé qui sont activé
	PARAMETRE : état des générateurs, état des bris
	RETOUR : 1 si tout est beau, 0 s'il y a un problème
*/
int valider_bris(unsigned int etat_gen, unsigned int etat_bris);

void assert_valider_bris(void);

//=========================================================
/*
	Trouve les endroits où un générateur peut être activé, en considérant les bris
	PARAMETRE : etat_gen, nombre binaire a vérifier
				etat_bris, endroit où les générateur sont brisés
	RETOUR : nombre binaire où un 1 représente les endroits où un 
			 générateur peut être activé
*/
unsigned int get_bits_dispo2(unsigned int etat_gen, unsigned int etat_bris);

//=========================================================
/*
	Génère aléatoirement des bris de générateur
	PARAMETRE : etat_gen, nombre binaire a vérifier
				etat_bris, endroit où les générateur sont brisés
	RETOUR : 1 si tout est beau, 0 si il y a un échec
*/
int gestion_bris(unsigned int *etat_gen, unsigned int *etat_bris);

//=========================================================
/*
	Permutation de deux générateur, en prennant en compte les générateurs brisés
	PARAMETRE : état des générateurs, état des bris
	RETOUR : état des générateur après la permutation
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

	unsigned int etat_gen_ions = 0; // État des générateurs
	int i = 0;


	etat_gen_ions = init_gen(); // Initialise les générateurs

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
	//Initialisation du générateur aléatoire
	srand_sys();

	int tab_essais[NB_TESTS];

	int min, max;

	unsigned int etat_gen_ions;

	unsigned int bris_gen_ions;

	int nb_passages = 0;


	//Compteur du nombre d'itération
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


			// Affiche des données tous les 100 itérations
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

			// Répare les génrateurs périodiquement
			if (nb_passages % PERIODE_REPARATION == 0)
				bris_gen_ions = 0;

		}

		// Affiche le nombre d'itération
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
//		       DÉFINITIONS DES FONCTIONS			       //
//=========================================================//

//=========================================================
/*
	Vérifie qu'il n'y a pas 3 bits à 1 de suite
	PARAMETRE : etat_gen, nombre binaire a vérifier
	RETOUR : 1 si tout est beau, 0 si 3 bits ou plus se suivent
*/
int principe1(unsigned int etat_gen) {
	int test = 1;

	// Vérifie trois bits côte à côte
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
	Trouve les endroits où un générateur peut être activé
	PARAMETRE : etat_gen, nombre binaire a vérifier
	RETOUR : nombre binaire où un 1 représente les endroits ou
			 un générateur peut être activé
*/
unsigned int get_bits_dispo(unsigned int etat_gen) {
	unsigned int bits_possible = 0;

	// test chaque bit pour voir si le bit en question peut être mis à 1
	for (int i = 0; i < N; i += 1) {

		// si le bit i est 0
		if (get_bit(etat_gen, i) == 0) {
			etat_gen = set_bit(etat_gen, i); //met le bit à 1

			// Test si la règle du principe 1 est respectée
			if (principe1(etat_gen)) {
				bits_possible = set_bit(bits_possible, i);
			}

			etat_gen = clear_bit(etat_gen, i); // remet le bit à 0
		}
	}

	return bits_possible;
}

//=========================================================
/*
	Choisi aléatoirement un endroit où activer un générateur
	PARAMETRE : bit_possible, chaine de bit ou un 1 représente
				là où un générateur peut être activé
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
		// Choisi un bit aléatoire dans les bits possibles
		while (bit == 0) {
			ordre = randi(N);
			bit = get_bit(bit_possible, ordre);
		}
	}
	return ordre;
}

//=========================================================
/*
	Initialisation des générateur : active aléatoirement K générateurs
	PARAMETRE : void
	RETOUR : N bits avec K générateurs activés
*/
unsigned int init_gen(void) {

	unsigned int config_initiale = 0; // Variable à remplir pour les générateurs
	unsigned int bits_dispo = 0; // Variable temporaire pour les bits dispo
	int ordre = 0; // Variable temporaire pour contenir l'ordre d'un bit

	// Choisi K bits aléatoirement à activer tout en respectant le principe 1
	for (int i = 0; i < K; i++) {
		bits_dispo = get_bits_dispo(config_initiale);
		ordre = choix_alea_bit1(bits_dispo);
		//printf("%d ", ordre);

		//Vérifie que l'ordre est bon
		assert(ordre < N && ordre >= 0);

		config_initiale = set_bit(config_initiale, ordre);

	}

	//test du principe 1
	assert(principe1(config_initiale) == 1);

	return config_initiale;
}

//=========================================================
/*
	Permutation de deux générateur, active aléatoirement 1 et en désactive un autre
	PARAMETRE : état des générateurs
	RETOUR : état des générateur après la permutation
*/
unsigned int permuter_bits(unsigned int etat_gen) {

	int ordre_a_eteindre = 0;
	int ordre_a_allumer = 0;

	//choisi aléatoirement un bit à éteindre
	ordre_a_eteindre = choix_alea_bit1(etat_gen);
	//Trouve les bits disponible et en choisi un aléatoirement pour l'allumer
	ordre_a_allumer = choix_alea_bit1(get_bits_dispo(etat_gen));

	//Vérification des ordres
	assert(ordre_a_allumer < N && ordre_a_allumer >= 0);
	assert(ordre_a_eteindre < N && ordre_a_eteindre >= 0);

	//échange les valeurs des 2 bits
	etat_gen = flip_bit(etat_gen, ordre_a_eteindre);
	etat_gen = flip_bit(etat_gen, ordre_a_allumer);

	//Validation du principe 1
	assert(principe1(etat_gen) == 1);

	return etat_gen;
}

//=========================================================
/*
	Valider qu'il y a exactement K générateur d'activé
	PARAMETRE : état des générateurs
	RETOUR : 1 si tout est beau, 0 s'il y a un problème
*/
int valider_etatK(unsigned int etat_gen) {
	int compteur_de_1 = 0;

	// Vérifie le principe 1
	if (principe1(etat_gen) == 0) 
		return 0;
	
	// Compte le nombre de générateur actif
	for (int i = 0; i < N; i++) {
		if (get_bit(etat_gen, i) == 1) {
			compteur_de_1 += 1;
		}
	}
	//printf("Bit compte : %d\n", compteur_de_1); // Affiche le nbr de bit compté

	// Vérifie si compteur == K
	if (compteur_de_1 != K) 
		return 0;
	
	// Vérifie les bit entre 31 et N
	for (int i = 31; i >= N; i--) {
		if (get_bit(etat_gen, i) == 1)
			return 0;
	}

	// Si tout est beau
	return 1;
	
}

//=========================================================
/*
	Valider qu'il n'y a pas de générateur brisé qui sont activé
	PARAMETRE : état des générateurs, état des bris
	RETOUR : 1 si tout est beau, 0 s'il y a un problème
*/
int valider_bris(unsigned int etat_gen, unsigned int etat_bris) {
	// Vérifie si les 2 variables ont des bits commun
	if ((etat_bris & etat_gen) == 0) {
		return 1;
	}
	else {
		return 0;
	}
}

//=========================================================
/*
	Trouve les endroits où un générateur peut être activé, en considérant les bris
	PARAMETRE : etat_gen, nombre binaire a vérifier
				etat_bris, endroit où les générateur sont brisés
	RETOUR : nombre binaire où un 1 représente les endroits où un
			 générateur peut être activé
*/
unsigned int get_bits_dispo2(unsigned int etat_gen, unsigned int etat_bris) {
	unsigned int bits_possible = 0;

	// test chaque bit pour voir si le bit en question peut être mis à 1
	for (int i = 0; i < N; i += 1) {

		// si le bit i est 0
		if (get_bit(etat_gen, i) == 0 && get_bit(etat_bris, i) == 0) {
			etat_gen = set_bit(etat_gen, i); //met le bit à 1

			// Test si la règle du principe 1 est respectée
			if (principe1(etat_gen)) {
				bits_possible = set_bit(bits_possible, i);
			}

			etat_gen = clear_bit(etat_gen, i); // remet le bit à 0
		}
	}

	return bits_possible;
}

//=========================================================
/*
	Génère aléatoirement des bris de générateur
	PARAMETRE : etat_gen, nombre binaire a vérifier
				etat_bris, endroit où les générateur sont brisés
	RETOUR : 1 si tout est beau, 0 si il y a un échec
*/
int gestion_bris(unsigned int *etat_gen, unsigned int *etat_bris) {
	
	int ordre = 0;

	// Pour chaque bit entre 0 et N-1
	for (int i = 0; i < N; i++) {
		
		// Si le générateur est activé et qu'il n'est pas brisé
		if (get_bit(*etat_gen, i) == 1 && get_bit(*etat_bris, i) == 0) {
			// Probabilité de bris
			if (randf() < PROB_BRIS) {
				*etat_gen = clear_bit(*etat_gen, i);
				*etat_bris = set_bit(*etat_bris, i);

				// Active un bit aléatoire
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
	Permutation de deux générateur, en prennant en compte les générateurs brisés
	PARAMETRE : état des générateurs, état des bris
	RETOUR : état des générateur après la permutation
*/
unsigned int permuter_bits2(unsigned int *etat_gen, unsigned int etat_bris) {

	int ordre_a_eteindre = 0;
	int ordre_a_allumer = 0;

	//choisi aléatoirement un bit à éteindre
	ordre_a_eteindre = choix_alea_bit1(*etat_gen);
	//Trouve les bits disponible et en choisi un aléatoirement pour l'allumer
	ordre_a_allumer = choix_alea_bit1(get_bits_dispo2(*etat_gen, etat_bris));

	//Vérification des ordres
	if (ordre_a_allumer >= N || ordre_a_allumer < 0) {
		return 0;
	}
	if (ordre_a_eteindre >= N || ordre_a_eteindre < 0) {
		return 0;
	}

	//échange les valeurs des 2 bits
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
	Permutation de deux générateur, en prennant en compte les générateurs brisés
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

	// Test plusiseurs cas différent pour s'assurer que tout fonctionne bien
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

	// test la sélection aléatoire 20 fois
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