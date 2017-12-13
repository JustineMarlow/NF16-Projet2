#include <stdio.h>
#include <stdlib.h>
#include "abr.h"
#include "al.h"

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
                print(dico);
                break;
        case 2: printf("Vous avez choisi la fonction verimot. \n");
                dico=verimot(dico);
                break;
        case 3: printf("Vous avez choisi la fonction veridico. \n");
                dico=veridico(dico);
                break;
        case 0: printf("A bientot ! \n");
                break;
        default : printf("Ce choix n'existe pas. \n");
        }
        printf("\n");
    }
    enregistrement_Dictionnaire_ABR(dico);
    }
    else{
        printf("Vous avez choisi la représentation AL. \n");
        DicoAL dico=chargement_Dictionnaire_AL();
        printf("dico : %c, alt1 : %c, alt2: %c, alt3 : %c, alt4 : %c\n",dico->c, dico->alt->c,dico->alt->alt->c, dico->alt->alt->alt->c, dico->alt->alt->alt->alt->c);
        fflush(stdout);
        //printf("Dico : \n");
        //afficherDicoAL(dico,NULL,NULL);
        choix=-1;
        /*Mot2* ls = suggestionMot2(4, dico,creerMot("alp"));
        int l;
        printf("Sugegstions pour alp \n");
        for(l= 0; l < 4; l++) afficherMot(ls[l]);*/
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
                    print2(dico);
                    break;
            case 2: printf("Vous avez choisi la fonction verimot. \n");
                    dico=verimot2(dico);
                    break;
            case 3: printf("Vous avez choisi la fonction veridico. \n");
                    dico=veridico2(dico);
                    break;
            case 0: printf("A bientot ! \n");
                    break;
            default : printf("Ce choix n'existe pas. \n");
            }
            printf("\n");
        }
        enregistrement_Dictionnaire_AL(dico);
        }

    return 0;
}
