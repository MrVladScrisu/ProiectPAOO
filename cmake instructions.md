Instructiuni:

**Comanda**: cmake -S . -B build -> genereaza instructiunile de compilare



CMake are nevoie de 2 lucruri:



-de unde să citească fișierele de configurare (CMakeLists.txt)

-unde să pună fișierele de lucru (cache, Makefile, obiecte .o, etc.)



De aceea are două opțiuni:



-S . → „Source directory” = directorul unde se află CMakeLists.txt (adică root-ul, .)

-B build → „Build directory” = folderul unde vrei să genereze toate fișierele de build



**Comanda**: cmake --build build -> comanda efectiva de compilare  (acelasi lucru cu cd build, make)

**Comanda**: ./build/ProiectPOC -> comanda de rulare a executabilului





Se mai poate si asa, dar e invechit:

cd build

cmake .. = generează un Makefile

make = citește acel Makefile și compilează codul


Deci trebuia să folosești două unelte diferite.


Dacă nu pui explicit, compilatorul poate face conversii automate.

Adică următorul cod este valabil:
Dream d = "am visat ceva";

Pentru că "am visat ceva" este un const char\*, iar C++ vede că există un constructor care primește const char\*,

și zice „ah, deci pot transforma acest string literal într-un Dream automat”







„deep copy” - înseamnă copiere completă a conținutului, nu doar a pointerului.

Daca zic Dream b = a (adica apelam copy ctor care creeaza o copie noua a unui obiect existent, fara el ar fi shallow copy) si apelam destructorii, ambele o sa arate catre acelasi text si se va elibera aceeasi zona de memorie, ceea ce nu e bine, de aceea se face deep copy ca sa se aloce zona de memorie diferita pentru acelasi text.



In schimb, la move ctor, se creeaza un obiect nou **mutand** resursele, nu **copiindu**-le!!!

Adica, copiaza doar **adresa** pointerului text, nu si continutul (nu mai aloca memorie ca la copy ctor) deci e un transfer de proprietate, si pune vechea resursa pe null, lasand o goala. E mult mai rapid decat copy.





Diferenta dintre shallow copy si deep copy este ca la shallow copiezi doar adresele pointerilor, nu continutul, pe scurt ambele vor arata catre aceeasi zona de memorie si cand se face free pe una se face si pe cealalta si apare double free, in timp ce la deep copy aloci o zona de memorie si copiezi continutul.





DIFERENTA DINTRE COPY ASSIGNEMENT SI COPY CTOR:
Dream a("mare");

Dream b = a;    // copy constructor — creează un nou obiect

Dream c("zbor");

c = a;          // operator= — obiectul exista deja, se rescrie

CA SA PUTEM FACE a=b=c





**De ce am folosit copy constructor și move constructor în tema asta**?



Clasa deține o resursă pe heap (char\* text\_).



Asta înseamnă că o copie „mecanică” (bit cu bit) ar copia doar adresa, nu și conținutul → două obiecte ar arăta spre același buffer ⇒ risc de double free la destructori.



De aceea:



Copy constructorul personalizat face deep copy (alocă nou buffer și copiază textul).

Move constructorul transferă proprietatea bufferului (fură pointerul) fără copiere de octeți ⇒ eficient.



Cazuri concrete (în proiectul tău)



Dream v2 = v1; → declanșează copy ctor: vrem două vise independente, nu două obiecte cu același char\*.



Dream v3 = std::move(v1); → declanșează move ctor: v3 ia bufferul lui v1; v1 devine „gol” (pointer nul). Eficient și sigur (nu mai copiem memoria).


add_copy si add_move → sunt folosite cand vreau să adaug din afara (din main de ex). 


Pentru item 10:

Scenarii care nu merg fara item 10:
La void operator=, lucruri de genul:
a = b = c;       // NU mai merge, pentru că b = c NU întoarce nimic
(a = b).size();  // NU merge, nu poți apela nimic pe rezultat


La Dream operator=, se creează un nou obiect temporar:

merge a = b = c;, dar:

b = c întoarce o copie, nu referința la b;
Se fac copii în plus (mai lent, mai multă memorie);
(a = b).id() se aplică pe un temporar, nu neapărat pe a.

Scenarii care merg ok cu item 10:
Deci, cu acel return *this introdus, a = b = c;
// interpretare: b = c întoarce referință la b,
// apoi a = (b) -> tot ok

(a = b).set_text("altceva");   // modifică direct a, fără temporare


Pentru item 11:

Am pus if (this == &other) return *this
ca sa fie safe sa fac x = x, pentru ca daca nu e pus, si sa zic ca in operatorul de copy fac
Dream& Dream::operator=(const Dream& other) {
    delete[] text_;                  // 1) Șterg textul meu
    text_ = new char[size_+1];       // 2) Copiez textul din OTHER
    memcpy(text_, other.text_, ...); // 3) Copiez conținutul
    return *this;
}

atunci ambele sunt acelasi obiect, deci sterg textul dintr-una si dupa incerc sa copiez textul din ea tot in ea, dar ea e aceiasi, deci se acceseaza o zona de memorie deja stearsa si corupem memoria. 
Am adaugat si partea cu copia si cu swap pentru ca nu vreau sa ating obiectul tinta pana nu am o copie valida pentru ca poate Dream temp(other) arunca o exceptie (nu mai e memorie) si swap nu se mai executa, asa ca ii fac o copie prima data ca swap sa se execute sigur


Pentru item 12:
atat cu copy ctor unde se copiaza tot, cat cu in swap care schimba tot, copiez toti membrii si toate bazele in toate functiile

