#include <iostream>
using namespace std;


class Nod
{
protected:
	int info;
	Nod *next;
public:
    Nod(int, Nod*); ///constructor
	Nod(const Nod &); ///constructor de copiere
	~Nod(){}; ///destructor
	virtual void citire(istream &in);
    virtual void afisare(ostream &out);
    friend istream &operator>>(istream &, Nod &);
    friend ostream &operator<<(ostream &, Nod &);
	Nod &operator=(Nod &);
	friend class Lista;
	friend class Lista_Circulara;
};

Nod::Nod(int i = 0, Nod *n = NULL)
{
	info = i;
	next = n;
}

Nod::Nod(const Nod &n)
{
	this->info = n.info;
	this->next = n.next;
}

void Nod::citire(istream &in)
{
	in >> info;
}

istream &operator>>(istream &in, Nod &n)
{
	n.citire(in);
	return in;
}

void Nod::afisare(ostream &out)
{
	out << info;
}

ostream &operator<<(ostream &out, Nod &n)
{
	n.afisare(out);
	return out;
}

Nod &Nod::operator=(Nod &n)
{
	info = n.info;
	next = n.next;
}

///----------------------------------------------------------------------------

class Nod_dublu:public Nod
{
protected:
	Nod *ante;
public:
	Nod_dublu(int, Nod *, Nod *); ///constructor
	Nod_dublu(const Nod_dublu &); ///constructor de copiere
	virtual void citire(istream &in);
	virtual void afisare(ostream &out);
	friend istream &operator<<(istream &, Nod_dublu &);
	friend ostream &operator>>(ostream &, Nod_dublu &);
	Nod_dublu &operator=(Nod_dublu &);
	~Nod_dublu(){} ///destructor
	friend class Lista;
	friend class Lista_Circulara;
};

Nod_dublu::Nod_dublu(int i = 0, Nod *n = NULL, Nod *nd = NULL):Nod(i, n)
{
    ante = nd;
}

Nod_dublu::Nod_dublu(const Nod_dublu &nd):Nod(nd)
{
    this->ante = nd.ante;
}

void Nod_dublu::citire(istream &in)
{
	Nod::citire(in);
}

istream &operator>>(istream &in, Nod_dublu &nd)
{
	nd.citire(in);
	return in;
}

void Nod_dublu::afisare(ostream &out)
{
	Nod::afisare(out);
}

ostream &operator<<(ostream &out, Nod_dublu &nd)
{
	nd.afisare(out);
	return out;
}

Nod_dublu &Nod_dublu::operator=(Nod_dublu &nd)
{
	Nod::operator=(nd);
	ante = nd.ante;
}

///----------------------------------------------------------------------------

class Lista:public Nod_dublu
{
protected:
	Nod_dublu *head;
	Nod_dublu *tail;
public:
	Lista(int, Nod *, Nod*, Nod_dublu *, Nod_dublu *); ///constructor
	Lista(const Lista &); ///constructor de copiere
	~Lista(){} ///destructor
	virtual void citire(istream &in);
	virtual void afisare(ostream &out);
	friend istream &operator<<(istream &, Lista &);
	friend ostream &operator>>(ostream &, Lista &);
	Lista &operator=(Lista &);
	virtual void insert_end();
	virtual void insert_front();
    void dimensiune();
	friend class List_Circulara;
};

Lista::Lista(int i = 0, Nod *n = NULL, Nod *nd = NULL, Nod_dublu *start = NULL, Nod_dublu *endd = NULL):Nod_dublu(i, n, nd)
{
    head = start;
    tail = endd;
}

Lista::Lista(const Lista &l):Nod_dublu(l)
{
    this->head = l.head;
    this->tail = l.tail;
}

Lista &Lista::operator=(Lista &l)
{
	Nod_dublu::operator=(l);
	head = l.head;
	tail = l.tail;
}

void Lista::citire(istream &in)
{
    cout << " Introduceti elementul : ";

    int elem;
    in >> elem;
    Nod_dublu *temp = new Nod_dublu;
    if (head == NULL)
    {
        head = temp;
        temp->ante = NULL;
        temp->info = elem;
        temp->next = NULL;
        tail = temp;
    }
    else
    {
        temp->info = elem;
        temp->ante = tail;
        tail->next = temp;
        tail = temp;
    }
}

istream &operator>>(istream &in, Lista &l)
{
	l.citire(in);
	return in;
}

void Lista::afisare(ostream &out)
{
	Nod *temp;
	temp = head;
	if(temp == NULL)
        out << " Lista este vida." << endl;
	else{
        out << " Lista este urmatoarea: [";
        while(temp != NULL)
	{
		out << " " << *temp;
		temp = temp->next;
	}
	out << " ]" << endl;}
	out << endl;
}

ostream &operator<<(ostream &out, Lista &l)
{
	l.afisare(out);
	return out;
}

void Lista::insert_end()
{
    cout << " Introduceti elementul nou pe care doriti sa il inserati: ";

    int val; cin >> val;
    Nod_dublu *temp = new Nod_dublu;
    temp->info = val;
    temp->ante = tail;
    tail->next = temp;
    tail = temp;

    cout << endl;
}

void Lista::insert_front()
{
    cout << " Introduceti elementul nou pe care doriti sa il inserati: ";

    int val; cin >> val;
    Nod_dublu *temp = new Nod_dublu;
    temp->next = head;
    temp->info = val;
    temp->ante = NULL;
    head->ante = temp;
    head = temp;

    cout << endl;
}

void Lista::dimensiune()
{
    Nod *temp = head;
    int nr_elem = 0;
    while(temp != NULL)
    {
        temp = temp->next;
        nr_elem++;
    }
    cout << " Lista are " << nr_elem << " elemente." << endl;
    cout << endl;
}

///----------------------------------------------------------------------------

class Lista_Circulara:public Lista
{
private:
    Lista *Begin;
    Lista *End;
public:
    Lista_Circulara();
    Lista_Circulara(const Lista_Circulara &);
    ~Lista_Circulara(){}
    void citire(istream &in);
	void afisare(ostream &out);
	friend istream &operator<<(istream &, Lista_Circulara &);
	friend ostream &operator>>(ostream &, Lista_Circulara &);
	Lista_Circulara &operator=(Lista_Circulara &);
	void insert_end();
	void insert_front();
	int dimensiune();
	void Problema_Josephus(int, int, int);
};

Lista_Circulara::Lista_Circulara()
{
    Begin = NULL;
    End = NULL;
}

Lista_Circulara::Lista_Circulara(const Lista_Circulara &l)
{
    this->Begin = l.Begin;
    this->End = l.End;
}

Lista_Circulara &Lista_Circulara ::operator=(Lista_Circulara &l)
{
	this->Begin = l.Begin;
    this->End = l.End;
}

void Lista_Circulara::citire(istream &in)
{
    cout << " Introduceti elementul : ";

    int elem;
    in >> elem;
    Lista *temp = new Lista;
    if (Begin == NULL)
    {
        Begin = temp;
        temp->ante = NULL;
        temp->info = elem;
        temp->next = NULL;
        End = temp;
        Begin->ante = End;
        End->next = Begin;
    }
    else
    {
        temp->info = elem;
        temp->ante = End;
        End->next = temp;
        End = temp;
        Begin->ante = End;
        End->next = Begin;
    }
}

istream &operator>>(istream &in, Lista_Circulara &l)
{
	l.citire(in);
	return in;
}

void Lista_Circulara::afisare(ostream &out)
{
    Nod *temp = new Nod;
	temp = Begin;
	Nod_dublu *temp2 = new Nod_dublu;
	temp2 = End;
    if(temp == NULL)
        out << " Lista este vida." << endl;
    else
    {
	out<<" Lista circulara este urmatoarea: [";
	if(Begin != NULL)
	{
	    while(temp != temp2){
		out << temp->info  << " -> ";
		temp = temp->next;}
		out << End->info;
	}
	out << "]" << endl;
	out << " Succesorul lui " << End->info << " este " << Begin->info << ", iar predecesorul lui " << Begin->info << " este " << End->info << "." <<endl;}
	out << endl;
}

ostream &operator<<(ostream &out, Lista_Circulara &l)
{
	l.afisare(out);
	return out;
}

void Lista_Circulara::insert_end()
{
    cout << " Introduceti elementul nou pe care doriti sa il inserati: ";

    int val; cin >> val;
    Lista *temp = new Lista;
    temp->info = val;
    temp->ante = End;
    End->next = temp;
    End = temp;

    cout << endl;
}

void Lista_Circulara::insert_front()
{
    cout << " Introduceti elementul nou pe care doriti sa il inserati: ";

    int val; cin >> val;
    Lista *temp = new Lista;
    temp->next = Begin;
    temp->info = val;
    temp->ante = NULL;
    Begin->ante = temp;
    Begin = temp;

    cout << endl;
}

int Lista_Circulara::dimensiune()
{
    Nod *temp = Begin;
    int nr_elem = 0;
    while(temp != NULL)
    {
        temp = temp->next;
        nr_elem++;
    }

    return nr_elem;
}

void Lista_Circulara::Problema_Josephus(int x, int y, int z)
{
    int poz[1000];
    for(int i=1; i<=x; i++)
    poz[i] = i;
    Lista *temp2 = new Lista;
    temp2 = Begin;
    Nod *temp = temp2;
    cout << " Au fost eliminati urmatorii: " << endl;
    int b = y;
    while(b > 1)
    {
        temp = temp->next;
        b--;
    }
    cout << temp->info << " ";
    for(int j=y; j<x; j++)
        poz[j] = poz[j+1];
    x--;
    int c = x; ///am decrementat nr pozitiilor
    y = y + z -1;
    while(c != 0) ///cat timp nu mai avem pozitii de parcurs
    {
        //c = c - z;
        int a = z;
        while(a != 0)
        {
            temp = temp->next;
            a--;
        }
        cout << temp->info << " ";
        for(int j=y; j<c; j++)
            poz[j] = poz[j+1];
        y = y + z; c--;
    }
}

///----------------------------------------------------------------------------

int main()
{
	Lista L; int choice; Lista_Circulara W;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
	cout << " Vom lucra cu o lista dublu inlantuita. " << endl;
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    do{
        cout << " Sunt posibile urmatoarele alegeri: " << endl;
        cout << " 1. Creare lista dublu inlantuita" << endl;
        cout << " 2. Afisare lista " << endl;
        cout << " 3. Adaugare element la inceput " << endl;
        cout << " 4. Adaugare element la sfarsit " << endl;
        cout << " 5. Numarul de elemente ale listei " << endl;
        cout << " 6. Crearea unei liste circulare " << endl;
        cout << " 7. Iesire " << endl;
        cout << " Introduceti alegerea din meniu: ";
        cin >> choice;
        cout << endl;

        switch(choice)
        {
        case 1: ///creare lista
            {
                cout << " Introduceti numarul de elemente pe care doriti sa le inserati in lista: ";
                int nr;
                cin >> nr;
                for (int i = 0; i < nr; i++)
                {
                    cin >> L;}
                    cout << endl;
            }
            break;
        case 2: ///afisare lista
            {
                cout << L;
            }
            break;
        case 3: ///inserare in fata
            {
                L.insert_front();
            }
            break;
        case 4: ///inserare la sfarsit
            {
                L.insert_end();
            }
            break;
        case 5: ///afisarea dimensiunii
            {
                L.dimensiune();
            }
            break;
        case 6: ///lista circulara
            {
                Lista_Circulara Lc;
                cout << " Introduceti numarul de elemente pe care doriti sa le inserati in lista circulara: ";
                int nr;
                cin >> nr;
                for (int i = 0; i < nr; i++)
                {
                    cin >> Lc;
                }
                cout << endl;
                int choice2;
                do{
                cout << " Ce doriti sa faceti mai departe? " << endl;
                cout << " 1. Adaugare element la inceput " << endl;
                cout << " 2. Adaugare element la final " << endl;
                cout << " 3. Afisare dimensiune lista circulara " << endl;
                cout << " 4. Afisare lista " << endl;
                cout << " 5. Problema Josephus " << endl;
                cout << " 6. Iesire " << endl;
                cout << " Tastati alegerea: ";
                cin >> choice2;
                cout << endl;
                //do{
                switch(choice2)
                {
                case 1: ///inserare la inceput
                    {
                        Lc.insert_front();
                    }
                    break;
                case 2: ///inserare la final
                    {
                       Lc.insert_end();
                    }
                    break;
                case 3: ///dimensiunea listei
                    {
                        cout << " Lista circulara are " << Lc.dimensiune() << " elemente." << endl;
                        cout << endl;
                    }
                    break;
                case 4: ///afisare
                    {
                        cout << Lc;
                        cout << endl;
                    }
                    break;
                case 5:
                    {
                        cout << " Urmeaza prezentarea rezolvarii problemei lui Josephus "  << endl;
                        int n = Lc.dimensiune();
                        cout << " Avem " << n << " pozitii." << endl;
                        cout << " Adaugati pozitia de start (cea de pe care se va pleca): ";
                        int k; cin >> k; cout << endl;
                        cout << " Adaugati valoarea saltului (numarul de pozitii peste care se va sari de fiecare data: ";
                        int m; cin >> m; cout << endl;
                        Lc.Problema_Josephus(n, k, m);
                    }
                    break;
                case 6: ///iesire
                    break;
                }}while(choice2 != 6);
            }
            break;
        case 7: ///iesire
            return 1;
            break;
        default:
            cout << " Numarul tastat nu face parte din meniul prezentat." << endl;
            cout << endl;
            break;
        }
    }while(choice != 7);
	return 0;
}
