#include <iostream>
#include <cmath>
#include <math.h>
using namespace std;
//CHERIM EROL 141INFO

class complex{
private:
    float re;
    float im;
public:
//constructori
    complex(){ //constructori fara parametri - valoarea default 0;
        this->re = 0;
        this->im = 0;
    };
    complex(float re, float im){this->re=re; this->im=im;} //constructor cu parametri
    complex(const complex& c){this->re=c.re; this->im=c.im;} //copy constructor

//getteri + setteri
    float setReal(float re){this->re = re;}
    float setImaginar(float im){this->im = im;}
    float getReal(){return re;}
    float getImaginar(){return im;}
    float getModul(){return sqrt(im*im + re*re);}

//supraincarcari operatori
    friend ostream& operator<<(ostream& out, const complex& c){
        out<<c.re; cout<<"+"; out<<c.im; cout<<"i";
        return out;
    };

    friend istream& operator>>(istream& in, complex& c){
        cout<<"Partea reala a numarului este: ";
        in>>c.re;
        cout<<"Partea imaginara a numarului este: ";
        in>>c.im;
        return in;
    };



    complex& operator=(const complex& c){
        this->re = c.re;
        this->im = c.im;
    }
//destructor
    ~complex(){};
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
//am incercat sa fac clasa de baza interfata(fara constructori)
//dar nu se respecta cerinta 1 (toate clasele trebuie sa aiba constructori)

class matrice{
protected:
    complex **v;
    const int idMatrice;
public:
    static int contorId; //contorul e public, ca in exemplele din lab
    matrice():idMatrice(contorId++){v = new complex*[1]; v[0] = new complex [1];} //folosesc iDMatrice doar la constructorul de baza pentru ca acesta este accesat de fiecare data cand se apeleaza orice constructor dintr-o clasa derivata
    const int getIdMatrice(){return idMatrice;}
    //functii virtuale (pure)
    virtual void afisare(){};
    virtual void setElement(int lin, int col, complex element){};
    virtual void diagonala(){};
    virtual complex getElement(){};
    virtual ~matrice(){}; //destructor virtual

};
int matrice::contorId = 0;

//-----------------------------------------------------------------------------------------------------------------------------------------------
class matrice_oarecare: public matrice{
private:
    int lin;
    int col;
public:
    matrice_oarecare():matrice(){}; //constructor fara parametri
    matrice_oarecare(int l, int c){ //se apeleaza si constructorul de baza matrice() cand se creaza un obiect de tip matrice_oarecare(int,int)
        lin = l;
        col = c;
        v = new complex*[c];
        for (int i=0; i<c; i++){
            v[i] = new complex[l];
        }
        for (int i=0; i<c; i++){
            for (int j=0; j<l; j++){
                v[i][j]=complex(0,0);
            }
        }
    };
    matrice_oarecare(const matrice_oarecare& m){ //copy constructor
        lin = m.lin;
        col = m.col;
        v = new complex*[m.col];
        for (int i=0l;i<m.col; i++){
            v[i] = new complex[m.lin];
        }
        for (int i=0; i<m.col; i++){
            for (int j=0; j<m.lin; j++){
                v[i][j] = m[i][j];
            }
        }
    };

    //set+get
    void setElement(int linie, int coloana, complex element){
        this->v[coloana][linie] = element;
    };

    complex getElement(int linie, int coloana){
        return this->v[coloana][linie];
    }

    int getLin(){return lin;}
    int getCol(){return col;}
    int setLin(int lin){this->lin=lin;}
    int setCol(int col){this->col=col;}
    //afisarea n obiecte (nu stiu daca trebuie facuta iterativ citirea a n obiecte)
    void afisare(){
        for (int i=0; i<col; i++){
           cout<<endl;
            for (int j=0; j<lin; j++){
                cout<<v[i][j]<<" ";
            }
        }
    };
    //citirea n obiecte
    void citire(istream& citire_in){
        cout<<"Introduceti dimensiunile matricei (coloane, apoi linii): "; cin>>lin>>col;
        v = new complex* [col];
        for (int i=0; i<col; i++){
            v[i] = new complex[lin];
        }
        cout<<"Introduceti elementele matricei"<<endl;
        for (int i=0; i<col; i++){
            for (int j=0; j<lin; j++){
                citire_in>>v[i][j];
            }
        }
    }
    //supraincarcare operatori [] << >> =
    complex* operator[](const int &idx) const{return v[idx];}

    friend ostream& operator<<(ostream& out, const matrice_oarecare& m){
            for (int i=0; i<m.col; i++){
                cout<<endl;
                for (int j=0; j<m.lin; j++){
                    out<<m[i][j]<<" ";
                }

            } return out;
    };

    matrice_oarecare& operator=(const matrice_oarecare& m){
        if (this!=&m){
            lin = m.lin;
            col = m.col;
            v = new complex*[m.col];
            for (int i=0l;i<m.col; i++){
                v[i] = new complex[m.lin];
            }
            for (int i=0; i<m.col; i++){
                for (int j=0; j<m.lin; j++){
                    v[i][j] = m[i][j];
                }
            }
        }
    };

//pentru fluxul de citire am alocat memorie in functia citire pentru ca daca incercam sa aloc memorie in interiorul functiei friend dadea eroare
    friend istream& operator>>(istream& citire_in, matrice_oarecare& m){
            m.citire(citire_in);
            return citire_in;
    }


//destructor
    ~matrice_oarecare(){
        for (int i=0; i<this->col; i++)
        {
            delete[] this->v[i];
        }
        delete[] this->v;
    };
};

//-----------------------------------------------------------------------------------------------------------------------------------------------
class matrice_patratica: public matrice{
private:
    int dim;
public:
    matrice_patratica():matrice(){}; //constructor fara parametri
    matrice_patratica(int d){ //constructor cu parametri
        dim = d;
        v = new complex*[d];
        for (int i=0; i<d; i++){
            v[i] = new complex[d];
        }
        for (int i=0; i<d; i++){
            for (int j=0; j<d; j++){
                v[i][j]=complex(0,0);
            }
        }
    }
    matrice_patratica(const matrice_patratica& m){ //copy constructor
        dim = m.dim;
        v = new complex*[m.dim];
        for (int i=0l;i<m.dim; i++){
            v[i] = new complex[m.dim];
        }
        for (int i=0; i<m.dim; i++){
            for (int j=0; j<m.dim; j++){
                v[i][j] = m[i][j];
            }
        }
    };

//set+get
    void setElement(int linie, int coloana, complex element){
        this->v[coloana][linie] = element;
    };


    complex getElement(int linie, int coloana){
        return this->v[coloana][linie];
    };

    int getDim(){return dim;}

    complex* operator[](const int &idx) const { return v[idx];}

//afisare
    void afisare(){
        for (int i=0; i<dim; i++){
           cout<<endl;
            for (int j=0; j<dim; j++){
                cout<<v[i][j]<<" ";
            }
        };
    }
//metoda care verifica daca matricea triunghiulara este diagonala
    void diagonala(){
        int c=0;
        for (int i=0; i<dim; i++){
            for (int j=0; j<dim; j++){
                if (i!=j){
                    if(v[i][j].getModul()==0){c+=0;}
                    else{c+=1;}
                }
            }
        }
        if(c==0){cout<<"\nMatricea triunghiulara este diagonala(elementele de sub/deasupra diagonalei principale sunt 0";}
        else{cout<<"\nMatricea nu este diagonala(elementele de sub/deasupra diagonalei nu sunt toate 0";}
    }

//citirea obiectelor
    void citire(istream& citire_in){
        cout<<"Introduceti dimensiunea matricei: "; cin>>dim;
        v = new complex* [dim];
        for (int i=0; i<dim; i++){
            v[i] = new complex[dim];
        }
        cout<<"Introduceti elementele matricei: "<<endl;
        for (int i=0; i<dim; i++){
            for (int j=0; j<dim; j++){
                citire_in>>v[i][j];
            }
        }
    }
//supraincarcari operatori
    matrice_patratica& operator=(const matrice_patratica& m){
        if (this!=&m){
            dim = m.dim;
            v = new complex*[m.dim];
            for (int i=0l;i<m.dim; i++){
                v[i] = new complex[m.dim];
            }
            for (int i=0; i<m.dim; i++){
                for (int j=0; j<m.dim; j++){
                    v[i][j] = m[i][j];
                }
            }
        }
    };

    friend ostream &operator<<(ostream& out, const matrice_patratica & m){
            for (int i=0; i<m.dim; i++){
            cout<<endl;
            for (int j=0; j<m.dim; j++){
                out<<m[i][j]; cout<<" ";
            }

        } return out;
    };
//pentru fluxul de citire am alocat memorie in functia citire pentru ca daca incercam sa aloc memorie in interiorul functiei friend dadea eroare
    friend istream& operator>>(istream& citire_in, matrice_patratica& m){
          m.citire(citire_in);
          return citire_in;
    };
//destructor
    ~matrice_patratica(){
        for (int i; i<this->dim; i++){
            delete[] this->v[i];
        }
        delete[] this->v;
    }

};
//functie pentru a calcula determinantul -- neterminata
float calculDeterminant(matrice_patratica &v, int d)
{
        int det = 0;
        d = v.getDim();
        matrice_patratica submatrix = matrice_patratica(d);
        if (d==1) {return v[0][0].getModul();}
        if (d==2) {return ((v[0][0].getModul()*v[1][1].getModul())-(v[1][0].getModul()*v[0][1].getModul()));}
        else {
//            for (int x=0; x<d; x++){
//                int subi=0;
//                for (int i=1; i<d; i++){
//                    int subj=0;
//                    for (int j=0; j<d; j++){
//                        if (j==x)
//                            continue;
//                            submatrix[subi][subj] = v[i][j];
//                            subj++;
//                    }
//                    subi++;
//                }
//            det=det+(pow(-1, x)*v[0][x].getModul()*calculDeterminant(submatrix,d-1));
//            }
// cod inspirat de https://www.tutorialspoint.com/cplusplus-program-to-compute-determinant-of-a-matrix
// din pacate nu am reusit sa fac varianta recursiva se functioneze asa ca am comentat-o
            cout<<"programul nu poate calcula pt n>=3         ";
        }
        return det;
};


//-----------------------------------------------------------------------------------------------------------------------------------------------
int main()
{
    matrice* lista_matrice[100];
    //meniu switch case
    int k=1;
    int i=0;
    while (k==1){
        cout<<"Cherim Erol 141 Info - Tema 10 clasele matrice, matrice_oarecare, matrice_patratica"<<endl;
        cout<<"\nMeniu interactiv";
        cout<<"\n1 Creati o matrice oarecare";
        cout<<"\n2 Creati o matrice patratica";
        cout<<"\n10 Terminare program"<<endl;
        int comanda;
        cin>>comanda;

        switch(comanda){

            case 1:{
                lista_matrice[i] = new matrice_oarecare;
                cin>>static_cast<matrice_oarecare&>(*(lista_matrice[i])); //ilustrare upcasting explicit de la matrice > matrice_oarecare
                cout<<"\n Matricea oarecare a fost adaugata cu succes";
                int num;
                cout<<"\n Doriti sa afisati matricea?";
                cout<<"\n 1 Da";
                cout<<"\n 2 Nu(revenire la meniul principal)"<<endl;
                cin>>num;
                switch(num){
                    case 1:{
                        lista_matrice[i]->afisare();
                        lista_matrice[i]->diagonala();
                    }
                    case 2:{
                        break;
                    }
                }
                i++;
                break;
            }
            case 2:{
                matrice_patratica mp1;
                cin>>mp1;
                matrice *pm1 = dynamic_cast<matrice*>(&mp1); //ilustrare downcasting de la matrice_patratica > matrice
                lista_matrice[i] = pm1;
                cout<<"\n Matricea patratica a fost adaugata cu succes.";
                cout<<"\n Doriti sa afisati matricea?";
                cout<<"\n 1 Da";
                cout<<"\n 2 Nu(revenire la meniul principal)"<<endl;
                int num1;
                cin>>num1;
                switch(num1){
                    case 1:{
                        lista_matrice[i]->afisare();
                        lista_matrice[i]->diagonala();
                        cout<<"\nDeterminantul este: "<<calculDeterminant(mp1, mp1.getDim());
                    }
                    case 2:{
                        break;
                    }
                }
                i++;
                break;
                break;
            }
            case 10:{
                k=0;
                break;
            }
        }
    }
    return 0;
};
