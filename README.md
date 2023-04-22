Aplicatie campionat basket

Tema aleasa pentru aceasta aplicatie este un turneu de basket american, unde echipele din NBA joaca intre ele.

Lista claselor pe care le am definite:
-MyString: este o clasa pe care o folosesc in locul std::string, pentru a acceasa mai usor denumirile echipelor, jucatorii din echipe etc;
-Player: este o clasa pentru fiecare jucator din fiecare echipa, care retine niste informatii generale despre un jucator;
-Team: este o clasa care retine informatii despre fiecare echipa, spre exemplu numele acesteia, jucatorii ei, recordul de win/loss;
-Game: este o clasa pe care o folosesc pentru a simula meciul care se desfasoara intre 2 echipe, retind informatii despre meci si facand update la statistici ;
-Tournament: este clasa cea mare in care sunt adaugate meciurile si echipele, care retine date precum castigator, numarul maxim de echipe, numarul maxim de meciuri.

Aplicatia este capabila sa simuleze un campionat de basket, unde:
-sunt sanse aleatorii de castig pentru fiecare echipa;
-se pot afisa jucatorii fiecarei echipe;
-se pot afisa meciurile jucate de fiecare echipa;
-se calculeaza echipa cu cele mai multe meciuri castigate.