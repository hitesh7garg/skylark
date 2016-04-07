/*#ifndef GRAPH_H
#define GRAPH_H*/
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<list>
#include<algorithm>
#include<queue>
#include<map>
#include<stack>


using namespace std;
class UnWUnDALGraph{
	vector < list<string> > aList;
	public :
		UnWUnDALGraph(int V){
			aList.resize(V);
		}
		bool addEdge(string src, string dest, map<string,int> wordmap){
			
			if(find(aList[wordmap[src]].begin(),aList[wordmap[src]].end(),dest)!=aList[wordmap[src]].end()){
			return false;
			}
			aList[wordmap[src]].push_back(dest);
			aList[wordmap[dest]].push_back(src);
			return true;
		}
		bool addEdge(int src, string dest){
			
			if(find(aList[src].begin(),aList[src].end(),dest)!=aList[src].end()){
			return false;
			}
			aList[src].push_back(dest);
			return true;
		}
		void ListToFile(int n, map<string,int> wordmap){
			for(long int i=0;i<aList.size();i++){
				fstream file;
				string Result;//string which will contain the result
		
				stringstream convert; // stringstream used for the conversion
				
				convert << n;//add the value of Number to the characters in the stream
				
				Result = convert.str();
		
		  		file.open (Result+"x.txt", fstream::in | fstream::out | fstream::app);
		  		file<<i<<"\t";
		
		    	for(list<string>::iterator it = aList[i].begin();it!=aList[i].end();it++){
		    		file<<*it<<"\t";
		    	}
		    	file<<"\n";
				
			}
		}
		void searchByBFS(string source,string end, map<string,int> wordmap){
			
			
			map<string,bool> visited;
			map<string,string> prev;
			queue<string>Q;
		    long int i;
			int c=0;
			string a;
			long int j=0;
			for(i=0;i<aList.size();i++){
				
				list<string>::iterator s;
				
				for(s=aList[i].begin();s!=aList[i].end();s++){
					visited[*s]=0;
					prev[*s]="b";
				}
			}	
					
					Q.push(source);
					visited[source]=1;
					
					while(!Q.empty()){
						string vc=Q.front();
						Q.pop();
						for(list<string>::iterator it = aList[wordmap[vc]].begin();(it!=aList[wordmap[vc]].end())&&(c==0);it++){
							if(visited[*it]==0){
								visited[*it]=true;
								
								Q.push(*it);
								prev[*it]=vc;
								if(*it==end){
									c=1;
									a=*it;	
								}
							}
							
						}
					}
						if(c==1){
				
				string new1;
				new1=a;
				stack<string> path;
				while(new1!="b"){
					path.push(new1);
					new1=prev[new1];
				}
				cout<<"\n";
				while(!path.empty()){
					cout<<"-->"<<path.top();
					path.pop();
				}
			}
			
		}
};
void FileToList(int n,string src, string end){
	fstream file;
	ifstream countfile;
	countfile.open("countfile.txt");
	string word;
	int count=1,value;
	while(countfile>>word){
		if(count==n){
			istringstream buffer(word);
			buffer>>value;
			break;
		}
		count++;
	}

	UnWUnDALGraph graph(value);
	
	string Result;//string which will contain the result
	
		stringstream convert;
		 // stringstream used for the conversion
		
		convert << n;//add the value of Number to the characters in the stream
		
		Result = convert.str();
			map<string,int> wordmap;
			ifstream file2;
			string word2;
			int j=0;
			file2.open(Result+".txt");
    		if (!file2.is_open()) return ;
    		while (file2 >> word2)
	    	{	
	    		wordmap[word2]=j;
	    		j++;
	    	}
	    	file2.close();
		file.open(Result+"x.txt");
		string linebuffer;

		while (file && getline(file, linebuffer)){
				if (linebuffer.length() == 0)continue;
				
				int i=0;
				char ch;
				string start;
				ch=linebuffer[0];
				start.erase();
				while(ch!='\t'){
					start.push_back(ch);
					i++;
					ch=linebuffer[i];
				}
				int startint;
				istringstream buffer(start);
				buffer>>startint;
				for(int j=i;j<linebuffer.length();j++){
					string newword;
					int nw=0;
					newword.erase();
					ch=linebuffer[j];
					while(ch!='\t'){
						newword.push_back(ch);
						j++;
						nw=1;
						ch=linebuffer[j];
					}
					
					if(nw==1){
						graph.addEdge(startint,newword);
					}
					
				}	
		}
		
		file.close();
		graph.searchByBFS(src,end,wordmap);
		
}
bool checkForOne(string word,string word1){
	int c=0,find=0;
	if(word.length()!=word1.length()){
		return 0;
	}
	for(int i=0;i<word.length();i++){
		if(word[i]!=word1[i]){
			if(find==1){
				return 0;
			}
			else{
				find=1;
			}
		}
	}
	if(find==1){
		return 1;
	}
	else{
		return 0;
	}
}
int main(){
	/*ifstream file,file2;
	long int count[28];
	for(int i=0;i<28;i++) count[i]=0;
	
    for(int i=1;i<=28;i++){
    	cout<<i;
    	string Result;//string which will contain the result

		stringstream convert; // stringstream used for the conversion
		
		convert << i;//add the value of Number to the characters in the stream
		
		Result = convert.str();
    	
    	
    	string word,word2;
    	map<string,int> wordmap;
    	file2.open(Result+".txt");
    	if (file2.is_open()) {
	    	while (file2 >> word2)
		    {
		    	wordmap[word2]=count[i-1];
		    	count[i-1]++;
		    }
		    
		    file2.close();
		}
	    fstream countfile;
	    countfile.open ("countfile.txt", fstream::in | fstream::out | fstream::app);
	    string countvalue;
	    stringstream convertn;
	    int c=count[i-1];
	    convertn<<c;
	    countvalue=convertn.str();
	    countfile<<countvalue<<"\n";
	    countfile.close();
	    
    	file.open (Result+".txt");
    	if (file.is_open()) {
    	
    	UnWUnDALGraph G(count[i-1]);
	    while (file >> word)
	    {
	    	
	    	string word1;
	    	ifstream file1;
	    	file1.open(Result+".txt");
	    	if (!file1.is_open()) return 0;
	    	while(file1>>word1){
	    		int x=checkForOne(word,word1);
	    		if(x){
	    			G.addEdge(word,word1,wordmap);
	    		}
	    	}
	    	file1.close();
	    }
	    file.close();
	    G.ListToFile(i,wordmap);
		}
	    
    }*/
    string src,dest;
    cin>>src>>dest;
    if(src.length()==dest.length())
    FileToList(src.length(),src,dest);
    else cout<<"not same length";
	return 0;
}
