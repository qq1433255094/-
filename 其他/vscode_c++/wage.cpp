#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>


using namespace std;

struct Wage{
    int number;
    string name;
    int base;
    int add;
    int sub;
    int fact;
};

void AddStaff(vector<struct Wage> &wage,int number,string name,int base,int add,int sub,int fact);
void ShowStaff(vector<struct Wage> wage,int number);
void Compute(vector<struct Wage> &wage);
void Sort(vector<struct Wage> &wage);
int Search(vector<struct Wage> wage,int number);
void Output(vector<struct Wage> wage,string name);
void AddMode(vector<struct Wage> &wage);

int main()
{
    vector<struct Wage> wage;
    int mode=1,num;
    char name[20];

    AddStaff(wage,50001,"zhanghua",6000,1200,500,0);
    AddStaff(wage,50003,"lifang",5000,1000,200,0);
    AddStaff(wage,50002,"sunlei",7000,800,100,0);
    AddStaff(wage,50005,"chenxin",4000,1100,300,0);
    AddStaff(wage,50004,"guyan",9000,1200,0,0);

    

    cout<<"�����������"<<endl;
    cin>>name;

    while(mode!=0)
    {
        system("cls");
        cout<<"����Ҫִ�е�����0~6"<<endl;
        cout<<"1:Compute()����ʵ������"<<endl;
        cout<<"2:Sort()��ְ��������"<<endl;
        cout<<"3:Search()��ְ��������"<<endl;
        cout<<"4:Output()�������ְ����Ϣ"<<endl;
        cout<<"5:����,����,���"<<endl;
        cout<<"6:���ְ����Ϣ"<<endl;
        cout<<"0:�˳�����"<<endl;
        cin>>mode;

        switch(mode)
        {
            case 0: 
            cout<<"�˳�����"<<endl;
            system("pause"); break;

            case 1:
            cout<<"����ʵ������"<<endl;
            Compute(wage);
            cout<<"�������"<<endl;
            system("pause"); break;

            case 2:
            cout<<"��ְ��������"<<endl;
            Sort(wage);
            cout<<"�������"<<endl;
            system("pause"); break;

            case 3:
            cout<<"��ְ��������"<<endl;
            cout<<"����Ҫ������ְ����:";
            cin>>num;
            if(num>=0 && num<999999)
                {
                    Search(wage,num);
                    cout<<"�������"<<endl;
                }
            else
                 cout<<"����������Χ"<<endl;
            system("pause"); break;

            case 4:
            cout<<"�������ְ����Ϣ"<<endl;
            Output(wage,name);
            cout<<"������"<<endl;
            system("pause"); break;
            break;

            case 5:
            cout<<"����,����,���"<<endl;
            Compute(wage);
            Sort(wage);
            Output(wage,name);
            cout<<"ִ�����"<<endl;
            system("pause"); break;
            break;

            case 6:
            AddMode(wage);
            break;

            default:
            cout<<"�����������ȷ����"<<endl;
            system("pause"); break;
        }
    }

    return 0;
}

void AddStaff(vector<struct Wage> &wage,int number,string name,int base,int add,int sub,int fact)
{
    struct Wage staff={number,name,base,add,sub,fact};
    wage.insert(wage.end(),staff);
}

void AddMode(vector<struct Wage> &wage)
{
    struct Wage staff={0};
    int mode;
    int repeat=0;

    while(mode!=0)
    {
        repeat=0;
        system("cls");
        cout<<"���ģʽ"<<endl;
        cout<<"����Ҫִ�е�����0~3"<<endl;
        cout<<"1:���ְ����Ϣ"<<endl;
        cout<<"2:ɾ������ְ����Ϣ"<<endl;
        cout<<"3:��ʾ����ְ����Ϣ"<<endl;
        cout<<"0:�˳����ģʽ"<<endl;
        cin>>mode;

        switch(mode)
        {
            case 0: 
            cout<<"�˳����ģʽ"<<endl;
            system("pause"); break;

            case 1:
            cout<<"���� ��� ���� �������� ���ӹ��� �۳����ʣ�"<<endl;
            cin>>staff.number>>staff.name>>staff.base>>staff.add>>staff.sub;
            if(staff.number>=0 && staff.number<1000000)
            {
                for(int i=0;i<wage.size();i++)
                    if(staff.number==wage[i].number)
                        repeat=1;
                if(!repeat)
                {
                    wage.insert(wage.end(),staff);
                    cout<<"������"<<endl;
                }
                else
                    cout<<"��Ŵ��󣬱�Ų����ظ�"<<endl;
            }
            else
                cout<<"��Ŵ��󣬱�ų���ָ����Χ"<<endl;
            system("pause"); break;

            case 2: 
            wage.clear();
            cout<<"ɾ�����"<<endl;
            system("pause"); break;

            case 3: 
            for(int i=0;i<wage.size();i++)
                ShowStaff(wage,i);
            cout<<"ɾ�����"<<endl;
            system("pause"); break;

            default:
            cout<<"�����������ȷ����"<<endl;
            system("pause"); break;
        } 
    }
}

void ShowStaff(vector<struct Wage> wage,int number)
{
    
    if(number>=0 && number<wage.size())
    {
        cout.setf(ios::left);
        cout
        <<"ְ����:"   <<setw(8)<<wage[number].number
        <<" ����:"    <<setw(14)<<wage[number].name
        <<" ��������:"<<setw(8)<<wage[number].base
        <<" ���ӹ���:"<<setw(8)<<wage[number].add
        <<" �۳�����:"<<setw(8)<<wage[number].sub
        <<" ʵ������:"<<setw(8)<<wage[number].fact
        <<endl;
    }
    else
        cout<<"����ְ����Χ"<<endl;
    //cout.setf(ios::right);
}

void Compute(vector<struct Wage> &wage)
{
    for(int i=0;i<wage.size();i++)
    {
        wage[i].fact=wage[i].base+wage[i].add-wage[i].sub;
    }
}

void Sort(vector<struct Wage> &wage)
{
    struct Wage change;

    for(int j=0;j<wage.size()-1;j++)
    {
        for(int i=j;i<wage.size()-1;i++)
        {
            if(wage[i].number>wage[i+1].number)
            {
                change=wage[i];
                wage[i]=wage[i+1];
                wage[i+1]=change;
            }
        }
    }
}

int Search(vector<struct Wage> wage,int number)
{
    int left=0,right=wage.size()-1,seek=(wage.size()-1)/2;
    for(;left!=right;)
    {
        if(number>wage[seek].number)
            left=seek;
        else if(number<wage[seek].number)
            right=seek;
        else if(number==wage[seek].number)
            {
                //cout<<"num:%d name:%s base:%d add:%d sub:%d fact:%d\n",
                //wage[seek].number,wage[seek].name,wage[seek].base,wage[seek].add,wage[seek].sub,wage[seek].fact
                //);
                ShowStaff(wage,seek);
                return seek;
            }
        seek=(left+right)/2;
    }
    cout<<"û�д�ְ����"<<endl;
    return -1;
}

void Output(vector<struct Wage> wage,string name)
{
    char date[20];
    struct tm *timep;
    time_t timel;
    int i;

    time(&timel);
    timep=localtime(&timel);
    sprintf(date,"%d/%d/%d",timep->tm_year+1900,timep->tm_mon+1,timep->tm_mday);

    ofstream outfile;
    outfile.open("gzbb.dat",ios::out|ios::trunc);
    outfile<<"\t\t\t\t\tGong zi Bao Biao\n";
    outfile<<"************************************************************\n";
    outfile<<"\tnum\t\tname\t\tbase\tadd\t\tsub\t\tfact\n";
    
    for(int i=0;i<wage.size();i++)
    {
        outfile.setf(ios::left);
        outfile
        <<"\t"<<setw(7)<<wage[i].number
        <<"\t"<<setw(10)<<wage[i].name
        <<"\t"<<setw(7)<<wage[i].base
        <<"\t"<<setw(7)<<wage[i].add
        <<"\t"<<setw(7)<<wage[i].sub
        <<"\t"<<setw(7)<<wage[i].fact
        <<endl;
    }
    outfile.setf(ios::right);
    outfile<<"************************************************************\n";
    outfile<<"\t\t\t\t\t\t\t\t\t\t\tname:"<<name<<endl;
    outfile<<"\t\t\t\t\t\t\t\t\t\t\tdate:"<<date<<endl;

    outfile.close();
}