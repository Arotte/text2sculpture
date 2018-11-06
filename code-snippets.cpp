        for(int y=0; y<50; ++y) {
            for(int x=0; x<50; ++x) {
                    if(x != from.x || y != from.y) {
                        locs[x][y][z+1] = locs[x][y][z];
                        //cout << "NO COORD CHANGE." << endl;
                    } else { /** FORWARD **/
                        //direction where = randDirection();
                        //cout <<"PREV: " << char_coords[placeInAlphabet].x << " " << char_coords[placeInAlphabet].y << endl;
                        //cout << "PREV AT: " << x << " " << y+1 << " " << z+1 << " | " << locs[x][y+1][z+1] << endl;
                        char_coords[placeInAlphabet].x = x;
                        char_coords[placeInAlphabet].y = y+1;
                        //if(0 <= x <= 50 && 0 <= y+1 <= 50)
                        locs[x][y+1][z+1] = true;
                        //cout <<"NEW: " << char_coords[placeInAlphabet].x << " " << char_coords[placeInAlphabet].y << endl;
                        //cout << "NEW AT: " << x << " " << y+1 << " " << z+1 <<  " | " <<locs[x][y+1][z+1] << endl;

                    }
            }
                        //cout << "COOORD CHANGE." << endl;
        }
















        int x=0; int y=0;
        while (x < 50) {
                while (y<50) {
                    if(x != from.x || y != from.y) {
                        locs[x][y][z+1] = locs[x][y][z];
                        //cout << "NO COORD CHANGE." << endl;
                    } else { /** FORWARD **/
                        //direction where = randDirection();
                        //cout <<"PREV: " << char_coords[placeInAlphabet].x << " " << char_coords[placeInAlphabet].y << endl;
                        //cout << "PREV AT: " << x << " " << y+1 << " " << z+1 << " | " << locs[x][y+1][z+1] << endl;
                        char_coords[placeInAlphabet].x = x;
                        char_coords[placeInAlphabet].y = y+1;
                        //if(0 <= x <= 50 && 0 <= y+1 <= 50)
                        locs[x][y+1][z+1] = true;
                        //cout <<"NEW: " << char_coords[placeInAlphabet].x << " " << char_coords[placeInAlphabet].y << endl;
                        //cout << "NEW AT: " << x << " " << y+1 << " " << z+1 <<  " | " <<locs[x][y+1][z+1] << endl;

                    }
                    y++;
                }
            x++;
        }










/* * * *****************************************/
/** HELPER functions for Creator::calcLocs() function **/
/* For Implementation1 in Creator::calcLocs; creates a pseudo-random direction, where should the building block go in the next iteration */
direction Creator::randDirection() {
    /** DEBUG **/
    cout << "randDirection() function called; output: ";

    srand (time(NULL));
    int r; r=rand()%8;
        cout << r << endl; /** DEBUG **/
    return (direction) r;

}

/* Updates class variable Creator::locs with the next layer and the new particle position */
void Creator::nextIter(coord from, direction where, int layer, int placeInAlphabet) {

    //layer+=2;
    for(int x=0; x<50; x++) {
        for(int y=0; y<50; y++) {
            if(from.x != x && from.y != y) {
                locs[x][y][layer] = locs[x][y][layer-1];
            } else {
                switch (where) {
                    case FORWARD: /** NOOOOOOOOOOOPE **/,
                        char_coords[placeInAlphabet].x = x;
                        char_coords[placeInAlphabet].y = y+1;
                        //if(0 <= x <= 50 && 0 <= y+1 <= 50)
                        locs[x][y+1][layer] = true;
                        break;
                    case BACKWARD: /** YAAAAAAAAAAAAAAAASSS **/
                        char_coords[placeInAlphabet].x = x;
                        char_coords[placeInAlphabet].y = y-1;
                        //if(0 <= x <= 50 && 0 <= y-1 <= 50)
                        locs[x][y-1][layer] = true;
                        break;
                    case RIGHT: /** NOOOOOOOOOOOPE **/
                        char_coords[placeInAlphabet].x = x+1;
                        char_coords[placeInAlphabet].y = y;
                        //if(0 <= x+1 <= 50 && 0 <= y <= 50)
                        locs[x+1][y][layer] = true;
                        break;
                    case LEFT: /** YAAAAAAAAAAAAAAAASSS **/
                        char_coords[placeInAlphabet].x = x-1;
                        char_coords[placeInAlphabet].y = y;
                        //if(0 <= x-1 <= 50 && 0 <= y <= 50)
                        locs[x-1][y][layer] = true;
                        break;
                    case UPPERLEFT: /** YAAAAAAAAAAAAAAAASSS **/
                        char_coords[placeInAlphabet].x = x-1;
                        char_coords[placeInAlphabet].y = y+1;
                        //if(0 <= x-1 <= 50 && 0 <= y+1 <= 50)
                            locs[x-1][y+1][layer] = true;
                        break;
                    case UPPERRIGHT: /** NOOOOOOOOOOOPE: WWWWWWWTFFFFFFFFFFF**/
                        char_coords[placeInAlphabet].x = x+1;
                        char_coords[placeInAlphabet].y = y+1;
                        //if(0 <= x+1 <= 50 && 0 <= y+1 <= 50)
                        locs[x+1][y+1][layer] = true;
                        break;
                    case LOWERLEFT: /** YAAAAAAAAAAAAAAAASSS **/
                        char_coords[placeInAlphabet].x = x-1;
                        char_coords[placeInAlphabet].y = y-1;
                        //if(0 <= x-1 <= 50 && 0 <= y-1 <= 50)
                        locs[x-1][y-1][layer] = true;
                        break;
                    case LOWERRIGHT: /** NOOOOOOOOOOOPE **/
                        char_coords[placeInAlphabet].x = x+1;
                        char_coords[placeInAlphabet].y = y-1;
                        //if(0 <= x+1 <= 50 && 0 <= y-1 <= 50)
                        locs[x+1][y-1][layer] = true;
                        break;
                }
            }
        }
    }


    /** DEBUG **/
    cout << "Creator::nextIter() function called, run." << endl;
}


/* Write 3D array to file */
void Creator::writeLocs2File() {

    //freopen("3d_array_output.txt", "w", stdout);
    ofstream ofs;
    ofs.open("3d_array_out3.txt", ios::out);

    ofs << "(x; y; z): 1" << endl;
    for(int z=0; z<500; z++) {
        for(int y=0; y<50; y++) {
            for(int x=0; x<50; x++) {
                if(locs[x][y][z] == true) ofs << "(" << x << "; " << y << "; " << z << "):" << (int) locs[x][y][z] << endl;
            }
        }
    }

    ofs.close();

    /** DEBUG **/
    cout << "Creator::writeLocs2File() function called, run." << endl;
}
