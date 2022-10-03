//
// Created by macio on 03.10.2022.
//

#ifndef POOR_DEV_MGR_FILE_WRITER_H
#define POOR_DEV_MGR_FILE_WRITER_H

#include <iostream>
#include <fstream>

using std::string;

namespace filewrite{

    class FileWriter{
    private:
        std::ofstream fileToWrite;
    public:
        explicit FileWriter(const string &filename){
            reopen(filename);
        }

        void write(const string& line, bool flush = true){
            if(!fileToWrite.bad()){
                fileToWrite<<line<<std::endl;
                if(flush)
                    fileToWrite.flush();
            }
            if(fileToWrite.bad())
                std::cerr<<"Could not write to the opened file";
        }

        void reopen(const string& filename){
            if(fileToWrite.is_open())
                fileToWrite.close();
            fileToWrite.open(filename);
            if(fileToWrite.bad()){
                std::cerr<<"Could not open file "<<filename<<"!\n";
            }
        }

        ~FileWriter(){
            fileToWrite.close();
        }

    };
}

#endif //POOR_DEV_MGR_FILE_WRITER_H
