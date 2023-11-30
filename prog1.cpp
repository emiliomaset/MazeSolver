// Name: Emilio Maset
// File Name: dsProg1.cpp
// Date: 31 August, 2023
// Program Description: A program to find a path in a text file based maze using a user provided start and end point
#include <iostream>
#include <fstream>

using namespace std;

#define ARRAYHEIGHT 12
#define ARRAYWIDTH 12

void loadMaze(char mazeArray[][ARRAYWIDTH], char* argv);
void printMaze(char mazeArray[][ARRAYWIDTH]);
bool findPath(char mazeArray[][ARRAYWIDTH], int startRow, int startCol, int endRow, int endCol);

int main(int argc, char* argv[]) {

    int startRow, startCol, endRow, endCol;
    char mazeArray[ARRAYHEIGHT][ARRAYWIDTH];

    if (argc == 1) { // argc is a counter of command line arguments. its value is 1 if no command line arguments are entered. the value 1 comes from the title of the file being counted
        cout << "No file name entered." << endl;
        return 0;
    }

    loadMaze(mazeArray, argv[1]); // passes array and file name (command-line argument)

    printMaze(mazeArray);



    cout << "Enter start position: ";
    cin >> startRow >> startCol;

    cout << "Enter end position: ";
    cin >> endRow >> endCol;

    cout << endl;


    if (!(findPath(mazeArray, startRow - 1, startCol - 1, endRow - 1, endCol - 1))) // if function call returns false, there is no path
        cout << "There is no path!";

    else // if function call returns true, put an S at the start point and print the array
    {
        mazeArray[startRow - 1][startCol - 1] = 'S';
        printMaze(mazeArray);
    }


    return 0;
} // end of main

// ============================================================================================================================

void loadMaze(char mazeArray[][ARRAYWIDTH], char* argv) { // function to load the maze into the 2-D array from the text file


    ifstream inFile(argv); // argv is a pointer containing the address of a command line argument. In this case, it is argv[1], which is the name of the file

    if (!inFile) {
        cout << "File not found." << endl;
        exit(0);
    }

    for (int i = 0; i < ARRAYHEIGHT; i++) {
        for (int j = 0; j < ARRAYWIDTH; j++) {
            mazeArray[i][j] = inFile.get();
        } // end of inner loop
        inFile.ignore(1, '\n');
        inFile.ignore(1, '\r');
    } // end of outer loop

    inFile.close();
} // end of loadMaze function

// ============================================================================================================================

void printMaze(char mazeArray[][ARRAYWIDTH]) {
    for (int i = 0; i < ARRAYHEIGHT; i++) {
        for (int j = 0; j < ARRAYWIDTH; j++) {
            cout << mazeArray[i][j];
        }
        cout << endl;
    }
    cout << endl;

} // end of printMaze function

// ============================================================================================================================

bool findPath(char mazeArray[][ARRAYWIDTH], int startRow, int startCol, int endRow, int endCol) {

    if ( (startRow < 0) || (startRow > ARRAYWIDTH - 1) || (startCol < 0) || (startCol > ARRAYWIDTH - 1) ) // if out of bounds, return false
        return false;

    if (mazeArray[startRow][startCol] == '*')
        return false;

    if (mazeArray[startRow][startCol] == 'o')
        return false;

    if (startRow == endRow && startCol == endCol) { // if we have reached the destination, return true and start backing out
        mazeArray[startRow][startCol] = 'E';
        return true;
    }

    mazeArray[startRow][startCol] = 'o'; // if element passes all base cases, it could be part of the path so put an 'o' there

    if (findPath(mazeArray, startRow - 1, startCol, endRow, endCol)) // traverse north
        return true;

    if (findPath(mazeArray, startRow, startCol + 1, endRow, endCol)) // traverse east
        return true;

    if (findPath(mazeArray, startRow + 1, startCol, endRow, endCol)) // traverse south
        return true;

    if (findPath(mazeArray, startRow , startCol - 1, endRow, endCol)) // traverse west
        return true;


    mazeArray[startRow][startCol] = ' '; // used to remove o's while backing out

    return false; // used if path is a dead end
} // end of findPath

// ============================================================================================================================