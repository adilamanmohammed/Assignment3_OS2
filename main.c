#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(int argc, char* argv[])
{

    int frame_size = atoi(argv[3]);
    int file = atoi(argv[1]);
    int algorithm_type = atoi(argv[2]);
    
    switch (file)
    {
    case 1:
        printf("\nYou selected test.txt");
        break;
    case 2:
        printf("\nYou selected gcc.txt");
        break;
    case 3:
        printf("\nYou selected bzip.txt");
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    
    switch (algorithm_type)
    {
    case 1:
        printf("\nYou selected FIFO");
        break;
    case 2:
        printf("\nYou selected LRU");
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    printf("\nselected number of frame size : %d\n",frame_size);

    if (algorithm_type == 1)
    {
        FIFO_algorithm(file, frame_size);
    }
    else
    {
        LRU_algorithm(file, frame_size);
    }
    return 0;
}
