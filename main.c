#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// defining struct for linked list
struct Linked_List
{
    char Refernce_String[10];
    struct Linked_List *next;
};

typedef struct Linked_List node;
node *Head = NULL;
node *Tail = NULL;

int main()
{
    int frames, file_name_value, algorithm_type_value;
    int file_name = 0;
    int algorithm_type = 0;

    printf("\nPlease Select one of the file you want to perform the Page replacement algorithm on :");
    printf("\n1. bzip.txt");
    printf("\n2. gcc.txt");
    printf("\n3. test.txt");
    printf("\nEnter your choice:\t");
    scanf("%d", &file_name);
    switch (file_name)
    {
    case 1:
        printf("\nYou selected bzip.txt");
        file_name_value = 1;
        break;
    case 2:
        printf("\nYou selected gcc.txt");
        file_name_value = 2;
        break;
    case 3:
        printf("\nYou selected test.txt");
        file_name_value = 3;
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    printf("\nPlease Select the algorithm you want to perform on the file : ");
    printf("\n1. FIFO");
    printf("\n2. LRU");
    printf("\nEnter your choice:\t");
    scanf("%d", &algorithm_type);
    switch (algorithm_type)
    {
    case 1:
        printf("\nYou selected FIFO");
        algorithm_type_value = 1;
        break;
    case 2:
        printf("\nYou selected LRU");
        algorithm_type_value = 2;
        break;
    default:
        printf("\nPlease Select correct option ");
    }

    printf("\nWhat are the total number of frames:\t");
    scanf("%d", &frames);

    if (algorithm_type_value == 1)
    {
        FIFO_algorithm(file_name_value, frames);
    }
    else
    {
        LRU_algorithm(file_name_value, frames);
    }
    return 0;
}
