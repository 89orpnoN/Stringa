
#include <vector>
#include "StandardLib.h"


class stringa{ //cioè immagina essere
    private:
        std::vector <char> vettore;

    public:

        explicit stringa(char* stringa, int len = 0){
            set(stringa, len);
        }

        //crea vettore e lo riempe della stringa passata
        void set(char* stringa, int len = 0){ //i goto perché si. //inoltre non aggiunge '\0' alla fine del vettore
            vettore = std::vector <char>();

            int i=0;
            start:

            vettore.push_back(stringa[i]);

            ++i;
            if (!(i==(len-1) || stringa[i]=='\0')) goto start; //va finché non trova la fine della stringa o il numero di caratteri specificato
            0;
        }

        void reverse(){ //comportamento aggiustato per l'ascii esteso
            int Ri;
            std::vector<char> vett(vettore.size()); //vettore dove specchiare i caratteri

            for(int i = 0;i<vettore.size();i++){ //per la lunghezza del vettore
                 Ri = vettore.size()-i-1;
                 if (vettore[i]<0){ //se il carattere fa parte dell'ascii esteso
                    vett[Ri] = vettore[i+1]; //spostalo come blocco unico
                    vett[Ri-1] = vettore[i];
                    i++;
                 } else vett[Ri] = vettore[i]; //altrimenti sposta come un carattere normale
            }
            vettore = vett; //scambia i due vettori
        }

        char* toCharPointer(){ //siccome la mia stringa non è un array di caratteri devo convertirla esplicitamente
            char* p1 = (char*)calloc(sizeof (char),vettore.size()+1);
            p1 = std::copy(vettore.data(), vettore.data() + ~*this, p1)-vettore.size();
            p1[vettore.size()]='\0';
            return p1;
        }

        void stampa(){ //richiede la libreria "StandardLib" presente nel progetto
            print(toCharPointer());
        }

        int cerca(char ch){
            int i = (int)((std::find(vettore.begin(), vettore.end(), ch))-vettore.begin());
            if (i == vettore.size()){
                i=-1;
            }
            return i;
        }

        int conta(char ch){
            return (int)std::count(vettore.begin(), vettore.end(), ch);
        }

        void toUpper(){ //dai è gia tanto se ho reso l'inversione compatibile con l'ascii esteso.
            std::for_each(vettore.begin(), vettore.end(), [=](char& c){ c +=(c>91)*(c<123)*-32;});
        }

        void toLower(){
            std::for_each(vettore.begin(), vettore.end(), [](char& c){ c+=(c>64)*(c<91)*32; });
        }

        void ToFlip(){
            std::for_each(vettore.begin(), vettore.end(), [](char& c){ c +=(c>64)*(c<91)*32+(c>91)*(c<123)*-32; });
        }

        int palindroma(){ //per definizione un palindromo tiene conto di eventuali spazi
            int Ri;
            for(int i = 0;i<vettore.size()/2;i++){
                Ri = vettore.size()-i-1;
                if(vettore[i]!=vettore[Ri]) return 0;
            }
            return 1;
        }

        int operator~(){
            return (int)vettore.size();
        }

        stringa operator+(stringa s2)  {
            int Sc1 = ~*this, Sc2 = ~s2;
            int size = Sc1+Sc2; //lunghezza di questa stringa e la stringa 2
            char* p3 = (char*) calloc(sizeof (char), size); //alloca stringa spazio per entrambe

            p3 = (char*)std::copy(vettore.begin(), vettore.end(), p3)-Sc1; //copia i contenuti di questa stringa in p3

            p3 = (char*)std::copy(s2.vettore.begin(), s2.vettore.end(), p3+Sc1)-size; //aggiungi i contenuti di stringa2 in p3

            stringa str (p3); //rendi p3 una stringa
            return str;
        }

        int operator==(stringa s2){ //confronta ogni elemento per trovare incongruenze
            return std::equal(vettore.begin(),vettore.end(),s2.vettore.begin());
        }

        char operator [](int idx){ //accedi tramite indice
            return vettore[idx];
        }
};



int main() { //tempo di testare

    //stampare funziona
    stringa str ("clash of clans");
    stringa str2 ("bellò");
    str.stampa();
    str2.stampa();

    //invertire funziona
    str.set("còccò");
    str.stampa();
    str.reverse();
    str.stampa();
    str.reverse();

    //cercare e contare funziona
    int indice = str2.cerca('l');
    int quantita = str2.conta('l');
    stringa str3 ("l'indice è: ");
    stringa str4 ("ovvero la lettera N.");
    print(str3.toCharPointer(), indice, " \n", str4.toCharPointer(), quantita);

    //uppercase, lowercase e flip funzionano
    str.toUpper();
    str2.toLower();
    str3.set((str + str2).toCharPointer());
    print(str3.toCharPointer());
    str3.ToFlip();
    print(str3.toCharPointer());

    //palindromo funziona
    str4.set("annalilanna");
    print("la stringa : ", str4.toCharPointer(), (str4.palindroma()) ? " è palindroma" : " non è palindroma");

    //concatenazione e operatori vari funzionano
    str4 = str + str2 + str3 + str4;
    stringa str5 = str4;
    print("la stringa: ", str4.toCharPointer(), "\n  è lunga: " , ~str4 , ((str4==str5) ? " ed è " : " ed non è "), "uguale a se stessa");


    return 0;
}//potrebbe darsi che ci sono dei memory leak da qualche parte, ma sul mio pc funzionava tutto perfettamente
