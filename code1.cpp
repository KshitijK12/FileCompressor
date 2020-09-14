#include<iostream>
#include<queue>
#include<map>
#include<string>
#include<fstream>
#include<sstream>
#include<vector>
#include<bitset>
#include<algorithm>
using namespace std;
struct node
{
	char ele;
	int freq;
	node *left=NULL;
	node *right=NULL;
};

struct customCompare
{	
public:
	bool operator()(node *a,node *b)
	{ return a->freq > b->freq; }
};

string readFile(string file) //to read file for compression STEP 1
{
	ifstream ifs (file);
	string s;
	getline (ifs, s, (char) ifs.eof());
	return s;
}

vector<pair<char,int>> createFreqTable(string s) // create frequency table STEP 2
{
	vector<pair<char,int>> freqTable;
	map<char,int> freqMap;
	for(int i=0;i<s.length();i++)
	{	
			freqMap[s[i]]++;
	}
    	for (map<char, int>::iterator i = freqMap.begin(); i != freqMap.end(); i++)
    	{
        	freqTable.push_back(make_pair(i->first, i->second));
    	}
    return freqTable;
}

node *createTree(vector<pair<char,int>> table) //generate huffman tree from frequency table STEP 3
{
	priority_queue<node *, vector<node *>, customCompare> q;
	for(int i=0;i<table.size();i++)
	{
		node* n=new node();
		n->ele=table[i].first;
		n->freq=table[i].second;
		q.push(n);
	}
	while(q.size()>1)
	{
		node *x,*y;
		x=q.top();
		q.pop();
		
		y=q.top();
		q.pop();
		
		node *z= new node();
		z->freq=x->freq + y->freq;
		z->left=x;
		z->right=y;
		q.push(z);
		
	}
	
	return q.top();
}
		
void codeGenerator(node *root,string s1,string s2,map<char,string> &code) //Generate codes from huffman tree STEP 4
{
	s1+=s2;
	if(root->left==NULL && root->right==NULL)
		code[root->ele]=s1;
	if(root->left!=NULL)
		codeGenerator(root->left,s1,"0",code);
	if(root->right!=NULL)
		codeGenerator(root->right,s1,"1",code);
}

/*void display(map<char,string> &code)
{
	map<char,string>::iterator i;
	for(i=code.begin();i!=code.end();i++)
		cout<<i->first<<"\t"<<i->second<<"\t\t\t hi"<<endl;
}*/

int paddedCode(string s)
{
	int bits;
	bits=s.length()%7;
	return 7-bits;
}

string getBinary(string s, map<char,string> huffcodes)
{
	int l=s.length();
	string str="";
	
	for(int i=0;i<l;i++)
	{	
		str+=huffcodes[s[i]];
	}
	if(str.length()%7!=0)
	{
		int pad=paddedCode(str);
		for(int i=0;i<pad;i++)
			str+="0";
	}
	return str;
}



string binToAsc(string s)
{
	string ans="";
	int sec=s.length()/7;
	int c=0;
	string sub="";
	for(int i=0;i<s.length();i++)
	{
		sub+=s[i];c++;
		if(c==7)
		{	
			char ch=char(stoi(sub,0,2));
			ans+=ch;	
			sub="";
			c=0;
		}
	}	
        return ans;
}

void compress(string s)
{
	ofstream fout("CompressedFile.txt",ios::binary);
	string ans=binToAsc(s);
	fout<<ans;
	fout.close();
}

long long calcSize(string fileName)  //return ll after compression to get compression ratio
{
	ifstream fin(fileName, ios::binary);
	long long size;
	fin.seekg(0,ios::end);
	size=fin.tellg();
	fin.close();
	return size;
}
	
string convert2(string s)
{
	string ans="";
	int l=s.length();
	int bin;
	for(int i=0;i<l;i++)
	{
		bin=int(s[i]);
		
		string str="";
		while(bin>0)
		{
			if(bin%2==0)
				str+="0";
			else
				str+="1";
			bin=bin/2;
		}
		if(str.length()<7)
		{
		        int diff=7-str.length();
		        for(int j=0;j<diff;j++)
		            str+='0';
		}
		reverse(str.begin(),str.end());
		ans+=str;
	}
	return ans;
}			

/*char traverse(node* root1,char ch)  //returns to decompress
{
	node* temp=root1;
	if(ch=='0')
		temp=temp->left;
	if(ch=='1')
		temp=temp->right;
	
	if(temp->left==NULL && temp->right==NULL)
		return temp->ele;
	else
	{
		*root1=temp;
		return '\0';
	}
}*/	
	
void decompress(string filename, map<char,string> codes)
{
	
	string s=readFile(filename);
	
	//cout<<"s= "<<s<<endl;
	
	string bitstring=convert2(s);
	
	//cout<<"bitstring="<<bitstring<<endl;
	
	map<string,char> revcodes;
	for(map<char,string>::iterator i=codes.begin();i!=codes.end();i++)
		revcodes[i->second]=i->first;
	string ans="";
	string bitcode="";
	for(int i=0;i<bitstring.length();i++)
	{
		bitcode+=bitstring[i];
		if(revcodes.find(bitcode)!=revcodes.end())
		{
			if(revcodes[bitcode]==127)
				break;
			ans+=revcodes[bitcode];
			bitcode="";
		}
	}
	string newname;
	cout<<"\n Enter file name\n";
	cin>>newname;
	ofstream fout(newname,ios::binary);
	fout<<ans;
	fout.close();
}	
			
int main()
{
	/*compression part*/
	
	//step 1
	string filename;
	cout<<"enter file to be compressed\n";
	cin>>filename;
	string content;
	content= readFile(filename);
	content+=127;//----------------------------------------------------------------pseudo eof
	//step 2
	vector<pair<char,int>> freqt;
	freqt=createFreqTable(content);
	//check working of createFreqTable ::   
	//for(int i=0;i<freqt.size();i++)
	//	cout<<freqt[i].first<<"\t"<<freqt[i].second<<"\n";
		
	//step 3
	node *tree=createTree(freqt);

	//step 4
	map<char,string> code;
	codeGenerator(tree,"","",code);
	
	//cout<<endl;display(code);
	
	string paddedAns="";
	
	//cout<<content<<endl<<content.length()<<endl;
	//for(int i=0;i<content.length();i++)
	//	cout<<i<<"      "<<content[i]<<"\t"<<int(content[i])<<endl;
	
	paddedAns+=getBinary(content, code);
	
	//cout<<paddedAns<<endl;
	
	//step 5
	compress(paddedAns);
	//to check for proper compression , try to decompress it and compare both the contents
	
	//compression ratio
	long long sz1,sz2;
	sz1=calcSize(filename);
	sz2=calcSize("CompressedFile.txt");
	cout<<"Original size :"<<sz1<<" bytes \n";
	cout<<"Compressed size :"<<sz2<<" bytes \n";
	int choice;
	cout<<"\n decompress ??\n";
	cin>>choice;
	if(choice==1)
		decompress("CompressedFile.txt",code);
	return 0;
}

