#ifndef FUNCT_H
#define FUNCT_H

int determinant(int **,int);
int **coFactor(int **,int);
int **transpose(int **,int);
void encode(void);
void decode(void);
char mod(int);
int dom(char);
int **matrixFill(int *,int);
int **inverse(int **,int);
int *matrixMult(int **,int *,int);

#endif
