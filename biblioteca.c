#include "biblioteca.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Retea* Network_Creation(char *nume_fisier)
	{
		FILE *f;
		if((f=fopen(nume_fisier,"r"))==0)
		{
			printf("Nu s-a putut deschide fisierul");
			exit(1);
		}
		int i,j,k,x,y;
		int *nr_routere_aux=malloc(sizeof(int));
		fscanf(f,"%d",nr_routere_aux);
		Retea *network=malloc(sizeof(Retea));
		network->Nr_routere=*nr_routere_aux;
		free(nr_routere_aux);
		network->R=malloc(sizeof(Router)*(network->Nr_routere));//alocare memorie pentru routere
		for(i=0;i<network->Nr_routere;i++)
		{
			fscanf(f,"%ms",&network->R[i].nume_router);
			fscanf(f,"%ms",&network->R[i].ip_router);
			fscanf(f,"%d",&network->R[i].connected);
			network->R[i].nr_identificare_router=i;
			network->R[i].pc=malloc(sizeof(Pc)*network->R[i].connected);//alocare memorie in functie de numarul de PC-uri conectate
			for(j=0;j<network->R[i].connected;j++)//alocare memorie fiecarui PC + citire
			{
				fscanf(f,"%ms",&network->R[i].pc[j].nume_pc);
				fscanf(f,"%ms",&network->R[i].pc[j].ip_pc);
				fscanf(f,"%d",&network->R[i].pc[j].stare);
			}

		}
		
		fscanf(f,"%d",&network->nr_conexiuni_routere);//citire numarul de conexiuni intre routere
		network->Conexiune=malloc(sizeof(conexiune)*network->nr_conexiuni_routere);//aloc spatiu pentru conexiuni start-finish intre routere si distanta
		for(i=0;i<network->nr_conexiuni_routere;i++)
			{
				fscanf(f,"%ms ",&network->Conexiune[i].nume_router_start);
				fscanf(f,"%ms ",&network->Conexiune[i].nume_router_finish);
				fscanf(f,"%d ",&network->Conexiune[i].distanta);

			}

		fscanf(f,"%d",&network->Nr_operatii);//citire numarul de operatii cerute
		char *aux=malloc(sizeof(char)*6);//variabila auxiliara pentru a citi din fisier ce fel de operatie este
		int *v=malloc(sizeof(int)*8);//creare vector pentru a stoca numarul de aparitii a fiecarei sarcini posibile
		
		network->vector_de_ordine=calloc(network->Nr_operatii,sizeof(int));//vectorul in care se stocheaza ordinea operatiilor
	    network->nr_ping=0;
	    network->nr_sipn=0;  //initializare cu 0 numarul de aparitie al fiecarei operatii posibile
	    network->nr_si=0;
	    network->nr_trace=0;
	    network->nr_up=0;
	    network->nr_lc=0;
	    network->nr_broke=0;
	    network->nr_add=0;
	    

	    for(i=0;i<8;i++)
	    {
	    	v[i]=1;//initializare vector
	    }
		for(i=0;i<network->Nr_operatii;i++) //Citesc numele sarcinii intr-un aux apoi compar cu numele sarcii,iar in functie de ce sarcina apare stochez informatiile 
		 {
			fscanf(f,"%ms",&aux);
		
			if(strcmp(aux,"ping")==0)
			{
				network->ping=realloc(network->ping,sizeof(Ping)*v[0]);
				fscanf(f,"%ms ",&network->ping[v[0]-1].ping_1);//citesc ping 1
				fscanf(f,"%ms ",&network->ping[v[0]-1].ping_2);//citesc ping 2

				network->nr_ping=v[0];//adaug la numarul a apritie a sarcinii "ping"
				v[0]++;//incrementez vectorul pe pozitia 0 unde se afla valorile asociate numarului de aparitie pentru "ping"
				network->vector_de_ordine[i]=0;
				
			}
			else 
				if(strcmp(aux,"sipn")==0)
					{
						network->sipn=realloc(network->sipn,sizeof(Sipn)*v[1]);
						fscanf(f,"%ms ",&network->sipn[v[1]-1].sipn_1);
						network->nr_sipn=v[1];						
						v[1]++;
						network->vector_de_ordine[i]=1;
						

					}
					else
						if(strcmp(aux,"si")==0)
						{
							network->si=realloc(network->si,sizeof(Si)*v[2]);
							fscanf(f,"%ms ",&network->si[v[2]-1].si_1);
							network->nr_si=v[2];
							v[2]++;
							network->vector_de_ordine[i]=2;
							
						}
					else 
						if(strcmp(aux,"trace")==0)
						{
							network->trace=realloc(network->trace,sizeof(Trace)*v[3]);
							fscanf(f,"%ms ",&network->trace[v[3]-1].trace_1);
							fscanf(f,"%ms ",&network->trace[v[3]-1].trace_2);
							network->nr_trace=v[3];
							v[3]++;

							network->vector_de_ordine[i]=3;
							
							
						}
						else
							if(strcmp(aux,"up")==0)
							{
								network->up=realloc(network->up,sizeof(Up)*v[4]);
								fscanf(f,"%ms ",&network->up[v[4]-1].up_1);
								network->nr_up=v[4];
								v[4]++;
								network->vector_de_ordine[i]=4;
								
							}
							else
								if(strcmp(aux,"lc")==0)
								{
									network->lc=realloc(network->lc,sizeof(Lc)*v[5]);
									fscanf(f,"%ms ",&network->lc[v[5]-1].Lc_1);
									fscanf(f,"%ms ",&network->lc[v[5]-1].Lc_2);
									network->nr_lc=v[5];
									v[5]++;
									network->vector_de_ordine[i]=5;
									
								}
								else
									if(strcmp(aux,"broke")==0)
									{
										network->broke=realloc(network->broke,sizeof(Broke)*v[6]);
										fscanf(f,"%ms ",&network->broke[v[6]-1].broke_1);
										network->nr_broke=v[6];
										v[6]++;
										network->vector_de_ordine[i]=6;
										
									}
								else
									if(strcmp(aux,"add")==0)
									{
										network->add=realloc(network->add,sizeof(Add)*v[7]);
										fscanf(f,"%ms ",&network->add[v[7]-1].add_1);
										fscanf(f,"%ms ",&network->add[v[7]-1].add_2);
										fscanf(f,"%d ",&network->add[v[7]-1].cost_drum);

										network->nr_add=v[7];
										v[7]++;
										network->vector_de_ordine[i]=7;
										
									}



				}
				

				
		
		free(v);
		free(aux);
		fclose(f);

        network->a=malloc(sizeof(int *)*network->Nr_routere);//alocare memorie pentru matricea de adiacenta
        for(i=0;i<network->Nr_routere;i++)
        {
        	network->a[i]=malloc(sizeof(int)*network->Nr_routere);

        }
        for(i=0;i<network->Nr_routere;i++)
        {
        	for(j=0;j<network->Nr_routere;j++)
        	{	
        		network->a[i][j]=INF;//initializare matrice de adiacenta cu o valoare definita
        	}
        }

        for(i=0;i<network->nr_conexiuni_routere;i++)
        {
        		
        		for(j=0;j<network->Nr_routere;j++)
        		{
        				if(strcmp(network->Conexiune[i].nume_router_start,network->R[j].nume_router)==0)//comparare numele router-ului de la care incepe conexiunea cu router-ele existente pentru a gasi numarul de indentificare pe care il voi folosi in matricea de adiacenta
        					{
        						x=network->R[j].nr_identificare_router;//coordonata x care reprezinta linia in matrice
        					}
        		}
        		for (k=0;k<network->Nr_routere;k++)
        		{
        				if(strcmp(network->Conexiune[i].nume_router_finish,network->R[k].nume_router)==0)//comparare numele router-ului de la destinatia finala  cu router-ele existente pentru a gasi numarul de indentificare pe care il voi folosi in matricea de adiacenta
        					
        				{
        					  y=network->R[k].nr_identificare_router;//coordonata y care reprezinta coloana in matrice
        				}
        		}


        		network->a[x][y]=network->Conexiune[i].distanta;//stochez distanta dintre routere in matricea de adiacenta
        		network->a[y][x]=network->Conexiune[i].distanta;
        }

	
		return network;

	
}
void spin_verification(Retea *network,char *nume_fisier,int i)
{  FILE *f;
	if((f=fopen(nume_fisier,"a+"))==0)
	{
		printf("Nu s-a putut deschide fisierul\n");
		exit(1);
	}
	int j,k,x;
	
	
			for(j=0;j<network->Nr_routere;j++)
			{
				if(strcmp(network->sipn[i].sipn_1,network->R[j].ip_router)==0)
				{
					x=network->R[j].nr_identificare_router;//memorez pozitia routerului

				}
			}
			for(k=0;k<network->Nr_routere;k++)
			{
				if(network->a[x][k]!=INF)
				{
					fprintf(f,"%s ",network->R[k].ip_router);//afisez ce routere sunt conectate direct 
				}
				else
					if(network->a[k][x]!=INF)
					{
					fprintf(f,"%s ",network->R[k].ip_router);
					}
			
			}
	
	fprintf(f,"\n");
	fclose(f);
}
void si_verification(Retea *network,char *nume_fisier,int i) //afiseaza pc-urile direct conectate la un router
{	FILE *f;
	if((f=fopen(nume_fisier,"a+"))==0)
	{
		printf("Nu s-a putut deschide fisierul");
		exit(1);
	}

	int j,x;
	for(j=0;j<network->Nr_routere;j++)//compar ip-ul stocat in si cu ip-ul router-elor 
	{
		if(strcmp(network->si[i].si_1,network->R[j].ip_router)==0)
		{
			x=j;//stochez pozitia router-ului
		}
	}
	for(j=0;j<network->R[x].connected;j++)
	{
		if(network->R[x].pc[j].stare==1) //verific starea pc-urilor conectate la router
			fprintf(f,"%s ",network->R[x].pc[j].ip_pc); //scriu in date.out ip-uli pc-ului conectat
	}
	
	fprintf(f,"\n");

	fclose(f);
}

void up_pc(Retea **network,int i)
{
	

	int j,k;
    for(j=0;j<(*network)->Nr_routere;j++)//caut router-ul la care este conectat pc-ul
    {
    	for(k=0;k<(*network)->R[j].connected;k++)//caut care pc corespunde ip-ului cautat
    	{
    		if(strcmp((*network)->up[i].up_1,(*network)->R[j].pc[k].ip_pc)==0)//compar ip-urile
    		{
    			
    			(*network)->R[j].pc[k].stare=1;//deschid pc-ul
    		 	return;

    		}
    	}
    }

	

}
void broke_pc(Retea **network,int i)
{
	

	int j,k;
    for(j=0;j<(*network)->Nr_routere;j++)//caut router-ul la care este conectat pc-ul
    {
    	for(k=0;k<(*network)->R[j].connected;k++)//caut care pc corespunde ip-ului cautat
    	{
    		if(strcmp((*network)->broke[i].broke_1,(*network)->R[j].pc[k].ip_pc)==0)//compar ip-urile
    		{
    			
    			(*network)->R[j].pc[k].stare=0;//inchid pc-ul


    		 	return;

    		}
    	}
    }

	

}
void lc_operation(Retea **network,int i)
{
	int j,x,y;
	for(j=0;j<(*network)->Nr_routere;j++)//caut routerele dorite
	{
		if(strcmp((*network)->R[j].ip_router,(*network)->lc[i].Lc_1)==0) 
		{
			x=j;//memorez pozitia router-ului 1
			
		}
		else
			if(strcmp((*network)->R[j].ip_router,(*network)->lc[i].Lc_2)==0)
			{
				y=j;//memorez pozitia router-ului 2
			}

	}
	(*network)->a[x][y]=INF;//rup legatura intre routere
	(*network)->a[y][x]=INF;

	
	

}
void add_operation(Retea **network,int i)
{
	int j,x,y;
	for(j=0;j<(*network)->Nr_routere;j++)//caut routerele dorite
	{
		if(strcmp((*network)->R[j].ip_router,(*network)->add[i].add_1)==0)
		{
			x=j;//memorez pozitia router-ului 1
		}
		else
			if(strcmp((*network)->R[j].ip_router,(*network)->add[i].add_2)==0)
			{
				y=j;//memorez pozitia router-ului 2
			}

	}
	(*network)->a[x][y]=(*network)->add[i].cost_drum;//fac o legatura intre routere si adaug costul de drum
	(*network)->a[y][x]=(*network)->add[i].cost_drum;
	
	


}
void ping(Retea *network,char *nume_fisier,int i)
{
	
	FILE *f;
	if((f=fopen(nume_fisier,"a+"))==0)
	{
		printf("Nu s-a putut deschide fisierul");
		exit(1);
	}

	int z,j,k,x,y,nr_pc1,nr_pc2;
	int **v;
	v=malloc(sizeof(int *)*network->Nr_routere);//creez o matrice temporara in care stochez valorile din matricea de adiacenta
	for(j=0;j<network->Nr_routere;j++)
		v[j]=malloc(sizeof(int)*network->Nr_routere);
	for(j=0;j<network->Nr_routere;j++)
	{
		for(k=0;k<network->Nr_routere;k++)
			v[j][k]=network->a[j][k];//copiez valorile din matricea de adiacenta in matricea temporara
	}
	
	for(j=0;j<network->Nr_routere;j++)//caut nr de identificare al routerelor cautate
	{	for(k=0;k<network->R[j].connected;k++)//merg cu k pana la numarul de pc-uri conectate
		{if(strcmp(network->R[j].pc[k].ip_pc,network->ping[i].ping_1)==0)
			{x=j;//primul router
			 nr_pc1=k;//memorez pozitia pc-ului cautat
			}
		else 
			if(strcmp(network->R[j].pc[k].ip_pc,network->ping[i].ping_2)==0)
				{y=j;//al doilea router
				 nr_pc2=k;//memorez pozitia pc-ului cautat
				}
		}
	}
	for(z=0;z<network->Nr_routere;z++)//algoritm Floyd Warshall
	{
		for(j=0;j<network->Nr_routere;j++)
		{
			for(k=0;k<network->Nr_routere;k++)
			{
				if(v[j][z]+v[z][k]<v[j][k])
					v[j][k]=v[j][z]+v[z][k];
			}
		}
	}
	int verif=0;
	if(v[x][y]!=INF)//daca exista drum de la x la y
	{
		if(network->R[x].pc[nr_pc1].stare==1)//verific starea pc-ului 1
			verif++;//incrementez
		if(network->R[y].pc[nr_pc2].stare==1)//verific starea pc-ului 2
			verif++;//incrementez


		if(verif==2) fprintf(f,"OK\n"); //daca verif=2 inseamna ca ambele pc-uri sunt deschise deci exista o legatura intre ele
		else
			fprintf(f,"NO\n");//in caz contrar unul din pc-uri este inchis sau amandoua sunt inchise
	}
	else
		fprintf(f,"NO\n");//nu exista drum intre cele doua pc-uri
	
	free(v);//eliberez vectorul temporar
	fclose(f);

}
void trace_operation(Retea *network,char *nume_fisier,int i)
{
	FILE *f;
	if((f=fopen(nume_fisier,"a+"))==0)
	{
		printf("Nu s-a putut deschide fisierul");
		exit(1);
	}

	int **v;//matrice de cost
	int *dist=malloc(sizeof(int)*network->Nr_routere);//vector de distante
	int *predecesor=malloc(sizeof(int)*network->Nr_routere);//predecesorul fiecarui nod
	int *visited=malloc(sizeof(int)*network->Nr_routere);//vector al elementelor vizitate
	int next_node;//memorez pozitia predecesorului
	int min_distance=INF;//memorez distanta minima
	int j,k,z,x,y;
//--------------------------------------------Alocare matrice de cost------------------------------------------------------------------------------------------------------
	v=malloc(sizeof(int*)*network->Nr_routere);
	for (j=0;j<network->Nr_routere;j++)
	{
		v[j]=malloc(sizeof(int)*network->Nr_routere);
	}
//-------------------------------------------Initializare matrice de cost--------------------------------------------------------------------------------------------------
	for(j=0;j<network->Nr_routere;j++)
	{
		for(k=0;k<network->Nr_routere;k++)
		{
			v[j][k]=network->a[j][k];
		}
	}
//----------------Cautarea pozitiilor routerelor la care sunt conectate pc-urile cautate-----------------------------------------------------------------------------------
	for(j=0;j<network->Nr_routere;j++)
	{
		for(k=0;k<network->R[j].connected;k++)
		{if(strcmp(network->R[j].pc[k].ip_pc,network->trace[i].trace_1)==0)
			{
				
				x=j;//router start
			}
		
		}
		for(k=0;k<network->R[j].connected;k++)
		{if(strcmp(network->R[j].pc[k].ip_pc,network->trace[i].trace_2)==0)
			{
				
				y=j;//router finish
			}
		
		}

	}
//------------------------------------------------Drum de cost minim---------------------------------------------------------------------------------------------------------
	for(j=0;j<network->Nr_routere;j++)
	{
		dist[j]=v[x][j];//Initialize vectorul ce contine costul de drum de la pozitia de start x pana la restul nodurilor.Daca nu exista va aparea INF
		predecesor[j]=x;//Initializez toti predecesorii cu valoarea lui x
		visited[j]=0;//Initializez vectorul de vizite cu 0; 1-pentru vizitat si 0-pentru nevizitat
	}
	dist[x]=0;//Distanta nodului de start este 0 pentru ca deja sunt acolo
	visited[x]=1;//Marchez ca vizitat nodul de start
	for(z=0;z<network->Nr_routere;z++)
	{	min_distance=INF;//Initializez distanta minima cu INF
		for(j=0;j<network->Nr_routere;j++)
		{
			if(dist[j]<min_distance&&visited[j]==0)//Caut distanta minima din vectorul de distante curente si verifica daca nodul gasit ca find minim nu e vizitat
			{
				min_distance=dist[j];//actualizez minimul
				next_node=j;//memorez predecesorul

			}

		}
	
		visited[next_node]=1;//marchez nodul "minim" ca find vizitat
		for (j=0;j<network->Nr_routere;j++)
		{
				if(visited[j]==0)
				{
					if(min_distance+v[next_node][j]<dist[j]&&v[next_node][j]!=INF)//daca distanta de la sursa la nodul curent este mai mica decat cea inregistrata in vectorul distanta actualizez distanta
					{
						dist[j]=min_distance+v[next_node][j];
						predecesor[j]=next_node;//pun in lista predecesorilor predecesorul nodului j
					}
				}
		}
	}

//---------------------------------------------------------Afisarea drumului--------------------------------------------------------------------------------------------------
	char **ip;//memorez ip-urile de la trece route in ordine inversa
	ip=malloc(sizeof(char*)*strlen(network->R[0].ip_router));
	for(j=0;j<network->Nr_routere;j++)
	{
		ip[j]=malloc(sizeof(char)*strlen(network->R[0].ip_router));
	}
	j=y;//setez j-ul pe pozitia y ,adica setez j-ul la destinatie pentru a putea merge pe predecesori
	k=network->Nr_routere-1;//setez k pe ultima pozitie pentru a putea pune valorile in ordine inversa din moment ce merg pe predecesori
	
	strcpy(ip[k],network->R[j].ip_router);//copiez primul ip din trace route
	k--; //decrementez k
	
	do{		
		    j=predecesor[j];//il setez pe j sa devina predecesorul sau 
		    strcpy(ip[k],network->R[j].ip_router);//copiez ip-ul
		    k--;//decrementez k si repet
			

	}while(j!=x);//cat timp j nu a ajuns pe pozitia de inceput repet
	
	for(j=k+1;j<network->Nr_routere;j++)
	    fprintf(f,"%s ",ip[j]);
	
	fprintf(f,"\n");

	fclose(f);
}
	
void execution(Retea *network,char *nume_fisier)
{	
	FILE *f;
	if((f=fopen(nume_fisier,"w"))==0)
	{
		printf("Nu s-a putut deschide fisierul");
		exit(1);
	}
	fclose(f);

	int i;
	int *v=malloc(sizeof(int)*8);//vector ce retine a cata operatie de un anumit tip va fi executata;De exemplu trace[0] trace[1]...
	for(i=0;i<8;i++)
	{
		v[i]=0;//initializare vector de pozitie pentru fiecare task;
	}
	printf("Nr operatie=%d   nr_trace=%d\n",network->Nr_operatii,network->nr_trace);
	for(i=0;i<network->Nr_operatii;i++)
	{

		if(network->vector_de_ordine[i]==0)
		{
			if(v[0]<network->nr_ping)
			{
				ping(network,nume_fisier,v[0]);
				v[0]++;
			}
		}
		else
			if(network->vector_de_ordine[i]==1)
			{
					if(v[1]<network->nr_sipn)
					{
						spin_verification(network,nume_fisier,v[1]);
						v[1]++;
					}
			}
			else
				if(network->vector_de_ordine[i]==2)
				{
					if(v[2]<network->nr_si)
					{
						si_verification(network,nume_fisier,v[2]);
						v[2]++;
					}
				}

				else
					if(network->vector_de_ordine[i]==3)
					{
						if(v[3]<network->nr_trace)
						{	
							trace_operation(network,nume_fisier,v[3]);
							v[3]++;
						}
					}
					else
						if(network->vector_de_ordine[i]==4)
							{
								if(v[4]<network->nr_up)
								{
									up_pc(&network,v[4]);
									v[4]++;
								}
							}

							else
								if(network->vector_de_ordine[i]==5)
									{
										if(v[5]<network->nr_lc)
										{
											lc_operation(&network,v[5]);
											v[5]++;
										}
									}
									else
										if(network->vector_de_ordine[i]==6)
											{
												if(v[6]<network->nr_broke)
												{
													broke_pc(&network,v[6]);
													v[6]++;
												}
											}
										else
										if(network->vector_de_ordine[i]==7)
											{	
												if(v[7]<network->nr_add)
												{
													add_operation(&network,v[7]);
													v[7]++;
												}
											}
										





	}
}	 	
           
            
           
         

		
    



	



