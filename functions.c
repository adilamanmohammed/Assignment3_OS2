#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_list
{
    struct s_list *next;
    char stringrf[1000];
};

typedef struct s_list nd;
nd *start_pt = NULL;
nd *end_pt = NULL;

void insert_nd(char *A)
{
    nd *buff_nd;
    buff_nd = (nd *)malloc(sizeof(nd));

    strcpy(buff_nd->stringrf, A);
    buff_nd->next = NULL;

    // For the 1st element
    if (start_pt == NULL)
    {
        start_pt = buff_nd;
        end_pt = buff_nd;
    }
    else
    {
        end_pt->next = buff_nd;
        end_pt = buff_nd;
    }
}

void del_nd(int nd_p,int type)
{
    if(type==1)
    {
        nd *target;
        if (start_pt == NULL)
        {
            printf("Empty list found");
        }
        else
        {
            target = start_pt;
            start_pt = start_pt->next;
        }
    }
    else
    {
        nd *buff_nd = start_pt; // Creating a buffer variable pointing to start_pt
        if (nd_p == 0)
        {
            start_pt = start_pt->next; // Advancing the start_pt pointer
            buff_nd->next = NULL;
            insert_nd(buff_nd->stringrf);
        }
        else
        {
            for (int i = 0; i < nd_p - 1; i++)
            {
                buff_nd = buff_nd->next;
            }
            nd *nd_del = buff_nd->next; // del pointer points to the node to be deleted
            buff_nd->next = buff_nd->next->next;
            insert_nd(nd_del->stringrf);
            nd_del->next = NULL;
        }
    }
}

int searching(char *B, int nm)
{
    if(nm==1)
    {
    nd *searchNode = start_pt;
    int flag = 0;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->stringrf, B) == 0)
        {
            flag = 1;
            break;
        }
        else
            searchNode = searchNode->next;
    }
    if (flag == 0)
    {
    }
    return flag;
    }
    else
    {
        nd *searchNode = start_pt;
    int position = -1;
    int count = -1;

    while (searchNode != NULL)
    {
        count++;
        if (strcmp(searchNode->stringrf, B) == 0)
        {
            position = count;
            break;
        }
        else
            searchNode = searchNode->next;
    }

    return position;
    }
}



void print_List()
{
    printf("\nContents of Page Frame are\n");
    nd *pt;
    pt = start_pt;
    while (pt != NULL)
    {
        printf("%s ", pt->stringrf);
        pt = pt->next;
    }
}



void algo(int file_number, int frame_size, int algo_nm)
{

    char reference_string[10], operator;
    FILE *p;
    if (file_number == 1)
    {
        char *fileName = "test.txt";
        p = fopen(fileName, "r");
    }
    else if (file_number == 2)
    {
        char *fileName = "gcc.txt";
        p = fopen(fileName, "r");
    }
    else
    {
        char *fileName = "bzip.txt";
        p = fopen(fileName, "r");
    }

    if (p == NULL)
    {
        printf("File does not exist \n");
        exit(0);
    }

    int frame_count = 0, page_miss = 0, page_hit = 0, read_count = 0, write_count = 0;

    if(algo_nm==1)
    {
        printf("Chosen algorithm is : FIFO\n");
        while (fscanf(p,"%s %c\n", reference_string, &operator) != EOF)
        {
            if (frame_count < frame_size)
            {
                if (searching(reference_string, algo_nm) == 0) // Check if page is present in Frame queque
                {
                    insert_nd(reference_string);
                    frame_count++; // Update frame index as page has been added
                    page_miss++;
                    if (operator== 'R')
                    {
                        read_count++;
                    }
                    else
                    {
                        write_count++;
                    }
                }
                else
                {
                    page_hit++;
                }
            }
            else
            {
                if(searching(reference_string, algo_nm) == 0) // Check if page is present in Frame queue
                {
                    del_nd(0,1);
                    insert_nd(reference_string);
                    page_miss++;
                    if (operator== 'R')
                    {
                       read_count++;
                    }
                    else
                    {
                        write_count++;
                    }
                }
                else
                {
                    page_hit++;
                }
            }
        }
    }
    else
    {   
        printf("Chosen algorithm is : LRU\n");
        while (fscanf(p,"%s %c\n", reference_string, &operator) != EOF)
        {
            int position;
            if (frame_count < frame_size)
            {
                position = searching(reference_string, algo_nm);
                if (position == -1) // Check if page is present in Frame queque
                {
                    insert_nd(reference_string);
                    frame_count++; // Update frame index as page has been added
                    page_miss++;
                    if (operator== 'R')
                    {
                        read_count++;
                    }
                    else
                    {
                        write_count++;
                    }
                }
                else
                {
                    page_hit++;
                    del_nd(position,2);
                }
            }
            else
            {
                position = searching(reference_string, algo_nm);
                if (position == -1) // Check if page is present in Frame queue
                {
                    del_nd(0,1);
                    insert_nd(reference_string);
                    page_miss++;
                    if (operator== 'R')
                    {
                        read_count++;
                    }
                    else
                    {
                        write_count++;
                    }
                }
                else
                {
                    page_hit++;
                    del_nd(position,2);
                }
            }
        }
    }

    print_List();
    printf("\nNumber of Reads: %d\nNumber of Writes: %d\n", read_count, write_count);
    fclose(p);
}
