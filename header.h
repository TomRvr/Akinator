#ifndef HEADER_H
#define HEADER_H

#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NB_perso 28
#define NB_questions 28
/*---------------------------------------------VARIABLES GLOBALES--------------------------------------------------------------------------*/
GtkWidget *texte;
GtkWidget *texte_fin;
GtkWidget *bar;
int cpt_q;	/*Compteur qui compte le nombre de questions deja posée*/
int gagner;
int num_q;		/*numero de question*/
int reponse;	/*reponse donnee*/
char *q; /*a 0 tant que l'ordinateur n'a pas trouvé le personnage*/
int nb_q;
int *T_notes;
int* T_q;
int a;
int arret;
int *tabnewperso;
/*---------------------------------------------STRUCTURE--------------------------------------------------------------------------*/

typedef struct perso{
	char nom[30];
	int reponses[NB_perso];
	int score;
	struct perso *perso_suiv;
}PERSO;

typedef struct population{
    int nb_perso;
    PERSO *tete;
} POPULATION;

/*---------------------------------------------LECTURE POPULATION-------------------------------------------------------------------*/

void init_population(POPULATION *ptr_pop);
PERSO *creer_perso(int nb_q);
void ajouter_debut_liste(POPULATION *ptr_pop, PERSO *ptr_p);
void afficher_perso(PERSO p, int nb_q);
void lecture_population(POPULATION *pop, int nb_q);
void afficher_population(POPULATION pop, int nb_q);

/*---------------------------------------------SCORE---------------------------------------------------------------------------------*/

int score_perso(int rep_donnee,int rep_atendue,int score);
void calcul_score_perso(int donnee, POPULATION *T, int numeroquestion, int nb_q);

/*---------------------------------------------NOTE----------------------------------------------------------------------------------*/

void creation_T_notes(int* score, int nb_q, POPULATION *pop, int *tab);
int questionaposer(int *tab, int questres);
int note(POPULATION *pop, int num_question);

/*---------------------------------------------SUPPRIMER SCORE------------------------------------------------------------------------*/

void supprime(POPULATION *pop, int score_min);

/*---------------------------------------------AFFICHER QUESTION----------------------------------------------------------------------*/

char* afficher_question (int numero_question);

/*---------------------------------------------TROUVE---------------------------------------------------------------------------------*/

int depasserseuil(POPULATION *pop, int seuil);

/*---------------------------------------------SUPPRIMER PERSO------------------------------------------------------------------------*/

void suppression_une_personne(char son_nom[30],POPULATION *pop);

/*---------------------------------------------SUPPRIMER QUESTION------------------------------------------------------------------------*/

int calcule_nb_question();
int* remplir_tab_quest(int n);
void quest_reste(int *tab_quest,int question_posee,int n);

/*---------------------------------------------AJOUTER REPONSE------------------------------------------------------------------------*/
void ajoute_zero(int reponse);
void ajout_perso(int *tab, int nombre_question);
int ajout_question();

/*--------------------------------------------- INTERFACE GRAPHIQUE--------------------------------------------------------------------*/
void reponse_question(GtkWidget *widget, gpointer data);
void perso_bon(GtkWidget *widget, gpointer data);
void perso_mauvais(GtkWidget *widget, gpointer data);

/*-----------------------------------------------AUTRES---------------------------------------------------------------------------*/
void jeu();


     POPULATION *pop;



#endif
