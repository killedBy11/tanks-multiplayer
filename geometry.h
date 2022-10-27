//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_GEOMETRY_H
#define GRAPHICSTEST_GEOMETRY_H

typedef enum {
    POINT, VECTOR
} ObjectType;

typedef struct {
    int x;
    int y;
    ObjectType type;
} Point;

typedef struct {
    int i;
    int j;
    ObjectType type;
} Vector;

// Functions

// constructors for structs defined above

// allocate space in memory for a Point object and initialise
Point *createPoint(int x, int y);

// allocate space in memory for a Vector object and initialise
Vector *createVector(int i, int j);

// destructors that go recursively for the structs defined above

// deallocate memory for Point
// input: gets the address of the pointer that stores the Point
// output: sets the pointer given as a parameter to NULL
void freePoint(Point **p);

// deallocate memory for a Vector
// input: gets the address of the pointer that stores the Vector
// output: sets the pointer given as a parameter to NULL
void freeVector(Vector **v);

// functions that compute vectors

// add 2 vectors together and return a pointer to the resulting vector, newly allocated
Vector *addVector(Vector *v1, Vector *v2);

#endif //GRAPHICSTEST_GEOMETRY_H