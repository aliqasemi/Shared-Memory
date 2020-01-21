#ifndef PREPROCESSOR
#define PREPROCESSOR

//we used a preprocessor
struct NUMBER{
    int m1 ;
    int m2 ;
    int n[4] ;
    int state;
};

#define NAME "/shared_memory12"

#define NUM 4

#define SIZE (sizeof(struct NUMBER) + NUM * sizeof(int))

#endif