#ifndef TP4_H_INCLUDED
#define TP4_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct ABR{
    char valeur[30];
    struct ABR* pere;
    struct ABR* gauche;
    struct ABR* droit;
} DicoABR;

typedef struct mot{
    char valeur[30];
    struct Mot* suivant;
} Mot;

typedef struct liste{
    Mot* tete;
    Mot* queue;
    int taille;
} ListeMots;

DicoABR* initDico(); //vérifié
void ajoutMot(DicoABR* dico, char* valeur); //vérifié
void afficherDico(DicoABR* dico); //vérifié
DicoABR* rechercheMot(DicoABR* dico, char* valeur); //vérifié
DicoABR* minimum(DicoABR* dico); //vérifié
DicoABR* successeur(DicoABR* dico); //vérifié
DicoABR* supprimeMot(DicoABR* dico, char* valeur);

void copierDictionnaire(DicoABR* dico, DicoABR* copie);
void afficherListe(ListeMots* liste);
int taillePrefixeCommun(char* mot1, char* mot2);
DicoABR* motLePlusProche(DicoABR* dico, char* souschaine);
ListeMots* ajoutListe(ListeMots* liste, char* val);
ListeMots* suggestionMots(int k, DicoABR* dico, char* souschaine);

DicoABR* chargement_Dictionnaire_ABR();
DicoABR* verimot(DicoABR* dico);
void veridico(DicoABR* dico);
void enregistrement_Dictionnaire_ABR(DicoABR* dico);

#endif // TP4_H_INCLUDED
