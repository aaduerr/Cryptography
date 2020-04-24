#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "scanner.h"
#include "funct.h"

int determinant(int **a,int n)
    {
    int i,j,j1,j2;
    int det = 0;
    int **m = NULL;

    if (n < 1) fprintf(stderr,"determinant: Determinant cannot be less than 1");

    else if (n == 1) { det = a[0][0]; } //Det of single number is itself
    else if (n == 2)
        {
        det = a[0][0] * a[1][1] - a[1][0] * a[0][1]; //2x2 matrix formula
        }
    else
        {
        det = 0;
        for (j1=0; j1 < n; j1++)
            {
            m = malloc((n-1)*sizeof(int *));
            for (i = 0; i < n-1; i++)
                m[i] = malloc((n-1)*sizeof(int));
            for (i = 1; i < n; i++)
                {
                j2 = 0;
                for (j = 0; j < n; j++)
                    {
                    if (j == j1) continue;
                    m[i-1][j2] = a[i][j];
                    j2++;
                    }
                }
            det += pow(-1,j1+2) * a[0][j1] *determinant(m,n-1);
            for (i = 0; i < n-1; i++)
                free(m[i]);
            free(m);
            }
        }
    return (det);
    }

int **coFactor(int **a,int n)
    {
    int i,j,ii,jj,i1,j1;
    int det;
    int **b,**c;
    
    b = malloc((n-1)*sizeof(int *));
    for (i = 0; i < n-1; i++)
        b[i] = malloc((n-1)*sizeof(int));


    c = malloc((n-1)*sizeof(int *));
    for (i = 0; i < n-1; i++)
        c[i] = malloc((n-1)*sizeof(int));

    for (j = 0; j < n; j++)
        {
        for (i = 0; i < n; i++)
            {
            i1 = 0;
            for (ii = 0; ii < n; ii++)
                {
                if (ii == i) continue;
                j1 = 0;
                for (jj = 0; jj < n; jj++)
                    {
                    if (jj == j) continue;
                    c[i1][j1] = a[ii][jj];
                    j1++;
                    }
                i1++;
                }
            det = determinant(c,n-1);
            b[i][j] = pow(-1.0,i+j+2.0) * det;
            }
        }
    return b;
    
    for (i = 0; i < n-1; i++)
        free(b[i]);
    free(b);
    
    for (i = 0; i < n-1; i++)
        free(c[i]);
    free(c);
    }

int **transpose(int **a,int n)
    {
    int i,j;
    int temp;

    for (i = 1; i < n; i++)
        {
        for (j = 0; j < i; j++)
            {
            temp = a[i][j];
            a[i][j] = a[j][i];
            a[j][i] = temp;
            }
        }
    return a;
    }

void encode(void)
    {
    int i,j,n,z,*a,*c,*x,*temp,count;
    char *b,*d;
    printf("What is the block size? ");
    n = readInt(stdin);
    a = malloc(sizeof(int)*n);
    printf("What is the key? (enter all numbers separated by spaces, row by row)\n");
    printf("Key: ");
    for (i = 0; i < n*n; n++)
        {
        a[i] = readInt(stdin);
        }
    printf("Enter in a string: ");
    b = readToken(stdin);
    
    if (strlen(b)%n !=0)
        {
        c = malloc(sizeof(int)*(n*strlen(b)+1));
        z = n*strlen(b)+1;
        }
    else
        {
        c = malloc(strlen(b));
        z = strlen(b);
        }

    for (i = 0; i < strlen(b); i++)
        {
        if (i < z)
            c[i] = dom(b[i]);
        else
            c[i] = 28;
        }
    
    x = malloc(sizeof(int)*z);

    for(i = 0; i < z; i+=n)
        {
        count = 0;
        for(j = i; j < i+n; j++)
            {
            temp[count] = c[j];
            count++;
            }
        temp = matrixMult(matrixFill(a,n),temp,n);
        count = 0;
        for(j = i; j < i+n; j++)
            {
            x[j] = temp[count];
            count++;
            }
        }

    d = malloc(sizeof(char)*z);

    for (i = 0; i < z; i++)
        {
        d[i] = mod(x[i]);
        }
    
    printf("The string %s encoded becomes %s",b,d);

    return;
    }

void decode(void)
    {
    int i,j,n,z,**A,*a,*c,*x,*temp,count;
    char *b,*d;
    printf("What is the block size? ");
    n = readInt(stdin);
    a = malloc(sizeof(int)*n);

    printf("What is the key? (enter all numbers separated by spaces, row by row)\n");
    printf("Key: ");
    for (i = 0; i < n*n; n++)
        {
        a[i] = readInt(stdin);
        }
    printf("Enter in a string: ");
    b = readToken(stdin);
    
    A = matrixFill(a,n);
    A = inverse(A,n);

    if (strlen(b)%n !=0)
        {
        c = malloc(sizeof(int)*(n*strlen(b)+1));
        z = n*strlen(b)+1;
        }
    else
        {
        c = malloc(strlen(b));
        z = strlen(b);
        }

    for (i = 0; i < strlen(b); i++)
        {
        if (i < z)
            c[i] = dom(b[i]);
        else
            c[i] = 28;
        }
    
    x = malloc(sizeof(int)*z);

    for(i = 0; i < z; i+=n)
        {
        count = 0;
        for(j = i; j < i+n; j++)
            {
            temp[count] = c[j];
            count++;
            }
        temp = matrixMult(A,temp,n);
        count = 0;
        for(j = i; j < i+n; j++)
            {
            x[j] = temp[count];
            count++;
            }
        }

    d = malloc(sizeof(char)*z);

    for (i = 0; i < z; i++)
        {
        d[i] = mod(x[i]);
        }
    
    printf("The string %s encoded becomes %s",b,d);

    return;
    }

char mod(int a)
    {
    char x[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','.',',',' '};

    return x[a];
    }

int dom(char x)
    {
    int i;
    for (i = 0; i < 29; i++)
        {
        if (x == mod(i)) return i;
        }
    return -1;
    }

int **matrixFill(int *a, int n)
    {
    int i,j,**m;
    m = malloc(sizeof(int *));
    for (i = 0; i < n; i++)
        m[i] = malloc(sizeof(int) * n);

    for (i = 0; i < n; i++)
        {
        for (j = 0; j < n; j++)
            {
            m[i][j] = a[(i*n)+j];
            }
        }

    return m;
    }

int **inverse(int **a,int n)
    {
    int d,e,i,j;
    d = determinant(a,n);
    e = 0;
    for(i = 0; i < 29; i++)
        if ((d*i)%29 == 1)
            e = i;
        else e = 0;
        
    if (e == 0) {
        fprintf(stderr,"inverse: could not mod determinant"); }

    a = transpose(coFactor(a,n),n);

    for(i = 0; i < n; i++)
        {
        for(j = 0; j < n; j++)
            {
            a[i][j] = a[i][j]*e;
            }
        }
    return a;
    }

int *matrixMult(int **a,int *b, int n)
    {
    int i,j,x[n];
    for (i = 0; i < n; i++)
        {
        x[i] = 0;
        for (j = 0; j < n; i++)
            {
            x[i] += a[i][j]*b[i];
            }
        }
    b = x;
    return b;
    }
