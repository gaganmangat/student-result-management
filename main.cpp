#include <iostream>
#include<iomanip>
#include<malloc.h>
#include<process.h>
#include<fstream>
#include<string.h>
#include<stdio.h>

using namespace std;

struct scheme_l //linked list for scheme
{
    char sub_code[10];
    char sub_title[20];
    int sess_marks;
    int theo_marks;
    int sem;
    struct scheme_l* next;
};
typedef struct scheme_l Scnode;
Scnode* start = NULL;

Scnode* writeScheme(Scnode* );
Scnode* displayScheme(Scnode* );
Scnode* readScheme(Scnode* );
Scnode* addnode(Scnode*,Scnode* );
Scnode* deleteScheme(Scnode* );

struct student
{
    int roll_no; //primary key
    char name[20];
    char f_name[20];
    char dob[10];
    int sem;
    int yoa; //year of admission
    struct student* next;
};
typedef struct student Stnode;
Stnode* starts = NULL;

Stnode* writeStudentRecord(Stnode* );
Stnode* displayStudentRecord(Stnode* );
Stnode* readStudentRecord(Stnode* );
Stnode* addnodeStudent(Stnode*,Stnode* );

struct record_l
{
    int r_roll_no;
    char r_name[20];
    int r_sem;
    int ma_sess; //marks awarded
    int ma_theo;
    struct record_l* next;
};
typedef struct record_l Rnode;

Rnode* startl = NULL;
Rnode* input_marks(Rnode* );
Rnode* writeRecord(Rnode*, Rnode* );
Rnode* readRecord(Rnode* );
Rnode* addnodeRecord(Rnode*, Rnode* );
Rnode* displayMarksRecord(Rnode* );
Rnode* printRecordSemester(Rnode* );
Rnode* listRecord(Rnode* );

int main()
{
    int choice;
    while(1)
    {
        cout<<"\n1.Add student records\n";
        cout<<"2.Display student records\n";
        cout<<"3.Add new scheme\n";
        cout<<"4.Display all schemes\n";
        cout<<"\t\t\t5.Read schemes from file\n";
        cout<<"6.Delete a scheme\n";
        cout<<"\t\t\t7.Read student records from file\n";
        cout<<"8.Input marks awarded\n";
        cout<<"\t\t\t9.Read marks awarded\n";
        cout<<"10.Display marks awarded\n";
        cout<<"11.Print result semester wise\n";
        cout<<"12.Random access of a record\n";

        cin>>choice;
        switch(choice)
        {
        case 1:
            starts = writeStudentRecord(starts);
            break;
        case 2:
            starts = displayStudentRecord(starts);
            break;
        case 3:
            start = writeScheme(start);
            break;
        case 4:
            start = displayScheme(start);
            break;
        case 5:
            start = readScheme(start);
            break;
        case 6:
            start = deleteScheme(start);
            break;
        case 7:
            starts = readStudentRecord(starts);
            break;
        case 8:
            startl = input_marks(startl);
            break;
        case 9:
            startl = readRecord(startl);
            break;
        case 10:
            startl = displayMarksRecord(startl);
            break;
        case 11:
            startl = printRecordSemester(startl);
            break;
        case 12:
            startl = listRecord(startl);
            break;
        default:
            return 0;
            break;
        }
    }
    return 0;
}

Scnode* writeScheme(Scnode* start)
{
    FILE* fp;
    fp = fopen("Scheme.txt","ab+");

    Scnode* newnode;
    newnode = (Scnode*)malloc(sizeof(Scnode));
    Scnode* ptr;
    char dsub_code[10];
    char dsub_title[20];
    int dsess_marks;
    int dtheo_marks;
    int dsem;

    cout<<"Enter subject code\n";
    cin>>dsub_code;
    cout<<"Enter subject name\n";
    fflush(stdin);
    gets(dsub_title);
    fflush(stdin);
    cout<<"Enter maximum marks of sessional\n";
    cin>>dsess_marks;
    cout<<"Enter maximum marks of end semester theory\n";
    cin>>dtheo_marks;
    cout<<"Enter semester number (1-8)\n";
    cin>>dsem;

    strcpy(newnode->sub_code,dsub_code);
    strcpy(newnode->sub_title,dsub_title);
    newnode->sess_marks = dsess_marks;
    newnode->theo_marks = dtheo_marks;
    newnode->sem = dsem;

    if(start == NULL)
    {
        cout<<"Making the first node\n";
        start = newnode;
        newnode->next = NULL;
        cout<<"Writing start to file\n";
        fwrite(start,sizeof(Scnode),1,fp);

    }
    else
    {
        cout<<"Making new node\n";
        ptr = start;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
        cout<<"Writing node to file\n";
        fwrite(ptr->next,sizeof(Scnode),1,fp);
    }
    fclose(fp);
    return start;
}

Scnode* readScheme(Scnode* start) //function to read linked lists from file
{
    FILE* fq;
    fq = fopen("Scheme.txt","rb+");
    Scnode sc;

    fread(&sc,sizeof(Scnode),1,fq);
    start = displayScheme(start);

    while(!feof(fq))
    {
        cout<<"\nYES\n";
        start = addnode(start,&sc);
        cout<<endl<<sc.sub_code<<endl<<sc.sub_title<<endl<<sc.sess_marks<<endl<<sc.theo_marks<<endl<<sc.sem;
        fread(&sc,sizeof(Scnode),1,fq);
        start = displayScheme(start);
    }
    fclose(fq);
    return start;
}

Scnode* displayScheme(Scnode* start)
{
    cout<<"\nIN DISPLAY\n";
    Scnode* ptr;
    ptr = start;
    if(ptr == NULL) cout<<"List Empty\n";
    else
    {
        cout<<setw(15)<<"SUBJECT CODE"<<setw(15)<<"SUBJECT TITLE"
            <<setw(15)<<"MM SESSIONAL"<<setw(15)<<"MM FINALS"<<setw(15)<<"SEMESTER\n";
        while(ptr != NULL)
        {
            cout<<setw(15)<<ptr->sub_code<<setw(15)<<ptr->sub_title<<
                  setw(15)<<ptr->sess_marks<<setw(15)<<ptr->theo_marks<<
                  setw(15)<<ptr->sem<<endl;
            ptr = ptr->next;
        }
    }
    return start;
}

Scnode* addnode(Scnode* start, Scnode* sc)
{
    cout<<"\nIN ADDNODE\n";
    Scnode* newnode;
    newnode = (Scnode*)malloc(sizeof(Scnode));
    Scnode* ptr;

    strcpy(newnode->sub_code,sc->sub_code);
    strcpy(newnode->sub_title,sc->sub_title);
    newnode->sess_marks = sc->sess_marks;
    newnode->theo_marks = sc->theo_marks;
    newnode->sem = sc->sem;

    if(start == NULL)
    {
        cout<<"Making the first node\n";
        start = newnode;
        newnode->next = NULL;

    }
    else
    {
        cout<<"Making new node\n";
        ptr = start;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
    }
    return start;
}

Scnode* deleteScheme(Scnode* start)
{
    FILE* fp;
    fp = fopen("Scheme.txt","wb+");
    if(start == NULL)
    {
        cout<<"List is empty\n";
        return start;
    }

    Scnode* ptr;
    Scnode* preptr;
    char dsub_code[10];
    cout<<"Enter the subject code of the subject to be deleted\n";
    fflush(stdin);
    gets(dsub_code);
    fflush(stdin);
    cout<<"Here\n";
    ptr = start;
    if(strcmp(ptr->sub_code,dsub_code) == 0)
    {
        start = start->next;
        free(ptr);
        fwrite(start,sizeof(Scnode),1,fp);
        return start;
    }
    else
    {
        while(strcmp(ptr->sub_code,dsub_code) != 0)
        {
            fwrite(ptr,sizeof(Scnode),1,fp);
            preptr = ptr;
            ptr = ptr->next;
        }
        preptr->next = ptr->next;
        free(ptr);
        while(preptr->next != NULL)
        {
            fwrite(preptr->next,sizeof(Scnode),1,fp);
        }
        return start;
    }


}

Stnode* writeStudentRecord(Stnode* starts)
{
    FILE* fp;
    fp = fopen("Student.txt","ab+");

    Stnode* newnode;
    newnode = (Stnode*)malloc(sizeof(Stnode));
    Stnode* ptr;
    int droll_no;
    char dname[20];
    char df_name[20];
    char ddob[10];
    int dsem;
    int dyoa;

    cout<<"Enter roll number\n";
    cin>>droll_no;
    cout<<"Enter name of the student\n";
    fflush(stdin);
    gets(dname);
    fflush(stdin);
    cout<<"Enter Fathers name of the student\n";
    fflush(stdin);
    gets(df_name);
    fflush(stdin);
    cout<<"Enter Date of Birth\n";
    cin>>ddob;
    cout<<"Enter semester number (1-8)\n";
    cin>>dsem;
    cout<<"Enter year of admission\n";
    cin>>dyoa;

    newnode->roll_no = droll_no;
    strcpy(newnode->name,dname);
    strcpy(newnode->f_name,df_name);
    strcpy(newnode->dob,ddob);
    newnode->sem = dsem;
    newnode->yoa = dyoa;

    if(starts == NULL)
    {
        cout<<"Making the first node\n";
        starts = newnode;
        newnode->next = NULL;
        cout<<"Writing start to file\n";
        fwrite(starts,sizeof(Stnode),1,fp);

    }
    else
    {
        cout<<"Making new node\n";
        ptr = starts;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
        cout<<"Writing node to file\n";
        fwrite(ptr->next,sizeof(Stnode),1,fp);
    }
    fclose(fp);
    return starts;
}

Stnode* displayStudentRecord(Stnode* starts)
{
    Stnode* ptr;
    ptr = starts;
    if(ptr == NULL) cout<<"List Empty\n";
    else
    {
        cout<<setw(18)<<"ROLL NUMBER"<<setw(20)<<"NAME"<<
              setw(20)<<"FATHERS NAME"<<setw(18)<<"DATEOFBIRTH"<<
              setw(18)<<"SEMESTER"<<setw(18)<<"ADMISSION YEAR\n";
        while(ptr != NULL)
        {
            cout<<setw(18)<<ptr->roll_no<<setw(20)<<ptr->name<<
                  setw(20)<<ptr->f_name<<setw(18)<<ptr->dob<<
                  setw(18)<<ptr->sem<<setw(18)<<ptr->yoa<<endl;
            ptr = ptr->next;
        }
    }
    return starts;
}

Stnode* addnodeStudent(Stnode* starts, Stnode* st)
{
    cout<<"\nIN ADDNODE\n";
    Stnode* newnode;
    newnode = (Stnode*)malloc(sizeof(Stnode));
    Stnode* ptr;

    newnode->roll_no = st->roll_no;
    strcpy(newnode->name,st->name);
    strcpy(newnode->f_name,st->f_name);
    strcpy(newnode->dob,st->dob);
    newnode->sem = st->sem;
    newnode->yoa = st->yoa;

    if(starts == NULL)
    {
        cout<<"Making the first node\n";
        //ptr = start;
        starts = newnode;
        newnode->next = NULL;

    }
    else
    {
        cout<<"Making new node\n";
        ptr = starts;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
    }
    return starts;
}

Stnode* readStudentRecord(Stnode* starts)
{
    FILE* fq;
    fq = fopen("Student.txt","rb+");
    Stnode st;

    fread(&st,sizeof(Stnode),1,fq);

    while(!feof(fq))
    {
        cout<<"\nYES\n";
        starts = addnodeStudent(starts,&st);
        cout<<endl<<st.roll_no<<endl<<st.name<<endl<<st.f_name<<endl<<st.dob<<endl<<st.sem<<endl<<st.yoa<<endl;
        fread(&st,sizeof(Stnode),1,fq);
        starts = displayStudentRecord(starts);
    }
    fclose(fq);
    return starts;
}

Rnode* input_marks(Rnode* start)
{
    FILE* fp;
    FILE* ft;

    Scnode sc;
    Stnode st;
    Rnode rt;

    int sem;
    cout<<"Enter semester number\n";
    cin>>sem;

    int masess;
    int matheo;
    int droll;

    fp = fopen("Student.txt","rb+");
    ft = fopen("Scheme.txt","rb+");

    fread(&st, sizeof(Stnode),1,fp);
    fread(&sc,sizeof(Scnode),1,ft);

    while(!feof(ft)) //scheme loop
    {
        rewind(fp);
        fread(&st, sizeof(Stnode),1,fp);
        while( !feof(fp)) //student loop
        {
            if(sc.sem == st.sem && sc.sem == sem)
            {
                cout<<"In "<<sc.sem<<" semester\n";
                cout<<"Enter roll number of the student\n";
                cin>>droll;
                if(st.roll_no == droll)
                {
                    cout<<"Enter marks awarded in sessionals\n";
                    cin>>masess;
                    cout<<"Enter marks awarded in end semester theory\n";
                    cin>>matheo;
                    rt.r_roll_no = st.roll_no;
                    strcpy(rt.r_name,st.name);
                    rt.r_sem = st.sem;
                    rt.ma_sess = masess;
                    rt.ma_theo = matheo;
                    startl = writeRecord(startl, &rt);
                }
            }
            fread(&st,sizeof(Stnode),1,fp);
        }
        fread(&sc,sizeof(Scnode),1,ft);
    }
    fclose(fp);
    fclose(ft);
    return startl;

}

Rnode* writeRecord(Rnode* startl, Rnode* rt)
{
    FILE* fs;
    fs = fopen("Record.txt","ab+");

    Rnode* newnode;
    newnode = (Rnode*)malloc(sizeof(Rnode));
    Rnode* ptr;

    newnode->r_roll_no = rt->r_roll_no;
    strcpy(newnode->r_name,rt->r_name);
    newnode->r_sem = rt->r_sem;
    newnode->ma_sess = rt->ma_sess;
    newnode->ma_theo = rt->ma_theo;

    if(startl == NULL)
    {
        cout<<"Making the first node\n";
        startl = newnode;
        newnode->next = NULL;
        cout<<"Writing startl to file\n";
        fwrite(startl,sizeof(Rnode),1,fs);

    }
    else
    {
        cout<<"Making new node\n";
        ptr = startl;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
        cout<<"Writing node to file\n";
        fwrite(ptr->next,sizeof(Rnode),1,fs);
    }
    fclose(fs);
    return startl;
}

Rnode* readRecord(Rnode* startl)
{
    FILE* fq;
    fq = fopen("Record.txt","rb+");
    Rnode rt;

    fread(&rt,sizeof(Rnode),1,fq);

    while(!feof(fq))
    {
        cout<<"\nYES\n";
        startl = addnodeRecord(startl,&rt);
        cout<<endl<<rt.r_roll_no<<endl<<rt.r_name<<endl<<rt.r_sem<<endl<<rt.ma_sess<<endl<<rt.ma_theo<<endl;
        fread(&rt,sizeof(Rnode),1,fq);
        startl = displayMarksRecord(startl);
    }
    fclose(fq);
    return startl;
}
Rnode* addnodeRecord(Rnode* startl, Rnode* rt)
{
    cout<<"\nIN ADDNODE\n";
    Rnode* newnode;
    newnode = (Rnode*)malloc(sizeof(Rnode));
    Rnode* ptr;

    newnode->r_roll_no = rt->r_roll_no;
    cout<<"Roll number assigned to new node is "<<rt->r_roll_no<<endl;
    strcpy(newnode->r_name,rt->r_name);
    newnode->r_sem = rt->r_sem;
    newnode->ma_sess = rt->ma_sess;
    newnode->ma_theo = rt->ma_theo;

    if(startl == NULL)
    {
        cout<<"Making the first node\n";
        startl = newnode;
        newnode->next = NULL;
    }
    else
    {
        cout<<"Making new node\n";
        ptr = startl;
        while(ptr->next != NULL) ptr = ptr->next;
        ptr->next = newnode;
        newnode->next = NULL;
    }
    return startl;
}
Rnode* displayMarksRecord(Rnode* startl)
{
    Rnode* ptr;
    ptr = startl;
    if(ptr == NULL) cout<<"List Empty\n";
    else
    {
        cout<<setw(18)<<"ROLL NUMBER"<<setw(20)<<"NAME"<<
              setw(18)<<"SEMESTER"<<setw(18)<<"SESSIONAL MARKS"<<
              setw(18)<<"FINALS MARKS"<<endl;
        while(ptr != NULL) //not ptr->next, it should be ptr != NULL
        {
            cout<<setw(18)<<ptr->r_roll_no<<setw(20)<<ptr->r_name<<
                  setw(18)<<ptr->r_sem<<setw(18)<<ptr->ma_sess<<
                  setw(18)<<ptr->ma_theo<<endl;
            ptr = ptr->next;
        }
    }
    return startl;
}

Rnode* printRecordSemester(Rnode* startl)
{
    Rnode* ptr;
    int dsem;
    cout<<"Enter semester number\n";
    cin>>dsem;
    ptr = startl;
    if(ptr == NULL) cout<<"List Empty\n";
    else
    {
        cout<<"IN "<<dsem<<" SEMESTER\n\n";
        cout<<setw(18)<<"ROLL NUMBER"<<setw(20)<<"NAME"<<
              setw(18)<<"SEMESTER"<<setw(18)<<"SESSIONAL MARKS"<<
              setw(18)<<"FINALS MARKS"<<endl;
        while(ptr != NULL)
        {
            if(ptr->r_sem == dsem)
            {
              cout<<setw(18)<<ptr->r_roll_no<<setw(20)<<ptr->r_name<<
                  setw(18)<<ptr->r_sem<<setw(18)<<ptr->ma_sess<<
                  setw(18)<<ptr->ma_theo<<endl;
            }
            ptr = ptr->next;
        }
    }
    return startl;
}
Rnode* listRecord(Rnode* startl)
{
    Rnode* ptr;
    int dsem;
    cout<<"Enter semester number\n";
    cin>>dsem;
    int droll;
    cout<<"Enter roll number to access\n";
    cin>>droll;
    int flag = 0;
    ptr = startl;
    if(ptr == NULL) cout<<"List Empty\n";
    else
    {
        cout<<"IN "<<dsem<<" SEMESTER\n\n";
        cout<<setw(18)<<"ROLL NUMBER"<<setw(20)<<"NAME"<<
              setw(18)<<"SEMESTER"<<setw(18)<<"SESSIONAL MARKS"<<
              setw(18)<<"FINALS MARKS"<<endl;

        while(ptr != NULL)
        {
            if(ptr->r_sem == dsem && ptr->r_roll_no == droll)
            {
              flag = 1;
              cout<<setw(18)<<ptr->r_roll_no<<setw(20)<<ptr->r_name<<
                  setw(18)<<ptr->r_sem<<setw(18)<<ptr->ma_sess<<
                  setw(18)<<ptr->ma_theo<<endl;
            }
            ptr = ptr->next;
        }
        if(flag == 0) cout<<"The given record does not exist\n";
    }
    return startl;
}
