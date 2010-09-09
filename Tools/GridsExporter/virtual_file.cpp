#include "string_append.h"
#include "virtual_file.h"
//using namespace std;


void string_append_float(string &s,const float data,const string format="")
{
    string fullformat("%");
    fullformat.append(format);
    fullformat.append("f");
    char temp[100];
    sprintf(temp,fullformat.c_str(),data);
    s.append(temp);
}

void string_append_int(string &s,const int data,const string format="")
{
    string fullformat("%");
    fullformat.append(format);
    fullformat.append("d");
    char temp[100];
    sprintf(temp,fullformat.c_str(),data);
    s.append(temp);
}

void string_append_char(string &s,const char data)
{
    s.push_back(data);
}


void string_append_string(string &s,const string &data)
{
    s.append(data);
}






void VIRTUAL_FILE_WRITE_ONLY::write_char(const unsigned char data)
{
    string_append_char(buffer,data);
}

void VIRTUAL_FILE_WRITE_ONLY::writetofile()
{
    FILE *f=fopen(filename.c_str(),"wb");
    fwrite(buffer.c_str(),1,buffer.length(),f);
    fclose(f);
}

void VIRTUAL_FILE_WRITE_ONLY::write_int(const int data)
{
	unsigned char s[4];
	int integer = *(int *) &data;
	for(int i = 0; i<4; i++)
		s[3-i]=(integer >> 8*i) & 0xFF;
	for(int i = 0; i<4; i++)
		string_append_char(buffer,s[i]);
}

void VIRTUAL_FILE_WRITE_ONLY::write_float(const float data)
{
	unsigned char s[4];
	int integer = *(int *) &data;
	for(int i = 0; i<4; i++)
		s[3-i]=(integer >> 8*i) & 0xFF;
	for(int i = 0; i<4; i++)
		string_append_char(buffer,s[i]);
}


void VIRTUAL_FILE_WRITE_ONLY::write_string(const string &data)
{
		write_int(data.length());
		string_append_string(buffer,data);
}

VIRTUAL_FILE_READ_ONLY::VIRTUAL_FILE_READ_ONLY(string filename)
{
    FILE *f=fopen(filename.c_str(),"rb");
    fseek (f , 0 , SEEK_END);
    int fsize=ftell (f);
    unsigned char *temp = new unsigned char[fsize+2];
    rewind (f);
    fread (temp,1,fsize,f);
    temp[fsize]='\0';
    fclose(f);
    buffer.append((char *)temp,fsize);
    cursor=0;
    delete temp;
}


int VIRTUAL_FILE_READ_ONLY::read_int()
{

	unsigned char s[4];
	for(int i=0;i<4;i++)
	s[i]=buffer[cursor+i];
	cursor+=4;
	int integer=0;
	for(int i = 0; i<4; i++)
		integer+=(unsigned char)s[3-i]<< (8*i);
    return *(int *) &integer;
}

void VIRTUAL_FILE_READ_ONLY::rewind_virtual()
{
    cursor=0;
}

void VIRTUAL_FILE_READ_ONLY::move_cursor(int n)
{
    cursor=n;
}

float VIRTUAL_FILE_READ_ONLY::read_float()
{

	unsigned char s[4];
	for(int i=0;i<4;i++)
	s[i]=buffer[cursor+i];
	cursor+=4;
	int integer=0;
	for(int i = 0; i<4; i++)
		integer+=(unsigned char)s[3-i]<< (8*i);
    return *(float *) &integer;
}

unsigned char VIRTUAL_FILE_READ_ONLY::read_char()
{
	unsigned char c=buffer[cursor];
	cursor++;
    return c;
}

unsigned char VIRTUAL_FILE_READ_ONLY::read_char(int position)
{
	unsigned char c=buffer[position];
    return c;
}


int VIRTUAL_FILE_READ_ONLY::get_size()
{
return buffer.length();
}


string VIRTUAL_FILE_READ_ONLY::read_string()
{
		string s;
		int n=read_int();
		s=buffer.substr(cursor,n);
		cursor+=n;
		return s;
}
