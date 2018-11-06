#include<iostream>
#include "Creator.h"
#include<fstream>
//#include "STLParser.hpp"
using namespace std;

int main() {
    cout << "Let's start building that tower!" << endl;

    Creator creator;
    //STLParser stlParser;

    /* Load coordinates of char from file */
    creator.loadCharCoords("in_coord2.txt");
    /* Load base text to be converted to tower from file */
    creator.loadBaseText("aaa.txt");


    /** DEBUG **/
    ofstream ofs;
    ofs.open("OUT/gheci.txt", ios::out);
    for(int i=0; i<26; i++) {
        ofs << creator.char_coords[i].c << " " <<creator.char_coords[i].x <<" " << creator.char_coords[i].y << endl;
    }
    ofs.close();
    /*ofstream ofs2;
    ofs2.open("OUT/gheci2.txt", ios::out);
    int i = 0;
    while (creator->baseText[i] != '\n') { ofs2 << creator->baseText[i]; ++i;}
    ofs2.close();*/

    /** /DEBUG **/

    /* Calculate the locations of each building block of the tower */
    creator.calcLocs();
    /* Output the calculated locations to file for debugging */
    //creator.writeLocs2File();

    /* Create and STL file using the locations for each building block */
    //creator.createSTL("OUTPUT11.stl");
    creator.createSTL("OUT/DRAGA.stl");

    cout << "main.cpp run succesfully." << endl;
	//delete creator;
    return 0;
}
