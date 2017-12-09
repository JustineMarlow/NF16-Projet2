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

typedef Car * Mot;

typedef struct T_Cel{
    char c;
    struct T_Cel * succ;
    struct T_Cel * alt;
} Cellule;

typedef Cellule* Dico ;

Mot creerMot(char* s);

Dico initDico2(Dico dico, Mot mot);

Dico prefixeMot(Dico dico, Mot mot);

int rechercheMot2(Mot mot, Dico dico);

Dico ajoutMot2(Mot mot, Dico dico);

void afficherMot(Mot mot);

void afficherDico (Dico dico, Mot mot, Car* last);

Dico supprimmeMot2(Dico dico, Mot mot);

void copieMot(Mot mot, Mot* copie);

Dico copieDico(Dico dico);

void append(Mot mot, Car* car);

Mot closest(Dico dico, Mot mot);

Mot shortest(Dico dico, Mot prev);

Mot* suggestionMot2(int k, Dico dico, Mot souschaine);

#endif /* al_h */
