///TEMA3


#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <vector>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>
using namespace std;


///--------------------------------------------------------------------EXAM
class Exam
{
protected:
    static int index;
    int id; ///numarul examenului
    string subject; ///denumirea materiei
    double mark; ///nota scris
public:
    Exam(string, double);
    Exam(const Exam &);
    ~Exam();

    virtual void read(istream &in);
    virtual void show(ostream &out);
    friend istream &operator>>(istream &, Exam &);
    friend ostream &operator<<(ostream &, Exam &);
    Exam &operator=(const Exam &);

    void setSubject(string name){subject=name;}
    string getSubject(){return this->subject;}
    int getId() const;
    friend class Student;
};
int Exam::index=1;
Exam::Exam(string s=" ", double m=0.0)
{
    subject=s;
    mark=m;
}
Exam::Exam(const Exam &E)
{
    index=E.index;
    subject=E.subject;
    mark=E.mark;
}
Exam::~Exam()
{
    index=0;
    subject=" ";
    mark=0.0;
}
void Exam::read(istream &in)
{
    cout<< "Examenul la "<< getSubject()<< endl;
    cout<< "Id examen: "<< getId()<< "\n";;
    cout<< "Nota obtinuta la examenul scris: "; in>> mark;
}
void Exam::show(ostream &out)
{
    out<< "Examenul la "<< getSubject()<< ".\n";
    out<< "Nota la scris "<< mark<< ".";
    out<< endl;
}
istream &operator>>(istream &in, Exam &E)
{
    E.read(in);
    return in;
}
ostream &operator<<(ostream &out, Exam &E)
{
    E.show(out);
    return out;
}
Exam &Exam::operator=(const Exam &E)
{
    index=E.index;
    subject=E.subject;
    mark=E.mark;
}
int Exam::getId() const
{
    return this->index++;
}


///----------------------------------------------------------------------PARTIAL
class Partial:public Exam
{
protected:
    double oral_mark; ///nota oral
    double partial_mark; ///nota partial
public:
    Partial(string, double, double, double);
    Partial(const Partial &);
    ~Partial();

    void read(istream &in);
    void show(ostream &out);
    friend istream &operator>>(istream &, Partial &);
    friend ostream &operator<<(ostream &, Partial &);
    Partial &operator=(const Partial &);

    double get_oralMark() const {return this->oral_mark;}
    double getpartialGrade(double) const;
};
Partial::Partial(string s=" ", double m=0.0, double o_m=0.0, double p_m=0.0):Exam(s,m)
{
    oral_mark=o_m;
    partial_mark=p_m;
}
Partial::Partial(const Partial &P)
{
    oral_mark=P.oral_mark;
    partial_mark=P.partial_mark;
}
Partial::~Partial()
{
    oral_mark=0.0;
    partial_mark=0.0;
}
void Partial::read(istream &in)
{
    Exam::read(in);

    cout<< "Nota obtinuta la proba orala: ";
    in>> oral_mark;
    cout<< "Nota obtinuta la partial: ";
    in>> partial_mark;
}
void Partial::show(ostream &out)
{
    Exam::show(out);

    out<< "Nota la partial "<< getpartialGrade(0.0)<< "."<< endl;
}
istream &operator>>(istream &in, Partial &P)
{
    P.read(in);
    return in;
}
ostream &operator<<(ostream &out, Partial &P)
{
    P.show(out);
    return out;
}
Partial &Partial::operator=(const Partial &P)
{
    oral_mark=P.oral_mark;
    partial_mark=P.partial_mark;
}
double Partial::getpartialGrade(double x) const
{
    double partialResult;
    if(x==0.0)
        partialResult=(oral_mark+partial_mark)/2;
    else
        partialResult=(oral_mark+x)/2;
    return partialResult;
}


///------------------------------------------------------------FINALEXAM
class FinalExam:public Partial
{
protected:
    double project_mark; ///nota proiect
    double final_grade; ///nota FINALA
public:
    FinalExam(string, double, double, double, double, double);
    FinalExam(const FinalExam &);
    ~FinalExam();

    void read(istream &in);
    void show(ostream &out);
    friend istream &operator>>(istream &, FinalExam &);
    friend ostream &operator<<(ostream &, FinalExam &);
    FinalExam &operator=(const FinalExam &);
    //friend ostream& operator<<(ostream &, const FinalExam &);

    double setfinalGrade(double,double,double);
};
FinalExam::FinalExam(string s=" ", double m=0.0, double o_m=0.0, double p_m=0.0, double pm=0.0, double f_g=0.0):Partial(s,m,o_m,p_m)
{
    project_mark=pm;
    final_grade=f_g;
}
FinalExam::FinalExam(const FinalExam &FE)
{
    project_mark=FE.project_mark;
    final_grade=FE.final_grade;
}
FinalExam::~FinalExam()
{
    project_mark=0.0;
    final_grade=0.0;
}
void FinalExam::read(istream &in)
{
    Partial::read(in);

    cout<< "Nota obtinuta la proiect: ";
    in>> project_mark;
    cout<< endl;
}
void FinalExam::show(ostream &out)
{
    Partial::show(out);

    out<< "Nota obtinuta la proiect "<< project_mark<< ". \n";
    out<< endl;
    out<< "Asadar, nota finala la "<< getSubject()<< " este "<< setfinalGrade(0.0,0.0,0.0)<< "."<< endl;
}
istream &operator>>(istream &in, FinalExam &FE)
{
    FE.read(in);
    return in;
}
ostream &operator<<(ostream &out, FinalExam &FE)
{
    FE.show(out);
    return out;
}
/*ostream& operator<<(ostream& os, const FinalExam& ob)
{
    os<< ob;
}*/
FinalExam &FinalExam::operator=(const FinalExam &FE)
{
    project_mark=FE.project_mark;
    final_grade=FE.final_grade;
}
double FinalExam::setfinalGrade(double x, double z, double part)
{
    ///40%partial+60%scris+bonus proiect
    ///x-quiz
    ///z-examen scris
    ///part-partial

    if(part==0.0)
    {
        if(z==0)
            final_grade=0.40*getpartialGrade(0.0)+0.60*mark+0.10*project_mark+x;
        else
            final_grade=0.40*getpartialGrade(0.0)+0.60*z+0.10*project_mark+x;
    }
    else
    {
        if(z==0)
            final_grade=0.40*part+0.60*mark+0.10*project_mark+x;
        else
            final_grade=0.40*part+0.60*z+0.10*project_mark+x;
    }

    if(this->final_grade>10)
        return 10;
    else
        return this->final_grade;
}


///---------------------------------------------------------------QUIZ
class Quiz
{
private:
    const int nrItems;
    double grade;
public:
    Quiz(int it):nrItems(it){grade=0;}
    ~Quiz(){int nrItems=0;}

    void read(istream &in);
    void show(ostream &out);
    friend istream &operator>>(istream &, Quiz &);
    friend ostream &operator<<(ostream &, Quiz &);

    double getquizGrade() const;
};
void Quiz::read(istream &in)
{
    cout<< "Marirea este compusa din " <<nrItems <<" intrebari de tip grila. \n";
    cout<< "Introduceti nota de la quiz (numar natural): ";
    cin>> grade;
    if(grade>=11)
    {
        cout<< "Nota maxima este 10.\nIntroduceti din nou nota de la quiz (numar natural): ";
        cin>> grade;
    }
    else if(grade<0)
    {
        cout<< "Nota minima este 0. Nota introdusa nu este un numar natural.\nIntroduceti din nou nota de la quiz (numar natural): ";
        cin>> grade;
    }
}
void Quiz::show(ostream &out)
{
    if(getquizGrade()>0)
        out<< "Nota de la quiz reprezinta "<< getquizGrade()<< " puncte bonus care se vor adauga la nota finala. ";
    else
        out<< "Nota de la quiz reprezinta "<< getquizGrade()<< " puncte bonus. In acest caz, nota finala nu se va modifica. ";
    out<< endl;
}
istream &operator>>(istream &in, Quiz &Q)
{
    Q.read(in);
    return in;
}
ostream &operator<<(ostream &out, Quiz &Q)
{
    Q.show(out);
    return out;
}
double Quiz::getquizGrade() const
{
    double result;
    result=grade*0.20;
    return result;
}


///--------------------------------------------------------STUDENT
class Student
{
protected:
    FinalExam *f;
    int nrExams;
    string studName;

    set<string> subjectName;
    /*vector<int> finalExams; ///denumire materii cu nota finala<5 a studentului in cauza
    unordered_map<string, string> failedFExams;*/

    vector<string> N;
    unordered_map<string,vector<string>> failedN;

    vector<double> finalGrades;
    vector<double> writtenExams;
    vector<double> partialGrades;
    vector<double> modifiedFGrades;
    vector<double> quizGrades;
    vector<string> answers;

public:
    Student(FinalExam*, int, string);
    Student(const Student&);
    ~Student();

    void read(istream &in);
    void show(ostream &out);
    friend istream &operator>>(istream&, Student&);
    friend ostream &operator<<(ostream&, Student&);
    Student &operator==(Student &);
    //friend ostream &operator<<(ostream &, Student&);

    void set_nrExams(int y){nrExams=y;}
    int get_nrExams()const {return this->nrExams;}
    string getName()const {return this->studName;}
    void FFinalExams(Student &);
    void showFFinalExams(Student &);
    void compareforQuiz(Student &);
    void compareforPartial(Student &);
    void compareforFinal(Student &);
    void finalsReplacement(Student &);
    int nrfailedFExams();
    int nrfailedPExams();
    void addName(string);
};
Student::Student(FinalExam *F=NULL, int nr=0, string name=" ")
{
    nrExams=nr;
    f=new FinalExam[get_nrExams()];
    for(int i=0; i<get_nrExams(); i++)
        f[i]=F[i];
    studName=name;
}
Student::Student(const Student &s)
{
    nrExams=s.nrExams;
    f=new FinalExam[get_nrExams()];
    for(int i=0; i<get_nrExams(); i++)
    f[i]=s.f[i];
    studName=s.studName;
}
Student::~Student()
{
    delete [] f;
}
void Student::read(istream &in)
{
    cout<< "Introduceti numele de familie al studentului: ";
    in>> studName; cout<< endl;
    f=new FinalExam[get_nrExams()];
    int i=0;
    for(set<string>::iterator it=subjectName.begin(); it!=subjectName.end(); it++)
    {
        f[i].setSubject(*it);
        in>>f[i];
        i++;
    }
}
void Student::show(ostream &out)
{
    if(get_nrExams()==1)
        out<< "Nota finala a examenului dat de catre "<< studName<< " este compusa din:\n";
    else
        out<< "Notele finale ale examenelor date de catre "<< studName<< " sunt compuse din:\n";
    out<< endl;
    for(int i=0; i<get_nrExams(); i++)
    {
        out<< f[i]<< "\n";
    }
}
istream &operator>>(istream& in, Student& s)
{
    s.read(in);
    return in;
}
ostream &operator<<(ostream& out, Student& s)
{
    s.show(out);
    return out;
}
/*ostream& operator<<(ostream& os, const Student& ob)
{
    os<< ob;
}*/
void Student::compareforQuiz(Student &s)
{
    Quiz quiz(10); string answer; double quiz_mark;

    for(int i=0; i<s.get_nrExams(); i++)
    {
        if(s.f[i].setfinalGrade(0.0,0.0,0.0)>=5 && s.f[i].setfinalGrade(0.0,0.0,0.0)<10)
        {
            cout<< "Studentul "<< s.getName()<< " doreste sa dea marire la "<< s.f[i].getSubject()<< "? Tastati doreste/nu: ";
            cin>> answer;
            if(answer.size()==7)
                {
                    cin>> quiz;
                    quiz_mark=quiz.getquizGrade();
                    cout<< quiz;
                    double result=s.f[i].setfinalGrade(quiz_mark,0.0,0.0);
                    cout<< "In urma quiz-ului, nota finala la "<< s.f[i].getSubject()<< " este "<< result<< ".\n";
                    quizGrades.push_back(result);
                }
            /*else if(answer.size()!=7 || answer.size()!=2)
            {
                cout<< "Tastati de data aceasta: doreste/nu. Daca studentul "<< s.getName()<< " nu doreste sa dea marire la "<< s.f[i].getSubject()
                    << " atunci tastati: nu.\n";
                cout<< "Alegerea dumneavoatra: ";
                cin>> answer;
                if(answer.size()==7)
                {
                    cin>> quiz;
                    quiz_mark=quiz.getquizGrade();
                    cout<< quiz;
                    double result=s.f[i].setfinalGrade(quiz_mark,0.0,0.0);
                    cout<< "In urma quiz-ului, nota finala la "<< s.f[i].getSubject()<< " este "<< result<< ".\n";
                    quizGrades.push_back(result);
                }
            }*/
                answers.push_back(answer);
            }
         else if (s.f[i].setfinalGrade(0.0,0.0,0.0)>=10)
            cout<< "Studentul "<< s.getName()<< " are deja nota maxima la "<< s.f[i].getSubject()<< ".\n";
        }

    cout<< endl;
}
void Student::compareforPartial(Student &s)
{
    double wp=0.0;
    for(int i=0; i<get_nrExams(); i++)
    {
        if(s.f[i].getpartialGrade(0.0)<5)
        {
            cout<< "Studentul "<< s.studName<< " va trebui sa refaca lucrarea scrisa a partialului la "<< s.f[i].subject<< ".\n";
            cout<< "Pentru a putea fi luata in considerare, media acesteia cu nota deja obtinuta la proba orala trebuie sa fie >=5.\n";
            cout<< "Altfel, va fi pastrata nota veche. Calculul ce urmeaza sa fie facut va folosi presupunerea ca nota adaugata "
                <<"va respecta ceea ce este scris chiar deasupra.\n";
            cout<< "Introduceti noua nota a acesteia: ";
            cin>> wp;
            double y=s.f[i].getpartialGrade(wp);
            if((s.f[i].get_oralMark()+wp)/2>=5)
                {
                    cout<< "Noua nota la partial este "<< y<< "."<< endl;
                    partialGrades.push_back(y);
                }
            else if(y>=0.0 && y<s.f[i].getpartialGrade(0.0))
                cout<< "Nota este mai mica decat cea de dinainte, asadar va fi pastrata cea veche.";
            cout<< endl;
        }
    }
}
void Student::compareforFinal(Student &s)
{
    double *v, we;
    v=new double[partialGrades.size()];
    vector<double>::iterator it;
    int sz=partialGrades.size();
    int j=0;
    for(int i=0; i<sz; i++)
        {
            it=partialGrades.begin();
            v[i]=(*it);
            partialGrades.erase(partialGrades.begin());
        }
    for(int i=0; i<get_nrExams(); i++)
    {
        if(s.f[i].getpartialGrade(0.0)<5) ///am presupus ca daca nota nemodificata a partialului e <5, atunci cu siguranta cea modificata e >=5
                                          ///(daca nota veche a partialului e <5, atunci aceasta sigur a fost modificata, deci urmeaza sa
                                          ///accesez in vector nota modificata)
        {
            if(s.f[i].setfinalGrade(0.0,0.0,v[j])<5)
            {
                cout<< "Deoarece in urma refacerii lucrarii partialului, studentul "<< s.studName<< " tot nu a reusit sa promoveze examenul ";
                cout<< "la "<< s.f[i].subject<< ", acesta va trebui sa refaca si partea scrisa a examenului care valoarea 60% din nota.\n";;
                cout<< "Introduceti noua nota a acesteia: ";
                cin>> we;
                double y=s.f[i].setfinalGrade(0.0,we,v[j]);
                if(y>s.f[i].setfinalGrade(0.0,0.0,v[j]))
                {
                    cout<< "Noua nota finala este "<< y<< "."<< endl;
                    finalGrades.push_back(y);
                    writtenExams.push_back(we);
                }
                else if(y>=0.0 && y<s.f[i].setfinalGrade(0.0,0.0,v[j]))
                cout<< "Nota finala este mai mica decat cea de dinainte, asadar va fi pastrata cea veche.";
            cout<< endl;
            j++;
            }
        }
        else if(s.f[i].mark<5)
            {
                cout<< "Studentul "<< s.studName<< " trebuie sa refaca examenul scris la "<< s.f[i].subject<< " pentru a promova.\n";;
                cout<< "Introduceti noua nota a acestuia: ";
                cin>> we;
                double y=s.f[i].setfinalGrade(0.0,we,0.0);
                if(y>s.f[i].setfinalGrade(0.0,0.0,0.0))
                {
                    cout<< "Noua nota finala este "<< y<< endl;
                    finalGrades.push_back(y);
                    writtenExams.push_back(we);
                }
                else if(y>=0.0 && y<s.f[i].setfinalGrade(0.0,0.0,0.0))
                    cout<< "Nota finala este mai mica decat cea de dinainte, asadar va fi pastrata cea veche.";
                cout<< endl;
            }
    }
}
void Student::finalsReplacement(Student &s)
{
    double *v, *w, *p, *q;
    string *z;
    vector<double>::iterator it;
    v=new double[finalGrades.size()];
    vector<double>::iterator a;
    w=new double[writtenExams.size()];
    vector<double>::iterator b;
    p=new double[partialGrades.size()];
    vector<double>::iterator c;
    q=new double[quizGrades.size()];
    vector<string>::iterator d=answers.begin();
    //z=new string[answers.size()];
    int sz1=finalGrades.size();
    int sz2=writtenExams.size();
    int sz3=partialGrades.size();
    int sz4=quizGrades.size();
    //int sz5=answers.size();
    /*for(int i=0; i<sz1; i++) ///vector alocat dinamic doar cu notele finale modificate dupa restanta
    {
        it=finalGrades.begin();
        v[i]=(*it);
        finalGrades.erase(finalGrades.begin());
    }*/
    for(int k=0; k<sz2; k++) ///vector alocat dinamic doar cu noile note de la examenul scris
    {
        a=writtenExams.begin();
        w[k]=(*a);
        writtenExams.erase(writtenExams.begin());
    }
    for(int q=0; q<sz3; q++) ///vector alocat dinamic doar cu notele de la partial(oral+scris) dupa refacerea scrisului
    {
        b=partialGrades.begin();
        p[q]=(*b);
        partialGrades.erase(partialGrades.begin());
    }
    for(int r=0; r<sz4; r++) ///vector alocat dinamic cu notele finale in urma quiz-ului
    {
        c=quizGrades.begin();
        q[r]=(*c);
        quizGrades.erase(quizGrades.begin());
    }

    int l=0, m=0, f=0, g=0;
    for(int i=0; i<get_nrExams(); i++)
    {
        if(s.f[i].setfinalGrade(0.0,0.0,0.0)<5)
        {
            cout<< "Noua situatie finala a studentului "<< s.studName<< " la "<< s.f[i].subject<< " este urmatoarea"<< endl;
            if(s.f[i].getpartialGrade(0.0)<5)
            {
                if(s.f[i].setfinalGrade(0.0,0.0,p[m]<5))
                {
                    cout<< "Nota la scris in urma refacerii acestuia este "<< w[l]<< ".\n";
                    cout<< "Nota la partial in urma refacerii lucrarii scrise a acestuia este "<< p[m]<< ".\n";
                    cout<< endl;
                    cout<< "In urma refacerii atat a examenului scris, cat si a partialului, nota finala la "<< s.f[i].subject<< " este "<< s.f[i].setfinalGrade(0.0,w[l],p[m])<< ".\n";
                    m++;
                }
            }
            else
            {
                cout<< "Nota la scris in urma refacerii acestuia este "<< w[l]<< ".\n";
                cout<< "Nota la partial este "<< s.f[i].getpartialGrade(0.0)<< ".\n";
                cout<< endl;
                cout<< "In urma notei obtinute la refacerea examenului scris, nota finala la "<< s.f[i].subject<< " este "<< s.f[i].setfinalGrade(0.0,w[l],0.0)<< ".\n";
            }
            l++;
            cout<< endl;
        }

        else if(s.f[i].setfinalGrade(0.0,0.0,0.0)>=5 && s.f[i].getpartialGrade(0.0)<5)
        {
            cout<< "Noua situatie finala a studentului "<< s.studName<< " la "<< s.f[i].subject<< " este urmatoarea"<< endl;
            cout<< "Nota la scris este "<< s.f[i].mark<< ".\n";
            cout<< "Nota la partial in urma refacerii lucrarii scrise a acestuia este "<< p[m]<< ".\n";
            m++;
            cout<< endl;
            cout<< "In urma notei obtinute la refacerea partialului, nota finala la "<< s.f[i].subject<< " este "<< s.f[i].setfinalGrade(0.0,0.0,p[m])<< ".\n";
            cout<< endl;
        }

        else if(s.f[i].setfinalGrade(0.0,0.0,0.0)>=5 && s.f[i].setfinalGrade(0.0,0.0,0.0)<10 && s.f[i].getpartialGrade(0.0)>=5 && (*d)=="da")
            {
                cout<< s.f[i]<< "\nIar in urma quiz-ului dat, noua nota finala este "<< q[f]<< ".\n";
                f++;
                answers.erase(answers.begin());
                d=answers.begin();
            }
        else
        {
            cout<< "Situatia finala a studentului "<< s.studName<< ":\n";
            cout<< s.f[i]<< endl;
        }
    }

    finalGrades.erase(finalGrades.begin(),finalGrades.end()); ///doar ma asigur
    writtenExams.erase(writtenExams.begin(),writtenExams.end());
    partialGrades.erase(partialGrades.begin(),partialGrades.end());
}
void Student::FFinalExams(Student &s)
{
    /*string *v;
    v=new string[s.nrfailedFExams()];
    int k=0;*
    for(int i=0; i<get_nrExams(); i++)
    {
        if(s.f[i].setfinalGrade(0.0,0.0,0.0)<5)
            {
                v[k]=s.f[i].subject;
                k++;
            }
    }
    failedFExams[s.studName]=*v;*/

    vector<string> N;
    unordered_map<string,vector<string>> failedN;
    for(int i=0; i<get_nrExams(); i++)
    {
        if(s.f[i].setfinalGrade(0.0,0.0,0.0)<5)
            N.push_back(s.f[i].subject);
    }
    failedN[s.studName]=N;
}
void Student::showFFinalExams(Student &s)
{
    /*for(auto it: failedFExams)
    {
        cout<< it.first<< " are urmatoarele restante: "<< endl;
        for(int i=0; i<it.second.size(); i++)
        {
            cout<< it.second;
            cout<< endl;
        }
    }*/

    for(auto it: failedN)
    {
        cout<< it.first<< " are urmatoarele restante: "<< endl;
        for(vector<string>::iterator i=N.begin(); i!=N.end(); i++)
            cout<< (*i)<<  endl;
    }
}
int Student::nrfailedFExams()
{
    int nr=0; double x=0.0, y=0.0;
    for(int i=0; i<get_nrExams(); i++)
        if(f[i].setfinalGrade(x,y,0.0)<5)
            nr++;

    return nr;
}
int Student::nrfailedPExams()
{
    int nr=0; double x=0.0;
    for(int i=0; i<get_nrExams(); i++)
        if(f[i].getpartialGrade(x)<5)
            nr++;

    return nr;
}
void Student::addName(string n)
{
    subjectName.insert(n);
}


template <class t> class CatalogIndividual
{
private:
    static int studId;
    int nrExams;
    t student;
    list<vector<string>> Sheet;
    friend t;
public:
    CatalogIndividual(int nr):nrExams(nr)
    {
        nrExams=student.get_nrExams();
    }
    ~CatalogIndividual()
    {
        nrExams=0;
       Sheet.erase(Sheet.begin(),Sheet.end());
    }
    friend istream& operator>>(istream &in, CatalogIndividual<t> &c)
    {
        c.studId++;
        cout<< "Se introduce in catalog studentul cu numarul matricol "<< c.studId<< endl;
        in>> c.student; c.addSheet(c);
        return in;
    }
    friend ostream& operator<<(ostream &out, CatalogIndividual<t> &c)
    {
        out<< "Informatii extrase din catalogul virtual: \n";
        out<< "Numar matricol - "<< c.studId<< endl;
        out<< c.student;
        if(c.Sheet.size()==0)
            out<< "Nu exista lista de observatie pentru studentul cu acest numar matricol.\n";
        else
        {
            for(list<vector<string>>::iterator it=c.Sheet.begin(); it!=c.Sheet.end(); it++)
            {
                for(int i=0; i=it->size(); i++)
                    out<< it->at(i);
            }
        }
        return out;
    }
    list<vector<string>> &operator+=(const vector<string> &sheet)
    {
        Sheet.push_back(sheet);
        return Sheet;
    }
    void addSheet(CatalogIndividual<Student> &c)
{
    vector<string> exp;
    string subjName, obs, answer;
    int n1=0, n2=0;
    cout<< "Adaugarea unei noi fise de observatie pentru un examen.\n";
    cout<< "Introduceti denumirea materiei: ";
    exp.push_back("Fisa de observatii pentru ");
    cin>> subjName;
    exp.push_back(subjName);
    cout<< "Introduceti observatiile. \n";
    do{
        cin>> obs;
        cout<< "Doriti sa mai adaugati o observatie? Tastati da/nu: ";
        cin>> answer;
        if(answer=="da")
            n2++;
        n1++;
        exp.push_back(obs);
        exp.push_back("\n");
    }while(n1<=n2);
    c+=exp;
}
};
template <class t> int CatalogIndividual<t>::studId=0;



int main()
{
    cout<< "Introduceti numele facultatii: ";
    string uniName;
    getline(cin,uniName);
    cout<< endl;

    cout<< "Examinarea se face in felul urmator: \nLa fiecare materie studentii au de facut proiect,"
        <<" de dat partial, proba orala si examen scris. \n";
    cout<< "Nota finala va avea urmatoarea structura:\n40% partialul (care este compus 50% din testul scris si 50% din proba orala)"
        << " + 60% examenul scris + puncte bonus din proiect.\n";
    cout<< "Daca nota partialului este mai mica decat 5, atunci lucrarea scrisa a acestuia va trebui refacuta.\nDaca nota partialului"
        << " este mai mare decat 5, dar nota finala este mai mica decat 5, atunci examenul scris va trebui refacut.\n";
    cout<< "Chiar daca nota partialului a fost initial mai mica decat 5, iar dupa modificarea acesteia astfel incat sa fie mai mare decat 5"
        << ", nota finala a examenului este inca mai micat decat 5, atunci trebuie refacut si examenul scris.\n";
    cout<< "Daca studentul a reusit sa obtina nota de trecere fara sa trebuiasca sa-si refaca vreuna dintre componentele acesteia, acesta poate opta"
        << " pentru marire.\n";
    cout<< endl;

    cout<< "Cati studenti au sustinut sesiunea la "<< uniName<< "?\nTastati numarul: ";
    int nrStud;
    cin>> nrStud;
    cout<< endl;

    cout<< "Cate examene au fost date la "<< uniName<< "?\nTastati numarul: ";
    int x; cin>>x;
    vector<string> names;
    cout<< endl;

    CatalogIndividual<Student> STUDENT(x);

    if(x==1)
        cout<< "Introduceti numele materiei la care studentii dau examen (restrangeti denumirea intr-un singur cuvant): ";
    else
        cout<< "Introduceti numele celor "<< x<< " materii la care studentii dau examen (restrangeti denumirea intr-un singur cuvant):\n";
    string name;
    for(int i=0; i<x; i++)
    {
        cin>> name;
        names.push_back(name);
    }
    cout<< endl;

    Student *S=new Student[nrStud];
    for(int i=0; i<nrStud; i++){S[i].set_nrExams(x);}
    for(int i=0; i<nrStud; i++)
    {
        for(vector<string>::iterator it=names.begin(); it!=names.end(); it++)
            S[i].addName(*it);
    }
    for(int i=0; i<nrStud; i++)
        cin>> S[i];


    vector<FinalExam> exams;
    unordered_set<string> Names;

    int choice;
    do
    {
        cout<< "De acum aveti urmatoarele posibilitati:\n";
        cout<< "1. Afisarea notelor studentilor.\n";
        cout<< "2. Situatia restantierilor.\n";
        cout<< "3. Posibilitatea de marire a notelor care sunt deja mai mari de 5.\n";
        cout<< "4. Adaugati observatii referitoare la examene.\n";
        cout<< "5. Afisati observatiile referitoare la examene.\n";
        cout<< "6. Iesire!\n";
        cout<< "Tastati alegerea: ";
        cin>> choice;
        cout<< endl;
        switch(choice)
        {
        case 1:
            {
                for(int i=0; i<nrStud; i++)
                        cout<< S[i];
            }
            break;
        case 2: ///RESTANTE
            {
                for(int i=0; i<nrStud; i++)
                {
                    if(S[i].nrfailedFExams()>0)
                        S[i].FFinalExams(S[i]);
                }                                   ///MENTIONAREA MATERIILOR CARE REPREZINTA RESTANTE
                for(int i=0; i<nrStud; i++)
                {
                    S[i].showFFinalExams(S[i]);
                    cout<< endl;
                }

                for(int i=0; i<nrStud; i++)
                {
                    if(S[i].nrfailedPExams()>0)
                        S[i].compareforPartial(S[i]);
                }

                for(int i=0; i<nrStud; i++)
                {
                    if(S[i].nrfailedFExams()>0)
                        S[i].compareforFinal(S[i]);
                }

                int choice2;
                do{
                    cout<< "Ce doriti sa faceti mai departe?\n";
                    cout<< "1. Afisarea situatiei actuale a notelor.\n";
                    cout<< "2. Iesire!\n";
                    cout<< "Introduceti alegerea: ";
                    cin>> choice2;
                    cout<< endl;
                    switch(choice2)
                    {
                    case 1:
                        {
                            for(int i=0; i<nrStud; i++)
                                S[i].finalsReplacement(S[i]);
                        }
                        break;
                    case 2:
                        return 1;
                    default:
                        cout << " Numarul tastat nu face parte din meniul prezentat." << endl;
                        cout << endl;
                        break;
                    }
                }while(choice2!=2);
            }
            break;
        case 3: /// QUIZ
            {
                for(int i=0; i<nrStud; i++)
                {
                    S[i].compareforQuiz(S[i]);
                }

                int choice3;
                do{
                    cout<< "Ce doriti sa faceti mai departe?\n";
                    cout<< "1. Afisarea situatiei actuale a notelor.\n";
                    cout<< "2. Iesire!\n";
                    cout<< "Introduceti alegerea: ";
                    cin>> choice3;
                    cout<< endl;
                    switch(choice3)
                    {
                    case 1:
                        {
                            for(int i=0; i<nrStud; i++)
                                S[i].finalsReplacement(S[i]);
                        }
                        break;
                    case 2:
                        return 1;
                    default:
                        cout << " Numarul tastat nu face parte din meniul prezentat." << endl;
                        cout << endl;
                        break;
                    }
                }while(choice3!=2);
            }
            break;
        case 4:
            {
                for(int i=0; i<nrStud; i++)
                    cin>> STUDENT;
            }
            break;
        case 5:
            {
                for(int i=0; i<nrStud; i++)
                    cout<< STUDENT;
            }
            break;
        case 6:
            return 1;
            break;
        default:
            cout << " Numarul tastat nu face parte din meniul prezentat." << endl;
            cout << endl;
            break;
        }
    }while(choice!=6);
    return 0;
}
