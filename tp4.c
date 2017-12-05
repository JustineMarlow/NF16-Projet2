#include "tp4.h"

DicoABR* initDico(){
    DicoABR* newDico=malloc(sizeof(DicoABR));
    if(newDico == NULL){
        printf("Erreur, allocation impossible ! \n");
        return NULL;
    }
    strcpy(newDico->valeur,"\0");
    newDico->pere=NULL;
    newDico->droit=NULL;
    newDico->gauche=NULL;
    return newDico;
};

void ajoutMot(DicoABR* dico, char* val){
    if (dico==NULL) printf("Erreur, le dictionnaire n'existe pas \n");
    else {
        if (strcmp(dico->valeur,"\0")==0) strcpy(dico->valeur,val);
        else {
            DicoABR* newWord=initDico();
            strcpy(newWord->valeur,val);
            DicoABR* y=NULL;
            DicoABR* x=dico;
            while (x!=NULL){
                y=x;
                if (strcmp(x->valeur,val)>0) x=x->gauche;
                else x=x->droit;
            }
            newWord->pere=y;
            if (strcmp(y->valeur,val)>0) y->gauche=newWord;
            else y->droit=newWord;
    }
    }
};

void afficherDico(DicoABR* dico){
    if (dico==NULL) printf("Erreur, le dictionnaire n'existe pas \n");
    else {
        if (strcmp(dico->valeur,"\0")==0) printf("Le dictionnaire est vide \n");
        else {
        if (dico->gauche!=NULL) afficherDico(dico->gauche);
        printf("%s \n", dico->valeur);
        if (dico->droit!=NULL) afficherDico(dico->droit);
    }
    }
};

DicoABR* rechercheMot(DicoABR* dico, char* val){
    if (dico==NULL){
        printf("Erreur, le dictionnaire n'existe pas \n");
        return NULL;
    }
    if (strcmp(dico->valeur,"\0")==0){
        printf("Erreur, le dictionnaire est vide \n");
        return NULL;
    }
    if (val==NULL){
        printf("Erreur, la valeur est vide \n");
        return NULL;
    }
    DicoABR* curseur=dico;
    while (curseur!=NULL){
        if (strcmp(curseur->valeur,val)==0) return curseur;
        if (strcmp(curseur->valeur,val)>0) curseur=curseur->gauche;
        else curseur=curseur->droit;
    }
    if (curseur==NULL) printf("Le mot n'apparait pas dans le dictionnaire \n");
    return curseur;
};

DicoABR* minimum(DicoABR* dico){
    if (dico==NULL){
        printf("Erreur, le dictionnaire n'existe pas \n");
        return NULL;
    }
    if (strcmp(dico->valeur,"\0")==0){
        printf("Erreur, le dictionnaire est vide \n");
        return NULL;
    }
    DicoABR* curseur=dico;
    while (curseur->gauche!=NULL)
        curseur=curseur->gauche;
    return curseur;
};

DicoABR* successeur(DicoABR* dico){
    if (dico->droit!=NULL) return minimum(dico->droit);
    DicoABR* x=dico;
    DicoABR* y=dico->pere;
    while (y!=NULL && x==y->droit){
        x=y;
        y=y->pere;
    }
    return y;
};

DicoABR* supprimeMot(DicoABR* dico, char* val){
    if (dico==NULL) {
        printf("Erreur, le dictionnaire n'existe pas \n");
        return dico;
    }
    if (strcmp(dico->valeur,"\0")==0) {
        printf("Erreur, le dictionnaire est vide \n");
        return dico;
    }
    DicoABR* find=rechercheMot(dico, val);
    if (find==NULL) {
        printf("Erreur, le mot n'apparait pas dans le dictionnaire \n");
        return dico;
    }
    //Si find n'a pas de fils
    if (find->gauche==NULL && find->droit==NULL){
        if (find->pere==NULL) {strcpy(dico->valeur, "\0"); //s'il s'agit de la racine
                         return dico;}
        else {
            if (find->pere->gauche==find) find->pere->gauche=NULL;
            else find->pere->droit=NULL;
        free(find);
        }
        return dico;
    }
    //Si find a un seul fils gauche
    if (find->gauche!=NULL && find->droit==NULL){
        if (find->pere==NULL){ //il s'agit de la racine
            find->gauche->pere=NULL;
            DicoABR* retour=find->gauche;
            free(find);
            return retour;
        }
        if (find->pere->gauche==find) find->pere->gauche=find->gauche;
        else find->pere->droit=find->gauche;
        find->gauche->pere=find->pere;
        free(find);
        return dico;
    }
    //Si find a un seul fils droit
    if (find->gauche==NULL && find->droit!=NULL){
        if (find->pere==NULL){ //il s'agit de la racine
            find->droit->pere=NULL;
            DicoABR* retour=find->droit;
            free(find);
            return retour;
        }
        if (find->pere->gauche==find) find->pere->gauche=find->droit;
        else find->pere->droit=find->droit;
        find->droit->pere=find->pere;
        free(find);
        return dico;
    }
    //Si find a deux fils
    DicoABR* remplace=successeur(find);
    strcpy(find->valeur,remplace->valeur);
    supprimeMot(remplace, remplace->valeur);
    return dico;
};

/*
Implémenter et tester une fonction suggestionMots; suggestionMots prend en entrées: k un
entier positif, dico un dictionnaire et souschaine une chaîne de caractères. La fonction
retourne les k mots plus proches de souschaine se trouvant dans dico.
Soient deux mots x et y qui commencent respectivement par les n1 et n2 premières lettres de
souschaine. x est plus proche de souschaine que y si n1>n2 ou bien n1=n2 et x est plus petit
que y dans l’ordre lexicographique.
*/
int taillePrefixeCommun(char* mot1, char* mot2){
    int taille=0;
    while (mot1[taille]==mot2[taille]) taille++;
    return taille;
}

DicoABR* motLePlusProche(DicoABR* dico, char* souschaine){
    if (dico->droit==NULL && dico->gauche==NULL) return dico;
    if (dico->droit==NULL && dico->gauche!=NULL){
        int taille1 = taillePrefixeCommun(dico->valeur, souschaine);
        Mot* gauche = motLePlusProche(dico->gauche, souschaine);
        int taille2 = taillePrefixeCommun(gauche->valeur, souschaine);
        if (taille1 > taille2 || (taille1==taille2 && strcmp(dico->valeur, gauche->valeur)<0)) return dico;
        else return gauche;
    }
    if (dico->droit!=NULL && dico->gauche==NULL){
        int taille1 = taillePrefixeCommun(dico->valeur, souschaine);
        Mot* droit = motLePlusProche(dico->droit, souschaine);
        int taille2 = taillePrefixeCommun(droit->valeur, souschaine);
        if (taille1 > taille2 || (taille1==taille2 && strcmp(dico->valeur, droit->valeur)<0)) return dico;
        else return droit;
    }
    Mot* gauche = motLePlusProche(dico->gauche, souschaine);
    Mot* droit  = motLePlusProche(dico->droit, souschaine);
    int taille2 = taillePrefixeCommun(gauche->valeur, souschaine);
    int taille3 = taillePrefixeCommun(droit->valeur, souschaine);
    Mot* proche;
    int tailleMax;
    if (taille2 > taille3 || (taille2==taille3 && strcmp(gauche->valeur, droit->valeur)<0)) {proche=gauche; tailleMax=taille2;}
        else {proche=droit; tailleMax=taille3;}
    int taille1 = taillePrefixeCommun(dico->valeur, souschaine);
    if (taille1 > tailleMax || (taille1==tailleMax && strcmp (dico->valeur, proche->valeur)<0)) return dico;
        else return proche;
}

ListeMots* ajoutListe(ListeMots* liste, char* val){
    Mot* nouveau=malloc(sizeof(Mot));
    strcpy(nouveau->valeur,val);
    if (liste->tete==NULL) liste->tete=nouveau;
    if (liste->queue==NULL) liste->queue=nouveau;
    else { liste->queue->suivant=nouveau;
           liste->queue=nouveau;
           }
    liste->taille++;
    return liste;
}

void copierDictionnaire(DicoABR* dico, DicoABR* copie){
    ajoutMot(copie, dico->valeur);
    if (dico->gauche!=NULL) copierDictionnaire(dico->gauche, copie);
    if (dico->droit!=NULL) copierDictionnaire(dico->droit, copie);
}


ListeMots* suggestionMots(int k, DicoABR* dico, char* souschaine){
    DicoABR* tmp=initDico();
    copierDictionnaire(dico, tmp);
    ListeMots* liste=malloc(sizeof(ListeMots));
    if (liste==NULL){
        printf("Erreur lors de l'allocation dynamique \n");
        return NULL;
    }
    liste->tete=NULL;
    liste->queue=NULL;
    liste->taille=0;
    Mot* proche;
    while (liste->taille<k && strcmp(tmp->valeur, "\0")!=0){
        proche=motLePlusProche(tmp, souschaine);
        liste=ajoutListe(liste, proche->valeur);
        tmp=supprimeMot(tmp, proche->valeur);
    }
    free(tmp);
    return liste;
}

void afficherListe(ListeMots* liste){
    if (liste==NULL) printf("La liste n'existe pas \n");
    else {
        if (liste->taille==0) printf("La liste est vide \n");
        else {
            int i;
            Mot* curseur=liste->tete;
            for (i=0; i<liste->taille; i++) {
                printf("%s \n",curseur->valeur);
                curseur=curseur->suivant;
            }
        }
    }
}

DicoABR* chargement_Dictionnaire_ABR(){
    FILE* fichier=NULL;
    fichier=fopen("dictionnaire.txt","r");
    if (fichier==NULL){
        printf("Erreur lors de l'ouverture du fichier dictionnaire.txt ! \n");
        return NULL;
    }
    DicoABR* nouveau=initDico();
    if (nouveau==NULL) return nouveau;
    char chaine[30]="";
    while (fgets(chaine, 30, fichier)!=NULL){
        chaine[strlen(chaine)-1]='\0'; //on enleve le \n final
        ajoutMot(nouveau, chaine);
    }
    fclose(fichier);
    return nouveau;
}

DicoABR* verimot(DicoABR* dico){
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
    DicoABR* mot_tmp;
    int choix;
    int k=5;
    int i;
    while (fgets(chaine, 30, fichier)!=NULL){
        chaine[strlen(chaine)-1]='\0'; //on enleve le \n final
        printf("%s \n", chaine);
        mot_tmp=rechercheMot(dico, chaine);
        if (mot_tmp==NULL){//le mot n'existe pas dans le dictionnaire
            choix=0;
            while (choix!=1 && choix!=2){
                printf("Que voulez vous faire ? \n");
                printf("(1) Remplacer ce mot dans le fichier par un mot choisi du dictionnaire \n");
                printf("(2) Ajouter le mot dans le dictionnaire \n");
                scanf("%d",&choix);
            }
            if (choix==2){
                ajoutMot(dico, chaine);
                fputs(chaine, nouveau);
                fputs("\n", nouveau);
            }
            else {
                choix=-1;
                printf("Choisissez un mot parmi cette sélection : \n");
                ListeMots* liste=suggestionMots(k,dico,chaine);
                Mot* curseur;
                while (choix<=0 || choix>liste->taille){
                    i=1;
                    curseur=liste->tete;
                    while (curseur!=NULL){
                        printf("(%d) %s \n",i,curseur->valeur);
                        curseur=curseur->suivant;
                        i++;
                    }
                    scanf("%d",&choix);
                }
                curseur=liste->tete;
                for (i=1; i<choix; i++)
                    curseur=curseur->suivant;
                printf("%s à corriger en %s \n", chaine, curseur->valeur);
                fputs(curseur->valeur, nouveau);
                fputs("\n", nouveau);
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

void veridico(DicoABR* dico){
    if (dico==NULL) {
        printf("Erreur, le dictionnaire n'existe pas \n");
    }
    else {
        if (dico->gauche!=NULL) veridico(dico->gauche);
        int choix=0;
        while (choix!=1 && choix!=2 && choix!=3){
            printf("%s \n", dico->valeur);
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
            ajoutMot(dico, chaine);
            dico=supprimeMot(dico, dico->valeur);
        }
        else if (choix==2) dico=supprimeMot(dico, dico->valeur);
        if (dico->droit!=NULL) veridico(dico->droit);
    }
}

void enregistrement_Dictionnaire_ABR(DicoABR* dico){
    FILE* fichier=NULL;
    fichier=fopen("dictionnaire.txt","w+");
    if (fichier==NULL){
        printf("Erreur lors de l'ouverture du fichier dictionnaire.txt ! \n");
        return NULL;
    }
    while (strcmp(dico->valeur, "\0")!=0){
        fputs(dico->valeur, fichier);
        fputs("\n", fichier);
        dico=supprimeMot(dico, dico->valeur);
    }
    fclose(fichier);
}
