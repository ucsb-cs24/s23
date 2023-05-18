#include "Point.h"

// These are the locations of the keys on a QWERTY keyboard.
// - Q is at the origin.
// - Increasing X values move right.
// - Increasing Y values move closer to the user.
// You can change this file if you really want to.
// Gradescope will use the original.

const Point QWERTY[26] = {
    {0.25, 1.00}, // A
    {4.75, 2.00}, // B
    {2.75, 2.00}, // C
    {2.25, 1.00}, // D
    {2.00, 0.00}, // E
    {3.25, 1.00}, // F
    {4.25, 1.00}, // G
    {5.25, 1.00}, // H
    {7.00, 0.00}, // I
    {6.25, 1.00}, // J
    {7.25, 1.00}, // K
    {8.25, 1.00}, // L
    {6.75, 2.00}, // M
    {5.75, 2.00}, // N
    {8.00, 0.00}, // O
    {9.00, 0.00}, // P
    {0.00, 0.00}, // Q
    {3.00, 0.00}, // R
    {1.25, 1.00}, // S
    {4.00, 0.00}, // T
    {6.00, 0.00}, // U
    {3.75, 2.00}, // V
    {1.00, 0.00}, // W
    {1.75, 2.00}, // X
    {5.00, 0.00}, // Y
    {0.75, 2.00}  // Z
};
