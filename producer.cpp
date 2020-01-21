#include "preprocessor.h"

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <time.h>
using namespace std ;
int main(){

    //create a shared memory
    int id = shm_open(NAME,O_CREAT | O_EXCL | O_RDWR , 0666 ) ;

    //checked for error
    if (id < 0){
        cerr << "shm_open is not make" << endl;
        return EXIT_FAILURE ;
    }

    // set size of shared memory for id
    ftruncate(id , SIZE) ;

    //use the struct and map this
    struct NUMBER *number = (struct NUMBER *)
            mmap(0 , SIZE , PROT_READ | PROT_WRITE , MAP_SHARED ,id , 0);


    number -> m1 = 1 ;

    number -> m2 = 3 ;

    cout << "Producer Started to produce" << endl ;

    number -> state = 1 ;

    cout << "I will produce " << number -> m1 << " number(s)for c1, and " << number -> m2 << " number(s) for c2" << endl ;

    //initialize random seed:
    srand (time(NULL));

    //begin c1 customer
    number -> state ++ ;
    //make random number for c1

    for (int i = 0; i < number -> m1 ; i++) {

        number -> n[i] = rand() % 10 ;

        cout << "I produced number " << number -> n[i] << " for c1" << endl;

        cout << "I will sleep for 1 second" << endl ;

        sleep(1);

        number -> state ++ ;
    }


    for (int i = number -> m1; i < number -> m1 + number -> m2 ; i++) {

        number -> n[i] = rand() % 10 ;

        cout << "I produced number " << number -> n[i] << " for c2" << endl;

        cout << "I will sleep for 1 second" << endl ;

        sleep(1);

        number -> state ++ ;
    }


    while (number -> state != number -> m1 + number -> m2 + 3 ){
        //do nothing
    }

    cout << "I terminated" << endl ;

    munmap(number, SIZE);

    close(id);

    shm_unlink(NAME);

    return EXIT_SUCCESS;

}

