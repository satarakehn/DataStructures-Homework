#include <iostream>
#include <fstream>
#include <string>
#include <sstream> 
using namespace std;


struct studentData {
    string studentName;
    int homework;
    int recitation;
    int quiz;
    int exam; 
    double average; 
};

void addStudentData(studentData students[],string studentName, int homework, int recitation, int quiz, int exam, int length);
char calcLetter(double avg);
void printList(const studentData students[],int length);

int main(int argc, char* argv[])
{
    //variable char upperbound and char lower bound, initiate them to argv[2][0], upper argv[3][0]
    //if student average is equal to lower or upper, 
    char lwb_Grade=argv[3][0];
    char upb_Grade=argv[4][0];

    studentData students[100];
    int length = 0;
    string line;
    string fileName = argv[1];

    ofstream out_file;
    ifstream file(fileName);
    if(file.is_open()){
        while(getline(file,line)){
            stringstream s(line);
            string temp;
            string studentName;
            int homework;
            int recitation;
            int quiz;
            int  exam;
            getline(s,studentName,',');
            getline(s,temp,',');
            homework = stoi(temp);
            getline(s,temp,',');
            recitation = stoi(temp);
            getline(s,temp,',');
            quiz = stoi(temp);
            getline(s,temp);
            exam = stoi(temp);
            addStudentData(students,studentName,homework,recitation, quiz, exam ,length);
            length++;
        }
        printList(students,length);
        out_file.open(argv[2]);
        for(int i =0; i < length; i++){
            if(calcLetter(students[i].average)<= lwb_Grade && calcLetter(students[i].average) >= upb_Grade){
                 out_file << students[i].studentName << "," << students[i].average <<","<< calcLetter(students[i].average) << endl;

            }
        }

    }
    out_file.close();
    file.close();
 

}

void addStudentData(studentData students[],string studentName, int homework, int recitation, int quiz, int exam, int length){
    students[length].studentName =studentName;
    students[length].homework =homework;
    students[length].recitation =recitation;
    students[length].quiz =quiz;
    students[length].exam =exam;
    students[length].average = ((double)(homework+recitation+exam+quiz))/4;
    //void function so does not return anything
}

char calcLetter(double avg){
    if(avg>=90){
        return 'A';
    }else if(avg >=80 && avg <= 89.99){
        return 'B';
    }else if(avg>=70 && avg <= 79.99){
        return 'C';
    }else if(avg>=60 && avg<= 69.99){
        return 'D';
    }else{
        return 'F';
    }
}
void printList(const studentData students[],int length){
    for(int i=0;i < length;i++){
        cout << students[i].studentName << " earned " << students[i].average << " which is an "<< calcLetter(students[i].average)<<endl;
    }
}

