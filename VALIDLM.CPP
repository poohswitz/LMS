
//***************************************************************
//                   HEADER FILE USED IN PROJECT
//****************************************************************
#include<ctype.h>
#include<fstream.h>
#include<conio.h>
#include<stdio.h>
#include<process.h>
#include<string.h>
#include<iomanip.h>

//***************************************************************
//                   CLASS USED IN PROJECT
//****************************************************************


class book
{  	public:
	int bno;
	char bname[50];
	char aname[20];
	void create_book();
	void show_book();
	void modify_book();

	int retbno()
	{
	return bno;
	}

	void report()
	{
	cout<<bno<<setw(30)<<bname<<setw(30)<<aname<<endl;
	}
};
class student
{ public:
    int admno;
    char name[20];
    int stbno;
    int token;
    void create_student();
    void show_student();
    void modify_student();

    int retadmno()
    {
	return admno;
    }

    int retstbno()
    {
	return stbno;
    }

    int rettoken()
    {
	return token;
    }

    void addtoken()
    {token=1;}

    void resettoken()
    {token=0;}

    void getstbno(int t)
    {
     stbno=t;
    }

    void report()
    {cout<<"\t"<<admno<<setw(20)<<name<<setw(10)<<token<<endl;}

};         //class ends here   //class ends here


void book::create_book()
{
	cout<<"\nNEW BOOK ENTRY...\n";
	cout<<"\nEnter The book no.\t";
	cin>>bno;
	cout<<"\n\nEnter The Name of The Book \t";
	gets(bname);
	int j=0;
	while(bname[j]!='\0')
	{
	for(int i=0;i<strlen(bname);i++)
	{
	if(isalpha(bname[i])==0)
	{
	cout<<"Enter proper book name with alphabets only\t";
	gets(bname);
	}
	}
	j++;
	}
	cout<<"\n\nEnter The Author's Name ";
	gets(aname);
	int a=0;
	while(aname[a]!='\0')
	{
	for(int b=0;b<strlen(aname);b++)
	{
	if(isalpha(aname[b])==0)
	{
	cout<<"Enter proper author name with alphabets only\t";
	gets(aname);
	}
	}
	a++;
	}
	cout<<"\n\n\nBook Created..";
	}


void book::show_book()
    {
	cout<<"\nBook no. : "<<bno;
	cout<<"\nBook Name : ";
	puts(bname);
	cout<<"Author Name : ";
	puts(aname);
    }
void book::modify_book()
    {
	cout<<"\nBook no. : "<<bno;
	cout<<"\nModify Book Name : ";
	gets(bname);
	cout<<"\nModify Author's Name of Book : ";
	gets(aname);
    }

 void student::create_student()
    {
	clrscr();
	cout<<"\nNEW STUDENT ENTRY...\n";
	cout<<"\nEnter The admission no. ";
	cin>>admno;
	cout<<"\n\nEnter The Name of The Student ";
	gets(name);
	int j=0;
	while(name[j]!='\0')
	{
	for(int i=0;i<strlen(name);i++)
	{
	if(isalpha(name[i])==0)
	{
	cout<<"Enter proper student name with alphabets only\t";
	gets(name);
	}
	}
	j++;
	}
	token=0;
	stbno=0;
	cout<<"\n\nStudent Record Created..";
    }
 void student::show_student()
    {
	cout<<"\nAdmission no. : ";
	cin>>admno;
	cout<<"\nStudent Name : ";
	puts(name);
	cout<<"\nNo of Book issued : ";
	cin>>token;
	if(token==1)
	    cout<<"\nBook No ";
	    cin>>stbno;
    }

 void student:: modify_student()
    {
	cout<<"\nAdmission no. : "<<admno;
	cout<<"\nModify Student Name : ";
	gets(name);
    }

//***************************************************************
//        global declaration for stream object, object
//****************************************************************

fstream fp,fp1;
book bk;
student st;


//***************************************************************
//        function to write in file
//****************************************************************

void write_book()
{
    char ch;
    fp.open("book.dat",ios::out|ios::app);
    do
    {
	clrscr();
	bk.create_book();
	fp.write((char*)&bk,sizeof(book));
	cout<<"\n\nDo you want to add more record..(y/n?)";
	cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}

void write_student()
{
    char ch;
    fp.open("student.dat",ios::out|ios::app);
    do
    {
	st.create_student();
	fp.write((char*)&st,sizeof(student));
	cout<<"\n\ndo you want to add more record..(y/n?)";
	cin>>ch;
    }while(ch=='y'||ch=='Y');
    fp.close();
}


//***************************************************************
//        function to read specific record from file
//****************************************************************


void display_spb(int n)
{
    cout<<"\nBOOK DETAILS\n";
    int flag=0;
    fp.open("book.dat",ios::in);
    while(fp.read((char*)&bk,sizeof(book)))
    {
	if(bk.retbno()==int(n))
	{
	    bk.show_book();
	     flag=1;
	}
    }

    fp.close();
    if(flag==0)
	cout<<"\n\nBook does not exist";
    getch();
}

void display_sps(int n)
{
    cout<<"\nSTUDENT DETAILS\n";
    int flag=0;
    fp.open("student.dat",ios::in);
    while(fp.read((char*)&st,sizeof(student)))
    {
	if(st.retadmno()==n)
	{
	    st.show_student();
	    flag=1;
	}
    }

    fp.close();
    if(flag==0)
	    cout<<"\n\nStudent does not exist";
     getch();
}


//***************************************************************
//        function to modify record of file
//****************************************************************


void modify_book()
{
    int n;
    int found=0;
    clrscr();
    cout<<"\n\n\tMODIFY BOOK REOCORD.... ";
    cout<<"\n\n\tEnter The book no. of The book";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&bk,sizeof(book)) && found==0)
    {
	if(bk.retbno()==n)
	{
	    bk.show_book();
	    cout<<"\nEnter The New Details of book"<<endl;
	    bk.modify_book();
	    int pos=-1*sizeof(bk);
		fp.seekp(pos,ios::cur);
		fp.write((char*)&bk,sizeof(book));
		cout<<"\n\n\t Record Updated";
		found=1;
	}
    }

	fp.close();
	if(found==0)
	    cout<<"\n\n Record Not Found ";
	getch();
}


void modify_student()
{
    int n;
    int found=0;
    clrscr();
    cout<<"\n\n\tMODIFY STUDENT RECORD... ";
    cout<<"\n\n\tEnter The admission no. of The student";
    cin>>n;
    fp.open("student.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
    {
	if(st.retadmno()==n)
	{
	    st.show_student();
	    cout<<"\nEnter The New Details of student"<<endl;
	    st.modify_student();
	    int pos=-1*sizeof(st);
	    fp.seekp(pos,ios::cur);
	    fp.write((char*)&st,sizeof(student));
	    cout<<"\n\n\t Record Updated";
	    found=1;
	}
    }

    fp.close();
    if(found==0)
	cout<<"\n\n Record Not Found ";
    getch();
}

//***************************************************************
//        function to delete record of file
//****************************************************************


void delete_student()
{
    int n;
    int flag=0;
    clrscr();
	cout<<"\n\n\n\tDELETE STUDENT...";
	cout<<"\n\nEnter The admission no. of the Student You Want To Delete : ";
	cin>>n;
	fp.open("student.dat",ios::in|ios::out);
	fstream fp2;
	fp2.open("Temp.dat",ios::out);
	fp.seekg(0,ios::beg);
	while(fp.read((char*)&st,sizeof(student)))
    {
	if(st.retadmno()!=n)
		 fp2.write((char*)&st,sizeof(student));
	else
	       flag=1;
    }

    fp2.close();
	fp.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	if(flag==1)
	     cout<<"\n\n\tRecord Deleted ..";
	else
	     cout<<"\n\nRecord not found";
	getch();
}


void delete_book()
{
    int n;
    clrscr();
    cout<<"\n\n\n\tDELETE BOOK ...";
    cout<<"\n\nEnter The Book no. of the Book You Want To Delete : ";
    cin>>n;
    fp.open("book.dat",ios::in|ios::out);
    fstream fp2;
    fp2.open("Temp.dat",ios::out);
    fp.seekg(0,ios::beg);
    while(fp.read((char*)&bk,sizeof(book)))
    {
	if(bk.retbno()!=n)
	{
	    fp2.write((char*)&bk,sizeof(book));
	}
    }

    fp2.close();
	fp.close();
	remove("book.dat");
	rename("Temp.dat","book.dat");
	cout<<"\n\n\tRecord Deleted ..";
	getch();
}



//***************************************************************
//        function to display all students list
//****************************************************************

void display_alls()
{
    clrscr();
	 fp.open("student.dat",ios::in);
	 if(!fp)
	 {
	       cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
	       getch();
	       return;
	 }

    cout<<"\n\n\t\tSTUDENT LIST\n\n";
    cout<<"==================================================================\n";
    cout<<"\tAdmission No."<<setw(10)<<"Name"<<setw(20)<<"Book Issued\n";
    cout<<"==================================================================\n";

    while(fp.read((char*)&st,sizeof(student)))
    {
	st.report();
    }

    fp.close();
    getch();
}


//***************************************************************
//        function to display Books list
//****************************************************************

void display_allb()
{
    clrscr();
    fp.open("book.dat",ios::in);
    if(!fp)
    {
	cout<<"ERROR!!! FILE COULD NOT BE OPEN ";
	       getch();
	       return;
	 }

    cout<<"\n\n\t\tBook LIST\n\n";
    cout<<"=========================================================================\n";
    cout<<"Book Number"<<setw(20)<<"Book Name"<<setw(25)<<"Author\n";
    cout<<"=========================================================================\n";

    while(fp.read((char*)&bk,sizeof(book)))
    {
	bk.report();
    }
	 fp.close();
	 getch();
}



//***************************************************************
//        function to issue book
//****************************************************************

void book_issue()
{
    int sn,bn;
    int found=0,flag=0;
    clrscr();
    cout<<"\n\nBOOK ISSUE ...";
    cout<<"\n\n\tEnter The student's admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
	fp1.open("book.dat",ios::in|ios::out);
	while(fp.read((char*)&st,sizeof(student)) && found==0)
	   {
	if(st.retadmno()==sn)
	{
	    found=1;
	    if(st.rettoken()==0)
	    {
		      cout<<"\n\n\tEnter the book no. ";
		cin>>bn;
		while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
		{
		       if(bk.retbno()==bn)
		    {
			bk.show_book();
			flag=1;
			st.addtoken();
			st.getstbno(bk.retbno());
			int pos=-1*sizeof(st);
			fp.seekp(pos,ios::cur);
			fp.write((char*)&st,sizeof(student));
			cout<<"\n\n\t Book issued successfully\n\nPlease Note: Write current date in backside of book and submit within 15 days fine Rs. 1 for each day after 15 days period";
		    }
		    }
		  if(flag==0)
			cout<<"Book no does not exist";
	    }
		else
		  cout<<"You have not returned the last book ";

	}
    }
	  if(found==0)
	cout<<"Student record not exist...";
    getch();
      fp.close();
      fp1.close();
}

//***************************************************************
//        function to deposit book
//****************************************************************

void book_deposit()
{
    int sn,bn;
    int found=0,flag=0,day,fine;
    clrscr();
    cout<<"\n\nBOOK DEPOSIT ...";
    cout<<"\n\n\tEnter The studentâ€™s admission no.";
    cin>>sn;
    fp.open("student.dat",ios::in|ios::out);
    fp1.open("book.dat",ios::in|ios::out);
    while(fp.read((char*)&st,sizeof(student)) && found==0)
       {
	if(st.retadmno()==sn)
	{
	    found=1;
	    if(st.rettoken()==1)
	    {
	    while(fp1.read((char*)&bk,sizeof(book))&& flag==0)
	    {
	       if(bk.retbno()==st.retstbno())
	    {
		bk.show_book();
		flag=1;
		cout<<"\n\nBook deposited in no. of days";
		cin>>day;
		if(day>15)
		{
		   fine=(day-15)*1;
		   cout<<"\n\nFine has to deposited Rs. "<<fine;
		}
		    st.resettoken();
		    int pos=-1*sizeof(st);
		    fp.seekp(pos,ios::cur);
		    fp.write((char*)&st,sizeof(student));
		    cout<<"\n\n\t Book deposited successfully";
	    }
	    }
	  if(flag==0)
	    cout<<"Book no does not exist";
	      }
	 else
	    cout<<"No book is issued..please check!!";
	}
       }
      if(found==0)
    cout<<"Student record not exist...";
    getch();
  fp.close();
  fp1.close();
  }




//***************************************************************
//        INTRODUCTION FUNCTION
//****************************************************************

void intro()
{
    clrscr();
    gotoxy(35,11);
    cout<<"LIBRARY";
    gotoxy(35,14);
    cout<<"MANAGEMENT";
    gotoxy(35,17);
    cout<<"SYSTEM";
    getch();
}



//***************************************************************
//        ADMINISTRATOR MENU FUNCTION
//****************************************************************

void admin_menu()
{
    clrscr();
    int ch2;
    cout<<"\n\n\n\tADMINISTRATOR MENU";
    cout<<"\n\n\t1.CREATE STUDENT RECORD";
    cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORD";
    cout<<"\n\n\t3.DISPLAY SPECIFIC STUDENT RECORD ";
    cout<<"\n\n\t4.MODIFY STUDENT RECORD";
    cout<<"\n\n\t5.DELETE STUDENT RECORD";
    cout<<"\n\n\t6.CREATE BOOK ";
    cout<<"\n\n\t7.DISPLAY ALL BOOKS ";
    cout<<"\n\n\t8.DISPLAY SPECIFIC BOOK ";
    cout<<"\n\n\t9.MODIFY BOOK ";
    cout<<"\n\n\t10.DELETE BOOK ";
    cout<<"\n\n\t11.BACK TO MAIN MENU";
    cout<<"\n\n\tPlease Enter Your Choice (1-11) ";
    cin>>ch2;
    switch(ch2)
    {
	    case 1: clrscr();
		    write_student();
		    break;
	    case 2: display_alls();
		    break;
	    case 3:
		   int num;
		   clrscr();
		   cout<<"\n\n\tPlease Enter The Admission No. ";
		   cin>>num;
		   display_sps(num);
		   break;
	      case 4: modify_student();break;
	      case 5: delete_student();break;
	case 6: clrscr();
	    write_book();break;
	case 7: display_allb();break;
	case 8: {
		   int num;
		   clrscr();
		   cout<<"\n\n\tPlease Enter The book No. ";
		   cin>>num;
		   display_spb(num);
		   break;
	    }
	      case 9: modify_book();break;
	      case 10: delete_book();break;
	     case 11: return;
	      default:cout<<"\a";
       }
       admin_menu();
}


//***************************************************************
//        THE MAIN FUNCTION OF PROGRAM
//****************************************************************


void main()
{
    char ch;
    intro();
    do
    {
	clrscr();
	cout<<"\n\n\n\tMAIN MENU";
	cout<<"\n\n\t01. BOOK ISSUE";
	cout<<"\n\n\t02. BOOK DEPOSIT";
	  cout<<"\n\n\t03. ADMINISTRATOR MENU";
	  cout<<"\n\n\t04. EXIT";
	  cout<<"\n\n\tPlease Select Your Option (1-4) ";
	  ch=getche();
	  switch(ch)
	  {
	    case '1':clrscr();
		 book_issue();
		    break;
	      case '2':book_deposit();
		     break;
	      case '3':admin_menu();
		 break;
	      case '4':exit(0);
	      default :cout<<"\a";
	}
        }while(ch!='4');
}

//***************************************************************
//                END OF PROJECT
//***************************************************************
//