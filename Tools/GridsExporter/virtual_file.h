#ifndef VIRTUAL_FILE_H
#define VIRTUAL_FILE_H
#include <iostream>
#include <vector>
using namespace std;

#include "string_append.h"

class VIRTUAL_FILE_WRITE_ONLY{
public:
VIRTUAL_FILE_WRITE_ONLY(string filename):filename(filename),buffer(""){};
void write_char(const unsigned char data);
void write_int(const int data);
void write_float(const float data);
void write_string(const string &data);
void writetofile();
private:
string filename;
string buffer;
};

class VIRTUAL_FILE_READ_ONLY{
public:

VIRTUAL_FILE_READ_ONLY(string filename);


int read_int();
float read_float();
unsigned char read_char();
unsigned char read_char(int position);
void move_cursor(int n);
int get_size();
void rewind_virtual();
string read_string();
~VIRTUAL_FILE_READ_ONLY(){}
private:
string buffer;
int cursor;
};



#endif
