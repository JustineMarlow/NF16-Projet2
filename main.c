#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main()
{
    int choix=0;
    while (choix!=1 && choix!=2){
        printf("Veuillez choisir une représentation : ABR (1) ou AL (2) \n");
        scanf("%d",&choix);
    }
    if (choix==1) {
    printf("Vous avez choisi la représentation ABR. \n");
    DicoABR* dico=chargement_Dictionnaire_ABR();
    choix=-1;
    while (choix!=0){
        printf("========== Menu ========== \n");
        printf("Que voulez vous faire ?\n");
        printf("1 : print \n");
        printf("2 : verimot \n");
        printf("3 : veridico \n");
        printf("0 : Quitter \n");
        scanf("%d",&choix);

        switch(choix){
        case 1: printf("Vous avez choisi la fonction print. \n");
                choix=0;
                while(choix!=1 && choix!=2){
                    printf("Voulez vous afficher l'ensemble du dictionnaire (1) ou une partie seulement (2) ? \n");
                    scanf("%d",&choix);
                }
                if (choix==1){
                    printf("Le dictionnaire en totalité : \n");
                    afficherDico(dico);
                }
                else {
                    printf("Le dictionnaire en partie : \n");
                    //a faire
                }
                choix=1;
                break;
        case 2: printf("Vous avez choisi la fonction verimot. \n");
                dico=verimot(dico);
                break;
        case 3: printf("Vous avez choisi la fonction veridico. \n");
                veridico(dico);
                break;
        case 0: printf("A bientot ! \n");
                break;
        default : printf("Ce choix n'existe pas. \n");
        }
        printf("\n");
    }
    enregistrement_Dictionnaire_ABR(dico);
    }
    return 0;
}
