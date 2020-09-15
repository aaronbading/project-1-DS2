#include <iostream>
#include <string>
#include "filesystem.h"
#include "node.h"

FileSystem::FileSystem()
{
Node* ptr = new Node("root",true );
this->root=ptr;
this->currentDirectory=ptr;
}
FileSystem::~FileSystem()
{//calling delete function on root
}
string FileSystem::mkdir(string name)
{
	bool decision=true;
	 Node* cur=currentDirectory->getChild();

	//error checking
	while(cur !=nullptr)
        {
                if(cur->getName()==name)
                {decision=false;
                break;
                }
        cur=cur->getNext();
        }  

	//
    if(decision)
   {//success case
	cur=currentDirectory->getChild();
	Node* prev=cur;
	
	Node* ptr =new Node(name,true);
	 ptr->setParent(currentDirectory);

	if(cur!=nullptr)
	{	//nonempty list case
		int count =0;
		while(cur!=nullptr && cur->getName() < name)
		{
		prev = cur;
		cur= cur->getNext();
		count++;
		}
		 if(count==0)
             {currentDirectory->setChild(ptr);
             ptr->setNext(cur);}
             else
             {
                prev->setNext(ptr);
                ptr->setNext(cur);
                }

			
	}
	else
	{currentDirectory->setChild(ptr);} //empty list case

        return name;
     }
    else
    {//already exists
     string temp = currentDirectory->getName();
     temp.insert(0," already exists in ");
     temp.insert(0,name);
      return temp;
    }
}
void FileSystem::ls()
{
   Node* cur=currentDirectory->getChild();
	while(cur!=nullptr)
	{
		if(cur->isD())
		cout<<" D " << cur->getName() << endl;
		else
		cout<<" F  " << cur->getName() << endl;

		cur=cur->getNext();
	}
}
string FileSystem::addf(string name)
{
         bool decision=true;
         Node* cur=currentDirectory->getChild();

        //error checking
        while(cur !=nullptr)
        {
                if(cur->getName()==name)
                {decision=false;
                break;
                }
        	cur=cur->getNext();
        }
        //
    if(decision)
   {//case success
        cur=currentDirectory->getChild();
        Node* prev=nullptr;

        Node* ptr =new Node(name,false);

	ptr->setParent(currentDirectory);
        if(cur!=nullptr)
        {//case nonempty
		int count=0;
   	     while(cur!=nullptr && cur->getName() < name)
       		{

      		  prev = cur;
      		  cur= cur->getNext();
		count++;

	        }

	     if(count==0)
	     {currentDirectory->setChild(ptr);
	     ptr->setNext(cur);}
	     else
	     {
     		prev->setNext(ptr);
	        ptr->setNext(cur);
		}

        }
        else
        {currentDirectory->setChild(ptr);}//case empty
         return name;
    }
    else
    {//already exists
     string temp = " already exists";
     temp.insert(0,name);
      return temp;

    }

}
string FileSystem::pwd()
{
string temp="/";
Node* ptr= currentDirectory;

	 while(ptr!=root)
        {
        temp.insert(0,ptr->getName());
	temp.insert(0,"/");
        ptr=ptr->getParent();
        }
temp.insert(0,"Bading/root");
return temp;

}	
void FileSystem::rm(string name)
{
	 bool decision=false;
         Node* cur=currentDirectory->getChild();
	 Node* prev=cur;
//front of list case while ensuring we arent accesing a nullptr getname
	if(cur !=nullptr)
	{
	 if(cur->getName()==name)
	 {//front of list

		if(cur->getNext() != nullptr)
		{//case where there are other items

			currentDirectory->setChild(cur->getNext());
			cur->setNext(nullptr);
			rmhelper(cur);
		}
		else
		{//only one item
		rmhelper(cur);
		currentDirectory->setChild(nullptr);
		}
	   }
	 else
	 {

	
       	 //error checking
         	 while(cur !=nullptr)
  	      {
                if(cur->getName()==name)
                {decision=true;
                break;
                }
		prev=cur;
        	cur=cur->getNext();
        	}
	
		if(decision)
		{		prev->setNext(cur->getNext());
		cur->setNext(nullptr);
		rmhelper(cur);
		}
		else
		{cout << name << " was not found " << endl;}
	}
       }

cout << endl;

	//
}
void FileSystem::rmhelper(Node* ptr)
{
if(ptr != nullptr)
{

rmhelper(ptr->getNext());
rmhelper(ptr->getChild());

delete ptr;
return;
}
}
void FileSystem::mv(string from, string to)
{//error checking
 Node* cur = currentDirectory->getChild();
        bool decision= true;
        while(cur !=nullptr)
        {
                if(cur->getName()==to)
                {decision=false;
                break;
                }
        cur=cur->getNext();
        }
	//
if(decision)
{
cp(from, to );
rm(from);
cout << endl;
}
else
{
cout << to << " already exists " << endl;	
}

}
void FileSystem::cp(string item, string name)
{
	//error checking
	Node* cur = currentDirectory->getChild();
	bool decision= false;
	while(cur !=nullptr)
        {
                if(cur->getName()==item)
                {decision=true;
                break;
                }
        cur=cur->getNext();
        }
// 
	if(decision)
	{//case success
		Node* ptr= new Node(name,cur->isD());
		ptr->setParent(cur->getParent());
	copyhelper(cur->getChild(),ptr,true);
	//now insert into the right position
	cur = currentDirectory->getChild();
        Node* prev=cur;
        ptr->setParent(currentDirectory);

        if(cur!=nullptr)
        {
     		   while(cur!=nullptr && cur->getName() < name)
       		 {
     	  	  prev = cur;
     	 	  cur= cur->getNext();

       		 }
        prev->setNext(ptr);
        ptr->setNext(cur);

        }

	//	
	}
	else
	{cout << "No such item in this directory" << endl;}

}
void FileSystem::copyhelper(Node* cur , Node* copy, bool decision)
{
if(cur !=nullptr)
{

//create a copy
Node* ptr= new Node(cur->getName(), cur->isD());

	if(decision)
	{//child case
	copy->setChild(ptr);
	ptr->setParent(copy);
	}
	else
	{//traverse case
	copy->setNext(ptr);
	}
//child call
copyhelper(cur->getChild(),ptr,true);
	//traverse call
copyhelper(cur->getNext(),ptr,false);

}

}

string FileSystem::cd(string dirname)
{
	bool decision=false;
	if(dirname=="..")
	{// case where we are interested in switching to root
		if(currentDirectory!= root)
		{currentDirectory=currentDirectory->getParent();
		return pwd();}
		else
		{return "Already in root";}
	}
	else
	{
	// case where we want to switch to new directory

	Node* cur=currentDirectory->getChild();
	
		while(cur !=nullptr)
		{
			if(cur->getName()==dirname)
			{
			if(cur->isD()){
				decision=true;
			break;}}
			cur=cur->getNext();
		}
			

			if(decision)
			{this->currentDirectory=cur;
			return pwd();}
			else
			{string temp = " was not found";
				temp.insert(0,dirname);
				return temp;
			}

	}




}
void FileSystem::whereis(string name, Node* cur)
{//recursive function which calls next and child until name is found
	if(cur !=nullptr)
	{
		 whereis(name,cur->getNext());
	        whereis(name,cur->getChild());

		if(cur->getName()==name)
		{
		string temp="/";

		 while(cur!=root)
       		 {
      		  temp.insert(0,cur->getName());
  	          temp.insert(0,"/");
    	          cur=cur->getParent();
   		 }
	         temp.insert(0,"Bading/root");
         	cout << temp << endl;

		}
		
	}

}

void FileSystem::search(string name)
{whereis(name,currentDirectory->getChild());}

