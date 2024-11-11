#include <stdio.h>
#include <stdlib.h>
D�finir une structure Etudiant pour stocker les informations de chaque �tudiant (nom, �ge, ann�e scolaire).

Utiliser un fichier pour sauvegarder ces informations, afin qu'elles soient persistantes.

Cr�er des fonctions pour chaque op�ration : ajouter, afficher, mettre � jour, et supprimer.







#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "etudiants.dat"

typedef struct {
    int id;
    char nom[50];
    int age;
    int annee;
} Etudiant;

// Fonction pour ajouter un �tudiant
void ajouterEtudiant() {
    FILE *f = fopen(FILENAME, "ab");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    printf("Entrez l'ID de l'�tudiant : ");
    scanf("%d", &e.id);
    printf("Entrez le nom de l'�tudiant : ");
    scanf("%s", e.nom);
    printf("Entrez l'�ge de l'�tudiant : ");
    scanf("%d", &e.age);
    printf("Entrez l'ann�e scolaire de l'�tudiant : ");
    scanf("%d", &e.annee);

    fwrite(&e, sizeof(Etudiant), 1, f);
    fclose(f);
    printf("�tudiant ajout� avec succ�s !\n");
}

// Fonction pour afficher tous les �tudiants
void afficherEtudiants() {
    FILE *f = fopen(FILENAME, "rb");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    printf("\nListe des �tudiants :\n");
    printf("ID\tNom\t\tAge\tAnn�e scolaire\n");
    printf("-------------------------------------------------\n");

    while (fread(&e, sizeof(Etudiant), 1, f)) {
        printf("%d\t%s\t\t%d\t%d\n", e.id, e.nom, e.age, e.annee);
    }

    fclose(f);
}

// Fonction pour mettre � jour un �tudiant
void mettreAJourEtudiant(int id) {
    FILE *f = fopen(FILENAME, "r+b");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    int trouve = 0;

    while (fread(&e, sizeof(Etudiant), 1, f)) {
        if (e.id == id) {
            printf("Entrez le nouveau nom de l'�tudiant : ");
            scanf("%s", e.nom);
            printf("Entrez le nouvel �ge de l'�tudiant : ");
            scanf("%d", &e.age);
            printf("Entrez la nouvelle ann�e scolaire de l'�tudiant : ");
            scanf("%d", &e.annee);

            fseek(f, -sizeof(Etudiant), SEEK_CUR);
            fwrite(&e, sizeof(Etudiant), 1, f);
            printf("�tudiant mis � jour avec succ�s !\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("�tudiant avec l'ID %d non trouv�.\n", id);
    }

    fclose(f);
}

// Fonction pour supprimer un �tudiant
void supprimerEtudiant(int id) {
    FILE *f = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (f == NULL || temp == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    int trouve = 0;

    while (fread(&e, sizeof(Etudiant), 1, f)) {
        if (e.id == id) {
            trouve = 1;
        } else {
            fwrite(&e, sizeof(Etudiant), 1, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (trouve) {
        printf("�tudiant supprim� avec succ�s !\n");
    } else {
        printf("�tudiant avec l'ID %d non trouv�.\n", id);
    }
}

int main() {
    int choix, id;

    while (1) {
        printf("\n--- Syst�me de Gestion des Dossiers des �tudiants ---\n");
        printf("1. Ajouter un �tudiant\n");
        printf("2. Afficher tous les �tudiants\n");
        printf("3. Mettre � jour un �tudiant\n");
        printf("4. Supprimer un �tudiant\n");
        printf("5. Quitter\n");
        printf("Entrez votre choix : ");
        scanf("%d", &choix);

        switch (choix) {
            case 1:
                ajouterEtudiant();
                break;
            case 2:
                afficherEtudiants();
                break;
            case 3:
                printf("Entrez l'ID de l'�tudiant � mettre � jour : ");
                scanf("%d", &id);
                mettreAJourEtudiant(id);
                break;
            case 4:
                printf("Entrez l'ID de l'�tudiant � supprimer : ");
                scanf("%d", &id);
                supprimerEtudiant(id);
                break;
            case 5:
                exit(0);
            default:
                printf("Choix invalide, veuillez r�essayer.\n");
        }
    }

    return 0;
}
