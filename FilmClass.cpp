#include <iostream>
#include <cstdlib>
#include <string.h>

using namespace std;

class film
{

private:
    char denumire_film[30];
    char gen_film[20];
    char regizor_film[30];
    float rating_film;

public:
    film();
    film(char*, char*, char*, float); ///constructor initializare
    film(const film&); ///constructor copiere
    ~film(); ///destructor;
    void set_denumire(char*); ///set denumire
    void set_gen(char*); ///set gen
    void set_regizor(char*); ///set regizor
    void set_rating(float); ///set rating
    char* get_denumire(){return this->denumire_film;}; ///get denumire
    char* get_gen(){return this->gen_film;}; ///get gen
    char* get_regizor(){return this->regizor_film;}; ///get regizor
    float get_rating(){return this->rating_film;}; ///get rating
    void citire();
    void afisare();
    friend istream& operator>>(istream&, film&); ///supraincarcare pe >>
    friend ostream& operator<<(ostream&, film&); ///supraincarcare pe <<
    film& operator=(const film& FILM); ///supraincarcare pe =
    film& operator[](int index);
    int operator>(film& FILM2); ///supraincarcare pe >
    int operator<(film& FILM2); ///supraincarcare pe <

};

film::film()
{
    strcpy(denumire_film,"");
    strcpy(gen_film,"");
    strcpy(regizor_film,"");
    this->rating_film = 0.0;
}

film::film(char den_film[30], char gen[20], char reg_film[30], float rate_film)
{
    //this->denumire_film = new char[256];
    strcpy(this->denumire_film,den_film);
    //this->gen_film = new char[256];
    strcpy(this->gen_film,gen);
    //this->regizor_film = new char[256];
    strcpy(this->regizor_film,reg_film);
    this->rating_film=rate_film;
}

film::film(const film& FILM)
{
    //this->denumire_film = new char[256];
    strcpy(this->denumire_film,FILM.denumire_film);
    //this->gen_film = new char[256];
    strcpy(this->gen_film,FILM.gen_film);
    //this->regizor_film = new char[256];
    strcpy(this->regizor_film,FILM.regizor_film);
    this->rating_film=FILM.rating_film;
}

film::~film()
{
    delete []denumire_film;
    delete []gen_film;
    delete []regizor_film;
    rating_film = 0.0;
    cout<<"Destructor"<<endl;
}

void film::citire()
{
    cout << "Numele filmului este: "; cin >> denumire_film; cout << endl;
    cout << "Genul filmului este: "; cin >> gen_film; cout << endl;
    cout << "Filmul este regizat de: "; cin >> regizor_film; cout << endl;
    cout << "Ratingul filmului (imdb) este: "; cin >> rating_film; cout << endl;

    cout << denumire_film << endl << gen_film << endl << regizor_film << endl << rating_film << endl;
}

istream& operator>>(istream& in, film &FILM)
{
    cout << "Numele filmului este: "; in >> FILM.denumire_film; cout << endl;
    cout << "Genul filmului este: "; in >> FILM.gen_film; cout << endl;
    cout << "Filmul este regizat de: "; in >> FILM.regizor_film; cout << endl;
    cout << "Ratingul filmului (imdb) este: "; in >> FILM.rating_film; cout << endl;
    return in;
}

void film::afisare()
{
    //if(denumire_film != '\n')
        cout << "Filmul " << denumire_film;
    //if(gen_film != '\n')
        cout << " de genul " << gen_film << ",";
    //if(regizor_film != '\n')
        cout << " este regizat de " << regizor_film;
    //if(rating_film != 0.0)
        cout << " si are urmatorul rating: " << rating_film;
        cout << endl;
}

ostream& operator <<(ostream& out, film& FILM)
{
    //if(denumire_film != '\n')
        out << "Filmul " << FILM.denumire_film;
    //if(gen_film != '\n')
        out << " de genul " << FILM.gen_film << ",";
    //if(regizor_film != '\n')
        out << " este regizat de " << FILM.regizor_film;
    //if(rating_film != 0.0)
        out << " si are urmatorul rating: " << FILM.rating_film;
        out << endl;
    return out;
}

void film::set_denumire(char denumire[30])
{
    strcpy(this->denumire_film,denumire);
}
void film::set_gen(char gen[20])
{
    strcpy(this->gen_film,gen);
}
void film::set_regizor(char regizor[30])
{
    strcpy(this->regizor_film, regizor);
}
void film::set_rating(float rating)
{
    this->rating_film = rating;
}

film& film::operator=(const film& FILM)
{
    //this->denumire_film=new char[256];
    strcpy(this->denumire_film,FILM.denumire_film);
    //this->gen_film=new char[256];
    strcpy(this->gen_film,FILM.gen_film);
    //this->regizor_film=new char[256];
    strcpy(this->regizor_film,FILM.regizor_film);
    this->rating_film=FILM.rating_film;
}

film& film::operator[](int index)
{
    return this[index];
}

int film::operator>( film& FILM2)
{
    return this->rating_film>FILM2.rating_film;
}

int film::operator<(film& FILM2)
{
   return this->rating_film<FILM2.rating_film;
}

int main()
{
    int choice, nr;
    film *F;

    do{
        cout << " Sunt posibile urmatoarele alegeri: " << endl;
        cout << " 1 - Adaugare film \n" << " 2 - Afisare filme \n" << " 3 - Compararea a doua filme \n" << " 4 - Modificarea informatiilor unui film \n" << " 5 - Iesire \n" << endl;
        cout << " Introduceti alegerea: ";
        cin >> choice;
        cout << endl;

        switch(choice)
        {
        case 1: ///adaugarea filmelor
            {
            cout << "Numarul de filme pe care doresti sa le introduci: ";
            cin >> nr;
            cout << "Adaugati informatiile referitoare la film \n";
            film *vect = new film[nr+1];
            for(int i = 1; i <= nr; i++)
            {
                cin >> vect[i];
            }
            F = vect;
            }
            break;
        case 2: ///afisarea filmelor
            {
                if(nr != 0)
                    for(int i = 1; i <= nr; i++)
                {cout << "Filmul cu indexul " << i <<endl ; cout << F[i]; cout << " ~~~~~~~~~~~~~~~~~~ \n";}
            }
            break;
        case 3: ///compararea filmelor
            {
            if(nr < 2)
                {cout << "Numarul de filme introduse este insuficient pentru comparare. \n"; break;}
            cout << "Indecsii aferenti filmelor dorite comparate sunt: ";
            int a, b;
            cin >> a >> b;
            if(F[a] > F[b])
                cout << "Filmul " << F[a].get_denumire() << " are un rating mai bun decat " << F[b].get_denumire()<< endl;
            else if(F[a] < F[b])
                cout << "Filmul " << F[b].get_denumire() << " are un rating mai bun decat " << F[a].get_denumire() << endl;
            else cout << "Filmele " << F[a].get_denumire() << " si " << F[b].get_denumire() << " au acelasi rating. \n";
            }
            break;
        case 4: ///modificarea informatiilor unui film
            {
                int n;
                char *K, *Z;
                float W;
                cout << "Ce film doriti sa modificati? Tastati indexul acestuia. \n";
                cin >> n;
                cout << "Ce doriti sa modificati dintre informatiile despre film? Tastati denumire/ regizor/ gen/ rating. \n";
                                                                                /// strlen= 8    strlen= 7     strlen= 6
                cin >> K;
                if(strlen(K)==8)
                {
                    cout << "Noua denumire va fi: ";
                    cin >> Z;
                    F[n].set_denumire(Z);
                }
                else if(strlen(K)==7)
                {
                    cout << "Noul regizor va fi: ";
                    cin >> Z;
                    F[n].set_regizor(Z);
                }
                else if(strlen(K)==6)
                {
                    cout << "Noul rating va fi: ";
                    cin >> W;
                    F[n].set_rating(W);
                }
                else
                {
                    cout << "Noul gen va fi: ";
                    cin >> Z;
                    F[n].set_gen(Z);
                }
                cout << "Noile informatii sunt: ";
                cout << F[n];
                cout << endl;
            }
            break;
        case 5:
            return 1;
        default:
            cout << "Numarul tastat nu face parte din meniu. \n";
            break;
        }
        }while(choice != 5);
        delete []F;
    return 0;
}
