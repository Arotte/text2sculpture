#pragma once

#include<iostream>
#include<bitset>
using namespace std;

/** -------------------------------------- **/
typedef struct char_coord {
    /* Char and corresponding coordinates at the n*n (preferably 100*100) grid */
    char c; /* Basic char type cant hold utf8 chars */
    int x, y;
} char_coord;

typedef struct coord {
    int x, y;
} coord;

enum direction {
    FORWARD, BACKWARD, LEFT, RIGHT,
    UPPERLEFT, UPPERRIGHT, LOWERLEFT, LOWERRIGHT
};
/** -------------------------------------- **/

class Creator {

public:
    /** DATA **/
    /* Text to be converted to the sculpture */
    char baseText[501];
    /* This 100*100*1000 (length*width*height) array stores the locations of each building block */
    bool locs[500][50][50];
    /* Chars of the Hungarian alphabet, and corresponding (previously defined) coordinates for them at the n*n grid */
    char_coord char_coords[26]; // There are 44 chars in the extended Hungarian alphabet

    /** STRUCTORS **/
    /* It's important to place 0s to all places at 'locs' because not all of them are going to be used */
    Creator();
	~Creator();

    /** FUNCTIONS **/
    /* Load char coordinates from file in 'path' to 'char_coords' */
    void loadCharCoords(const char* path);
    /* Load base text from file in 'path' to 'baseText' */
    void loadBaseText(const char* path);
    /* Calculate the locations for each building block, and store them in 'locs' */
    void calcLocs(int shift); /** DEBUG: **/ void dbgCalcLocs();
        /* Updates class variable Creator::locs with the next layer and the new particle position */
        void nextIter(coord from, direction where, int layer, int placeInAlphabet);
        int findPlaceInAlphabet(char ch);
        int randDirection();


    /** STL PARSER FUNCTIONS **/
    void createSTL(const char* path);
    void drawCubeAt(int x, int y, int z);

    /** .OBJ PARSER FUNCTIONS **/
    void createOBJ(const char* path, int size);
		void drawOBJCubeAt(int x, int y, int z, int no, int size);
		void drawOBJCuboidAt(int x, int y, int z, int no, int sizeX, int sizeY, int sizeZ);
		void drawOBJTetrahedronAt(int x, int y, int z, int no, double size);
		void drawOBJTetrahedron90At(int x, int y, int z, int no, double size);
	



    /* Write 3D array to file; DEBUG */
    void writeLocs2File();
};
