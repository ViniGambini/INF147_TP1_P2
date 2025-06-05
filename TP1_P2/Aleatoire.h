
/*=========================================================*/
//	Librairie Aleatoire.h
//
//
/*=========================================================*/

/*=========================================================*/
/*	la constante qui permet de désactiver certains
	warnings achalants de Visual-Studio.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// Déclarer juste 1x
#ifndef ALEA_LIB_OK
#define ALEA_LIB_OK 1

#define EPSILON (0.0000000001)    //la différence réelle minimale

/*=========================================================*/
/*  randf() donne un nombre réel dans l'intervalle ouvert (0,1)

	PARAMETRES :  aucun
	RETOUR : une valeur réelle dans l'intervalle (0,1)

	SPECIFICATIONS : aucune
*/
double randf(void);

/*=========================================================*/
/*  randi() donne un nombre entier dans l'intervalle [0, N[
	(un entier positif entre 0 et la borne reçue - 1)
	PARAMETRES : nombre, un entier positif
	RETOUR : une valeur entre 0 et (nombre-1)

	SPECIFICATIONS : recevant nombre <= 0 retour automatique de 0
*/
int randi(int nombre);

/*=========================================================*/
/*  randf_bornes() donne un nombre réel dans l'intervalle spécifié
	PARAMETRES : deux réels quelconques
	RETOUR : une valeur réelle dans l'intervalle défini par ses
			 deux paramètres

	SPECIFICATIONS : l'ordre des paramètres est sans importance
*/
double randf_bornes(double b1, double b2);

/*=========================================================*/
/*  srand_sys() initialise le générateur de la valeur de
	l'horloge interne de la machine
	PARAMETRES :  Rien
	RETOUR : Rien

	SPECIFICATIONS : DANS UNE SIMULATION NUMÉRIQUE, ON NE DOIT JAMAIS
					 INITIALISER PLUS D'UNE FOIS LE GÉNÉRATEUR
*/
void srand_sys(void);

/*=========================================================*/
/*
	Sort un entier de 32 bits aleatoires
	PARAMETRE : Aucun
	RETOUR : l'entier de 32 bits aleatoires
*/
unsigned int valeur_aleatoire(void);

#endif