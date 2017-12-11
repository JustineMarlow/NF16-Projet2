//
//  al.h
//  NF16-TP4
//
//  Created by Elias  on 30/11/2017.
//  Copyright © 2017 Elias . All rights reserved.
//

#ifndef al_h
#define al_h
#define MAX 100
#include <stdio.h>
typedef struct T_Car{
    char c;
    struct T_Car *suiv;
} Car;

typedef Car * Mot2;

typedef struct T_Cel{
    char c;
    struct T_Cel * succ;
    struct T_Cel * alt;
} Cellule;

typedef Cellule* DicoAL ;

Mot2 creerMot2(char* s);

DicoAL initDicoAL(DicoAL dico, Mot2 mot);

DicoAL prefixeMot2(DicoAL dico, Mot2 mot);

int rechercheMot2(Mot2 mot, DicoAL dico);

DicoAL ajoutMot2(Mot2 mot, DicoAL dico);

void afficherMot2(Mot2 mot);

void afficherDicoAL(DicoAL dico, Mot2 mot, Car* last);

DicoAL supprimmeMot2(DicoAL dico, Mot2 mot);

void copieMot2(Mot2 mot, Mot2* copie);

DicoAL copieDicoAL(DicoAL dico);

void append(Mot2 mot, Car* car);

Mot2 closest(DicoAL dico, Mot2 mot);

Mot2 shortest(DicoAL dico, Mot2 prev);

char* toString(Mot2 mot);

Mot2* suggestionMot2(int k, DicoAL dico, Mot2 souschaine);

DicoAL chargement_Dictionnaire_AL();

void print2(DicoAL dico);

DicoAL verimot2(DicoAL dico);

DicoAL veridico2(DicoAL dico);

void enregistrement_Dictionnaire_AL(DicoAL dico);



#endif /* al_h */
