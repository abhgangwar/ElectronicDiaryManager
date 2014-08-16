#include<fstream>
#include<iostream>
#include<string.h>
#include<math.h>
#include<stdlib.h>
#include<string.h>
#include<stdio.h>
#include<termios.h>

using namespace std;
char cl; // to empty input buffer using cin.get(cl)
int n=1; // to check max no of login attempts in logmenu()
/*                                                        
                                                     $$$ USER CLASS DECLARATION $$$


*/


static struct termios old,cur;

void set_echo_opt(int echo)
{
tcgetattr(0, &cur);
old = cur; //copy current setting to other termios type variable old for futher recovery of terminal to its normal state
cur.c_lflag= ~ICANON; // set non-buffered io [non canonical input(no lne editing... see "man termios" for help)]
cur.c_lflag=echo ? ECHO : ~ECHO; //set terminal to no echo if echo=0
tcsetattr(0,TCSANOW, &cur); //apply cur termios setting to terminal immediately(TCSANOW) 
}

void restore_old()
{
tcsetattr(0, TCSANOW, &old);
}

void _getch(int echo)
{
set_echo_opt(echo);
}


char gch;
char getch()
{
_getch(0);
cin.get(gch);
restore_old();
return gch;
}

char getche()
{
_getch(1);
cin.get(gch);
restore_old();
return gch;
}

char getpass(char tpass[])
{
int i=0;
char ch;
while(1)
{
ch=getch();
if(int(ch)==13 || i==15)
break;
tpass[i]=ch;
i++;
}

}



class date
{
public:
int dt[4];
unsigned long a;
long double b;
int cdate(int *q)
{
int r;
if(*q==dt[2]&&*(q+2)==dt[1]&&*(q+4)==dt[0])
r=1;
else
r=0;
return r;
}


};

class entry
{
date d1,d2;
public:
int k;
date getdate()
{
date tempd;
cout<<"\nEnter day [interger]:";
cin>>tempd.dt[0];
cout<<"Enter month [integer]:";
cin>>tempd.dt[1];
cout<<"Enter year [integre]:";
cin>>tempd.dt[2];
return tempd;
}

int checkdate(date supp,date str)
{
int r;
if(supp.dt[0]==str.dt[0]&&supp.dt[1]==str.dt[1]&&supp.dt[2]==str.dt[2])
r=1;
else
r=0;
return r;
}

int plentry(char usr1[])
{
char temp[40],ch;
strcpy(temp,".");
strcat(temp,usr1);
strcat(temp,"temp");
ifstream fpl;
fpl.open(temp,ios::in);
while(fpl)
{
fpl.get(ch);
cout<<ch;
}

return 1;
}

int ppentry(char usr1[])
{
date suppd;
char usr[31];
int r=0;
cout<<"\nplease enter the following details to view a perticular date entry\n";
suppd=getdate();
ifstream finpp;
strcpy(usr,".");
strcat(usr,usr1);
finpp.open(usr,ios::in);
if(finpp)
{
long double pos,pos1;
while(finpp)
{
finpp.read((char *) &d1,sizeof(d1));
r=checkdate(suppd,d1);
pos=finpp.tellg();
pos1=pos+d1.b;
if(r==1)
{
char ch;
system("clear");
printf("%50s","			              Entry you requested\n\n\n");
while(pos1>=pos)
{
finpp.get(ch);
cout<<ch;
pos++;
}
break;
}
else
finpp.seekg(pos1+1);
}
if(r==0)
cout<<"\nNo entry on the date provoded is registered\n";
getch();
}
else
cout<<"\nError in opening file\n";
finpp.close();
return r;
}


int wentry(char usr1[],unsigned long & m)
{
int i,r=1;
char text,usr[30],temp[36];
strcpy(usr,".");
strcat(usr,usr1);
strcat(temp,usr);
strcat(temp,"temp");
ofstream fout;
fout.open(usr,ios::app);
if(!fout)
cout<<"error in openinig main users file";
d2.b=fout.tellp();
cout<<"\npress any key to continue";
getch();
date dtae;
dtae=getdate();
d2.dt[0]=dtae.dt[0];d2.dt[1]=dtae.dt[1];d2.dt[2]=dtae.dt[2];
cout<<"\npress any key to proceed";
getch();
system("clear");
puts("                                                     Write An Entry\n");
puts("                                    Please press ctr+F and Enter to save your entry when finished\n");
i=0;
ofstream ftemp;
ftemp.open(temp,ios::out);
while(1)
 {
        cin.get(text);
        if(int(text)==6)
        {
        break;
        }
        ftemp.put(text);
	i++;
 }
d2.b=i;
fout.write((char *) &d2,sizeof(d2));
ftemp.close();
ifstream ftemp1;
ftemp1.open(temp,ios::in);
while(ftemp1)
{
ftemp1.get(text);
fout.put(text);
}
ftemp1.close();
fout.close();
return r;

}

};


class users
{
long pwdi;
unsigned long m;
public:
char uname[30];
entry e;
char getdata()
{
cout<<"Press any key to continue\n";
getch();
cout<<"Enter UserName [max 20 characters]:";
cin.getline(uname,29,'\n');
cout<<"Enter Paasword [max 16 characters will be accepted]: ";
char pwd[17],tm;
int i=0;
getpass(pwd);
pwdi=hash(pwd);
}

int count()
{
m=0;
return m;
}

long hash(char p[])
{
long temp=0;
int l=strlen(p);
int i;
for(i=0;i<l;i++)
temp+=pow(13,i)*p[i];
return temp;
}
int checkhash(char p[])
{
int r;
if(hash(p)==pwdi)
{
r=1;
}
else
r=0;
return r;
}
void umenu()
{
system("clear");
char c;
cout<<"\nPlease pick up a right choice[1,2,3]:\n1.Write a new entry\n2.View last entry\n3.View a perticular entry\n4.Exit\n";
c=getch();
switch(c)
{
case '1':
        system("clear");
        printf("%50s","Write a new entry\n");
        e.wentry(uname,m);
	cout<<"\n\n\npress any key continue\n";
	getch();
	system("clear");
	umenu();
        break;
case '2':
        system("clear");
        printf("%50s","				Your last entry\n\n\n");
        e.plentry(uname);
	cout<<"\n\n\nPress any key to continue\n";
	getch();
	system("clear");
	umenu();
        break;
case '3':
        system("clear");
        e.ppentry(uname);
	cout<<"\n\n\nPress any key to continue\n";
	getch();
	system("clear");
	umenu();
        break;
case '4':
        exit(1);
default:
        cout<<"\nPlease enter a valid choice only[1,2,3]\nPress '1' or '2' or '3' '4' from your keyboard buttons\nPress any key to continue\n";
	getch();
        umenu();
        break;
}
}

}u;

/*                                                         $$$ USER CLASS DECLARATION ENDS HERE $$$
 
                                                       Different function definitions starts from here now




                                                       $$$ FUNCTION TO CHECK REGISTRATION OF A USER $$$


*/
int ureg(char usr[])
{
int r=0;
ifstream fin;
fin.open(".users",ios::in);
if(!fin)
{
        cout<<"\nSorry you don't have enough permissions to access program\n\nAsk your adminitrator to help you out\n";
        cout<<"Press any key to exit";
        getch();
	cout<<"\n";
        exit(1);
}
while(fin)
{
        fin.read((char *) &u,sizeof(u));
        if(!strcmp(u.uname,usr))
        {
        r=1;
        break;
        }

}
return r;
}
/*                                                           $$$ FUNCTION TO REGISTER A NEW USER $$$


*/

void reg()
{
        system("clear");
        printf("%50s","                                 Please Enter following details to register\n");
        u.getdata();
        ofstream fout;
        fout.open(".users",ios::app);
        if(!fout)
        {
        cout<<"\nSorry users database file couldn't be opened\n Ask your administrator to help you\nbreaking......\n";
        exit(1);
        }
        u.count();
        fout.write((char *) &u,sizeof(u));
        cout<<"\nYour diary has been successfully created...now you can login\n  <<press any key to continue\n";
	getch();
        fout.close();
        u.umenu();
}
/*

                                                             $$$ FuUNCTION TO RECEIVE LOGIN DETAILS $$$


*/


int logmenu()
{
        int r=0;
        cout<<"\nPress any to continue\n";
        getch();
        system("clear");
        printf("%50s","Enter Login Details\n\n\n");
        cout<<"UserName:";
        char usr[20];
        cin.getline(usr,29,'\n');
        if(!ureg(usr))
        {
                cout<<"\nSorry you are not registered...please creat a diary first to login\n";
                cout<<"do you want to create a diary[y/n]:";
		cin.get(cl);
		if(cl=='y'||cl=='Y')
                r=1; // ERROR CODE "r=1" IF USER IS NOT REGISTERED
        }
        else
        {
        char p[17];
        cout<<"Enter Password:";
        getpass(p);
        if(!u.checkhash(p))
        {
                cout<<"Incorrect password\nTry again\n";
                r=2;  // ERROR CODE "r=2" IF PASSWORD PROVIDED IS INCORRECT
                n++;
                if(n<=3)
                logmenu();
                else
                {
                cout<<"Sorry you have attempted maximum times.......press any key to exit\n";
                getch();
                exit(1);
                }
        }
        else
        u.umenu();
        }
return r;
}

char opmenu()
{
int r;
cout<<"Pick up a choice[1,2]:\n"
    <<"1.New User...Create a diary\n"
    <<"2.Login...Already have a diary\n"
    <<"3.Exit\n";
char ch;
ch=getch();
switch(ch)
{
case '1':
        reg();
     /* if(r!=0)
        cout<<"\n Sorry an unknown error occured....Press any key to exit";
        cin.get(cl);
        cin.get(cl);
        exit(1);  */
        break;
case '2':
        r=logmenu();
        if(r==1)
        reg();
        break;
case '3':
        exit(1);
        break;
default:
        cout<<"Please Enter right choice[1,2] and try again";
        break;
}
return r;
}


/*                                                                   Fuction definitons are ended here



                                                               $$$  MAIN FUNTION BELOW HERE [int main()] $$$


*/
int main()
{
opmenu();
return 0;
}  
