# Proiect2-POO

<h5>Autor: Plesca Maria-Erika, grupa 133</h5>
<h3>Descriere</h3>
Acest proiect implementează un sistem complet de gestiune pentru un service auto folosind principiile programării orientate pe obiecte în C++. Sistemul permite administrarea clienților, vehiculelor, angajaților, reparațiilor și facturilor, oferind o soluție minimală pentru gestionarea operațiunilor zilnice ale unui service auto.

<h3>URMEAZA SA MAI UPDATEZ PROIECTUL (lucrez la mai multe mosteniri, funcții virtuale (pure), constructori virtuali (clone), dynamic_cast)</h3>

<h3>Structura proiectului</h3>
Proiectul este organizat într-o arhitectură modulară, cu fiecare entitate implementată ca o clasă separată:
├── angajat.h, angajat.cpp    # Gestionează angajații service-ului <br>
├── client.h, client.cpp      # Administrează datele clienților  <br>
├── masina.h, masina.cpp      # Gestionează informații despre vehicule  <br>
├── reparatie.h, reparatie.cpp # Înregistrează intervențiile efectuate  <br>
├── factura.h, factura.cpp    # Gestionează facturile și plățile  <br>
├── main.cpp                  # Conține bucla principală a aplicației  <br>
├── Makefile                  # Configurație pentru compilare <br>
└── input.in                  # Fișier cu date de intrare <br>


<h3>Funcționalități principale</h3>
Sistemul oferă următoarele funcționalități: <br>
- Gestionarea  lienților: Adăugarea și afișarea clienților (persoane fizice și juridice). <br>
- Gestiunea vehiculelor: Înregistrarea și afișarea mașinilor cu detalii de identificare. <br>
- Administrarea angajaților: Adăugarea și listarea angajaților și stațiilor de lucru. <br>
- Înregistrarea reparațiilor: Documentarea intervențiilor cu detalii despre mașină, client, angajat și costul reparației. <br>
- Interschimbarea stațiilor de lucru: Modificarea asignărilor pentru reparații. <br>
- Calculul costurilor: Calcularea sumei totale de plată pentru un client specific. <br>
- Generarea facturilor: Crearea și gestionarea facturilor cu calculul TVA și discount-urilor. <br>


<h3>Formatul datelor de intrare (input.in) </h3>
Sistemul citește date din fișierul input.in care conține, pe fiecare linie, un număr de opțiune urmat de datele specifice operației:<br>


1 [Numele clientului] [Tip client]                # Adăugare client <br>
2                                                 # Afișare clienți <br>
3 [Nr.Inm] [Marca] [Model] [Nume proprietar] [Tip proprietar] # Adăugare mașină <br>
4                                                 # Afișare mașini <br>
5 [Numele angajatului] [Statia de lucru]          # Adăugare angajat <br>
6                                                 # Afișare angajați <br>
7 [Nr.Inm] [Marca] [Model] [Nume proprietar] [Tip proprietar] [Nume angajat] [Statia de lucru] [Tip reparatie] [Cost] # Adăugare reparație <br>
8                                                 # Afișare reparații <br>
9 [Nr. Reparatiei 1] [Nr. Reparatiei 2]           # Interschimbare stații de lucru <br>
10 [Numele clientului]                            # Afișare sumă totală de plată <br>
11 [Detalii factură]                              # Generare factură <br>
12 [ID factură]                                   # Afișare factură specifică <br>

Exemplu concret din input.in: <br>
1 Irina-Petronela Persoana_fizica  <br>
1 Indaco_SRL Persoana_juridica <br>
3 NT56DRE VOLVO X60 Irina-Petronela Persoana_fizica <br>
7 NT56DRE VOLVO X60 Irina-Petronela Persoana_fizica Vasile-Cozma 2 Geometrie_roti 1187.56 <br>

<h3>Implementare OOP</h3>

<h4>Clase și Ierarhii</h4>
Proiectul conține următoarele clase: <br>
Client: Stochează informații despre clienți (nume, tip client). <br>
Mașină: Gestionează date despre vehicule (nr. înmatriculare, marcă, model, proprietar). <br>
Angajat: Administrează informații despre angajați (nume, stația de lucru). <br>
Reparație: Înregistrează detalii despre reparații (mașină, angajat, tip reparație, cost). <br>
Factură: Gestionează facturile (client, reparații, data emitere, TVA, status plată). <br>

<h4>Constructori și Destructori </h4>
Fiecare clasă implementează: <br>
<ul>
<li>Constructor implicit: Inițializează membrii cu valori implicite</li>
<li>Constructor parametrizat: Permite crearea obiectelor cu valori specifice</li>
<li>Constructor de copiere: Pentru copierea corectă a obiectelor</li>
<li>Operator de atribuire: Pentru asignarea corectă a obiectelor</li>
<li>Destructor: Pentru eliberarea resurselor (deși în acest proiect sunt simple, fără alocare dinamică)</li>
</ul>

Exemplu din clasa "Client": <br>
<code>Client();  // Constructor implicit <br>
Client(const std::string& m_nume, const std::string& m_tipClient);  // Constructor parametrizat<br>
~Client();  // Destructor<br>
Client(const Client& other);  // Constructor de copiere<br>
Client& operator=(const Client& other);  // Operator de atribuire<br>
</code>

<h4>Relațiile între clase</h4>
Proiectul folosește concepte OOP pentru a modela relațiile dintre entități:
<ul>
  <li>Compoziție: Clasa Mașină conține un obiect Client (proprietarul)</li>
  <li>Agregare: Clasa Reparație agregă obiecte Mașină și Angajat</li>
  <li>Colecții: Clasa Factură utilizează un vector de obiecte Reparație</li>
</ul>

<h4>Exemple de utilizare</h4>
Sistemul poate fi utilizat pentru următoarele scenarii: <br>
<ul>
  <li>Înregistrarea unui nou client în sistem</li>
  <li>Adăugarea mașinilor clienților</li>
  <li>Înregistrarea angajaților service-ului</li>
  <li>Documentarea reparațiilor efectuate</li>
  <li>Generarea facturilor pentru clienți</li>
  <li>Calculul costurilor totale pentru un client</li>
  <li>Interschimbarea stațiilor de lucru între reparații</li>
</ul>

<h3>Bibliografie</h3>
https://www.youtube.com/watch?v=oRBK0Mh_gG0 <br>
https://www.makeareadme.com <br>
https://github.com/MicrosoftDocs/cpp-docs/blob/main/docs/cpp/virtual-functions.md <br>
https://www.reddit.com/r/cpp_questions/comments/15o5049/i_created_a_c_oop_template_kind_of_a_newbie_can/ <br>
https://www.youtube.com/watch?v=6yp0C5G5EKo <br>
https://bito.ai/resources/virtual-functions-in-c-plus/ <br>
https://www.youtube.com/watch?v=v2_Pth8MrKA&t=550s <br>
