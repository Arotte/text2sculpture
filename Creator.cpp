#include<iostream>
#include<time.h> /* For function randDirection() */
#include<stdlib.h> /* For srand() in function randDirection() */
#include "Creator.h" /* Class definition header */
#include<fstream> /* For handling text files */

using namespace std;


/** STRUCTORS **/
/* It's important to place 0s to all places at 'locs' because not all of them are going to be used */
Creator::Creator() {
    locs = new bool**[500];
    for(int i=0; i<500; ++i) {
        locs[i] = new bool*[50];
        for(int j=0; j<50; ++j) {
            locs[i][j] = new bool[50];
        }
    }

    for(int z=0; z<500; z++)
        for(int x=0; x<50; x++)
            for(int y=0; y<50; y++)
                locs[x][y][z] = 0;

    for (int i = 0; i<501; i++)
        baseText[i] = '\n';


	/** DEBUG **/
	cout << "Creator object created." << endl;
}

Creator::~Creator() {

    for(int i=0; i<500; ++i) {
        for(int j=0; j<50; ++i) {
            delete[] locs[i][j];
        }
        delete[] locs[i];
    }
    delete[] locs;
}


/** FUNCTIONS **/
/* Load char coordinates from file in 'path' to 'char_coords' */
void Creator::loadCharCoords(const char* path) {

    /* Customize stdin to get data from file */
    freopen(path, "r", stdin);
    for(int i=0; i<26; i++) {
            cin >> char_coords[i].c;
            cin >> char_coords[i].x;
            cin >> char_coords[i].y;
    }


    /** DEBUG **/
    cout << "Creator::loadCharCoords() function called, run." << endl;
}

/* Load base text from file in 'path' to 'baseText' */
void Creator::loadBaseText(const char* path) {

    /* Opening input stream and file specified by 'path' */
    ifstream fin;
    fin.open(path, ios::in);

    /* Local variable 'c' for storing current character; 'i' for iterating */
    char c;
    int i = 0;

    /* Go through the file's content char by char 'till end of file */
	while (!fin.eof()) {
        fin.get(c);
        /* If a char is not a space, digit, or symbol, add it to class var 'baseText' */
        if(isalpha(c)) { // !isspace(c) && !isdigit(c) && !ispunct(c)
             if(i < 500) {
                baseText[i] = c;
                ++i;
             } else break;
        }
	}

	fin.close();

	/** DEBUG **/
	cout << "Creator::loadBaseText() function called, run." << endl;
}


/* Calculate the locations for each building block, and store them in 'locs' */
void Creator::calcLocs() {

    /****************************************************************************************************/
    for(int x=0; x<26; x++) {
        if(char_coords[x].c != '\n') locs[char_coords[x].x][char_coords[x].y][0] = true;
    }


    //int z=0;
    for(int z=0; z<500; ++z) {
    //while(z <500 ) {
        if(baseText[z] == '\n') break;
        //if(!isalpha(baseText[z])) break;

        int placeInAlphabet = findPlaceInAlphabet(baseText[z]);
        cout << "CHAR COUNT: " << z << endl;
        coord from;
        from.x = char_coords[placeInAlphabet].x;
        from.y = char_coords[placeInAlphabet].y;

        for(int x=0; x<50; x++) {
            for(int y=0; y<50; y++ ) {
                    //int xx = x; if(x<49) ++xx; int yy = y; if(y>0) --y;
                    if(x != from.x || y != from.y) {
                        locs[z+1][x][y] = locs[z][x][y];
                        //cout << "NO COORD CHANGE." << endl;
                    } else {
                        char_coords[placeInAlphabet].x = x-1;
                        char_coords[placeInAlphabet].y = y-1;
                        //if(0 <= x-1 <= 50 && 0 <= y-1 <= 50)
                        locs[z+1][x-1][y-1] = true;

                    }
            }
                        //cout << "COOORD CHANGE." << endl;
        }
        //z++;
    }

    /** debug **/
    //locs[20][30][1] = true;
}
    /****************************************************************************************************/







int Creator::findPlaceInAlphabet(char ch) {
    /** DEBUG **/
    cout << "Creator::findPlaceInAlphabet() function called; output: ";
    char ch2 = tolower(ch);

    for(int i= 0; i<26; i++) {
        char ch1 = tolower(char_coords[i].c);
        if (ch1 == ch2) {
                cout << i <<endl; /** DEBUG **/
                return i;
        }
    }
    cout << "-1; " << ch << endl; /** DEBUG **/
    return -1;
}





/** **************************** **/
/** STL PARSER FUNCTIONS **/
void Creator::createSTL(const char* path) {

    //ofstream stl;
    //stl.open(path, ios::out);
    //stl << "solid ascii" << endl;
    freopen(path, "w", stdout);
    cout << "solid ascii" << endl;

    for(int z=0; z<500; z++) {
        for(int x=0; x<50; x++) {
            for(int y=0; y<50; y++) {
                if(locs[z][x][y] == true) drawCubeAt(x, y, z);
            }
        }
    }


    cout << "endsolid";
    //stl << "endsolid";
    //stl.close();
    fclose(stdout);
}

void Creator::drawCubeAt(int x, int y, int z) {
    //freopen(pat, "w", stdout);
    cout << "facet normal 0 1 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << -1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 1 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << -1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 0 1" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 0 1" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << 1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 1 0 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << 1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 1 0 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 0 -1" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 -1 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal 0 -1 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << -1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal -1 0 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << 1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    cout << "facet normal -1 0 0" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << 1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;


    cout << "facet normal 0 0 -1" << endl;
    cout << "outer loop" << endl;
    cout << "vertex " << -1+x << " " << -1+y << " " << -1+z << endl;
    cout << "vertex " << -1+x << " " << 1+y << " " << -1+z << endl;
    cout << "vertex " << 1+x << " " << 1+y << " " << -1+z << endl;
    cout << "endloop" << endl;
    cout << "endfacet" << endl;

    //fclose(stdout);
}



/** *********************************************************************************************** **/
/** .OBJ PARSER FUNCTIONS **/

void Creator::createOBJ(const char* path) {
    freopen(path, "w", stdout);
    cout << "# Tower" << endl;

    int i=0;
    for(int z=0; z<500; ++z) {
        for(int y=0; y<50; ++y) {
            for(int x=0; x<50; ++x) {
                if(locs[x][y][z] == true) {
                        drawOBJCubeAt(x, y, z, i);
                        ++i;
                }
            }
        }
    }

    fclose(stdout);
}


void Creator::drawOBJCubeAt(int x, int y, int z, int no) {
    //cout << endl;
    cout << "o Object." << no+1 << endl;

    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+1 << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+1 << ".000000 " << y+0 << ".000000 " << z+1 << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+1 << ".000000" << endl;
    cout << "v " << x+1 << ".000000 " << y+1 << ".000000 " << z+1 << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+1 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+1 << ".000000 " << y+1 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+1 << ".000000 " << z+1 << ".000000" << endl;

    cout << endl << endl;

    cout << "f " << 3+(no*8) << " " << 1+(no*8) << " " << 2+(no*8) << endl;
    cout << "f " << 7+(no*8) << " " << 3+(no*8) << " " << 2+(no*8) << endl;
    cout << "f " << 3+(no*8) << " " << 7+(no*8) << " " << 5+(no*8) << endl;
    cout << "f " << 8+(no*8) << " " << 3+(no*8) << " " << 5+(no*8) << endl;
    cout << "f " << 3+(no*8) << " " << 8+(no*8) << " " << 4+(no*8) << endl;
    cout << "f " << 8+(no*8) << " " << 1+(no*8) << " " << 4+(no*8) << endl;
    cout << "f " << 1+(no*8) << " " << 8+(no*8) << " " << 6+(no*8) << endl;
    cout << "f " << 7+(no*8) << " " << 1+(no*8) << " " << 6+(no*8) << endl;
    cout << "f " << 8+(no*8) << " " << 7+(no*8) << " " << 6+(no*8) << endl;
    cout << "f " << 7+(no*8) << " " << 8+(no*8) << " " << 5+(no*8) << endl;
    cout << "f " << 1+(no*8) << " " << 7+(no*8) << " " << 2+(no*8) << endl;
    cout << "f " << 1+(no*8) << " " << 3+(no*8) << " " << 4+(no*8) << endl;

    cout << endl;
}



