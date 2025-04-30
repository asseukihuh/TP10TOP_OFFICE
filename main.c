////////////////////////// TP10

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "prod.h"

int lireProchaineCommande() //pour lire l'int contenu dans nextFact
{
FILE *f;
int N;
f=fopen("nextFact","r");
fread(&N,sizeof(int),1,f);
fclose(f);
//printf("\n--->lu N=%d",N);
return N;
}

void convertirNenChaine4(int N,char *N4) //convertit l'int N en une chaine de 4 caracteres
{ // si N=1234 alors N4 sera égal à "1234"
int m,c,d,u;
char cm,cc,cd,cu;
m=N/1000;cm=48+m;
N%=1000;
c=N/100;cc=48+c;
N%=100;
d=N/10;cd=48+d;
u=N%10;
cu=48+u;
N4[0]=cm;N4[1]=cc;N4[2]=cd;N4[3]=cu;N4[4]='\0';
}


double rechercheproduit(int*pRef,char*lib){
	FILE*fp=NULL;
	int laref;
	double prix;
	
	fp=fopen("produits.txt","r");
	if (fp!=NULL)
	{
		do
		{
			fscanf(fp,"%d" "%s" "%lf",&laref,lib,&prix);
			if (laref==*pRef) //revoir
			{
				fclose(fp);
				return prix;
			}
			
		} while (!feof(fp));
		
	}
	fclose(fp);
	return prix;
	

}


void lireCommande(FILE *fic, char*NNNN){
	//FILE* fact=fopen("nextFact","w"); // pas trop capte faut creer le fichier facture 
	FILE* fact=NULL;
	
	char NOM[100], libelle[100], chemin[100];
	int ref, qt, stock, qt_final;
	double pu, soustotal, total;
	fscanf(fic,"%s",NOM);
	strcpy(chemin,"./factures/facture");
	strcat(chemin,NNNN);
	strcat(chemin,".txt");
	fact=fopen(chemin,"w");
	fprintf(fact,"facture de : %s",NOM);

	do
	{
		fscanf(fic,"%d %d",&ref,&qt); //pas trop compris atoi 
		
		pu = rechercheproduit(&ref,libelle); 
		soustotal=qt*pu;
		
		fprintf(fact,"\n%d %s %lf = %lf",qt,libelle,pu,soustotal); //faire un truc sous total
			//ecrire nouvelle ligne dans facture 0001.txt
			//fprintf(fact,"%d %s %f %f",qt,libelle,pu,qt*pu); //definir le fichier fact fact.txt
			total+=soustotal;
	} while (!feof(fic));
	fprintf(fact,"\n total: %lf:",total);
	fclose(fact);
};


void lireLesCommandes() //cette fonction ouvre tous les fichiers commandeXXX.txt avec XXXX démarrant à N
{
FILE *ficCommande=NULL;
int FINI=0;
int N = lireProchaineCommande(); //numero de la premiere commande qui sera lue et traitee
char NNNN[5];
char nomCommande[29];

do //ce do while prend fin dès que fichier commandeXXXX.txt est absent 
	{
	strcpy(nomCommande,"./commandes/commande");
	convertirNenChaine4(N,NNNN); 
	//printf("\n==>%s<==",NNNN);
	ficCommande=NULL;
	strcat(nomCommande,NNNN);
	strcat(nomCommande,".txt");
	
	//printf("\n traitement de  %s",nomCommande);
	
	ficCommande=fopen(nomCommande,"rt");
	if (ficCommande!=NULL)
		{ // le fichier commandeNNNN.txt existe
			printf("\n fichier %s present",nomCommande); // nomCommande on a changé ca 
			lireCommande(ficCommande, NNNN); // à vous de coder cette fonction lors de ce TP9
			fclose(ficCommande);
		}
	else
		{
			printf("\n toutes les commandes presentes ont ete traitees.");
			FILE *f=fopen("nextFact","w"); // on va ecrire la valeur de N dans enxtFact 
			// pour 
			fwrite(&N,1,sizeof(int),f);
			fclose(f);
			FINI=1;			
		}

	N++;
	}while(FINI==0);		

}





int main()
{
	//creation d un fichier d'un seul int nommé nextFact et contenant l'int 1
	// code à utiliser pour réinitialiser nextFact à 1 si besoin au cours du TP 
	
	/*
	FILE *f;int N=1;
	f=fopen("nextFact","w");
	fwrite(&N,1,sizeof(int),f);
	fclose(f);
	*/
	//on a decommente ca ca permet de recreer tt 

	//PARTIE 1 du TP : sans Gestion de stock
	lireLesCommandes(); //lecture de tous les fichiers commandeXXX.txt (fichiers non traités jusqu'ici)	
	

	//PARTIE 2 du TP : avec Gestion de stock
	//copiez coller votre travail précédent puis modifiez le  
	//lireLesCommandes2(); 	

	return 0;
}