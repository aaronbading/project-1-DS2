#include "terminal.h"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

Terminal::Terminal()
{FileSystem* fs= new FileSystem();
this->fs=fs;}

void Terminal::Run(string filename)
{
ifstream myfile(filename);
bool decision=true;
if(myfile.is_open())
{
do
{
cout << "$" ;
string temp1 , temp2,function,name,name2;
int count =0;
getline(myfile,temp1);
istringstream inSS(temp1);
while(inSS>>temp2)
{
	
// first extraction
if(count==0)
{
function=temp2;
}
//
if(count ==1)
{
//function  has the information
name=temp2;
}
//
if(count==2)
{name2=temp2;}
//
count++;
}

if(count==1)
{

if(function=="ls")
{fs->ls();
}
if(function=="pwd")
{cout << fs->pwd() << endl;}
if(function=="bye")
{decision=false;}

}

if(count==2)
{

if(function=="mkdir")
{cout << fs->mkdir(name) << endl;}
if(function=="cd")
{cout << fs->cd(name)<< endl; }
if(function=="addf")
{cout << fs->addf(name) << endl;}
if(function=="rm")
{ fs->rm(name);}
if(function=="whereis")
{fs->search(name);}

}
if(count==3)
{//function should be mv
if(function=="mv")
 fs->mv(name,name2);
if(function=="cp")
fs->cp(name,name2);	

}


}while(decision);
}
else
{cout << "Failed to open file" << endl;}


}
