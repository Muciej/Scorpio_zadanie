//
// Created by macio on 03.10.2022.
//

#include <iostream>
#include <memory>
#include "file_writer.h"
#include "file_reader.h"
#include <vector>

using std::cout;
using std::endl;
using stringV = std::vector<string>;

void read_test();
void write_test();

int main(){
    read_test();
//    write_test();
    return 0;
}

void write_test(){
    filewrite::FileWriter writer("test.txt");
    std::string nextline;
//    std::cin>>nextline;
    std::getline(std::cin, nextline);
    while(nextline != "end"){
        writer.write(nextline);
        std::cin>>nextline;
    }
}

void read_test(){
    fileread::File_reader reader;
    reader.readFile("test.txt");
    std::unique_ptr<stringV> pasredLine = reader.getParsedLine(2);
    for(const auto& str: *pasredLine){
        cout<<str<<endl;
    }
}