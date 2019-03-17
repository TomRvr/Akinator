#include "header.h"

int main(int argc, char **argv){
	
	cpt_q = 0;	/*Compteur qui compte le nombre de questions deja posée*/
	gagner = 0;
	arret = 0;
	
	gtk_init(&argc, &argv);

	GtkWidget *window;
		
	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_default_size(GTK_WINDOW(window),300,500);
    gtk_window_set_title(GTK_WINDOW(window),"Le Devin");
    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

	GtkWidget *image;
	image = gtk_image_new_from_file ("akinator.ico");
	/*gtk_container_add(GTK_CONTAINER(window),image);*/

	GtkWidget *box;
	box=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	gtk_container_add(GTK_CONTAINER(window),box);
	
	
	gtk_box_pack_start(GTK_BOX(box),image,TRUE, TRUE,0);

/*///////////////////AFFICHAGE PREMIERE QUESTION////////////////////////////////////*/	
	
	pop = (POPULATION*) malloc(sizeof(POPULATION));
    init_population(pop);
    
    nb_q = calcule_nb_question();
    
    lecture_population(pop,nb_q);
    
    PERSO *ptr_cour;
    for(ptr_cour = pop->tete;ptr_cour!=NULL;ptr_cour = ptr_cour->perso_suiv){
            ptr_cour->score=0;
    }
	

	printf("\nPopulation de départ :\n");
    afficher_population(*pop,nb_q);

    tabnewperso=(int*)malloc((nb_q+1)*sizeof(int));
	T_notes=(int*)malloc(nb_q*sizeof(int));
	printf("%d",nb_q);

	int k;
    for(k=0; k<nb_q; k++){
        tabnewperso[k]=0;
    }

    T_q = remplir_tab_quest(nb_q);
    int m;
    for(m=0; m<nb_q; m++){
		printf("%d\n",T_q[m]);
	}
	
	printf("Notes questions :\n");

    creation_T_notes(T_notes,NB_questions,pop,T_q); /*création d'un tableau comprenant les notes de toutes les questions*/
	int i;
	for(i=0;i<NB_questions;i++){
		printf("ok%d\n",T_notes[i]);
	}

    num_q=questionaposer(T_notes, NB_questions);
    printf("Question a poser :\t%d\n",num_q+1);

    printf("Affichage question :\t");
    q = afficher_question(num_q+1);

	printf("%s",q);
	
	texte=gtk_label_new(q);

	gtk_box_pack_start(GTK_BOX(box),texte,TRUE, TRUE,0);

	bar = gtk_progress_bar_new ();
	gtk_box_pack_start(GTK_BOX(box),bar,TRUE, TRUE,0);
	gtk_progress_bar_set_show_text (GTK_PROGRESS_BAR(bar),TRUE);
	gtk_progress_bar_set_text (GTK_PROGRESS_BAR(bar), NULL);
	
	
	GtkWidget *bouton[5];
	bouton[0]=gtk_button_new_with_label("Oui");
	bouton[1]=gtk_button_new_with_label("Peut etre");
	bouton[2]=gtk_button_new_with_label("Ne sais pas");
	bouton[3]=gtk_button_new_with_label("Surement pas");
	bouton[4]=gtk_button_new_with_label("Non");
	
	char *rep1,*rep2,*rep3,*rep4,*rep5;
	
	rep1="1";
	rep2="2";
	rep3="3";
	rep4="4";
	rep5="5";

	/*fonctions de callback*/
	g_signal_connect(G_OBJECT(bouton[0]), "clicked", G_CALLBACK( reponse_question ), rep1);
	g_signal_connect(G_OBJECT(bouton[1]), "clicked", G_CALLBACK( reponse_question ), rep2);
	g_signal_connect(G_OBJECT(bouton[2]), "clicked", G_CALLBACK( reponse_question ), rep3);
	g_signal_connect(G_OBJECT(bouton[3]), "clicked", G_CALLBACK( reponse_question ), rep4);
	g_signal_connect(G_OBJECT(bouton[4]), "clicked", G_CALLBACK( reponse_question ), rep5);
	
	GtkWidget *box2;
	box2=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	gtk_container_add(GTK_CONTAINER(box),box2);

	gtk_box_pack_start(GTK_BOX(box2), bouton[0],TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(box2), bouton[1],TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(box2), bouton[2],TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(box2), bouton[3],TRUE, TRUE,0);
	gtk_box_pack_start(GTK_BOX(box2), bouton[4],TRUE, TRUE,0);

    gtk_widget_show_all(window);

    gtk_main();

    free(pop);
    
	return 0;
}
