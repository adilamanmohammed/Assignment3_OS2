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



void algo(int f_nm, int f_sz, int algo_nm)
{

    FILE *p;
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

    int frm_c = 0, pg_miss = 0, p_hit = 0, rd_c = 0, wr_c = 0;

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

    print_List();
    printf("\nNumber of Reads: %d \nNumber of Writes: %d\n", rd_c, wr_c);
    fclose(p);
}
