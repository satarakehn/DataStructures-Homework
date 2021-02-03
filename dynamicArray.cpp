#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;

struct wordRecord{
    string word;
    int count;
};

void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]);
bool isIgnoreWord(string word, string ignoreWords[]);
int getTotalNumberNonIgnoreWords(wordRecord distinctWords[],int length);
void sortArray(wordRecord distinctWords[], int length);
void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords);


int main(int argc, char *argv[])
{
    if(argc != 4){
        cout << "Usage: Assignment2Solution <number of works> <inputfilename.txt> <ignoreWordsfilename.txt>" << endl;
        return -1;
    }
    
    //set size to 100, doublesize if array is full
    int index = 0; //find out where 
    int size =100;
    int doublesize = 0; 
    int *newarray;

    wordRecord *distinctWords = new wordRecord[size];

    string ignoreWords[50];
    getIgnoreWords(argv[3],ignoreWords);
    int position = stoi(argv[1]);
    string line; 
    ifstream file;
    file.open(argv[2]);
    
    //if(file.is_open()) //scan for isIgnoreWord if, scan for a duplicate as our for loop we need to make our own, then if we pass both if it isnot ignore or duplicate, then store it in array 

    //while to start start with a fail pass 
    if(!file.is_open()){
        cout << "File has failed to open. " << endl;
        return -1;
    }
    
    while(file >> line)
        {   
            bool check = false; //bool variable set to false to catch to see whether if ignorewords has already been used
            if(isIgnoreWord(line,ignoreWords) == false)
            {
                for(int i = 0; i < index; i++)
                {
                    if(line == (distinctWords+i) -> word)
                    {
                        (distinctWords+i) -> count++; //increminting
                        check = true;
                    }
                }
                if(check == false)
                {
                    if(index == size)
                    {
                        size = size * 2; //doubling the size
                        wordRecord *copyArray = new wordRecord[size];//assigning elements disctint words to copy array //for loop 
                        for(int i = 0; i < size / 2; i++)
                        {
                            copyArray[i]=distinctWords[i];
                        } 
                        delete[] distinctWords;
                        distinctWords = copyArray; 
                        distinctWords[index].word = line;
                        distinctWords[index].count = 1;
                        index++;
                        doublesize++;
                    }else{
                        distinctWords[index].word = line;
                        distinctWords[index].count = 1;
                        index++;
                    }
            
                }
            }
            
    
        }

    file.close();
    cout << "Array doubled: " << doublesize << endl; 
    cout << "Distinct non-common words: " << index << endl;
    cout << "Total non-common words: " << getTotalNumberNonIgnoreWords(distinctWords,size) << endl;
    cout << "Probability of next 10 words from rank " << argv[1] << endl;
    cout << "---------------------------------------" << endl;
    printTenFromN(distinctWords, position ,getTotalNumberNonIgnoreWords(distinctWords,size));
    return 0;

}


void getIgnoreWords(const char *ignoreWordFileName, string ignoreWords[]){
    int i = 0;
    string newString;
    ifstream file;
    file.open(ignoreWordFileName);
    if(file.fail()){
        return;
    }else{
        while(getline(file,newString)){
            ignoreWords[i]=newString;
            i++;
        }

    }
}; //WORKS

bool isIgnoreWord(string word, string ignoreWords[]){
    for(int i =0; i <50;i++){
        if(ignoreWords[i] == word)
        {
            return true;
        }
    }
    return false;
}; //WORKS NOW

int getTotalNumberNonIgnoreWords(wordRecord distinctWords[],int length){
    int total = 0;
    for(int i =0; i<length;i++){
        total += distinctWords[i].count;
    }
    return total;
}; //WORKS

void sortArray(wordRecord distinctWords[], int length){
    for(int i=0; i < length; i++){
        for(int j = 0;j < length - i;j++){
            if(distinctWords[j].count < distinctWords[j+1].count){
                //wordRecord temp = distinctWords[j];
                //distinctWords[j]=distinctWords[j+1];
                //distinctWords[j+1] = temp;
                swap(distinctWords[j],distinctWords[j+1]);
            }
            else if(distinctWords[j].count == distinctWords[j+1].count)
            {
                if(int(distinctWords[j].word[0]) > int(distinctWords[j+1].word[0]))
                    swap(distinctWords[j],distinctWords[j+1]);
            }
        }
    }
    //bubble sort 

}; //WORKS NOW

void printTenFromN(wordRecord distinctWords[], int N, int totalNumWords){

    for(int i = N; i < N + 10; i++){
        float prob1 = (float) distinctWords[i].count /totalNumWords;
        cout << setprecision(5) << fixed << prob1 << " - " << distinctWords[i].word << endl;
    }
};