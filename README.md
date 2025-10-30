# PSO_PROIECT


-


Componente Proiect:
1. Serverul de Metadate 
  -Serverul de Metadate este punctul central de control. Nu stocheaza date, ci gestioneaza metadatele esentiale despre date/fisiere.

  -Rolul lui principal este de a mentine harta fisierolr: retine care fisier este stocat pe ce nod de stocare si pe ce noduri se afla fiecare copiile sale. De asemenea, monitorizeaza starea tuturor nodurilor prin mesaje de tip Heartbeat. Daca un nod esueaza, serverul initiaza recuperarea automata (crearea de noi replici) pentru a mentine fiabilitatea datelor.
-----------------------------------------
2. Nodurile de Stocare
  -Fiecare instanta de nod  este un executabil independent care ruleaza pe un port si un director de stocare unic.

  -Acest nod se ocupa cu stocarea fizica a fisierelor (folosind o structura de tip manager pentru acces pe disc) si gestioneaza transferul de date. El primeste cereri directe de la Client pentru citire/scriere. In timpul unui proces de upload, nodul de stocare participa la replicare : dupa ce primeste si scrie un bloc, il trimite catre nodul urmator din lantul creat de Serverul de Metadate. Nodul raporteaza periodic starea si fisierele detinute catre Serverul de Metadate (Heartbeat).
----------------------------------
3. Client
  -Clientul este cel care se va ocupa cu initierea de upload/download , rulat sub un terminal.

  -Pentru a accesa un fisier, Clientul intreaba initial Serverul pentru a obtine planul de stocare (harta cu locatiile fisierelor/copiilor). Dupa ce primeste confirmare, Clientul se conecteaza direct la Nodul de Stocare  specific pentru a citi sau a scrie datele efective (o singura data în versiunea simplificata, deoarece fisierele sunt tratate ca un singur bloc mare,[momentan :) ]). Aceasta redirectionare asigura o performanta optima.

----------------------------------------
 Criteriile de calitate specificate sunt atinse prin:

Concurenta: Utilizarea threading-ului  pentru a gestiona multiple conexiuni simultan.

Fiabilitate: Asigurarea disponibilitatii datelor prin replicarea blocurilor pe noduri diferite si recuperarea automata la esec.

Scalabilitate: Arhitectura permite extinderea facilă a sistemului prin adaugarea oricator instante noi a nodurilor de retea.
