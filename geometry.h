//
// Created by Antoniu Ficard on 27.10.2022.
//

#ifndef GRAPHICSTEST_GEOMETRY_H
#define GRAPHICSTEST_GEOMETRY_H

#define TOTAL_RADIUS 360
#define PI 3.14159265359

enum ObjectType {
    POINT, POINT_F, VECTOR
};

typedef struct {
    int x;
    int y;
    enum ObjectType type;
} Point;

typedef struct {
    float x;
    float y;
    enum ObjectType type;
} Point_f;

typedef struct {
    float i;
    float j;
    enum ObjectType type;
} Vector;

// Functions

// constructors for structs defined above

// allocate space in memory for a Point object and initialise
Point *createPoint(int x, int y);

// allocate space in memory for a Point object and initialise
Point *createPointFromPoint_f(Point_f p);

// allocate space in memory for a Point_f object and initialise
Point_f *createPoint_f(float x, float y);

// allocate space in memory for a Point_f object and initialise
Point_f *createPoint_fFromPoint(Point p);

// allocate space in memory for a Vector object and initialise
Vector *createVector(float i, float j);

// destructors that go recursively for the structs defined above

// deallocate memory for Point
// input: gets the address of the pointer that stores the Point
// output: sets the pointer given as a parameter to NULL
void freePoint(Point **p);

// deallocate memory for Point_f
// input: gets the address of the pointer that stores the Point_f
// output: sets the pointer given as a parameter to NULL
void freePoint_f(Point_f **p);

// deallocate memory for a Vector
// input: gets the address of the pointer that stores the Vector
// output: sets the pointer given as a parameter to NULL
void freeVector(Vector **v);

// functions that compute vectors

// add 2 vectors together and return a pointer to the resulting vector, newly allocated
Vector *addVector(Vector *v1, Vector *v2);

// returns a new Point which represents point p rotated with radians in trigonometric sense
// input:  p - Point*: address of point you want to rotate
//         radians - float:  the number of radians by which the point will be rotated
// output: the new rotated point
Point *rotatePoint(Point *p, float radians);

// returns a new Point_f which represents point p rotated with radians in trigonometric sense
// input:  p - Point_f*: address of point you want to rotate
//         radians - float:  the number of radians by which the point will be rotated
// output: the new rotated point
Point_f *rotatePoint_f(Point_f *p, float radians);

// returns the scalar(dot) product of two vectors
// input:v1- vector
//      v2-vector
// output: float representing scalar product between v1 and v2
float getDotProduct(Vector *v1, Vector *v2);

// returs the absolute value of a float given as a parameter
float absoluteValue(float x);

// convert an angle given in degrees and convert it to radians
float degreesToRadians(unsigned short int angle);

Vector *createVectorByAngle(float angle, float value);

// adds two angle values from degrees
unsigned short int addDegrees(short int angle1, short int angle2);

// get the distance between two points
// input: point1 - pointer to a Point
//        point2 - pointer to a Point
// output: returns - the distance between the two points given as parameters
//                   -1 - if the pointers are not valid
float distance(Point *point1, Point *point2);

// get the distance between two points
// input: point1 - pointer to a Point_f
//        point2 - pointer to a Point_f
// output: returns - the distance between the two points given as parameters
//                   -1 - if the pointers are not valid
float distancef(Point_f *point1, Point_f *point2);

#endif //GRAPHICSTEST_GEOMETRY_H
