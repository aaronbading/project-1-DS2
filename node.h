#ifndef Node_H
#define Node_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Node
{
public:
Node(string name, bool decision); // constructor taking in name and bool
Node* getNext();  // getters and setters
Node* getChild();
Node* getParent();
void setNext(Node* next);
void setChild(Node* child);
void setParent(Node* parent);
bool isD();
string getName();

private:
string name;
bool isDirectory;
Node* child;
Node* next;
Node* parent;



};
#endif
