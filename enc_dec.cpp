#include <bits/stdc++.h>
using namespace std;

int key=1;

fstream fin,fout;
string file_name,ext;

void decrypt(string str,int key){
    int i;
    char a='a';
    for(i=0;i<str.size();i++)
    {
        a=str[i];
        a=(a+key)%128;
        fout<<a;      
    }
}

void encrypt(string str,int key){
    int i;
    char a='a';
    for(i=0;i<str.size();i++)
    {
        a=str[i];
        a=(a-key)%128;
        fout<<a;      
    }
}

string file_name_extractor(string str)
{
    int i;
    for(i=0;i<str.size();i++)
    {
        if(str[i]=='.')
        {
            return str.substr(0,i);
        }
    }   
}

string extention_extractor(string str)
{
    int i;
    for(i=0;i<str.size();i++)
    {
        if(str[i]=='.')
        {
            return str.substr(i+1,str.size()-i-1);
        }
    }   
}

void encrypter(string input)
{
    string str;
    
    file_name+=".serial_coders";
    fout.open(file_name.c_str(),ios::out );
    
    str=extention_extractor(input);
    encrypt(ext,1);
    fout<<endl;
    
    while(true)
	{
	    getline(fin,str);
	    encrypt(str,key);
	    if(fin.eof()){
	        break;
	    }
	    fout<<endl;
	}
}

void decrypter(string input)
{
    string str;
    
    //add orig extention to file_name
	getline(fin,str);
	char a;
	file_name+=".";
	for(int i=0;i<str.size();i++)
    {
        a=str[i];
        a=(a+key)%128;
        file_name+=a;     
    }
    fout.open(file_name.c_str(),ios::out );
    
    while(true)
	{
	    getline(fin,str);
	    decrypt(str,key);
	    if(fin.eof()){
	        break;
	    }
	    fout<<endl;
	}
}

int main(int argc, char *argv[])
{
	string input,str;
	
	input=argv[1];
	fin.open(input.c_str(),ios::in);
	ext=extention_extractor(input);
	file_name=file_name_extractor(input);
	
	if(ext=="serial_coders")//to be decrypted
	{
	    decrypter(input);
	}
	else//to be encrypted
	{
	    encrypter(input);
	}
	
    str=(string)"rm "+input+" ";
    system(str.c_str());
    
	fin.close();
	fout.close();
	return 0;
}
