//
//  main.cpp
//  ChiaTeam
//
//  Created by Anh Le on 22/03/2021.
//

#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int teamCount = 10;
double footage[10];
double kqTeam[10];
double kqIndexTeam[10];
double finalTeam[10];
int finalIndexTeam[10];
int thamTeam[10] = { 0 };
string teamName[10];
double s1 = 0;
double s2 = 0;

double s1Final = 0;
double s2Final = 0;

double sMinx = 1000;

void kiemtra() {
    if (sMinx > abs(s1 - s2)) {
        sMinx = abs(s1 - s2);
        s1Final = s1;
        s2Final = s2;
        for (int k=0;k<teamCount;k++) {
            finalTeam[k] = kqTeam[k];
            finalIndexTeam[k] = kqIndexTeam[k];
        }
    }
}

void timTeam(int indexOfKQ, int indexOfFootage) {
    kqTeam[indexOfKQ] = footage[indexOfFootage];
    kqIndexTeam[indexOfKQ] = indexOfFootage;
    thamTeam[indexOfFootage] = 1;
    if (indexOfKQ % 2 == 0) {
        s1 += kqTeam[indexOfKQ];
    } else {
        s2 += kqTeam[indexOfKQ];
    }
    if (indexOfKQ >= teamCount - 1) {
        kiemtra();
    }
    for(int j=0;j<teamCount;j++) {
        if (thamTeam[j] == 0) {
            int next = indexOfKQ + 1;
            timTeam(next, j);
        }
    }
    if (indexOfKQ % 2 == 0) {
        s1 -= kqTeam[indexOfKQ];
    } else {
        s2 -= kqTeam[indexOfKQ];
    }
    kqTeam[indexOfKQ] = 0;
    thamTeam[indexOfFootage] = 0;
    kqIndexTeam[indexOfKQ] = 0;
}

void chiaTeam() {
    s1 = 0;
    s2 = 0;
    timTeam(0, 0);
}

int main(int argc, const char * argv[]) {
    // insert code here...
    
    string cur_dir(argv[0]);
    int pos = cur_dir.find_last_of("/\\");
    string path = cur_dir.substr(0, pos);
    
//    cout << path << endl;
    
    ifstream fileInput(path + "/input.txt");
    if (fileInput.fail()) {
        cout << "Failed to open this file" << endl;
    }
    
    int dong = 1;
    while (true) {
        fileInput >> teamName[dong-1];
        fileInput >> footage[dong-1];
        dong++;
        if (dong > teamCount) {
            break;
        }
    }
    
    
    fileInput.close();
    
    chiaTeam();
    
    cout << "--> TEAM 1: ";
    for (int i=0;i<teamCount;i++) {
        if (i % 2 == 0) {
            cout << teamName[finalIndexTeam[i]];
            if (i < teamCount - 2) {
                cout << ", ";
            }
        }
    }
    cout << endl;
    cout << "--> TEAM 2: ";
    for (int i=0;i<teamCount;i++) {
        if (i % 2 != 0) {
            cout << teamName[finalIndexTeam[i]];
            if (i < teamCount - 1) {
                cout << ", ";
            }
        }
    }
    cout << endl;
    cout << "=========================" << endl;

    cout << "Sum Team 1 = " << s1Final << endl;
    cout << "Sum Team 2 = " << s2Final << endl;
    cout << "-> Gaps: " << sMinx << endl;

    cout << "=========================" << endl;
    
    return 0;
}
