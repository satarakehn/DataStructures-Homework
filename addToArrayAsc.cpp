#include <iostream>
#include <fstream>
using namespace std;

int addToArrayAsc(float sortedArray[],int numElements,float newValue);

int main(int argc, char *argv[])
{
    float sortedArray[100];
    int numElements = 0;
    ifstream infile; //using page 141 of cplusplus
    infile.open("infile.txt");
    if(infile.is_open()){
      while(!infile.eof())
      {
        string line =" ";
        getline(infile,line);
        addToArrayAsc(sortedArray,numElements,stof(line));
        numElements++;
        for(int i=0;i<numElements;i++){
        cout << sortedArray[i] << "," ;
    }
        cout << endl;
    }
        infile.close();
    }
    else cout << "Failed to open the file.";

    
    return 0;
}

int addToArrayAsc(float sortedArray[],int numElements,float newValue){
    sortedArray[numElements] = newValue;
    for(int i=0;i<numElements;i++)
    {
        for(int j=0;j<numElements;j++)
        {
            if(sortedArray[j]>sortedArray[j+1])
            {
                newValue=sortedArray[j];
                sortedArray[j]=sortedArray[j+1];
                sortedArray[j+1]=newValue;
            }
        }
    }
    return numElements+1;
}   
