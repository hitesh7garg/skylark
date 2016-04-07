#include<iostream>
#include<fstream>
#include<string>
#include <sstream>
using namespace std;
void readFile()
{
    ifstream file;
    
    file.open ("wordsEn.txt");
    if (!file.is_open()) return;

    string word;
    while (file >> word)
    {
    	int n=word.length();
    	
    	fstream filestr;
    	string Result;//string which will contain the result

		stringstream convert; // stringstream used for the conversion
		
		convert << n;//add the value of Number to the characters in the stream
		
		Result = convert.str();

  		filestr.open (Result+".txt", fstream::in | fstream::out | fstream::app);

    	filestr<<word<<"\n";
    	
        
    }
}
int main(){
	readFile();
	return 0;
}
