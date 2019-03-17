#include "header.h"

/*---------------------------------------------LECTURE POPULATION-------------------------------------------------------------------*/

void init_population(POPULATION *ptr_pop)
{
	ptr_pop = (POPULATION*) malloc(sizeof(POPULATION));
    ptr_pop->tete = NULL;
    ptr_pop->nb_perso = 0;
}

PERSO *creer_perso(int nb_q)
{
	PERSO *p1;
    p1 = (PERSO*) malloc(sizeof(PERSO));
    int i;

	for(i=0;i<nb_q;i++){
		p1->reponses[i]=0;
	}
    p1->score = 0;
    p1->perso_suiv = NULL;
	return p1;
}

void ajouter_debut_liste(POPULATION *ptr_pop, PERSO *ptr_p)
{
    ptr_p->perso_suiv = ptr_pop->tete;
	ptr_pop->tete = ptr_p;
	ptr_pop->nb_perso ++;
}

void afficher_perso(PERSO p, int nb_q)
{
	int i;
	printf("\nNom :\t%s \nScore :\t%d\nReponses :", p.nom,p.score);
	for(i=0;i<nb_q;i++){
		printf("%d ",p.reponses[i]);
	}
	printf("\n----------");
}

void lecture_population(POPULATION *pop, int nb_q)
{
	FILE *flux;
	flux = fopen("population.txt","r");
	char prenom[40],nom[40];
	int c,n=0,i=0;


	if(flux!=NULL){
		do{
			PERSO *p;
			p = creer_perso(nb_q);
			fscanf(flux,"%s %s",nom,prenom);
			strcat(nom," ");	/*concatenation*/
			strcat(nom,prenom);
			strcpy(p->nom,nom);	/*copie du nom*/

			fscanf(flux," %d",&c);
			i=0;
			while(!(c==-1)){
				p->reponses[i] = c;
				fscanf(flux," %d",&c);
				i++;
			}
			n++;
			ajouter_debut_liste(pop,p);
		}while(n<NB_perso);
		fclose(flux);
	}
}

void afficher_population(POPULATION pop, int nb_q)
{
    PERSO *ptr_cour;

	for(ptr_cour = pop.tete;ptr_cour!=NULL;ptr_cour = ptr_cour->perso_suiv){
            afficher_perso(*ptr_cour, nb_q);
	}
}

/*---------------------------------------------SCORE---------------------------------------------------------------------------------*/

int score_perso(int rep_donnee,int rep_atendue,int score)
{
	if (rep_donnee==rep_atendue)
	{
	score=score+3;
	}
	else if (rep_donnee==rep_atendue-1 || rep_donnee==rep_atendue+1)
		{
        score=score+1;
        }
		else if (rep_donnee==rep_atendue-2 || rep_donnee==rep_atendue+2)
                {
                score=score-1;
                }
                else if (rep_donnee==rep_atendue-3 || rep_donnee==rep_atendue+3)
                      {
                      score=score-2;
                       }
                     else if (rep_donnee==rep_atendue-4 || rep_donnee==rep_atendue+4)
                           {
                        score=score-3;
                           }
 return score;
}

void calcul_score_perso(int donnee, POPULATION *P, int numeroquestion, int nb_q) /*calcul le nouveau score de chaque personnage*/
{
    PERSO *new;
    new = creer_perso(nb_q);
    new = P->tete;
    int rep_attend; /*réponse attendue par l'ordinateur*/
    int score,i;/*score précédent de chaque personnage*/
    for(i=0; i<P->nb_perso; i++){
        rep_attend=new->reponses[numeroquestion];
        score=new->score;
        new->score=score_perso(donnee,rep_attend,score);
        new=new->perso_suiv;
    }
}

/*---------------------------------------------NOTE----------------------------------------------------------------------------------*/

void creation_T_notes(int* notes, int nb_q, POPULATION *pop, int *tab)
{
    int i;
    for(i=0; i<nb_q; i++){
        if(tab[i]==-1){
            notes[i]=-1;
        } else {
        notes[tab[i]]=note(pop,tab[i]);
        printf("Q : %d note : %d\n", tab[i]+1, note(pop,tab[i]));
       }
    }
}

int questionaposer(int *tab, int questres){ /*fonction qui renvoie la numéro de la question qui a le plus grand score et donc le numéro de la question à poser*/
    int max=tab[0];/*On initialise la case 1 du tableau (qui contient le score de la question 1) a max) */
    int i;
    int position=0; /*position de la case qui a le plus grand score: correspond au numéro de la question à poser*/
    for(i=1; i<questres; i++){
        if(tab[i]>max){
            max=tab[i];
            position=i;
        }
    }
    return position;
}

int note(POPULATION *pop, int num_question)
{
    int effectif[6];
    int i, j;
    PERSO *new;
    new=pop->tete;
    int note; /*contient la note de la question*/
    note=1;

    for(i=0; i<6; i++){
        effectif[i]=0;
    }

    for(i=0; i<pop->nb_perso; i++){
        for(j=0; j<6; j++){
            if(new->reponses[num_question]==j){
                effectif[j]++;
            }
        }
        new=new->perso_suiv;
    }

    for(i=1; i<6; i++){
        note=note * (effectif[i] + 1);
    }

    return note;

}

/*---------------------------------------------SUPPRIMER SCORE------------------------------------------------------------------------*/

void supprime(POPULATION *pop, int score_min)
{
    /* définition de la fonction : fonction qui supprime les personnages de la liste dont le score est STRICTEMENT INFERIEUR au seuil désiré  score_min  */
    PERSO *ptr_cur;
    int nouveau_cardinal;
    nouveau_cardinal=pop->nb_perso;
    while(pop->tete->score < score_min )  /* On démare le parcours de la liste au premier personnage ayant un score suffisant */
    {
        if(pop->tete->perso_suiv != NULL){
            pop->tete=pop->tete->perso_suiv;
            nouveau_cardinal--;
        }
        else { /* SIon a que des personnages aux scores inferieur au seuil désiré */
         /* Appel de la fonction pour créer un nouveau personnage */
         free(pop->tete);
         return;
        }
    }
    ptr_cur=pop->tete;  /* Début du parcours */
    while (ptr_cur->perso_suiv != NULL)
    {
        if (ptr_cur->perso_suiv->score < score_min)  /* Si le personnage perso_suiv à un score insufisant alors on le saute */
        {

            nouveau_cardinal--;
            ptr_cur->perso_suiv=ptr_cur->perso_suiv->perso_suiv; /* On saute ptr_cur->perso_suiv */
        }

        else
        {
            ptr_cur=ptr_cur->perso_suiv;  /* Si le score est sufisant, alors on incrémante notre position dans la liste */
        }
    }
    if (ptr_cur->score < score_min)  /* Gestion du dernier maillon de la chaine, si son score est insufisant alors on le supprime */
    {
        free(ptr_cur);
        nouveau_cardinal--;
    }
    pop->nb_perso=nouveau_cardinal;
}

/*---------------------------------------------AFFICHER QUESTION----------------------------------------------------------------------*/

char* afficher_question (int numero_question)
/* definition de la fonction : lecture lit la numero_question ligne dans le fichier question.tkt.  Il retourne une chaine de caractère. Il est possible de décommenter la ligne (**********) pour effectuer un printf à l'écran*/
{
   static char question_a_afficher[128]; /* Sortie de la fonction contenant la question à afficher */


   static const char filename[] = "questions.txt";  /* source à lire */
   FILE *file = fopen ( filename, "r" );
         char line [ 128 ]; /* taille maximale de la question */

   if ( file != NULL )
   {

      while ( (fgets ( line, sizeof line, file ) != NULL) &&  (numero_question>1 )) /* Lire une ligne */
      {
          numero_question--; /* on décrémente jusqu'à la ligne désirée */

      }
      strcpy(question_a_afficher,line);
      fclose ( file );
	  /*printf("Ligne : %s", line);*/  /*  (**********) lecture d'une ligne à décommenter si besoin   */
   }
   else
   {
      perror ( filename ); /* si le fichier ne s'ouvre pas */
   }
   return question_a_afficher;
}

/*---------------------------------------------TROUVE---------------------------------------------------------------------------------*/

int depasserseuil(POPULATION *pop, int seuil){
    
    PERSO *P;
    P = creer_perso(nb_q);
    P=pop->tete;
    int a=0;
    PERSO *P_max;
    P_max = creer_perso(nb_q);
    P_max = P;
     
    char ch[50]="Le personnage est ";
    GtkWidget *window;
	GtkWidget *box1,*box2;
	
	GtkWidget *bouton1,*bouton2;
    
	window=gtk_window_new(GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_default_size(GTK_WINDOW(window),300,200);
	gtk_window_set_title(GTK_WINDOW(window),"Le Devin");

	box1=gtk_box_new(GTK_ORIENTATION_VERTICAL,0);
	box2=gtk_box_new(GTK_ORIENTATION_HORIZONTAL,0);
	gtk_container_add(GTK_CONTAINER(window),box1);
	
	texte_fin=gtk_label_new(ch);		
	gtk_box_pack_start(GTK_BOX(box1),texte_fin,TRUE,TRUE,0);
	gtk_container_add(GTK_CONTAINER(box1),box2);
	
	bouton1=gtk_button_new_with_label("Oui");
	bouton2=gtk_button_new_with_label("Non");
	
	gtk_box_pack_start(GTK_BOX(box2),bouton1,TRUE,TRUE,0);
	gtk_box_pack_start(GTK_BOX(box2),bouton2,TRUE,TRUE,0);
	
	if(cpt_q >15  || pop->nb_perso < 2){
		if(pop->nb_perso>1){
			while(P != NULL){
				if(P->score>=P_max->score){
						P_max = P;
				}
				P=P->perso_suiv;
			}
			strcat(ch,P_max->nom);
			gtk_label_set_text(GTK_LABEL(texte_fin),ch);
			gtk_widget_show_all(window);
		}else{
			strcat(ch,pop->tete->nom);
			gtk_label_set_text(GTK_LABEL(texte_fin),ch);
			gtk_widget_show_all(window);
		}
	}
    
    g_signal_connect(G_OBJECT(bouton1), "clicked", G_CALLBACK( perso_bon ), NULL);
	g_signal_connect(G_OBJECT(bouton2), "clicked", G_CALLBACK( perso_mauvais ), NULL);
   
    return a;
}

/*---------------------------------------------SUPPRIMER PERSO------------------------------------------------------------------------*/
void suppression_une_personne(char son_nom[30],POPULATION *pop)
/* Definition de la fonction : fonction qui prend en compte une chaine de caractère
"son_nom" de 30 caractère max et une population. Cette fonction supprime le la population "pop"
la structure donc le nom correspond à "son_nom[30]". */
{
  PERSO *ptr_pred;
  PERSO *ptr_cur;

  pop->nb_perso--; /* On décremente le nombre de personne dans la liste */
  ptr_cur=pop->tete;
  ptr_pred=ptr_cur;
  if(strcmp(ptr_cur->nom,son_nom)==0) /* Si la personne à supprimer se situe en tête de liste */
  {
    pop->tete=ptr_cur->perso_suiv; /* La tete pointe vers la deuxième personne */
    free(ptr_cur);
  }
  else
  {
    while(strcmp(ptr_cur->nom,son_nom)!=0) /* Parcours de la liste */
    {
      ptr_pred=ptr_cur;
      ptr_cur=ptr_cur->perso_suiv;
    }
    ptr_pred->perso_suiv=ptr_cur->perso_suiv;
    free(ptr_cur);
  }
}

/*---------------------------------------------SUPPRIMER QUESTION------------------------------------------------------------------------*/

int calcule_nb_question()
{
   FILE *question;
   int nb_lignes=0;
   int car_lu;

   question=fopen ("questions.txt","r");
   if(question==NULL)
    {
     printf("ouverture impossible de fichier question.txt\n");
     return 1;
    }
   else
    {
        while((car_lu=fgetc(question))!=EOF)
        {
                if(car_lu=='\n')
                {
                nb_lignes++;
                }

        }
    }
   fclose(question);

   return nb_lignes;
}

/* fontion qui remplit un tableau avec les questions  */
int* remplir_tab_quest(int n)
{
   int i;
   int *tab_quest;
   tab_quest=(int*)malloc(n*sizeof(int));
   for(i=0;i<n;i++)
   {

   tab_quest[i]=i;
   }
   return tab_quest;
}



/* fonction qui supprime les questions déja poseés*/
void quest_reste(int *tab_quest,int question_posee,int n)
{

int j;

    for(j=0; j<n; j++){
        if((question_posee)==tab_quest[j]){
        tab_quest[j]=-1;
		}
    }
}


/* Def fonction : fonction qui ajoute un 0 avant le -1 en fin de ligne sur chaque personnage du fichier population.txt */
/* Ne fonctionne que si le nom ne comporte pas de "1"*/
void ajoute_zero(int reponse )
{ 
    FILE *old,*new;
    old=fopen("population.txt","r+");
    new=fopen("population2.txt","w+");

    char c='a';
    c=fgetc(old);
    fputc(c,new);
    while(!feof(old))
    {
      if (c=='-')
      {
        fseek (new, -1, SEEK_CUR);
        fputc('0',new);
        fputc(' ',new);
        fputc('-',new);
        /*fputc('1',old);*/

        /*fputc('\n',old);*/
      }
      c=fgetc(old);
      if (c!=EOF){fputc(c,new);}
      /*fseek (old, -1, SEEK_CUR);
      fputc('0',old);
      fputc(' ',old);
      fputc('-',old);
      fputc(reponse,old);
      fputc('\n',old);*/

    }
    remove("population.txt");
    fclose(old);
    fclose(new);
    rename("population2.txt", "population.txt");

}

void ajout_perso(int *tab, int numero_question)
{
	/*fonction qui ajoute un personnage en bout de fichier, et les réponses aux questions associées /!\ ajoute -1 à la fin de la ligne*/
	
	char nom[30];
	
	
	printf("Je ne connais ce personnage. Peux-tu me donner son nom ?\n");
	getchar();
    scanf("%[^\n]",nom);

	
	
	FILE *f;

	f=fopen("population.txt","a");
	
	fprintf(f,"%s ",nom);
	
	int i;
	
	for(i=0;i<numero_question;i++)
	{
		fprintf(f,"%d ",tab[i]);
		
	}
	
	int c=-1;
	fprintf(f,"%d\n",c);
	
	fclose(f);
	
}

int ajout_question(){
	FILE *flux;
	flux = fopen("questions.txt","r+");
	char q[50];
    
	int r;
	
	printf("Saisir question :\n");
    getchar(); /* permet de vider le buffer */
	scanf("%[^\n]",q);
	fseek(flux,0,SEEK_END);
	
	fputs(q,flux);
    fputs("\n",flux);
	
	printf("Saisir reponse :\n");
	scanf("%d",&r);
	
	fclose(flux);
	
	return r;
}

/*---------------------------------------------JEU------------------------------------------------------------------------------*/

void jeu()
{
	tabnewperso[num_q]=reponse;
    printf("\nCalcul score personnage\n");
    calcul_score_perso(reponse, pop, num_q,nb_q);
    afficher_population(*pop,nb_q);
        
    quest_reste(T_q,num_q,nb_q);
        
    if(cpt_q>4){
        supprime(pop,2);
    }
        
	gagner=depasserseuil(pop, 20);
						
	printf("\n%d\n",reponse);

	printf("\n------------------------QUESTION : %d ------------------------\n",cpt_q+1);

	printf("Notes questions :\n");

    creation_T_notes(T_notes,NB_questions,pop,T_q); /*création d'un tableau comprenant les notes de toutes les questions*/
				
	int i;
	for(i=0;i<NB_questions;i++){
		printf("ok%d\n",T_notes[i]);
	}

    num_q=questionaposer(T_notes, nb_q);
    printf("Question a poser :\t%d\n",num_q+1);

    printf("Affichage question :\t");
    q = afficher_question(num_q+1);
    gtk_label_set_text(GTK_LABEL(texte),q);
        
    printf("%s",q);
        
        
    cpt_q++;
    gtk_progress_bar_set_fraction (GTK_PROGRESS_BAR(bar),cpt_q/20.0);
    gtk_progress_bar_set_text (GTK_PROGRESS_BAR(bar),NULL);
        
    nb_q --;    
}

