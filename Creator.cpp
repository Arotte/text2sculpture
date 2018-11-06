#include<iostream>
#include<time.h> /* For function randDirection() */
#include<stdlib.h> /* For srand() in function randDirection() */
#include "Creator.h" /* Class definition header */
#include<fstream> /* For handling text files */

using namespace std;


int Creator::randDirection() {
    /** DEBUG **/
    cout << "randDirection() function called; output: ";

    
    int r; r=rand()%100;
        cout << r << endl; /** DEBUG **/
    return r;

}


/** STRUCTORS **/
/* It's important to place 0s to all places at 'locs' because not all of them are going to be used */
Creator::Creator() {
    

    for(int z=0; z<500; z++)
        for(int x=0; x<50; x++)
            for(int y=0; y<50; y++)
                locs[z][x][y] = 0;

    for (int i = 0; i<501; i++)
        baseText[i] = '\n';


	/** DEBUG **/
	cout << "Creator object created." << endl;
}

Creator::~Creator() {
	cout << "Creator object deleted." << endl;
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
             if(i < 501) {
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
void Creator::calcLocs(int shift) {

    /****************************************************************************************************/
    for(int x=0; x<26; x++) {
        if(char_coords[x].c != '\n') locs[0][char_coords[x].x][char_coords[x].y] = true;
    }

	srand (time(NULL));
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
		
		
        for(int x=0; x<50; ++x) {
            for(int y=0; y<50; ++y) {
					if( x == 33 && y == 25 ||
						x == 16 && y == 25 ||
						x == 20 && y == 32 ||
						x == 29 && y == 32 ||
						x == 29 && y == 17 ||
						x == 20 && y == 17 ) { locs[z][x][y] = true; } 
				
                    //int xx = x; if(x<49) ++xx; int yy = y; if(y>0) --y;
                    if(x != from.x || y != from.y) {
                        locs[z+1][x][y] = locs[z][x][y];
                        //cout << "NO COORD CHANGE." << endl;
                    } else {
						int rand = randDirection();
						if (rand >= 0 && rand < 25 ) {
							char_coords[placeInAlphabet].x = x-shift;
							char_coords[placeInAlphabet].y = y-shift;
							locs[z+1][x-shift][y-shift] = true;
						} else if (rand >= 25 && rand < 50) {
							char_coords[placeInAlphabet].x = x;
							char_coords[placeInAlphabet].y = y-shift;
							locs[z+1][x][y-shift] = true;
						} else if (rand >= 50 && rand < 75) {
							char_coords[placeInAlphabet].x = x-shift;
							char_coords[placeInAlphabet].y = y+shift;
                            locs[z+1][x-shift][y+shift] = true;
						} else {
							char_coords[placeInAlphabet].x = x-shift;
							char_coords[placeInAlphabet].y = y;
							locs[z+1][x-shift][y] = true;
						}

                    }
            }
                        //cout << "	-COOORD CHANGE." << endl;
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

void Creator::createOBJ(const char* path, int size) {
    freopen(path, "w", stdout);
    cout << "# Tower" << endl;

    int i=0;
    for(int z=0; z<190; ++z) { /* z<500 */
        for(int y=0; y<50; ++y) {
            for(int x=0; x<50; ++x) {
                if(locs[z][x][y] == true) {
                        //drawOBJCubeAt(x, y, z, i, size);
						/*if(z < 45)
							drawOBJCuboidAt(x, y, z, i, 3, 3, 2);
						else if (z >= 45 && z < 90)
							drawOBJCuboidAt(x, y, z, i, 3, 5, 2);
						else if (z >= 90 && z < 140)
							drawOBJCuboidAt(x, y, z, i, 6, 9, 3);
						else if (z >= 140)
							drawOBJCuboidAt(x, y, z, i, 10, 12, 3);
						*/
						
						//int sizeXY = 2 + (z/30);
						//drawOBJCuboidAt(x, y, z, i, 4, 4, 4);
						//drawOBJCuboidAt(x, y, z, i, sizeXY, sizeXY, 2);
						
						//double size = 2+(z/15);
						double size = 4+(z/25);
						drawOBJTetrahedron90At(x, y, z, i, size);
                        ++i;
                }
            }
        }
    }

    fclose(stdout);
}


void Creator::drawOBJCubeAt(int x, int y, int z, int no, int size) {
    //cout << endl;
    cout << "o Object." << no+1 << endl;

    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+size << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+size << ".000000 " << y+0 << ".000000 " << z+size << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+size << ".000000" << endl;
    cout << "v " << x+size << ".000000 " << y+size << ".000000 " << z+size << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+size << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+size << ".000000 " << y+size << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+size << ".000000 " << z+size << ".000000" << endl;

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

void Creator::drawOBJCuboidAt(int x, int y, int z, int no, int sizeX, int sizeY, int sizeZ) {
    //cout << endl;
    cout << "o Object." << no+1 << endl;

    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+sizeX << ".000000 " << y+0 << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+sizeX << ".000000 " << y+0 << ".000000 " << z+sizeZ << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+0 << ".000000 " << z+sizeZ << ".000000" << endl;
    cout << "v " << x+sizeX << ".000000 " << y+sizeY << ".000000 " << z+sizeZ << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+sizeY << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+sizeX << ".000000 " << y+sizeY << ".000000 " << z+0 << ".000000" << endl;
    cout << "v " << x+0 << ".000000 " << y+sizeY << ".000000 " << z+sizeZ << ".000000" << endl;

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

void Creator::drawOBJTetrahedronAt(int x, int y, int z, int no, double size) {
	cout << "o Object." << no+1 << endl;

    cout << "v " << x+0 << " " << y+0 << " " << z+size << endl;
    cout << "v " << x+0 << " " << y+size << " " << z+0 << endl;
    cout << "v " << x-size << " " << y-size << " " << z+0 << endl;
    cout << "v " << x+size << " " << y-size << " " << z+0  << endl;

    cout << endl << endl;

    cout << "f " << 1+(no*4) << " " << 2+(no*4) << " " << 3+(no*4) << endl;
    cout << "f " << 1+(no*4) << " " << 3+(no*4) << " " << 4+(no*4) << endl;
    cout << "f " << 3+(no*4) << " " << 2+(no*4) << " " << 4+(no*4) << endl;
    cout << "f " << 2+(no*4) << " " << 1+(no*4) << " " << 4+(no*4) << endl;
    cout << endl;
	
	
}

void Creator::drawOBJTetrahedron90At(int x, int y, int z, int no, double size) {
	cout << "o Object." << no+1 << endl;

    cout << "v " << x+0 << " " << y+0 << " " << z+0 << endl;
    cout << "v " << x+0 << " " << y+size << " " << z+size << endl;
    cout << "v " << x+size << " " << y-size << " " << z+size << endl;
    cout << "v " << x-size << " " << y-size << " " << z+size  << endl;

    cout << endl << endl;

    cout << "f " << 1+(no*4) << " " << 2+(no*4) << " " << 3+(no*4) << endl;
    cout << "f " << 1+(no*4) << " " << 3+(no*4) << " " << 4+(no*4) << endl;
    cout << "f " << 3+(no*4) << " " << 2+(no*4) << " " << 4+(no*4) << endl;
    cout << "f " << 2+(no*4) << " " << 1+(no*4) << " " << 4+(no*4) << endl;
    cout << endl;
	
	
}



