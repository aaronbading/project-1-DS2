#include<iostream>
#include"node.h"
#include<string>
#include"filesystem.h"
#include"terminal.h"
using namespace std;

int main()
{
Terminal object;
object.Run("commands.txt");
return 0;
}

