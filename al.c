 //
//  al.c
//  NF16-TP4
//
//  Created by Elias  on 30/11/2017.
//  Copyright © 2017 Elias . All rights reserved.
//

#include "al.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define WMAX 255
Mot creerMot(char* s){
    Mot mot = NULL;
    Mot m = mot;
    int i = 0;
    for(i = 0; i < strlen(s); i++){
        Car* newCar = malloc(sizeof(Car));
        newCar->c = s[i];
        if(m == NULL){
            m = newCar;
            mot = m;
        }
        else{
            m->suiv = newCar;
            m = m->suiv;
        }
    }
    Car* newCar = malloc(sizeof(Car));
    newCar->c = '$';
    m->suiv = newCar;
    return mot;
}

Dico initDico2(Dico dico, Mot mot){
    Dico c = dico;
    Mot m = mot;
    while(m->c != '$'){
        if(m == NULL){
            printf("Warning : Le mot ajouté n'est pas terminé par un $ \n");
            c->c = '$';
            m = malloc(sizeof(Mot));
            m->c = '$';
        }
        else {
            c->c = m->c;
            m = m->suiv;
            c->succ = malloc(sizeof(Cellule));
            c = c->succ;
        }
    }
    c->c = '$';
    //printf("initialisation du dico avec :");
    c = dico;
    while(c->c != '$'){
        //printf("%c",c->c);
        c = c->succ;
    }
    //printf("\n");
    return dico;
}

Dico prefixeMot(Dico dico, Mot mot){
    Dico d = dico;
    Dico prev = d;
    Mot m = mot;
    if(dico == NULL ||mot == NULL) {
        printf("Erreur prefixe introuvable : Mot ou dictionnaire vide \n");
        return NULL;
    }
    while(d->c != mot->c){
        if(d->alt == NULL){
           //printf("Aucun préfixe dans l'arbre \n");
            return NULL;
        }
        else d = d->alt;
    }


    while(d != NULL && m != NULL){
        if(d->c == m->c) {
            prev = d;
            d = d->succ;
            m = m->suiv;
        }
        else{
            if(d->alt != NULL && d->alt->c == m->c){
                prev = d;
                d = d->alt;
            }
            else if(d->c == '$' ) d = d->alt;
            else d = NULL;

        }
    }
    return prev;
}

int rechercheMot2(Mot mot, Dico dico){
    Dico d = prefixeMot(dico,mot);
    if(d == NULL ||mot == NULL) return 0;
    if(d->c == '$') return 1;
    return 0;
}

Dico ajoutMot2(Mot mot, Dico dico){
    Dico d = dico;
    Dico prev = d;
    Mot m = mot;
    while(m != NULL){

        if(d == NULL || d->c == '\0'){
            Dico newCell = malloc(sizeof(Cellule));
            if(newCell == NULL) printf("ERREUR allocation mémoire dans ajoutMot2 \n");

            newCell->c = m->c;
            prev->succ = newCell;
            d = newCell->succ;
            prev = prev->succ;
            m = m->suiv;
        }
        else if(d->c == m->c){
            prev = d;
            d = d->succ;
            m = m->suiv;


        }
        else{
            if(d->c < m->c){
                if(d->alt != NULL){
                    prev = d;
                    d = d->alt;

                }
                else{
                    prev = d;
                    Dico newCell = malloc(sizeof(Cellule));
                    newCell->c = m->c;
                    d->alt = newCell;
                    d = d->alt;
                }
            }
            else if(prev->alt == d){
                Dico newCell = malloc(sizeof(Cellule));
                newCell->c = m->c;
                prev->alt = newCell;
                newCell->alt = d;
                d = newCell;
            }
            else{
                Dico newCell = malloc(sizeof(Cellule));
                newCell->c = m->c;
                prev->succ = newCell;
                newCell->alt = d;
                d = prev->succ;
            }
        }
    }
    return dico;
}

void afficherMot(Mot mot){
    Mot mc = mot;
    if(mc != NULL){
        while(mc != NULL && mc->c != '$'){
            printf("%c",mc->c);
            mc = mc->suiv;
        }
        printf("\n");
    }
    //else printf("Mot vide \n");
}

void afficherDico (Dico dico, Mot mot, Car* last){
    if(mot == NULL){
        if(dico->alt != NULL) afficherDico(dico->alt, mot,last);
        mot = malloc(sizeof(Car));
        mot->c = dico->c;
        last = mot;
        afficherDico(dico->succ, mot, last);
    }
    else{
        if(dico->alt != NULL){
            afficherDico(dico->alt, mot,last);
        }
        Car * newCar = malloc(sizeof(Car));
        newCar->c = dico->c;
        last->suiv = newCar;
        last = last->suiv;
        if(dico->c == '$') afficherMot(mot);
        else afficherDico(dico->succ, mot, last);
    }


}

Dico supprimmeMot2(Dico dico, Mot mot){
    if(mot == NULL || dico == NULL) return dico;
    Mot m = mot;
    Dico d = dico;
    int branchPos = 0;
    char branchC = mot->c;
    int i = 0;
    while(m->c != '$'){
        if(d->c == m->c){
            if(d->alt != NULL){
                branchPos = i;
                branchC = m-> c;
            }
            d = d->succ;
            m = m->suiv;
            i++;
        }
        else if(d->alt != NULL && m->c > d->c){
            branchPos = i;
            branchC = m->c;
            d = d->alt;
        }
        else{
            printf("Mot à supprimmer introuvable \n");
            return dico;
        }
    }
    //printf("branchC : %c  at %d\n", branchC, branchPos);
    d = dico;
    m = mot;
    Dico prev = d;
    int j = 0;
    //printf("prev : %c", prev->c);
    while(j != branchPos || d->c != branchC){
        //printf("%c,",d->c);
        if(d->c == m->c){
            prev = d;
            d = d->succ;
            m = m->suiv;
            j++;
        }
        else if(d->alt != NULL && m->c > d->c){
            prev = d;
            d = d->alt;
        }
    }
    if(d == dico) return dico->alt;
    if(prev->succ != NULL && prev->succ->c == d->c) prev->succ = d->alt;
    else prev->alt = d->alt;

    return dico;
}

void copieMot(Mot mot, Mot* copie){
    //if(mot == NULL) printf("Copie de mot NULL \n");
    Mot mHead = NULL;
    Mot mTail = mHead;
    Mot m = mot;
    while(m != NULL) {
        Car* newCar = malloc(sizeof(Car));
        newCar->c = m->c;
        if(mTail == NULL){
            mTail = newCar;
            mHead = mTail;
        }
        else{
            mTail->suiv = newCar;
            mTail = mTail->suiv;
        }
        m = m->suiv;
    }
    *copie = mHead;
}

Dico copieDico(Dico dico){
    if(dico == NULL) return NULL;
    Cellule* newCel = malloc(sizeof(Cellule));
    newCel->c = dico->c;
    newCel->alt = copieDico(dico->alt);
    newCel->succ = copieDico(dico->succ);
    return newCel;
}

void append(Mot mot, Car* car){
    if(mot != NULL){
        Mot m = mot;
        while(m->suiv != NULL) m = m->suiv;
        m->suiv = car;
    }
    else mot = car;

}

Mot closest(Dico dico, Mot mot){
    Dico lastLetter = prefixeMot(dico, mot);
    Dico d = dico;
    Mot m = mot;
    Mot closestHead = malloc(sizeof(Car));
    Mot closestTail = NULL;
    while(d != lastLetter && d != NULL){
        if(d->c == m->c) {
            Car* newCar = malloc(sizeof(Car));
            newCar->c = d->c;
            //printf("%c, ", newCar->c);
            if(closestTail != NULL){
                closestTail->suiv = newCar;
                closestTail = closestTail->suiv;
            }
            else{
                closestHead = newCar;
                closestTail = newCar;
            }
            d = d->succ;
            m = m->suiv;
        }
        else{
            if(d->alt != NULL && d->c < m->c){
                d = d->alt;
            }
            else if(d->c == '$') d = d->alt;
            else break;
        }

    }

    //if(d != NULL) printf(" \n Done, calling shortest with dico : %c",d->c);
    //else printf(" \n Done, calling shortest with null dico \n");

    if(closestTail != NULL) closestTail->suiv = shortest(d, NULL);
    else closestHead = shortest(d,NULL);
    return closestHead;

}

Mot shortest(Dico dico, Mot prev){
    Mot alt = NULL;
    Mot suc = NULL;
    if(dico->alt != NULL){
        Mot tmp1 = NULL;
        copieMot(prev,&tmp1);
        alt = shortest(dico->alt, tmp1);
    }
    Car* newCar = malloc(sizeof(Car));
    newCar->c = dico->c;
    if(prev != NULL) append(prev,newCar);
    else prev = newCar;
    //printf("Prev : ");
    //afficherMot(prev);
    //printf("\n");
    if(dico->succ != NULL){
        Mot tmp1 = NULL;
        copieMot(prev,&tmp1);
        suc = shortest(dico->succ, tmp1);
    }
    if(suc != NULL) return suc;
    if(alt != NULL) return alt;
    return prev;
}

Mot* suggestionMot2(int k, Dico dico, Mot souschaine){
    Mot *mots= malloc(MAX);
    Dico copie = copieDico(dico);
    int j;
    for(j = 0; j < k ; j++){
        if(copie != NULL){
            mots[j] = closest(copie, souschaine);
            copie = supprimmeMot2(copie, mots[j]);
        }
        else mots[j] = NULL;
        //if(copie == NULL) printf("Dico NULL \n");
    }

    return mots;

}



