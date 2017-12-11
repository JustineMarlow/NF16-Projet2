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
Mot2 creerMot2(char* s){
    Mot2 mot = NULL;
    Mot2 m = mot;
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
    if(m != NULL) m->suiv = newCar;
    else mot = newCar;
    return mot;
}

DicoAL initDicoAL(DicoAL dico, Mot2 mot){
    DicoAL c = dico;
    Mot2 m = mot;
    while(m->c != '$'){
        if(m == NULL){
            printf("Warning : Le mot ajouté n'est pas terminé par un $ \n");
            c->c = '$';
            m = malloc(sizeof(Mot2));
            m->c = '$';
        }
        else {
            printf("m :%c, suiv :%c",m->c, m->suiv->c);
            fflush(stdout);
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

DicoAL prefixeMot2(DicoAL dico, Mot2 mot){
    DicoAL d = dico;
    DicoAL prev = d;
    Mot2 m = mot;
    if(dico == NULL ||mot == NULL) {
        printf("Erreur prefixe introuvable : Mot2 ou dictionnaire vide \n");
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

int rechercheMot2(Mot2 mot, DicoAL dico){
    DicoAL d = prefixeMot2(dico,mot);
    if(d == NULL ||mot == NULL) return 0;
    if(d->c == '$') return 1;
    return 0;
}

DicoAL ajoutMot2(Mot2 mot, DicoAL dico){
    DicoAL d = dico;
    DicoAL prev = d;
    Mot2 m = mot;
    while(m != NULL){

        if(d == NULL || d->c == '\0'){
            DicoAL newCell = malloc(sizeof(Cellule));
            if(newCell == NULL) printf("ERREUR allocation mémoire dans ajoutMot2 \n");
            newCell->succ = NULL;
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
                    DicoAL newCell = malloc(sizeof(Cellule));
                    newCell->c = m->c;
                    d->alt = newCell;
                    d = d->alt;
                }
            }
            else if(prev->alt == d){
                DicoAL newCell = malloc(sizeof(Cellule));
                newCell->c = m->c;
                prev->alt = newCell;
                newCell->alt = d;
                d = newCell;
            }
            else if(prev == d){
                DicoAL newCell = malloc(sizeof(Cellule));
                newCell->c = m->c;
                newCell->alt = d;
                dico = newCell;
                d = dico;
                prev = d;
            }
            else{
                DicoAL newCell = malloc(sizeof(Cellule));
                newCell->c = m->c;
                prev->succ = newCell;
                newCell->alt = d;
                d = prev->succ;
            }
        }
    }
    return dico;
}

void afficherMot2(Mot2 mot){
    Mot2 mc = mot;
    if(mc != NULL){
        while(mc != NULL && mc->c != '$'){
            printf("%c",mc->c);
            mc = mc->suiv;
        }
        printf("\n");
    }
    //else printf("Mot2 vide \n");
}

void afficherDicoAL (DicoAL dico, Mot2 mot, Car* last){
    if(dico != NULL){
        if(mot == NULL){
            if(dico->alt != NULL){
                //printf(" alt ");
                afficherDicoAL(dico->alt, mot,last);
            }
            mot = malloc(sizeof(Car));
            mot->c = dico->c;
            last = mot;
            //printf(" succ ");
            afficherDicoAL(dico->succ, mot, last);
        }
        else{
            if(dico->alt != NULL){
                //printf(" alt ");
                afficherDicoAL(dico->alt, mot,last);
            }
            Car * newCar = malloc(sizeof(Car));
            newCar->c = dico->c;
            last->suiv = newCar;
            last = last->suiv;
            if(dico->c == '$') afficherMot2(mot);
            else {
                //printf(" succ ");
                afficherDicoAL(dico->succ, mot, last);
            }
        }
    }


}

DicoAL supprimmeMot2(DicoAL dico, Mot2 mot){
    if(mot == NULL || dico == NULL) return dico;
    Mot2 m = mot;
    DicoAL d = dico;
    int branchPos = 0;
    char branchC = mot->c;
    int i = 0;
    while(d != NULL && m != NULL && m->c != '$'){
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
            printf("Mot2 à supprimmer introuvable \n");
            return dico;
        }
    }
    //printf("branchC : %c  at %d\n", branchC, branchPos);
    d = dico;
    m = mot;
    DicoAL prev = d;
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
    //printf(" A la suppression, d :%c, branchC : %c, prev : %c \n",d->c,branchC,prev->c);
    if(d == dico) return dico->alt;
    if(prev->succ != NULL && prev->succ == d) prev->succ = d->alt;
    else prev->alt = d->alt;

    return dico;
}

void copieMot2(Mot2 mot, Mot2* copie){
    //if(mot == NULL) printf("Copie de mot NULL \n");
    Mot2 mHead = NULL;
    Mot2 mTail = mHead;
    Mot2 m = mot;
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

DicoAL copieDicoAL(DicoAL dico){
    if(dico == NULL) return NULL;
    Cellule* newCel = malloc(sizeof(Cellule));
    newCel->c = dico->c;
    fflush(stdout);
    newCel->alt = copieDicoAL(dico->alt);
    newCel->succ = copieDicoAL(dico->succ);
    return newCel;
}

void append(Mot2 mot, Car* car){
    if(mot != NULL){
        Mot2 m = mot;
        while(m->suiv != NULL) m = m->suiv;
        m->suiv = car;
    }
    else mot = car;

}

Mot2 closest(DicoAL dico, Mot2 mot){
    DicoAL lastLetter = prefixeMot2(dico, mot);
    DicoAL d = dico;
    Mot2 m = mot;
    Mot2 closestHead = malloc(sizeof(Car));
    Mot2 closestTail = NULL;
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
                //printf("dico : %c, m: %c, passing on to alt", d->c, m->c);
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

Mot2 shortest(DicoAL dico, Mot2 prev){
    if(dico == NULL) return NULL;
    Mot2 alt = NULL;
    Mot2 suc = NULL;
    if(dico->alt != NULL){
        Mot2 tmp1 = NULL;
        copieMot2(prev,&tmp1);
        alt = shortest(dico->alt, tmp1);
    }
    Car* newCar = malloc(sizeof(Car));
    newCar->c = dico->c;
    if(prev != NULL) append(prev,newCar);
    else prev = newCar;
    //printf("Prev : ");
    //afficherMot22(prev);
    //printf("\n");
    if(dico->succ != NULL){
        Mot2 tmp1 = NULL;
        copieMot2(prev,&tmp1);
        suc = shortest(dico->succ, tmp1);
    }
    if(suc != NULL) return suc;
    if(alt != NULL) return alt;
    return prev;
}

Mot2* suggestionMot2(int k, DicoAL dico, Mot2 souschaine){
    //printf("Sous chaine :");
    //afficherMot2(souschaine);
    Mot2 *mots= malloc(MAX);
    DicoAL copie = copieDicoAL(dico);
    int j;
    for(j = 0; j < k ; j++){
        if(copie != NULL){
            mots[j] = closest(copie, souschaine);
            copie = supprimmeMot2(copie, mots[j]);
            /*printf("DicoAL après suppression de ");
            afficherMot2(mots[j]);
            afficherDicoAL(copie,NULL,NULL);*/
        }
        else mots[j] = NULL;
        //if(copie == NULL) printf("DicoAL NULL \n");
    }

    return mots;

}

char* toString(Mot2 mot){

    char* chaine = malloc(30);
    if(mot == NULL){
            chaine[0] = '\n';
            return chaine;
    }
    int i;
    Mot2 m = mot;
    for(i = 0; i < 29 && m!= NULL &&  m->c != '$'; i++){
            chaine[i] = m->c;
            m = m->suiv;
    }
    chaine[29] = '\0';
    return chaine;
}

DicoAL chargement_Dictionnaire_AL(){
    FILE* fichier=NULL;
    fichier=fopen("dictionnaire.txt","r");
    if (fichier==NULL){
        printf("Erreur lors de l'ouverture du fichier dictionnaire.txt ! \n");
        return NULL;
    }
    DicoAL nouveau=malloc(sizeof(Cellule));
    int init = 0;
    //if (nouveau==NULL) return nouveau;
    char chaine[30]="";
    while (fgets(chaine, 30, fichier)!=NULL){
        printf("Lecture : %s \n", chaine);
        fflush(stdout);
        chaine[strlen(chaine)-1]='\0'; //on enleve le \n final

        if(!init){
            nouveau = malloc(sizeof(Cellule));
            nouveau = initDicoAL(nouveau, creerMot2(chaine));
            init= 1;

        }
        else {  printf("Insertion : %s \n", chaine);
                nouveau = ajoutMot2(creerMot2(chaine), nouveau);
                printf("Dico : \n");
                afficherDicoAL(nouveau,NULL,NULL);
        }
    }
    fclose(fichier);
    return nouveau;
}

void print2(DicoAL dico){
    int choix=0;
    char chaine[30];
    int nombre;
    while(choix!=1 && choix!=2){
        printf("Voulez vous afficher l'ensemble du dictionnaire (1) ou une partie seulement (2) ? \n");
        scanf("%d",&choix);
    }
    if (choix==1){
        printf("Le dictionnaire en totalité : \n");
        afficherDicoAL(dico,NULL,NULL);
    }
    else {
        Mot2* liste;
        nombre=0;
        while (nombre<=0){
            printf("Combien de mots voulez vous affichez ? \n");
            scanf("%d",&nombre);
        }
        choix=-1;
        while (choix!=1 && choix!=2){
            printf("Voulez vous afficher les %d premiers mots du dictionnaire (1) ou bien les %d mots les plus proches d'une chaine de caracteres (2) ? \n",nombre, nombre);
            scanf("%d",&choix);
        }
        if (choix==1){
            liste=suggestionMot2(nombre, dico, creerMot2("a"));
            int i;
            for(i = 0; i < nombre; i++) afficherMot2(liste[i]);
        }
        else{
            printf("Entrez la chaine de caracteres : \n");
            scanf("%s",&chaine);
            liste=suggestionMot2(nombre, dico, creerMot2(chaine));
            int i;
            for(i = 0; i < nombre; i++) afficherMot2(liste[i]);
        }
        free(liste);
    }
}

DicoAL verimot2(DicoAL dico){
    FILE* fichier=NULL;
    fichier=fopen("file.txt","r");
    if (fichier==NULL){
        printf("Erreur lors de l'ouverture du fichier file.txt ! \n");
        return dico;
    }
    FILE* nouveau=NULL;
    nouveau=fopen("newfile.txt","w+");
    if (nouveau==NULL){
        printf("Erreur lors de l'ouverture du fichier newfile.txt ! \n");
        fclose(fichier);
        return dico;
    }
    char chaine[30]="";
    DicoAL mot_tmp;
    int choix, choix2, mot_choisi;
    int k=5;
    int i;
    while (fgets(chaine, 30, fichier)!=NULL){
        chaine[strlen(chaine)-1]='\0'; //on enleve le \n final
        printf("%s \n", chaine);
        int isThere=rechercheMot2(creerMot2(chaine), dico);
        if (isThere==0){//le mot n'existe pas dans le dictionnaire
            choix=0;
            choix2=-1;
        while (choix!=choix2){
            choix=0;
            choix2=-1;
            while (choix!=1 && choix!=2){
                printf("Que voulez vous faire du mot %s ? \n", chaine);
                printf("(1) Remplacer ce mot dans le fichier par un mot choisi du dictionnaire \n");
                printf("(2) Ajouter le mot dans le dictionnaire \n");
                scanf("%d",&choix);
            }
            if (choix==2){
                printf("Vous avez choisi d'ajouter le mot %s dans le dictionnaire, veuillez confirmer l'ajout en saisissant de nouveau (2) \n", chaine);
                scanf("%d",&choix2);
                if (choix==choix2){
                ajoutMot2(creerMot2(chaine),dico);
                fputs(chaine, nouveau);
                fputs("\n", nouveau);
                }
            }
            else {
                mot_choisi=-1;
                printf("Choisissez un mot parmi cette sélection : \n");
                Mot2* liste=suggestionMot2(k, dico, creerMot2(chaine));
                while (mot_choisi<=0 || mot_choisi>k){
                    for(i = 0; i < k; i++){
                            printf("%d ",i+1);
                            afficherMot2(liste[i]);
                            printf("\n");
                    }
                    scanf("%d",&mot_choisi);
                }
                printf("Vous avez choisi de corriger %s en %s, veuillez confirmer la correction en saisissant de nouveau (1) \n", chaine, toString(liste[mot_choisi-1]));
                scanf("%d",&choix2);
                if (choix==choix2){
                fputs(toString(liste[mot_choisi-1]), nouveau);
                fputs("\n", nouveau);
                }
            }
        }
        }
        else {
            fputs(chaine, nouveau);
            fputs("\n", nouveau);
        }
    }
    fclose(nouveau);
    fclose(fichier);
    remove("file.txt");
    rename("newfile.txt","file.txt");
    return dico;
}

DicoAL veridico2(DicoAL dico){
    if (dico==NULL) {
        printf("Erreur, le dictionnaire n'existe pas \n");
        return dico;
    }
    else {
        Mot2* liste;
        int nombre=0;
        char chaine[30];
        while (nombre<=0){
            printf("Combien de mots voulez vous verifier ? \n");
            scanf("%d",&nombre);
        }
        int choix=-1;
        while (choix!=1 && choix!=2){
            printf("Voulez vous afficher les %d premiers mots du dictionnaire (1) ou bien les %d mots les plus proches d'une chaine de caracteres (2) ? \n",nombre, nombre);
            scanf("%d",&choix);
        }
        if (choix==1){
            liste=suggestionMot2(nombre, dico, creerMot2("a"));
        }
        else{
            printf("Entrez la chaine de caracteres : \n");
            scanf("%s",&chaine);
            liste=suggestionMot2(nombre, dico, creerMot2(chaine));
        }
        Mot2 curseur = NULL;
        if(liste != NULL) curseur = liste[0];
        int j = 0;

        DicoAL tmp=dico;
        while (j < nombre && curseur!=NULL){
            if(liste != NULL) curseur=liste[j];
            choix=0;
            int choix2=-1;
            while (choix!=1 && choix!=2 && choix!=3){
                afficherMot2(curseur);
                printf("Veuillez choisir l'action à effectuer : \n");
                printf("(1) Corriger ce mot \n");
                printf("(2) Supprimer ce mot \n");
                printf("(3) Valider ce mot \n");
                scanf("%d", &choix);
            }
            if (choix==1){
                char chaine[30];
                printf("Entrer la correction du mot \n");
                scanf("%s",&chaine);
                printf("Vous avez choisi de modifier le mot %s en %s dans le dictionnaire, veuillez confirmer la modification en saisissant à nouveau (1) \n", toString(curseur), chaine);
                scanf("%d",&choix2);
                if (choix==choix2) {
                tmp=supprimmeMot2(tmp,curseur);
                tmp = ajoutMot2(creerMot2(chaine), tmp);
                }
            }
            else if (choix==2) {
                printf("Vous avez choisi de supprimer le mot %s du dictionnaire, veuillez confirmer la suppression en saisissant à nouveau (2) \n", toString(curseur));
                scanf("%d",&choix2);
                if (choix==choix2){
                tmp=supprimmeMot2(tmp,curseur);
                }
                }
            else choix2=choix;
            if (choix==choix2) j++;
        }
    return tmp;
    }
}

void enregistrement_Dictionnaire_AL(DicoAL dico){
    FILE* fichier=NULL;
    fichier=fopen("dictionnaire.txt","w+");
    Mot2 mot = NULL;
    if (fichier==NULL){
        printf("Erreur lors de l'ouverture du fichier dictionnaire.txt ! \n");
        return;
    }
    while (dico != NULL){
        mot = closest(dico,creerMot2("a"));
        fputs(toString(mot), fichier);
        fputs("\n", fichier);
        dico=supprimmeMot2(dico, mot);
    }
    fclose(fichier);
}

