#include <iostream>
#include <unordered_map>
#include <string>
#include <stdlib.h>
#include <typeinfo>
using namespace std;

class Plata{
private:
    string data;
    int suma;
    const int id_plata;
public:
    static int contorID;

    Plata():id_plata(contorID++){
        this->data = "DD/MM/YYYY";
        this->suma = 0;
    };

    Plata(string data, int suma):id_plata(contorID++){
        this->data = data;
        this->suma = suma;
    };

    Plata(const Plata& p):id_plata(p.id_plata){
        this->data = p.data;
        this->suma = p.suma;
    };

    int getid_plata() const{return this->id_plata;}
    string getData() const{return this->data;}
    int getSuma() const{return this->suma;}

    Plata& operator=(const Plata& p){
        if (this!=&p){
        this->data = p.data;
        this->suma = p.suma;
        }
        return *this;
    };

    virtual void citire(istream &in){
        int suma;
        cout<<"\n Introduceti data in care s-a efectuat plata(DD/MM/YYYY): ";
        while(true){
            try{
                string data;
                getline(cin, data);
                if (data.size()==10){
                    this->data=data;
                }
                if (data.size()!=10) throw(data);
                else break;
            }
            catch(string s){
                cout<<"\n Formatul este incorect, va rugam reintroduceti (DD/MM/YYYY): ";
            }
        };

        cout<<"\n Introduceti suma platita: ";

        in>>suma;
        in.get();
        this->suma=suma;

    };

    virtual void afisare(){
        cout<<"\n Data platii este: "<<this->getData();
        cout<<"\n Suma platita este: "<<this->getSuma();
    }

    friend ostream& operator<<(ostream& out, const Plata& p){
        out<<"\n Data: "; out<<p.data;
        out<<"\n Suma: "; out<<p.suma;
        return out;
    };

    friend istream& operator>>(istream& in, Plata&p){
        p.citire(in);
        return in;
    };

    ~Plata(){};
};

int Plata::contorID = 1;

class Numerar: public Plata{
private:
    int nrBancnote;
public:
    Numerar():Plata(){
        this->nrBancnote = 0;
    };

    Numerar(string data, int suma, int nrBancnote):Plata(data, suma){
        this->nrBancnote = nrBancnote;
    };

    Numerar(const Numerar& n):Plata(n){
        this->nrBancnote = n.nrBancnote;
    };

    Numerar& operator=(const Numerar& n){
        if (this != &n){
            Plata::operator=(n);
            this->nrBancnote=n.nrBancnote;
        }
        return *this;
    };

    int getNrBancnote() const{return this->nrBancnote;}

    void citire(istream& in){
        int nrBancnote;
        Plata::citire(in);
        cout<<"\n Introduceti nr de bancnote folosit: ";
        in>>nrBancnote;
        in.get();
        this->nrBancnote=nrBancnote;
    };

    void afisare(){
        Plata::afisare();
        cout<<"\n Numarul de bancnote cu care s-a efectuat plata este "<<this->getNrBancnote();
    };

    friend ostream& operator<<(ostream& out, const Numerar &n){
        out<<(Plata&)n;
        out<<"\n Numarul de bancnote cu care s-a platit: "<<n.nrBancnote;
        return out;
    };

    friend istream& operator>>(istream& in, Numerar &n){
        n.citire(in);
        return in;
    };

    ~Numerar(){};
};

class Cec: public Plata{
private:
    string numeClient;
public:
    Cec():Plata(){
        this->numeClient = "necunoscut";
    };

    Cec(string data, int suma, string numeClient):Plata(data, suma){
        this->numeClient = numeClient;
    };

    Cec(const Cec& c):Plata(c){
        this->numeClient=c.numeClient;
    };

    Cec& operator=(const Cec& c){
        if (this != &c){
            Plata::operator=(c);
            this->numeClient=c.numeClient;
        }
        return *this;
    };

    string getNumeClient() const{return this->numeClient;}

    void citire(istream &in){
        string numeClient;
        Plata::citire(in);
        cout<<"\n Numele clientului este: ";
        getline(in, numeClient);
        this->numeClient=numeClient;
    }

    void afisare(){
        Plata::afisare();
        cout<<"\n Numele clientului este: "<<this->getNumeClient();
    }

    friend ostream& operator<<(ostream& out, const Cec& c){
        out<<(Plata&)c;
        out<<"\n Numele clientului este: "<<c.numeClient;
        return out;
    };

    friend istream& operator>>(istream& in, Cec& c){
        c.citire(in);
        return in;
    }

    ~Cec(){};
};

class Card: public Plata{
private:
    string numarCard;
    string numeClient;
public:
    Card():Plata(){
        this->numarCard = "necunoscut";
        this->numeClient = "necunoscut";
    };

    Card(string data, int suma, string numarCard, string numeClient):Plata(data, suma){
        this->numarCard = numarCard;
        this->numeClient = numeClient;
    };

    Card(const Card &c):Plata(c){
        this->numarCard = c.numarCard;
        this->numeClient = c.numeClient;
    };

    Card& operator=(const Card& c){
        if (this != &c){
            Plata::operator=(c);
            this->numarCard=c.numarCard;
            this->numeClient=c.numeClient;
        }
        return *this;
    };

    string getNumarCard() const{return this->numarCard;}
    string getNumeClient() const{return this->numeClient;}

    void citire(istream &in){
        string numeClient;
        Plata::citire(in);
        cout<<"\n Numele clientului este: ";
        getline(in, numeClient);
        this->numeClient=numeClient;
        cout<<"\n Introduceti numarul cardului(16 cifre fara spatii): ";
        while(true){
            try{
                string numarCard;
                getline(in, numarCard);
                if(numarCard.size()==16){
                    this->numarCard=numarCard;
                }
                if(numarCard.size()!=16) throw(numarCard);
                else break;
            }
            catch(string s){
                cout<<"\n Numarul de card este invalid, reintroduceti: ";
                }
            };
    };

    void afisare(){
        Plata::afisare();
        cout<<"\n Numarul cardului este: "<<this->getNumarCard();
        cout<<"\n Numele clientului este: "<<this->getNumeClient();
    }

    friend ostream& operator<<(ostream& out, const Card& c){
        out<<(Plata&)c;
        out<<"\n Numele clientului este: "<<c.numeClient;
        out<<"\n Numarul cardului este: "<<c.numarCard;
        return out;
    };

    friend istream& operator>>(istream& in, Card& c){
        c.citire(in);
        return in;
    };

    ~Card(){};
};

template <class t> class Gestiune
{
private:
    t *v;
    int nr;
public:
    Gestiune(t *p=NULL, int n=0){
        nr = n;
        v = new t[n];
        for(int i=0; i<n; i++){
            v[i]=p[i];
        }
    };
    Gestiune(Gestiune &a){
        nr = a.nr;
        v=new t[nr];
        for(int i=0;i<nr;i++){
            v[i]=a.v[i];
        }
    }
    ~Gestiune(){
        delete[] v;
    }

    int getNr(){return nr;}
    t getV(int i){return v[i];}

    friend istream& operator>>(istream &in, Gestiune <t> &g){
        cout<<"\n Introduceti numarul de plati: ";
        in>>g.nr;
        in.get();
        g.v=new t[g.nr];
        cout<<"\n Introduceti obiectele: \n";
        for(int i=0;i<g.nr;i++){
           in>>g.v[i];
           cout<<"\n";
        }
        return in;
    };

    friend ostream& operator<<(ostream &out, Gestiune <t> &g){
        out<<"\n In gestiune se gasesc urmatoarele "<<g.nr<<" plati:";
        for(int i=0;i<g.nr;i++)
            out<<g.v[i]<<"\n";
        return out;
    }
};

template <> class Gestiune<Card>
{
private:
    Card *v;
    int nr;
public:
    Gestiune(Card *p=NULL, int n=0)
    {
        nr=n;
        v=new Card[n];
        for(int i=0;i<n;i++)
        {
            v[i]=p[i];
        }
    }
    Gestiune(Gestiune &a)
    {
        nr=a.nr;
        v=new Card[nr];
        for(int i=0;i<nr;i++)
        {
            v[i]=a.v[i];
        }
    }
    ~Gestiune()
    {
        delete [] v;
    }
    int getNr(){return nr;}
    friend istream& operator >>(istream &in, Gestiune <Card> &g)
    {
        cout<<"Introduceti numarul de plati efectuate: ";
        in>>g.nr;
        in.get();
        g.v=new Card[g.nr];
        cout<<"Introduceti obiectele\n";
        for(int i=0;i<g.nr;i++)
        {
            in>>g.v[i];
        }
        return in;
    }
    friend ostream& operator <<(ostream &out, Gestiune<Card> &g)
    {
        out<<"\n In gestiune sunt "<<g.nr<<" plati cu cardul.";
        for (int i=0; i<g.nr; i++){
            out<<g.v[i];
        }
        return out;
    };
    Gestiune<Card>& operator+=(const Card& c){
        Card *aux;
        aux = new Card[++nr];
        for (int i=0; i<nr-1; i++){
            aux[i]=v[i];
        }
        aux[nr-1]=c;
        delete[] v;
        v = new Card[nr];
        for (int i=0; i<nr; i++){
            v[i]=aux[i];
        }
    };
};

void meniu(){
    int k=1;
    int i=0;
    int n;
    unordered_map<int, Plata*> plati;
    while (k==1){
        cout<<"\nCherim Erol 141 Info - Tema 1 gestiune plati firma"<<endl;
        cout<<"\nMeniu interactiv";
        cout<<"\n1 Introducerea si memorarea n obiecte";
        cout<<"\n2 Afisarea n obiecte";
        cout<<"\n3 Gestiune - Template tip plata numerar";
        cout<<"\n4 Gestiune - Template tip plata cec";
        cout<<"\n5 Gestiune - Template tip plata card - template specializat";
//        cout<<"\n6 Total suma - plata cu numerar din structura cu n obiecte";
//        cout<<"\n7 Total suma - plata cec din structura cu n obiecte";
//        cout<<"\n8 Total suma - plata card din structura cu n obiecte";
        cout<<"\n10 Terminare program"<<endl;
        int comanda;
        cout<<"\n Introduceti comanda: ";
        cin>>comanda;
        cin.get();
        switch(comanda){
            case 1:{
                cout<<"\n Introduceti numarul de plati pe care doriti sa le memorati: ";
                cin>>n;
                cin.get();
                string s;
                Plata *p;
                for(int i=1; i<=n; i++){
                    cout<<"\n Introduceti tipul de plata (numerar/cec/card): ";
                    getline(cin, s);
                    if(s=="numerar"){
                        p = new Numerar();
                        cin>>static_cast<Numerar&>(*(p)); //insert ul sau ceva nu e bun pentru ca la afisare imi afiseaza toate obiectele ca fiind de tip plata
                        plati.insert({p->getid_plata(), p}); //in principiu proiectul ar trebui sa fie complet, dar fara up/downcasting
                    }
                    else if(s=="cec"){
                        p = new Cec();
                        cin>>static_cast<Cec&>(*(p));
                        plati.insert({p->getid_plata(), p});
                    }
                    else if(s=="card"){
                        p = new Card();
                        cin>>static_cast<Card&>(*(p));
                        plati.insert({p->getid_plata(), p});
                    }
                    else{cout<<"\n tipul nu este valid"; i--;}
                }
                break;
            }
            case 2:{
                unordered_map<int, Plata*>::iterator i;
                for (i=plati.begin(); i!=plati.end(); ++i){
                    cout<<(*i).first<<"\n";
                    cout<<*((*i).second)<<"\n";
                }
                break;
            }
            case 3:{
                Gestiune<Numerar> n;
                cin>>n;
                cout<<n;
                break;
            }
            case 4:{
                Gestiune<Cec> c;
                cin>>c;
                cout<<c;
                break;
            }
            case 5:{
                Gestiune<Card> ca;
                cin>>ca;
                cout<<ca;
                break;
            }
//            case 6:{
//                Numerar *n;
//                int sumaT=0;
//                unordered_map<int, Plata*>::iterator i;
//                for (i=plati.begin(); i!=plati.end(); ++i){
//                        if(typeid(*((*i).second))!=typeid(Numerar))
//                                {
//                                     n=dynamic_cast<Numerar*>((*i).second);
//                                     sumaT+=n->getSuma();
//                                     cout<<"k";
//                                }
//                }
//
//                break;
//            }
//            case 7:{
//                Cec *c;
//                unordered_map<int, Plata*>::iterator i;
//                for (i=plati.begin(); i!=plati.end(); ++i){
//
//                }
//                break;
//            }
//            case 8:{
//                Card *ca;
//                unordered_map<int, Plata*>::iterator i;
//                for (i=plati.begin(); i!=plati.end(); ++i){
//
//                }
//                break;
//            }
            case 10:{
                k=0;
                break;
            }
        }
    }
    system("cls");


}

int main(){
    meniu();
return 0;
}
