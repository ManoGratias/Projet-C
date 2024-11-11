#include <stdio.h>
#include <stdlib.h>
Définir une structure Etudiant pour stocker les informations de chaque étudiant (nom, âge, année scolaire).

Utiliser un fichier pour sauvegarder ces informations, afin qu'elles soient persistantes.

Créer des fonctions pour chaque opération : ajouter, afficher, mettre à jour, et supprimer.







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

// Fonction pour ajouter un étudiant
void ajouterEtudiant() {
    FILE *f = fopen(FILENAME, "ab");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    printf("Entrez l'ID de l'étudiant : ");
    scanf("%d", &e.id);
    printf("Entrez le nom de l'étudiant : ");
    scanf("%s", e.nom);
    printf("Entrez l'âge de l'étudiant : ");
    scanf("%d", &e.age);
    printf("Entrez l'année scolaire de l'étudiant : ");
    scanf("%d", &e.annee);

    fwrite(&e, sizeof(Etudiant), 1, f);
    fclose(f);
    printf("Étudiant ajouté avec succès !\n");
}

// Fonction pour afficher tous les étudiants
void afficherEtudiants() {
    FILE *f = fopen(FILENAME, "rb");
    if (f == NULL) {
        perror("Erreur d'ouverture du fichier");
        return;
    }

    Etudiant e;
    printf("\nListe des étudiants :\n");
    printf("ID\tNom\t\tAge\tAnnée scolaire\n");
    printf("-------------------------------------------------\n");

    while (fread(&e, sizeof(Etudiant), 1, f)) {
        printf("%d\t%s\t\t%d\t%d\n", e.id, e.nom, e.age, e.annee);
    }

    fclose(f);
}

// Fonction pour mettre à jour un étudiant
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
            printf("Entrez le nouveau nom de l'étudiant : ");
            scanf("%s", e.nom);
            printf("Entrez le nouvel âge de l'étudiant : ");
            scanf("%d", &e.age);
            printf("Entrez la nouvelle année scolaire de l'étudiant : ");
            scanf("%d", &e.annee);

            fseek(f, -sizeof(Etudiant), SEEK_CUR);
            fwrite(&e, sizeof(Etudiant), 1, f);
            printf("Étudiant mis à jour avec succès !\n");
            trouve = 1;
            break;
        }
    }

    if (!trouve) {
        printf("Étudiant avec l'ID %d non trouvé.\n", id);
    }

    fclose(f);
}

// Fonction pour supprimer un étudiant
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
        printf("Étudiant supprimé avec succès !\n");
    } else {
        printf("Étudiant avec l'ID %d non trouvé.\n", id);
    }
}

int main() {
    int choix, id;

    while (1) {
        printf("\n--- Système de Gestion des Dossiers des Étudiants ---\n");
        printf("1. Ajouter un étudiant\n");
        printf("2. Afficher tous les étudiants\n");
        printf("3. Mettre à jour un étudiant\n");
        printf("4. Supprimer un étudiant\n");
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
                printf("Entrez l'ID de l'étudiant à mettre à jour : ");
                scanf("%d", &id);
                mettreAJourEtudiant(id);
                break;
            case 4:
                printf("Entrez l'ID de l'étudiant à supprimer : ");
                scanf("%d", &id);
                supprimerEtudiant(id);
                break;
            case 5:
                exit(0);
            default:
                printf("Choix invalide, veuillez réessayer.\n");
        }
    }

    return 0;
}
