#ifndef Filesystem_H
#define Filesystem_H

#include <iostream>
#include <string>
#include "node.h"
#include <vector>
using namespace std;

class FileSystem
{
public:

FileSystem();
~FileSystem();
string mkdir(string name);  // creates directory
string addf(string name);  // creates file
string pwd();   //prints the path so lie /root/dir1/dir2    string
void  ls();    //lists all the names of the things in the current directo
void rm(string name); 
void rmhelper(Node* ptr); //remove helper function
void cp(string item, string name);
void copyhelper( Node* cur, Node* copy ,bool decision); // copy helper function
void mv(string from, string to); //changes name of from to name to
string cd(string dirname);      // change directory so this is either a name or ..
void whereis(string name,Node* cur);
void search(string name); // whereis helper function
private:
Node* root;
Node* currentDirectory;
string filename;
};
#endif

