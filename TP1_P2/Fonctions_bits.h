
/*=========================================================*/
//	Librairie Fonctions_bits.h
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
#ifndef FCT_BIT_LIB_OK
#define FCT_BIT_LIB_OK 1

#define INT_BIT	(sizeof(int) * 8) // Taille d'un integer

//=========================================================
/*
	Donne la valeur du bit d'ordre sp�cifi�.
	PARAMETRES : nombre, un entier non sign�.
				 ordre, l'ordre du bit voulu dans le nombre.
	RETOUR : 0 ou 1
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne 0.
*/
int get_bit(unsigned int nombre, int ordre);

// Macro de la fonction get_bit()
#define GET_BIT(nombre, ordre) (((nombre) & (1 << (ordre))) != 0)

//=========================================================
/*
	Donne la valeur du nombre avec le bit d'ordre sp�cifi� mis � 1
	PARAMETRES : nombre, un entier non sign�.
				 ordre, sp�cifie l'ordre du bit mis � 1 dans le nombre.
	RETOUR : la valeur obtenue du param�tre avec ce bit � 1
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la m�me valeur re�ue.
*/
unsigned int set_bit(unsigned int nombre, int ordre);

// Macro de la fonction set_bit()
#define SET_BIT(nombre, ordre) (((nombre) | (1 << (ordre))))

//=========================================================
/*
	Donne la valeur du nombre avec le bit d'ordre sp�cifi� mis � 0
	PARAMETRES : nombre, un entier non sign�.
				 ordre, sp�cifie l'ordre du bit mis � 0 dans le nombre.
	RETOUR : la valeur obtenue du param�tre avec ce bit � 0
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la m�me valeur re�ue.
*/
unsigned int clear_bit(unsigned int  nombre, int ordre);

// Macro de la fonction clear_bit()
#define CLEAR_BIT(nombre, ordre) (((nombre) & ~(1 << (ordre))))

//=========================================================
/*
	Donne la valeur du nombre re�u apr�s l'inversaion du
	bit d'ordre sp�cifi�.
	PARAMETRES: nombre, un entier non sign�.
				ordre, sp�cifie l'ordre du bit � inverser dans le nombre.
	RETOUR : la valeur obtenue du param�tre avec ce bit invers�
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la m�me valeur re�ue.
*/
unsigned int flip_bit(unsigned int  nombre, int ordre);

// Macro de la fonction flip_bit()
#define FLIP_BIT(nombre, ordre) (GET_BIT((nombre), (ordre)) ?\
								 CLEAR_BIT((nombre), (ordre))\
                                : SET_BIT((nombre), (ordre)))

//=========================================================
/*
	Affiche les bits du nombre re�u � l'�cran.
	PARAMETRE : nombre, l'entier non sign� � afficher
	RETOUR : rien
	SPECIFICATIONS :
	Les bits sont affich�s du plus significatif au moins significatif (de 31->0)
*/
void voir_bits(unsigned int nombre);

//=========================================================
//Test pour la macro et la fonction get_bit()
void test_macro_GET_BIT(void);

//=========================================================
//Test pour la macro et la fonction set_bit()
void test_macro_SET_BIT(void);

//=========================================================
//Test pour la macro et la fonction clear_bit()
void test_macro_CLEAR_BIT(void);

//=========================================================
//Test pour la macro et la fonction flip_bit()
void test_macro_FLIP_BIT(void);

#endif