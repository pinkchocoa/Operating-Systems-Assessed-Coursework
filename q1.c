/* Start Header
*****************************************************************/
/*!
\file q1.c
\author Jodie Moh
\par email:
\date 
\brief
Write a C programming which is to simulate the functions of the OS
to implement the Banker's algorithm, to detect if the system is in
Safestate or unsafe state.

If it is in the safe state, your Banker’s algorithm need print out
(display) the execution sequences in which these processes may 
complete on the screen. 

If it is in the unsafe state, your Banker’s algorithm need display 
which process it fails at by showing the available resources at 
this point of time, and the processes needed resources at this 
point of time. 
*/
/* End Header
*******************************************************************/
#include <stdio.h>
#include <string.h>

#define PROCESS_NUM 6
#define RESOURCE_NUM 4

//need to take in 4 inputs
/*
1)Input 1: the number of total instances of resource type A.  
(e.g., entering 50, means there are 50 instances of resource type A).
2)Input 2: the number of total instances of resource type B. 
3)Input 3: the number of total instances of resource type C. 
4)Input 4: the number of total instances of resource type D. 
*/
void getResourceInput(int* typeA, int* typeB, int* typeC, int* typeD)
{
    while(printf("Enter the number of total instances of resource type A.\n") 
    && scanf("%d", typeA) != 1) //this loops as long as the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    while(printf("Enter the number of total instances of resource type B.\n") 
    && scanf("%d", typeB) != 1) //this loops as long as the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    while(printf("Enter the number of total instances of resource type C.\n") 
    && scanf("%d", typeC) != 1) //this loops as long as the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
        
    while(printf("Enter the number of total instances of resource type D.\n") 
    && scanf("%d", typeD) != 1) //this loops as long as the input is invalid
    //aka it will ask again
        scanf("%*[^\n]%*c"); /*clear buffer for next scanf*/
}

void getArrayInput(int& [PROCESS_NUM][RESOURCE_NUM])
{
}


int main()
{
    int typeA = 0, typeB = 0, typeC = 0, typeD = 0;
    int allocation[PROCESS_NUM][RESOURCE_NUM];
    int max[PROCESS_NUM][RESOURCE_NUM];
    getResourceInput(&typeA, &typeB, &typeC, &typeD);
    
    //printf("%d,%d,%d,%d", typeA, typeB, typeC, typeD);
    
    
    return 0;
}