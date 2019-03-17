#include "header.h"

void reponse_question(GtkWidget *widget, gpointer data)
{
	
	if(strcmp(data,"1")==0)
	{
		reponse=1;
	}else if(strcmp(data,"2")==0)
	{
		reponse=2;
	}else if(strcmp(data,"3")==0)
	{
			reponse=3;
	}else if(strcmp(data,"4")==0)
	{
		reponse=4;
	}else if(strcmp(data,"5")==0)
	{
		reponse=5;
	}
	
	jeu();
}

void perso_bon(GtkWidget *widget, gpointer data){
	
	gtk_label_set_text(GTK_LABEL(texte_fin),"J'ai gagné !!!");
}

void perso_mauvais(GtkWidget *widget, gpointer data){
	gtk_label_set_text(GTK_LABEL(texte_fin),"Je me suis trompé...");

	ajoute_zero(1);
	tabnewperso[nb_q-1]=ajout_question();
    printf("nb_q:%d\n", nb_q);
    int m;
	for(m=0; m<nb_q; m++){
		printf("%d\n",tabnewperso[m]);
	}
    ajout_perso(tabnewperso, nb_q);
}




