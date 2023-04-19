//declaration of library
#include<stdio.h>
#include <stdlib.h>
#include <string.h>

//declaration of linked list and struct 
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
    //declaration of pointer
    nd *buff_nd;
    //allocation of memory
    buff_nd = (nd *)malloc(sizeof(nd));

    //comparing the pointer nd with reference string
    strcpy(buff_nd->stringrf, A);
    buff_nd->next = NULL;

    //check if the list is empty
    if (start_pt == NULL)
    {
        start_pt = buff_nd;
        end_pt = buff_nd;
    }
    else
    {
        //move tail to next
        end_pt->next = buff_nd;
        end_pt = buff_nd;
    }
}

void del_nd(int nd_p,int type)
{
    //check delete operation for fifo or lru
    if(type==1)
    {
        //deletion of node for fifo
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
        //deletion function for lru
        // Creating a buffer variable for pointing to start_pt
        nd *buff_nd = start_pt;
        if (nd_p == 0)
        {
            //move the start_pt to next 
            start_pt = start_pt->next;
            buff_nd->next = NULL;
            //calling insert
            insert_nd(buff_nd->stringrf);
        }
        else
        {
            for (int i = 0; i < nd_p - 1; i++)
            {
                buff_nd = buff_nd->next;
            }
            nd *nd_del = buff_nd->next; 
            buff_nd->next = buff_nd->next->next;
            //calling insert_nd
            insert_nd(nd_del->stringrf);
            nd_del->next = NULL;
        }
    }
}

//searching function takes a string and number as input
int searching(char *B, int nm)
{
    if(nm==1) // check if for fifo or lru searching
    {
    //searching for fifo
    //declaration 
    nd *search_Nd = start_pt;
    //declaration of flag
    int f = 0;
    //while loop to serach till the end of the contents
    while (search_Nd != NULL)
    {
        if (strcmp(search_Nd->stringrf, B) == 0)
        {
            f = 1;
            break;
        }
        else
            search_Nd = search_Nd->next;
    }

    return f;
    }
    else
    {

        //searching for lru
    nd *search_Nd = start_pt;
    int p = -1;
    int c = -1;

    //loop to search
    while (search_Nd != NULL)
    {
        c++;
        if (strcmp(search_Nd->stringrf, B) == 0)
        {
            p = c;
            break;
        }
        else
            search_Nd = search_Nd->next;
    }

    return p;
    }
}


//print function for printing contents 
void print_Lt()
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



void algo(int f_nm, int f_sz, int algo_nm)
{

    FILE *p;
    int frm_c = 0, pg_miss = 0, p_hit = 0, rd_c = 0, wr_c = 0;
    char stringrf[100], optr;
    
    if (f_nm == 1)
    {
        char *fname = "test.txt";
        p = fopen(fname, "r");
    }
    else if (f_nm == 2)
    {
        char *fname = "gcc.txt";
        p = fopen(fname, "r");
    }
    else
    {
        char *fname = "bzip.txt";
        p = fopen(fname, "r");
    }

    if (p == NULL)
    {
        printf("File does not exist \n");
        exit(0);
    }



    if(algo_nm==1)
    {
        printf("Chosen algorithm is : FIFO\n");
        while (fscanf(p,"%s %c\n", stringrf, &optr) != EOF)
        {
            if (frm_c < f_sz)
            {
                if (searching(stringrf, algo_nm) == 0) // Check if page is present in Frame queque
                {
                    insert_nd(stringrf);
                    frm_c= frm_c+1; // Update frame index as page has been added
                    pg_miss=pg_miss+1;
                    if (optr== 'R')
                    {
                        rd_c=rd_c+1;
                    }
                    else
                    {
                        rd_c=rd_c+1;
                    }
                }
                else
                {
                    p_hit=p_hit+1;
                }
            }
            else
            {
                if(searching(stringrf, algo_nm) == 0) // Check if page is present in Frame queue
                {
                    del_nd(0,1);
                    insert_nd(stringrf);
                    pg_miss=pg_miss+1;
                    if (optr== 'R')
                    {
                       rd_c=rd_c+1;
                    }
                    else
                    {
                        wr_c=wr_c+1;
                    }
                }
                else
                {
                    p_hit=p_hit+1;
                }
            }
        }
    }
    else
    {   
        printf("Chosen algorithm is : LRU\n");
        while (fscanf(p,"%s %c\n", stringrf, &optr) != EOF)
        {
            int position;
            if (frm_c < f_sz)
            {
                position = searching(stringrf, algo_nm);
                if (position == -1) // Check if page is present in Frame queque
                {
                    insert_nd(stringrf);
                    frm_c=frm_c+1; // Update frame index as page has been added
                    pg_miss=pg_miss+1;
                    if (optr== 'R')
                    {
                        rd_c=rd_c+1;
                    }
                    else
                    {
                        wr_c=wr_c+1;
                    }
                }
                else
                {
                    p_hit=p_hit+1;
                    del_nd(position,2);
                }
            }
            else
            {
                position = searching(stringrf, algo_nm);
                if (position == -1) // Check if page is present in Frame queue
                {
                    del_nd(0,1);
                    insert_nd(stringrf);
                    pg_miss=pg_miss+1;

                    if (optr== 'R')
                    rd_c=rd_c+1;
                    else
                    wr_c=wr_c+1;
                }
                else
                {
                    p_hit=p_hit+1;
                    del_nd(position,2);
                }
            }
        }
    }

    print_Lt();
    printf("\nNumber of Reads: %d \nNumber of Writes: %d\n", rd_c, wr_c);
    fclose(p);
}
