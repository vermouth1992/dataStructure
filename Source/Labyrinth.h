//
//  labyrinth.h
//  testProgram
//
//  Created by Chi Zhang on 8/2/15.
//  Copyright (c) 2015 Chi Zhang
/*
 This program is free software; you can redistribute it and/or modify it under the terms of the GNU
 General Public License as published by the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.
 This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even
 the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public
 License for more details.
 You should have received a copy of the GNU General Public License along with this program; if not, write
 to the Free Software Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 If you have any questions, please email zhan527@usc.edu
*/

#ifndef __testProgram__labyrinth__
#define __testProgram__labyrinth__

#include <stdio.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <string>

typedef enum {AVAILALBE, WALL, ROUTE, NOWAY} Status;
typedef enum {NORTH, EAST, SOUTH, WEST} Direction;

class Cell {
public:
    int _x;
    int _y;
    Status _status;
    
    Cell(int x = 0, int y = 0, Status status = AVAILALBE): _x(x), _y(y), _status(status) {}
    void print() {
        cout << "x: " << _x << ' ' << "y: " << _y << ' ' << "status: " << _status << endl;
    }
};

typedef vector<vector<Cell> > vec2_cell;

class Labyrinth {
    int _size;
public:
    vec2_cell _laby;
    Labyrinth(vec2_cell laby, int size) : _laby(laby), _size(size) {}
    Labyrinth(string filename, int size) {
        _size = size;
        init();
        readFromFile(filename);
    }
    
    int size() { return _size;}
    
    void init() {    //open space for 2-order vector
        _laby.resize(_size);
        for (int i = 0; i < _size; i++) {
            _laby[i].resize(_size);
        }
    }
    
    void print_labyrinth() {
        for (int i = 0; i < _size; i++) {
            for (int j = 0; j < _size; j++) {
                cout << _laby[j][i]._status << ' ';
            }
            cout << endl;
        }
    }
    
    void readFromFile(string filename) {
        fstream labyFile;
        labyFile.open(filename);
        if (labyFile.is_open()) {
            int i = 0;
            int j = 0;
            while (!labyFile.eof()) {
                int temp;
                labyFile >> temp;
                if (temp) {
                    _laby[i][j]._status = WALL;
                } else {
                    _laby[i][j]._status = AVAILALBE;
                }
                _laby[i][j]._x = i;
                _laby[i][j]._y = j;
                if (i == _size - 1) {
                    i = 0;
                    j += 1;
                } else {
                    i += 1;
                }
            }
        } else {
            cout << "Can't open file!" << endl;
        }
        labyFile.close();
    }
    
};

Cell* neighbor(int size, Direction dir, Cell* current)
{
    switch (dir) {
        case WEST: return current - size - 1;
        case SOUTH: return current + 1;
        case EAST: return current + size + 1;
        case NORTH: return current - 1;
        default: exit(-1);
    }
}

void move(Cell*& current, Direction dir, int size)
{
    switch (dir) {
        case WEST: current = current - size - 1; break;
        case SOUTH: current = current + 1; break;
        case EAST: current = current + size + 1; break;
        case NORTH: current = current - 1; break;
        default: exit(-1); break;
    }
}

bool labyrinth(Labyrinth& testLaby, Cell* start, Cell* terminal, MyStack<Cell*>& path)
{
    int size = testLaby.size();
    Cell* current = start;
    path.push(current);
    current->_status = ROUTE;
    while (!path.empty()) {  //当路径栈不为空
        bool available_flag = false;
        if (current == terminal) {
            return true;
        }
        for (Direction dir = NORTH; dir <= WEST ; dir = Direction(dir + 1)) {
            if (neighbor(size, dir, current)->_status == AVAILALBE) {
                move(current, dir, size);
                path.push(current);
                current->_status = ROUTE;
                available_flag = true;
                break;
            }
        }
        if (available_flag == false) {
            path.pop()->_status = NOWAY;
            current = path.top();
        }
        if (path.top() != NULL) current->print();
    }
    return false;
}



void testForLabyrinth() {
    string filename = "labyrinth.txt";
    int size = 7;
    Labyrinth testLaby(filename, size);
    Cell* start = &testLaby._laby[1][5];
    Cell* terminal = &testLaby._laby[4][3];
    MyStack<Cell*> path;
    cout << labyrinth(testLaby, start, terminal, path) << endl;;
    testLaby.print_labyrinth();
}


#endif /* defined(__testProgram__labyrinth__) */
