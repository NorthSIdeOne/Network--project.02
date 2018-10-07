

																			The Network







-------------------------------------------------------------------------Network_Creation()------------------------------------------------------------------------------------------

 In functia "Network_Creation",am alocat memorie pentru fiecare tip de structura "Router","Pc"si "Conexiune",apoi am citit in ordine fiecare valoarea.Structura "Retea" cuprinde si numarul de routere,numarul de operatii ,numarul de conexiuni pe care le-am citit si le-am stocat in cate un camp "Nr_routere","nr_operatii" respectiv "nr_conexiuni_routere".
Pentru operatiile cerute,am creat cate un camp de exemplu "nr_ping" in care am stocat numarul de aparitie al acelei sarcini,apoi am initializat toate aceste campuri cu 0.Am creat un vector temporar initializat cu 1 iar pentru fiecare sarcina :ping ,sipn ,si , trace...corespunde un index incepand de la 0 la 8( 8 fiind numarul total de sarcini) in ordinea prezentata in program.Pentru fiecare aparitie a sarcinii se incrementa vectorul de pozitia specifica si se copia in variabila specifica,de exemplu "nr_si".In acelasi timp mai exista in structura un vector alocat dinamic in functie de numarul de operatii in care este stocata ordinea fiecarei operatii.Pentru fiecare citire si identificare a sarcinii se memoreaza pe pozitia curenta numarul specific sarcinii (de la 0 la 8) apoi se trece la urmatoarea pozitie.Apoi se creaza matricea de adiacenta cu ajutorul conexiunilor directe citite din fisier.Se returneaza "network".



------------------------------------------------------------------------Sipn_verification()------------------------------------------------------------------------------------------

Compar ip-ul routerului cautat cu toate ip-urile router-elor existente pana il gasesc,apoi memorez pozitia routerului gasit.Cu indicele memorat caut in matricea de adiacenta ce routere au legaturi directe cu router-ul cautat si le scriu in date.out.


-------------------------------------------------------------------------Si_verification()-------------------------------------------------------------------------------------------


Compar ip-ul router-ului cautat cu toate router-ele si memorez indicele router-ului gasit.Apoi verific toate pc-urile ce au starea "1" si le scriu in date.out.



-----------------------------------------------------------------------------Up_pc()-------------------------------------------------------------------------------------------------


Compar pe rand fiecare pc al fiecarui router pana dau de pc-ul cautat,il deschid(schimb starea in "1") apoi folosesc return sa ies din functie.


----------------------------------------------------------------------------Broke_Pc()-----------------------------------------------------------------------------------------------

Functioneaza la fel ca Up_pc() doar ca starea va fi "0" si nu "1".

--------------------------------------------------------------------------lc_operation()---------------------------------------------------------------------------------------------

Compar ip-ul fiecarui router cu primul ip care stocat la Lc_1 si stochez indicele router-ului in x apoi compar cu Lc_2 si stochez indicele router-ului in y.
Schimb in matricea de adiacenta in functie de indicii x si y valorile cu INF -ce reprezinta ca nu exista legatura intre cele doua routere.

--------------------------------------------------------------------------add_operation()--------------------------------------------------------------------------------------------
Functioneaza la fel ca la "lc_operation()" doar ca adaug noul cost de drum in matricea de adiacenta.


-------------------------------------------------------------------------------ping()------------------------------------------------------------------------------------------------

Creez o matrice temporara in care stochez matricea de adiacenta.Caut indicele router-ului si al pc-ului care corespunde cu ip-ul de la ping_1 ,pe care le stochez in x respectiv in nr_pc1 si pentru ping_2 la fel doar ca le stochez in y si nr_pc2.Folosesc matricea temporara si aplic algoritmul Floyd Warshall pentru drum de cost minim.Apoi cu indicii x si y verific in matricea temporara care a fost modificata daca exista drum de la x la y,iar daca exista verific daca ambele pc-uri sunt deschise.Daca sunt afisez "OK" daca nu afisez "NO" si eliberez vectorul temporar.

--------------------------------------------------------------------------trace_operation()------------------------------------------------------------------------------------------

Declar o matrice de cost,un vector de distanta,un vector ,un vector de vizite,un indice pentru pozitia predecesorului si un minim pentru distanta minima.
Aloc matricea de cost,o initializez apoi caut indicii router-elor la care sunt conectate pc-urile cautate si aplic Dijskstra.Afisez drumul folosindu-ma de predecesori.Stochez toate ip-urile intr-un vector temporar si le citesc invers pentru ca pornesc de la nodul destinatie la nodul sursa pentru ca folosesc predecesorii.


-----------------------------------------------------------------------------execution()---------------------------------------------------------------------------------------------

Creez un vector,in care indicii reprezinta fiecare operatie in parte(ping ,sipn,si,trace ....) si in care stochez numarul de executari al fiecarei operatiei.In functie de valorile din vector_de_ordine ,fiecare operatie va fi executata iar vectorul in  care sunt stocate numarul de executari va fi incrementat pana cand va ating numarul maxim de executari(numarul de aparitie al unei operatii in datele de intrare).

-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------



