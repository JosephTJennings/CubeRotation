#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

float A, B, C;

float calcX(int i, int j, int k) {
    return j * sin(A) * sin(B) * cos(C) - k * cos(A) * sin(B) * cos(C) +
         j * cos(A) * sin(C) + k * sin(A) * sin(C) + i * cos(B) * cos(C);
}

float calcY(int i, int j, int k) {
    return j * cos(A) * cos(C) + k * sin(A) * cos(C) -
         j * sin(A) * sin(B) * sin(C) + k * cos(A) * sin(B) * sin(C) -
         i * cos(B) * sin(C);
}

float calcZ(int i, int j, int k) {
    return k * cos(A) * cos(B) - j * sin(A) * cos(B) + i * sin(B);
}