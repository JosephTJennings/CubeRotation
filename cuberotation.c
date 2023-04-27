#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <stdlib.h>

float A, B, C;

typedef struct cube {
    float cubeWidth;
    int width;
    int height;
    int backgroundChar;
    int FOV;
    float xOffset;
    float K1;
    float acceleration;
    float x, y, z;
    float ooz;
    int xPos, yPos;
    int idx;
}cube_t;

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

void calcSurface(float cubeX, float cubeY, float cubeZ, float* zBuff, char* charBuff, cube_t* mainCube, int ch) {
    mainCube->x = calcX(cubeX, cubeY, cubeZ);
    mainCube->y = calcY(cubeX, cubeY, cubeZ);
    mainCube->z = calcZ(cubeX, cubeY, cubeZ) + mainCube->FOV;

    mainCube->ooz = 1 / mainCube->z;

    mainCube->xPos = (int)(mainCube->width / 2 + mainCube->xOffset + mainCube->K1 * mainCube->ooz * mainCube->x * 2);
    mainCube->yPos = (int)(mainCube->height / 2 + mainCube->K1 * mainCube->ooz * mainCube->y);

    mainCube->idx = mainCube->xPos + mainCube->yPos * mainCube->width;
    if (mainCube->idx >= 0 && mainCube->idx < mainCube->width * mainCube->height) {
        if (mainCube->ooz > zBuff[mainCube->idx]) {
            zBuff[mainCube->idx] = mainCube->ooz;
            charBuff[mainCube->idx] = ch;
        }
    }
}

int main(){
    cube_t* mainCube = malloc(sizeof(cube_t));
    mainCube->cubeWidth = 20;
    mainCube->width = 160;
    mainCube->height = 44;
    mainCube->backgroundChar = ' ';
    mainCube->FOV = 150;
    float zBuff[mainCube->width * mainCube->height];
    char charBuff[mainCube->width * mainCube->height];
    mainCube->xOffset = 0;
    mainCube->K1 = 40;
    mainCube->acceleration = 0.8;

    float origCubeWidth = mainCube->cubeWidth;
    while(1){
        memset(zBuff, 0, mainCube->width * mainCube->height * 4);
        memset(charBuff, mainCube->backgroundChar, mainCube->width * mainCube->height);
        mainCube->cubeWidth = origCubeWidth;
        mainCube->xOffset = -3 * mainCube->cubeWidth;
        
        for (float cubeX = -(mainCube->cubeWidth); cubeX < mainCube->cubeWidth; cubeX += mainCube->acceleration) {
            for (float cubeY = -(mainCube->cubeWidth); cubeY < mainCube->cubeWidth;
                cubeY += mainCube->acceleration) {
                calcSurface(cubeX, cubeY, -(mainCube->cubeWidth), zBuff, charBuff, mainCube, '@');
                calcSurface(mainCube->cubeWidth, cubeY, cubeX,  zBuff, charBuff, mainCube, '$');
                calcSurface(-(mainCube->cubeWidth), cubeY, -cubeX,  zBuff, charBuff, mainCube, '~');
                calcSurface(-cubeX, cubeY, mainCube->cubeWidth,  zBuff, charBuff, mainCube, '#');
                calcSurface(cubeX, -(mainCube->cubeWidth), -cubeY,  zBuff, charBuff, mainCube, ';');
                calcSurface(cubeX, mainCube->cubeWidth, cubeY,  zBuff, charBuff, mainCube, '+');
            }
        }


        mainCube->cubeWidth = 15;
        mainCube->xOffset = -1 * mainCube->cubeWidth;
        for (float cubeX = -(mainCube->cubeWidth); cubeX < mainCube->cubeWidth; cubeX += mainCube->acceleration) {
            for (float cubeY = -(mainCube->cubeWidth); cubeY < mainCube->cubeWidth;
                cubeY += mainCube->acceleration) {
                calcSurface(cubeX, cubeY, -(mainCube->cubeWidth), zBuff, charBuff, mainCube, '@');
                calcSurface(mainCube->cubeWidth, cubeY, cubeX,  zBuff, charBuff, mainCube, '$');
                calcSurface(-(mainCube->cubeWidth), cubeY, -cubeX,  zBuff, charBuff, mainCube, '~');
                calcSurface(-cubeX, cubeY, mainCube->cubeWidth,  zBuff, charBuff, mainCube, '#');
                calcSurface(cubeX, -(mainCube->cubeWidth), -cubeY,  zBuff, charBuff, mainCube, ';');
                calcSurface(cubeX, mainCube->cubeWidth, cubeY,  zBuff, charBuff, mainCube, '+');
            }
        }

        mainCube->cubeWidth = 10;
        mainCube->xOffset = 2 * mainCube->cubeWidth;
        for (float cubeX = -(mainCube->cubeWidth); cubeX < mainCube->cubeWidth; cubeX += mainCube->acceleration) {
            for (float cubeY = -(mainCube->cubeWidth); cubeY < mainCube->cubeWidth;
                cubeY += mainCube->acceleration) {
                calcSurface(cubeX, cubeY, -(mainCube->cubeWidth), zBuff, charBuff, mainCube, '@');
                calcSurface(mainCube->cubeWidth, cubeY, cubeX,  zBuff, charBuff, mainCube, '$');
                calcSurface(-(mainCube->cubeWidth), cubeY, -cubeX,  zBuff, charBuff, mainCube, '~');
                calcSurface(-cubeX, cubeY, mainCube->cubeWidth,  zBuff, charBuff, mainCube, '#');
                calcSurface(cubeX, -(mainCube->cubeWidth), -cubeY,  zBuff, charBuff, mainCube, ';');
                calcSurface(cubeX, mainCube->cubeWidth, cubeY,  zBuff, charBuff, mainCube, '+');
            }
        }

        mainCube->cubeWidth = 6;
        mainCube->xOffset = 8 * mainCube->cubeWidth;
        for (float cubeX = -(mainCube->cubeWidth); cubeX < mainCube->cubeWidth; cubeX += mainCube->acceleration) {
            for (float cubeY = -(mainCube->cubeWidth); cubeY < mainCube->cubeWidth;
                cubeY += mainCube->acceleration) {
                calcSurface(cubeX, cubeY, -(mainCube->cubeWidth), zBuff, charBuff, mainCube, '@');
                calcSurface(mainCube->cubeWidth, cubeY, cubeX,  zBuff, charBuff, mainCube, '$');
                calcSurface(-(mainCube->cubeWidth), cubeY, -cubeX,  zBuff, charBuff, mainCube, '~');
                calcSurface(-cubeX, cubeY, mainCube->cubeWidth,  zBuff, charBuff, mainCube, '#');
                calcSurface(cubeX, -(mainCube->cubeWidth), -cubeY,  zBuff, charBuff, mainCube, ';');
                calcSurface(cubeX, mainCube->cubeWidth, cubeY,  zBuff, charBuff, mainCube, '+');
            }
        }
        printf("\x1b[H");
        for (int k = 0; k < mainCube->width * mainCube->height; k++) {
            putchar(k % mainCube->width ? charBuff[k] : 10);
        }

        A += 0.05;
        B += 0.05;
        C += 0.01;
        usleep(8000 * 2);

    }
    free(mainCube);
}