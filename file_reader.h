//
// Created by macio on 03.10.2022.
//

#ifndef POOR_DEV_MGR_FILE_READER_H
#define POOR_DEV_MGR_FILE_READER_H

#include <iostream>
#include <vector>
#include <memory>

using std::string;
using std::endl;

namespace fileread{
    class File_reader{
    private:
        std::ifstream fileToRead;
        std::unique_ptr<std::vector<string>> lines;
    public:
        File_reader(){
            lines = std::make_unique<std::vector<string>>();
        }

        /*
         * closes previously opened file, clears lines vector and then reads a new file
         * and save it to lines vector
         */
        void readFile(const string& filename){
            lines->clear();
            if(fileToRead.is_open())
                fileToRead.close();

            fileToRead.open(filename, std::ifstream::in);
            string s;
            while(getline(fileToRead, s))
                lines->push_back(s);

//            for(const string& str: *lines){
//                std::cout<<str<<endl;
//            }
        }

        std::unique_ptr<std::vector<string>> getParsedLine(const int& no, const char& delim = ' '){
            string line = lines->at(no);
//            std::cout<<line<<std::endl;
            std::unique_ptr<std::vector<string>> parsedLine = std::make_unique<std::vector<string>>();
            size_t beg = 0;
            size_t end = line.find(delim, beg);
            while( end != std::string::npos){
                parsedLine->push_back(line.substr(beg, end-beg));
                beg = end+1;
                end = line.find(delim, beg);
            }
            parsedLine->push_back(line.substr(beg));
            return std::move(parsedLine);
        }

        ~File_reader(){
            if(fileToRead.is_open())
                fileToRead.close();
        }
    };
}

#endif //POOR_DEV_MGR_FILE_READER_H
