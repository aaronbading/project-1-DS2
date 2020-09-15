#include"node.h"
#include <iostream>
#include <string>

Node::Node(string name, bool decision)
{
this->name=name;
this->isDirectory=decision;
parent=nullptr;
child=nullptr;
next=nullptr;
}
bool Node::isD()
{return isDirectory;}
string Node::getName()
{return name;}
Node* Node::getNext()
{return next;}
Node* Node::getChild()
{return child;}
Node* Node::getParent()
{return parent;}
void Node::setNext(Node* next)
{this->next= next;}
void Node::setChild(Node* child)
{this->child=child;}
void Node::setParent(Node* parent)
{this->parent=parent;}





