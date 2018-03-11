#ifndef STX_H
#define STX_H

#include <windows.h>
#include <cstdio>
#include <cstdlib> 
#include <conio.h>
#include <ctime>
#include <cmath>
#include <cstring>
#include <iostream>
#include <vector>
#include <queue>
#include <pthread.h>
#define LL long long
#define INTPTR int*
#define CHARPTR char*
#define ABS(X) X>0?X:-X
#define DOUBLE(x) x*x
#define LEN(ARRAY,TYPE) (sizeof(ARRAY)/sizeof(TYPE))
#define MAX(x,y) x>y?x:y 
#define MIN(x,y) x>y?y:x
#define RAN(x) rand()%x

/*err tracker*/
typedef unsigned int STATUS; 
#define SUCCEED 0
#define NORM_FINISH 1
#define ABNORM_FINISH 2
#define OVERFLOWED 3

#endif

//INCLUDE WRITES HERE