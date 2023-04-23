/*
Enter frame size: 4
Start entering references:
7 0 1 2 0 3 0 4 2 3 0 3 2
*/
#include "stdio.h"
#include "stdlib.h"
#include "stdbool.h"

int pointer;
int hits=0;
int faults=0;

void print(int frame_size,int frame[])
{
    int i;
    for(i=0;i<frame_size;i++)
    {
        if(frame[i]==-1)
            printf("- ");
        else
            printf("%d ",frame[i]);
    }
    printf("\n");
}

void add_reference_fifo(int frame_size,int frame[], int reference)
{
    
    int i;
    bool alloted = false;
    for(i=0;i<frame_size;i++)
    {
        if(frame[i]==reference)
        {
            alloted = true;
            printf("  Hit for %d | ", reference);
            hits++;
            break;
        }
        else if(frame[i]==-1)
        {
            alloted = true;
            frame[i] = reference;
            printf("Fault for %d | ", reference);
            faults++;
            break;
        }
    }
    if(alloted == false)
    {
        faults++;
        printf("Fault for %d | ", reference);
        frame[pointer] = reference;
        pointer = (pointer+1)%frame_size;
    }
    print(frame_size, frame);
}

int predict(int reference_length, int references[], int page_no ,int frame_size,int frame[], int start)
{
    int pos = -1, farthest = start, i;
    for(i=0;i<frame_size;i++)
    {
        int j;
        for(j=start-1;j>=0;j--)
        {
            if(frame[i]==references[j])
            {
                if(j<farthest)
                {
                    farthest=j;
                    pos=i;
                }
                break;
            }
        }
        if(j==page_no)
            return i;
    }
    if(pos == -1)
        return 0;
    else
        return pos;
}

void add_reference_lru(int frame_size,int frame[], int reference, int current_position,int reference_length, int references[])
{
    int i;
    bool allocated=false;
    for(i=0;i<frame_size;i++)
    {
        
        if(frame[i]==reference)
        {
            printf("  Hit for %d | ", reference);
            hits++;
            allocated = true;
            break;
        }
        else if(frame[i]==-1)
        {
            frame[i] = reference;
            printf("Fault for %d | ", reference);
            faults++;
            allocated = true;
            break;
        }
    }
    if(allocated==false)
    {
        int j = predict(reference_length,references,current_position,frame_size,frame,current_position+1);
        frame[j] = reference;
        printf("Fault for %d | ", reference);
        faults++;   
    }
    print(frame_size, frame);
}
int main()
{
    int faults = 1, hits = 0;
    int frame_size,i,number_of_references;
    int choice;
    printf("Enter frame size: ");
    scanf("%d",&frame_size);
    int frame[frame_size];
    for(i=0;i<frame_size;i++)
    {
        frame[i] = -1;
    }
    print(frame_size,frame);
    printf("Enter the number of references: ");
    scanf("%d",&number_of_references);
    printf("1. FIFO\n2. LRU\nEnter Choice: ");
    scanf("%d",&choice);
    int reference[number_of_references];
    printf("\nStart entering references\n");
    switch(choice){
      case 1:
        for(i=0;i<number_of_references;i++)
        {
            scanf("%d",&reference[i]);
            add_reference_fifo(frame_size,frame,reference[i]);
        }
        // printf("\nNumber of faults: %d \nNumber of hits: %d\n",faults,hits );
        break;
      case 2:
        for(i=0;i<number_of_references;i++)
        {
            scanf("%d",&reference[i]);
            add_reference_lru(frame_size,frame,reference[i],i,number_of_references,reference);
        }
        // printf("\nNumber of faults: %d \nNumber of hits: %d\n",faults,hits );
        break;
       default:
        printf("Enter Correct Choice!!!");
    }
    printf("Do you want to run again?\n1. Yes\n2. No\nEnter: ");
    scanf("%d", &choice);
    if (choice==1){
        main();
    }
}

