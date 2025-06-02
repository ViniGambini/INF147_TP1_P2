
/*=========================================================*/
/*	la constante qui permet de désactiver certains
	warnings achalants de Visual-Studio.
*/
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

#define INT_BIT	(sizeof(int) * 8) // Taille d'un integer

//=========================================================
/*
	Donne la valeur du bit d'ordre spécifié.
	PARAMETRES : nombre, un entier non signé.
				 ordre, l'ordre du bit voulu dans le nombre.
	RETOUR : 0 ou 1
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne 0.
*/
int get_bit(unsigned int nombre, int ordre);

// c'est ici que viendra le développement de sa Macro
#define GET_BIT(nombre, ordre)  (((nombre) & (1 << (ordre))) != 0)

//c'est ici que viendra la déclaration de son test unitaire
void test_macro_GET_BIT(void);

//=========================================================
/*
	Donne la valeur du nombre avec le bit d'ordre spécifié mis à 1
	PARAMETRES : nombre, un entier non signé.
				 ordre, spécifie l'ordre du bit mis à 1 dans le nombre.
	RETOUR : la valeur obtenue du paramètre avec ce bit à 1
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la même valeur reçue.
*/
unsigned int set_bit(unsigned int nombre, int ordre);

// c'est ici que viendra le développement de sa Macro
#define SET_BIT(nombre, ordre)   ..........

//c'est ici que viendra la déclaration de son test unitaire
void test_macro_SET_BIT(void);

//=========================================================
/*
	Donne la valeur du nombre avec le bit d'ordre spécifié mis à 0
	PARAMETRES : nombre, un entier non signé.
				 ordre, spécifie l'ordre du bit mis à 0 dans le nombre.
	RETOUR : la valeur obtenue du paramètre avec ce bit à 0
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la même valeur reçue.
*/
unsigned int clear_bit(unsigned int  nombre, int ordre);

// c'est ici que viendra le développement de sa Macro
#define CLEAR_BIT(nombre, ordre)  ..........

//c'est ici que viendra la déclaration de son test unitaire
void test_macro_CLEAR_BIT(void);

//=========================================================
/*
	Donne la valeur du nombre reçu après l'inversaion du
	bit d'ordre spécifié.
	PARAMETRES: nombre, un entier non signé.
				ordre, spécifie l'ordre du bit à inverser dans le nombre.
	RETOUR : la valeur obtenue du paramètre avec ce bit inversé
	SPECIFICATIONS :
	Si ordre n'est pas dans l'intervalle [0, nb_bits_nombre-1],
	la fonction retourne la même valeur reçue.
*/
unsigned int flip_bit(unsigned int  nombre, int ordre);

// c'est ici que viendra le développement de sa Macro
#define FLIP_BIT(nombre, ordre)    .......... 

//c'est ici que viendra la déclaration de son test unitaire
void test_macro_FLIP_BIT(void);

//=========================================================
/*
	Affiche les bits du nombre reçu à l'écran.
	PARAMETRE : nombre, l'entier non signé à afficher
	RETOUR : rien
	SPECIFICATIONS :
	Les bits sont affichés du plus significatif au moins significatif (de 31->0)
*/
void voir_bits(unsigned int nombre);