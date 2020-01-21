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

    //sleep for .01 second because producer first execute
    sleep(.01) ;

    //checked for open shared memory
    int id = -1 ;
    while (id == -1){
        id = shm_open(NAME , O_RDWR , 0666) ;
        if(id < 0){
            cerr << "shm_open is not open" << endl ;
        }
    }

    // set size of shared memory for id
    ftruncate(id , SIZE) ;
    struct NUMBER *number = (struct NUMBER *)
            mmap(0 , SIZE ,PROT_READ |PROT_WRITE , MAP_SHARED , id , 0);

    while ((number -> state) != 2) {
        //do nothing
    }

    cout << "Consumer c2 started to consume" << endl ;

    cout << "c2 should consume " << number -> m2 << " number(s)" << endl ;


    for (int i = number -> m1 ; i < number -> m1 + number -> m2 ; i++) {
        //wait for produced number of c2
        while ((number -> state) != i + 3) {
            //do nothing
        }
        cout << "c2 consumed number " << number -> n[i] << endl ;
    }

    cout << "c2 is terminate" << endl ;

    number -> state ++ ;

    munmap(number , SIZE);




    close(id) ;

    return EXIT_SUCCESS ;

}