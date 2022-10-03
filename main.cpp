#include <iostream>
#include <ifaddrs.h>
#include "file_writer.h"
#include "file_reader.h"
#include <sstream>

using std::cout;
using std::cin;
using std::endl;

void saveFromFiles();
void saveIP();

std::unique_ptr<filewrite::FileWriter> writer;

int main() {
    writer = std::make_unique<filewrite::FileWriter>("system_data_readings.txt");
    saveFromFiles();
    saveIP();
    return 0;
}

void saveFromFiles(){
    fileread::File_reader reader;
    //CPU usage
    reader.readFile("/proc/stat");
    std::vector<string> cpu_cores_us;
    int i = 1;
    std::unique_ptr<std::vector<string>> parsed = reader.getParsedLine(i);
    do{
        int idle = stoi(parsed->at(4));
        int user = stoi(parsed->at(1));
        int nice = stoi(parsed->at(2));
        int iowait = stoi(parsed->at(5));
        int irq = stoi(parsed->at(6));
        int softirq = stoi(parsed->at(7));
        int steal = stoi(parsed->at(8));
        int system = stoi(parsed->at(3));
        int guest = stoi(parsed->at(9));
        int guest_nice = stoi(parsed->at(10));
        double usage = (double)(idle * 100) / (user + nice + system + idle + iowait + irq + softirq + steal + guest + guest_nice);
        std::stringstream stream;
        stream<<"cpu "<<i-1<<" usage is "<<usage;
//        cout<<stream.str()<<endl;
        cpu_cores_us.push_back(stream.str());
        i++;
        parsed = reader.getParsedLine(i);
    } while(parsed->at(0).substr(0,3) == "cpu");
    for(const auto& str: cpu_cores_us){
        writer->write(str);
    }

    //memory usage
    reader.readFile("/proc/meminfo");
    parsed = reader.getParsedLine(0, ' ');
//    cout<<parsed->at(8)<<endl;
    string totalMem = parsed->at(8);
    parsed = reader.getParsedLine(1, ' ');
    string freeMem = parsed->at(9);

    writer->write("Total system memory: " + totalMem + " kB");
    writer->write("Free system memory: " + freeMem + " kB");
    int usedMem = std::stoi(totalMem) - std::stoi(freeMem);
    string usedMemStr = std::to_string(usedMem);
    writer->write("used system memory:  " + usedMemStr + " kB");

}

void saveIP(){
    ifaddrs* head = nullptr;
    getifaddrs(&head);
    //todo wyciągnąć wszystkie ip i zamienić na dziesiętną
}