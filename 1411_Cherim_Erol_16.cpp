#include <iostream>
using namespace std;
//CHERIM EROL, grupa 141 INFO, tema 16
class individ{
private:
//membrii privati
    int i;
    char tip;
    double energie;
    int viu; //nu puteam sa afisez 1 sau 0 ca unsigned char asa ca l-am facut int (n-am respectat cerinta, nu stiu foarte bine c++)
    int varsta;

//metode private
    void hraneste(individ* &indivizi){
        indivizi[this->i].setEnergie(this->energie + rand() % 10 + 1);
    }

//metodele primesc ca parametru array-ul de obiecte (tablou unidimensional) si modificarile se fac in membrii acesteia
    void inmulteste(individ* &indivizi){
        if (indivizi[this->i+1].i == 0 && indivizi[this->i-1].i == 0){
            individ stanga(this->i-1, this->tip);
            stanga.setEnergie(indivizi[this->i].energie*2);
            individ dreapta(this->i+1, this->tip);
            dreapta.setEnergie(indivizi[this->i].energie*2);
            indivizi[this->i-1] = stanga;
            indivizi[this->i+1] = dreapta;
        }
    }

    void ataca(individ* &indivizi){
        if (indivizi[this->i-1].tip != indivizi[this->i].tip && indivizi[this->i].energie> indivizi[this->i-1].energie){
            indivizi[this->i].setEnergie(indivizi[this->i].energie - indivizi[this->i-1].energie);
            indivizi[this->i-1].moare();
        }
        else if (indivizi[this->i+1].tip != indivizi[this->i].tip && indivizi[this->i].energie > indivizi[this->i+1].energie){
            indivizi[this->i].setEnergie(indivizi[this->i].energie - indivizi[this->i+1].energie);
            indivizi[this->i+1].moare();
        }
    }

    void imbatraneste(individ* &indivizi){
        indivizi[this->i].setVarsta(this->varsta + 1);
        indivizi[this->i].setEnergie(this->energie - 7); //valoare  aleasa pentru energie
        if (indivizi[this->i].energie < 0){
            indivizi[this->i].moare();
        }
        if (indivizi[this->i].varsta > 20){ //valoare maxima alesa pentru varsta
            indivizi[this->i].moare();
        }
    }

    void moare() {
        this->viu = 0;
    }


public:
//constructori
    individ();
    individ& operator=(const individ& ind);


    individ(int i, char tip){ //constructor cu parametri
        this->i = i;
        this->tip = tip;
        this->varsta = 0;
        this->energie = 20;
        this->viu = 1;
    };

    individ(const individ& ind_vechi){ //copy constructor
        this->i = ind_vechi.i;
        this->tip = ind_vechi.tip;
        this->energie = ind_vechi.energie;
        this->viu = ind_vechi.viu;
        this->varsta = ind_vechi.varsta;
    };

    friend istream& operator>>(istream& in, individ& ind);
    friend ostream& operator<<(ostream& out, const individ& ind);


//metode publice
    void actualizare(individ* &indivizi){
        this->hraneste(indivizi);
        this->inmulteste(indivizi);
        this->ataca(indivizi);
        this->imbatraneste(indivizi);

    }

    void public_atac(individ* &indivizi){
        this->ataca(indivizi);
    }

    void public_hraneste(individ* &indivizi){
        this->hraneste(indivizi);
    }

    void public_imbatraneste(individ* &indivizi){
        this->hraneste(indivizi);
    }

    int esteViu(individ* &indivizi){
        if((int)(indivizi[this->i].viu) == 1){return 1;}
        else{return 0;}
    }

    void afisare(); //metoda publica pentru citirea a n obiecte
    void citire(); //si afisarea acestora

//getteri
    double getEnergie(){return this->energie;}
    int getVarsta(){return this->varsta;}
    int getViu(){return this->viu;}
    int getPozitie(){return this->i;}
    char getTip(){return this-> tip;}
//setteri
    double setEnergie(double energie){this->energie = energie;}
    int setVarsta(int varsta){this->varsta = varsta;};
    int setViu(int viu){this->viu = viu;};
    int setPozitie(int i){this->i = i;}

    ~individ(){} //destructor
};


individ::individ(){  //constructor fara parametri
    this->i = NULL;
    this->varsta = NULL;
    this->viu = 1;
    this->energie = 20;
    this->tip = NULL;

};

individ& individ::operator=(const individ& ind) //overloading la operatorul de assignment (egal)
{
    if (this!=&ind)
    {
        this->i = ind.i;
        this->varsta = ind.varsta;
        this->tip = ind.tip;
        this->viu = ind.viu;
        this->energie = ind.energie;

    }
    return *this;
}

istream& operator>>(istream& in, individ& ind){  //supraincarcare operator >> citire
    cout<<"\n Pozitia (alegeti un numar de la 1 la 30): "; in>>ind.i;
    cout<<"\n Varsta (maxim 20): "; in>>ind.varsta;
    cout<<"\n Tipul speciei(+ sau 0): "; in>>ind.tip;
    cout<<"\n Energia: "; in>>ind.energie;
    cout<<"\n Este viu? (1=DA/0=NU) "; in>>ind.viu;


    return in;
}

ostream& operator<<(ostream& out, individ& ind){ //supraincarcare operator << afisare
    out<<"\n Pozitia: "; out<<ind.getPozitie();
    out<<"\n Varsta: "; out<<ind.getVarsta();
    out<<"\n Tipul: "; out<<ind.getTip();
    out<<"\n Energia: "; out<<ind.getEnergie();
    out<<"\n Este viu: "; out<<ind.getViu();

    return out;
}

void individ::citire(){  //metoda publica citire
    cout<<"\n Pozitia "; cin>>this->i;
    cout<<"\n Varsta: "; cin>>this->varsta;
    cout<<"\n Tipul speciei(+ sau 0): "; cin>>this->tip;
    cout<<"\n Energia: "; cin>>this->energie;
    cout<<"\n Este viu? "; cin>>this->viu;
}

void individ::afisare(){  //metoda publica afisare
    cout<<"\n Pozitia: " <<this->i;
    cout<<"\n Varsta: " <<this->varsta;
    cout<<"\n Tipul: " <<this->tip;
    cout<<"\n Energia: " <<this->energie;
    cout<<"\n Este viu: " <<this->viu;
}

int main()
{
    individ* indivizi = new individ[30];

    individ aux[30];
    int i=0;

    int k=1;
    while (k==1){
    cout<<"\n Apasa 1 pentru a adauga un individ\n";
    cout<<"\n Apasa 2 pentru a actualiza un individ\n";
    cout<<"\n Apasa 3 pentru a vedea daca un individ este viu\n";
    cout<<"\n Apasa 4 pentru a vedea tipul unui individ\n";
    cout<<"\n Apasa 5 pentru a vedea toate datele unui individ\n";
    cout<<"\n Apasa 10 pentru STOP\n";

    int comanda;
    cin>>comanda;

    switch(comanda){
    case 1:{
        cin>>aux[i];
        cout<<"\n Individ adaugat cu succes cu urmatorii parametri: \n";
        cout<<aux[i]<<"\n";
        indivizi[aux[i].getPozitie()]=aux[i]; //se copiaza din arrayul secundar aux in arrayul principal indivizi(pe pozitia corecta)
        i++;
        break;
        }
    case 2:{
        int individDeActualizat;
        cout<<"\n Alegeti individul ce trebuie actualizat: \n";
        cin>> individDeActualizat;
        indivizi[individDeActualizat].actualizare(indivizi);
        break;
    }
    case 3:{
        int individViu;
        cout<<"\n Alegeti individul despre care doriti sa aflati daca este viu(pozitia din tablou unidimensional): \n";
        cin>>individViu;
        if(indivizi[individViu].getViu()==1){cout<<"Individul este viu";}
        else{cout<<"Individul nu este viu";}
        break;
        }
    case 4:{
        int individTip;
        cout<<"\n Alegeti individul caruia doriti sa ii aflati tipul(pozitia din tablou unidimensional) \n";
        cin>>individTip;
        if(indivizi[individTip].getTip() != NULL){cout<<"Individul este de tip: "<<indivizi[individTip].getTip();}
        else{cout<<"Individul nu are tip(probabil nu a fost initializat inca)";}
        break;
        }
    case 5:{
        int individDate;
        cout<<"\n Alegeti individul caruia doriti sa ii aflati toate datele(pozitia dint tabloul unidimensional) \n";
        cin>>individDate;
        cout<<indivizi[individDate];
        break;
    }

    case 10:{
        k=0;
        break;
        }
    }
    }
    return 0;
}
