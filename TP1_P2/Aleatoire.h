
/*=========================================================*/
//	Librairie Aleatoire.h
//
//
/*=========================================================*/

/*=========================================================*/
/*	la constante qui permet de d�sactiver certains
	warnings achalants de Visual-Studio.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

// D�clarer juste 1x
#ifndef ALEA_LIB_OK
#define ALEA_LIB_OK 1

#define EPSILON (0.0000000001)    //la diff�rence r�elle minimale

/*=========================================================*/
/*  randf() donne un nombre r�el dans l'intervalle ouvert (0,1)

	PARAMETRES :  aucun
	RETOUR : une valeur r�elle dans l'intervalle (0,1)

	SPECIFICATIONS : aucune
*/
double randf(void);

/*=========================================================*/
/*  randi() donne un nombre entier dans l'intervalle [0, N[
	(un entier positif entre 0 et la borne re�ue - 1)
	PARAMETRES : nombre, un entier positif
	RETOUR : une valeur entre 0 et (nombre-1)

	SPECIFICATIONS : recevant nombre <= 0 retour automatique de 0
*/
int randi(int nombre);

/*=========================================================*/
/*  randf_bornes() donne un nombre r�el dans l'intervalle sp�cifi�
	PARAMETRES : deux r�els quelconques
	RETOUR : une valeur r�elle dans l'intervalle d�fini par ses
			 deux param�tres

	SPECIFICATIONS : l'ordre des param�tres est sans importance
*/
double randf_bornes(double b1, double b2);

/*=========================================================*/
/*  srand_sys() initialise le g�n�rateur de la valeur de
	l'horloge interne de la machine
	PARAMETRES :  Rien
	RETOUR : Rien

	SPECIFICATIONS : DANS UNE SIMULATION NUM�RIQUE, ON NE DOIT JAMAIS
					 INITIALISER PLUS D'UNE FOIS LE G�N�RATEUR
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