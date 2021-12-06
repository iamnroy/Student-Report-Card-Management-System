#include<iostream>
#include<fstream>
#include<iomanip>
using namespace std;

class Student
{
	int rollno;
	char name[50];
	int e_marks, p_marks, c_marks, cs_marks, m_marks;
	double per;
	char grade;
	void calculate();	
public:
	void getdata();  	
	void showdata();	
	void show_tabular();
	int retrollno();
	
};
void   Student::calculate()
{
	per=(p_marks+c_marks+m_marks+e_marks+cs_marks)/5.0;
	if(per>=60)
		grade='A';
	else if(per>=50)
		grade='B';
	else if(per>=33)
		grade='C';
	else
		grade='F';
}

 void  Student::getdata()
{
	cout<<"\nEnter The roll number of student ";
	cin>>rollno;
	cout<<"\n\nEnter The Name of student ";
	cin.ignore();
	cin.getline(name,50);
	cout<<"\nEnter The marks in English: ";
	cin>>e_marks;
	cout<<"\nEnter The marks in Physics: ";
	cin>>p_marks;
	cout<<"\nEnter The marks in Chemistry: ";
	cin>>c_marks;
	cout<<"\nEnter The marks in Computer Science: ";
	cin>>cs_marks;
	cout<<"\nEnter The marks in Math: ";
	cin>>m_marks;
	calculate();
}
 void  Student::showdata()
{
	
	cout<<"\nRoll number of student : "<<rollno;
	cout<<"\nName of student : "<<name;
	cout<<"\nMarks in English : "<<e_marks;
	cout<<"\nMarks in Physics : "<<p_marks;
	cout<<"\nMarks in Chemistry : "<<c_marks;
	cout<<"\nMarks in Computer Science : "<<cs_marks;
	cout<<"\nMarks in Math :"<<m_marks;
	cout<<"\nPercentage of student is  :"<<per;
	cout<<"\nGrade of student is :"<<grade;
}
   void Student::show_tabular()
{
	cout<<rollno<<setw(6)<<" "<<name<<setw(10)<<p_marks<<setw(4)<<c_marks<<setw(4)<<m_marks<<setw(4)<<e_marks<<setw(4)<<cs_marks<<setw(8)<<per<<setw(6)<<grade<<endl;
}

int  Student::retrollno() 
{
	return rollno;
}

//function decleration
void write_student();	
void display_all();		
void display_sp(int);	
void modify_student(int);	
void delete_student(int);
void class_result();
void result();	
void intro();	
void entry_menu();

//main function
int main()
{
		char ch;
        intro();
	do
	{
		system("cls");
		cout<<"\n\n\n\tMAIN MENU";
		cout<<"\n\n\t01. RESULT MENU";
		cout<<"\n\n\t02. ENTRY/EDIT MENU";
		cout<<"\n\n\t03. EXIT";
		cout<<"\n\n\tPlease Select Your Option (1-3) ";
		cin>>ch;
		switch(ch)
		{
			case '1': result();
				break;
			case '2': entry_menu();
				break;
			case '3':
				break;
		}
    }while(ch!='3');
	return 0;
}

//write in file function
void write_student()
{
	Student st;
	ofstream outFile;
	outFile.open("student.dat",ios::binary|ios::app);
	st.getdata();
	outFile.write((char*) (&st), sizeof(Student));
	outFile.close();
    cout<<"\n\nStudent record Has Been Created ";
	cin.ignore();
	cin.get();
}

//read file function
void display_all()
{
	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open.";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tDISPLAY ALL RECORD\n\n";
	while(inFile.read((char*) (&st), sizeof(Student)))
	{
		st.showdata();
		cout<<"\n\n.....................................\n";
	}
	inFile.close();
	cin.ignore();
	cin.get();
}

//function to read specific record from file
void display_sp(int n)
{
	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	bool flag=false;
	while(inFile.read((char*) (&st), sizeof(Student)))
	{
		if(st.retrollno()==n)
		{
	  		 st.showdata();
	  		  flag=true;
		}
	}
	inFile.close();
	if(flag==false)
		cout<<"\n\nrecord not exist";
	cin.ignore();
	cin.get();
}

//modify record function
void modify_student(int n)
{
	bool found=false;
	Student st;
	fstream File;
	File.open("student.dat",ios::binary|ios::in|ios::out);
	if(!File)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	while(!File.eof() && found==false)
	{
		File.read((char*)(&st), sizeof(Student));
		if(st.retrollno()==n)
		{
			st.showdata();
			cout<<"\n\nPlease Enter The New Details of student"<<endl;
			st.getdata();
		    File.write((char*) (&st), sizeof(Student));
		    cout<<"\n\n\t Record Updated";
		    found=true;
		}
	}
	File.close();
	if(found==false)
		cout<<"\n\n Record Not Found ";
	cin.ignore();
	cin.get();

}

//delete file function
void delete_student(int n)
{
	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	ofstream outFile;
	outFile.open("Temp.dat",ios::out);
		while(inFile.read((char*)(&st), sizeof(Student)))
	{
		if(st.retrollno()!=n)
		{
			outFile.write((char * )(&st), sizeof(Student));
		}
	}
	outFile.close();
	inFile.close();
	remove("student.dat");
	rename("Temp.dat","student.dat");
	cout<<"\n\n\tRecord Deleted ..";
	cin.ignore();
	cin.get();
}

//display student report
void class_result()
{
	Student st;
	ifstream inFile;
	inFile.open("student.dat",ios::binary);
	if(!inFile)
	{
		cout<<"File could not be open !! Press any Key...";
		cin.ignore();
		cin.get();
		return;
	}
	cout<<"\n\n\t\tALL STUDENTS RESULT \n\n";
	cout<<"..................................................................\n";
	cout<<"R.No  Name   Eng   Phy   Che  CS   Math   %   Grade"<<endl;
	cout<<"..................................................................\n";
	while(inFile.read((char *) (&st), sizeof(Student)))
	{
		st.show_tabular();
	}
	cin.ignore();
	cin.get();
	inFile.close();
}

//result menu function
void result()
{
	char ch;
	int rno;
     system("cls");
	cout<<"\n\n\n\tRESULT MENU";
	cout<<"\n\n\n\t1. Class Result";
	cout<<"\n\n\t2. Student Report Card";
	cout<<"\n\n\t3. Back to Main Menu";
	cout<<"\n\n\n\tEnter Choice (1/2/3)? ";
	cin>>ch;
	switch(ch)
	{
	case '1' :	class_result();
	 break;
	case '2' :	cout<<"\n\n\tEnter Roll Number Of Student : "; cin>>rno;
				display_sp(rno);
				 break;
	case '3' :	break;
  
	}
}

void intro()
{
	cout<<"\n\n\n\t\t  STUDENT";
	cout<<"\n\n\t\tREPORT CARD";
	cout<<"\n\n\t\tCLASS PROJECT";
	cout<<"\n\t\tTHE BRITISH COLLEGE";
	cin.get();
}

//menu function
void entry_menu()
{
	char ch;
	int num;
	system("cls");
	cout<<"\n\n\n\tENTRY MENU";
	cout<<"\n\n\t1.CREATE STUDENT RECORD";
	cout<<"\n\n\t2.DISPLAY ALL STUDENTS RECORDS";
	cout<<"\n\n\t3.SEARCH STUDENT RECORD ";
	cout<<"\n\n\t4.MODIFY STUDENT RECORD";
	cout<<"\n\n\t5.DELETE STUDENT RECORD";
	cout<<"\n\n\t6.BACK TO MAIN MENU";
	cout<<"\n\n\tPlease Enter Your Choice (1-6) ";
	cin>>ch;
	switch(ch)
	{
	case '1':	write_student(); 
	break;
	case '2':	display_all(); 
	break;
	case '3':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				display_sp(num); 
				break;
	case '4':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				modify_student(num);
				break;
	case '5':	cout<<"\n\n\tPlease Enter The roll number "; cin>>num;
				delete_student(num);
				break;

	
	}
}

