#include <stdio.h>
#include <stdlib.h>
#include "tp4.h"

int main()
{
    DicoABR* nouveau=initDico();
    ajoutMot(nouveau, "mike");
    ajoutMot(nouveau, "dustin");
    ajoutMot(nouveau, "dart");
    ajoutMot(nouveau, "eleven");
    ajoutMot(nouveau, "will");
    ajoutMot(nouveau, "dartagnan");
    ajoutMot(nouveau, "zorro");
    ListeMots* liste=suggestionMots(2, nouveau, "da");
    printf(" Liste : \n");
    afficherListe(liste);
    printf("\n Dictionnaire : \n");
    afficherDico(nouveau);
    return 0;
}
