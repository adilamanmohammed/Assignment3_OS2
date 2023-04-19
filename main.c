/*
Name: Mohammed Adil Aman
CWID: A20395630
Description: The following code is the implementation of FIFO and LRU page replacement algorithm which takes input a 

*/

//library declarations
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

//main function
int main(int argc, char* argv[])
{
    //variable declaration and assigning value to it
    int file_nm = atoi(argv[1]);
    int frame_sz = atoi(argv[2]);
    int algo_nm = atoi(argv[3]);
    

    printf("\nSelection details of file, frames and algorithm :\n");

    //displaying the chosen details
    if(file_nm==1)
    printf("Chosen file : test.txt\n");
    else if(file_nm==2)
    printf("Chosen file : gcc.txt\n");
    else if(file_nm==3)
    printf("Chosen file : bzip.txt\n");
    else
    {
    printf("You have chosen a wrong file number please run the code again and enter the correct file number \n 1.test.txt or 2.gcc.txt or 3.bzip.txt\n");
    exit(0);
    }


    printf("Chosen number of frames : %d\n",frame_sz);

    //if loop to send the inputs to algo()
    if(algo_nm >2)
    {
        printf("You have chosen a wrong algorithm number please run the code again and enter the correct algorithm number \n1.FIFO or 2.LRU\n");
        exit(0);
    }
    else
    algo(file_nm,frame_sz, algo_nm);

    return 0;
}
