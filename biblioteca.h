#ifndef MY_LIBRARY
#define MY_LIBRARY
#define INF 999
typedef struct Ping//verifica conexiunea intre doua pc-uri
{ 
	char *ping_1;//memoreaaaza primul ip al statiei
	char *ping_2;//memoreaza al doilea ip al statiei
 }Ping;
typedef struct Sipn//afiseaza router-ele cu legatura directa
{
	char *sipn_1;//memoreaza ip-ul router-ului cerut 
}Sipn;
typedef struct Si//afiseaza ce pc-uri sunt conectata direct la router
{
	char *si_1;//memoreaza ip-ul unui router cerut pentru a putea identifica ce statii sunt conectate la router
}Si;
typedef struct Trace//traseaza cea mai eficienta ruta de la un router la altul
{
	char *trace_1;//ip-ul de start
	char *trace_2;//ip-ul destinatie
}Trace;
typedef struct Up//deschide un pc
{
	char *up_1;//ip-ul pc-ului ce urmeaza sa fie inchis
}Up;
typedef struct Lc //rupe o legatura intre 2 routere
{
	char *Lc_1;//ip-ul router-ului 1
	char *Lc_2;//ip-ul router-ului 2
}Lc;
typedef struct Broke//inchide un pc
{
	char *broke_1;//ip-ul pc-ului ce va fi inchis
}Broke;
typedef struct Add//adauga o legatura
{
	char *add_1;//memoreaza ip-ul primului router 
	char *add_2;//memoreaza ip-ul routerului 2
	int cost_drum;//costul de drum intre routere
}Add;
typedef struct pc
{
	char *nume_pc;
	char *ip_pc;
	int stare;
}Pc;
typedef struct router
{
	char *nume_router;
	char *ip_router;
	int   connected;//numarul de pc-uri conectate
	int nr_identificare_router;//pozitia router-ului
	Pc *pc;
}Router;

typedef struct conexiune//structura cu router-ele cu conexiuni directe
{
	char *nume_router_start;
	char *nume_router_finish;
	int distanta;//costul drumului dintre ele
}conexiune;

typedef struct retea
{
	
	int Nr_routere;//numarul total de routere din retea
	int nr_conexiuni_routere;//numarul de conexiuni directe intre routere
	int Nr_operatii;//numarul de operatii cerute
	int **a;//matrice de adiacenta
	int *vector_de_ordine;//vector in care se stocheaza ordinea operatiilor la citire 
    conexiune *Conexiune;//variabila de tip conexiune in care sunt stocate conexiunile directe intre routere si costul lor
	Router *R;
	Ping *ping;
	int nr_ping;//nuamrul de operatii cerute cu acet tip de cerinta "ping";de cate ori apare in date de intrare
	Sipn *sipn;
	int nr_sipn;
	Si *si;
	int nr_si;
	Trace *trace;
	int nr_trace;
	Up *up;
	int nr_up;
	Lc *lc;
	int nr_lc;
	Broke *broke;
	int nr_broke;
	Add *add;
	int nr_add;

}Retea;

Retea* Network_Creation(char *nume_fisier);
void spin_verification(Retea *network,char *nume_fisier,int i);
void si_verification(Retea *network,char *nume_fisier,int i);
void up_pc(Retea **network,int i);
void broke_pc(Retea **network,int i);
void lc_operation(Retea **network,int i);
void add_operation(Retea **network,int i);
void ping(Retea *network,char *nume_fisier,int i);
void trace_operation(Retea *network,char *nume_fisier,int i);
void execution(Retea *network,char *nume_fisier);
#endif