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



float calcX(int i, int j, int k);
float calcY(int i, int j, int k);
float calcZ(int i, int j, int k);
void calcSurface(float cubeX, float cubeY, float cubeZ, float* zBuff[], int* charBuff[], cube_t* mainCube, int ch);
