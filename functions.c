#include<stdio.h>
#include <stdlib.h>
#include <string.h>

struct s_list
{
    struct s_list *next;
    char stringrf[1000];
};

typedef struct s_list node;
node *start_pt = NULL;
node *end_pt = NULL;

void insert_Operation(char *value)
{
    node *temp_node;
    temp_node = (node *)malloc(sizeof(node));

    strcpy(temp_node->stringrf, value);
    temp_node->next = NULL;

    // For the 1st element
    if (start_pt == NULL)
    {
        start_pt = temp_node;
        end_pt = temp_node;
    }
    else
    {
        end_pt->next = temp_node;
        end_pt = temp_node;
    }
}

void del_nd(int pos,int type)
{
    if(type==1)
    {
        node *toDelete;
        if (start_pt == NULL)
        {
            printf("List is already empty.");
        }
        else
        {
            toDelete = start_pt;
            start_pt = start_pt->next;
        }
    }
    else
    {
        node *temp = start_pt; // Creating a temporary variable pointing to start_pt
        if (pos == 0)
        {
            start_pt = start_pt->next; // Advancing the start_pt pointer
            temp->next = NULL;
            insert_Operation(temp->stringrf);
        }
        else
        {
            for (int i = 0; i < pos - 1; i++)
            {
                temp = temp->next;
            }
            node *del = temp->next; // del pointer points to the node to be deleted
            temp->next = temp->next->next;
            insert_Operation(del->stringrf);
            del->next = NULL;
        }
    }
}

int searching(char *value, int nm)
{
    if(nm==1)
    {
    node *searchNode = start_pt;
    int flag = 0;
    while (searchNode != NULL)
    {
        if (strcmp(searchNode->stringrf, value) == 0)
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
        node *searchNode = start_pt;
    int position = -1;
    int count = -1;

    while (searchNode != NULL)
    {
        count++;
        if (strcmp(searchNode->stringrf, value) == 0)
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
    node *myLinkList;
    myLinkList = start_pt;
    while (myLinkList != NULL)
    {
        printf("%s ", myLinkList->stringrf);
        myLinkList = myLinkList->next;
    }
    puts("");
}



void algo(int file_number, int frame_size, int algo_nm)
{

    char reference_string[10], operator;
    FILE *fp;
    if (file_number == 1)
    {
        char *fileName = "test.txt";
        fp = fopen(fileName, "r");
    }
    else if (file_number == 2)
    {
        char *fileName = "gcc.txt";
        fp = fopen(fileName, "r");
    }
    else
    {
        char *fileName = "bzip.txt";
        fp = fopen(fileName, "r");
    }

    if (fp == NULL)
    {
        printf("File does not exist \n");
        exit(0);
    }

    int frame_count = 0, page_miss = 0, page_hit = 0, read_count = 0, write_count = 0;

if(algo_nm==1)
{
    while (fscanf(fp,"%s %c\n", reference_string, &operator) != EOF)
    {
        if (frame_count < frame_size)
        {
            if (searching(reference_string, algo_nm) == 0) // Check if page is present in Frame queque
            {
                insert_Operation(reference_string);
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
                insert_Operation(reference_string);
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
    while (fscanf(fp,"%s %c\n", reference_string, &operator) != EOF)
    {
        int position;
        if (frame_count < frame_size)
        {
            position = searching(reference_string, algo_nm);
            if (position == -1) // Check if page is present in Frame queque
            {
                insert_Operation(reference_string);
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
                insert_Operation(reference_string);
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
    fclose(fp);
}
