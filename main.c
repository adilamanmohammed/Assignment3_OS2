#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char* argv[])
{

    int frame_sz = atoi(argv[2]);
    int file_nm = atoi(argv[1]);
    int algo_nm = atoi(argv[3]);
    

    printf("Selection details of file, frames and algorithm :\n");


    if(file_nm==1)
    printf("chosen file : test.txt\n");
    else if(file_nm==2)
    printf("chosen file : gcc.txt\n");
    else if(file_nm==3)
    printf("chosen file : bzip.txt\n");
    else
    {
    printf("You have chosen a wrong file number please run the code again and enter the correct file number \n 1.test.txt or 2.gcc.txt or 3.bzip.txt\n");
    exit(0);
    }


    printf("chosen number of frames : %d\n",frame_sz);


    if(algo_nm >2)
    {
        printf("You have chosen a wrong algorithm number please run the code again and enter the correct algorithm number \n1.FIFO or 2.LRU\n");
        exit(0);
    }
    else
    algo(file_nm,frame_sz, algo_nm);

    return 0;
}
