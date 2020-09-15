#ifndef Terminal_H
#define Terminal_H

#include <iostream>
#include <string>
#include "filesystem.h"
#include <vector>
using namespace std;

class Terminal
{
public:
Terminal();
void Run(string filename);

private:
FileSystem* fs;
};
#endif

