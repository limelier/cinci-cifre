#include <cstring>
#include <fstream>
using namespace std;

fstream file;

bool getSetting(const char name[]) {
    file.open("settings.cfg");
    char input[100];
    do {
        file.getline(input, 100);
    } while (strstr(input, name) == nullptr);
    
    char value = input[strlen(input) - 1];
    file.close();
    return (value == '1');
}

void setSetting(const char name[], bool value) {
    file.open("settings.cfg");
    char input[100];
    do {
        file.getline(input, 100);
    } while (strstr(input, name) == nullptr);
    input[strlen(input) - 1] = '0' + value;
    file.seekp(-ios::off_type(strlen(input)) - 1 , ios::cur);
    file << input;
    file.close();
}