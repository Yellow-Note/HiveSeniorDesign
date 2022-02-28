// src/greeting.cpp
// from https://medium.com/jspoint/a-simple-guide-to-load-c-c-code-into-node-js-javascript-applications-3fcccf54fd32
#include <iostream>
#include <string>
#include "greeting.h"
std::string helloUser(std::string name)
{
    return "Hello " + name + "!";
}