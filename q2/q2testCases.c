/* Start Header
*****************************************************************/
/*!
\file q2testCases.c
\author Jodie Moh
\author Zhei Wei
\author Aloysius Wong
\date 31/03/2021
\brief
This is a preset test case values file to q2.c.
*/
/* End Header
*******************************************************************/
/**
 * @brief This function changes the values, copied from the preset test case 
 * to proceed with the dynamic memory allocation approaches.
 * 
 * @param MEM_PART Integer type variable for memory part. It is also constant 
 * in order to make its value fix, to prevent changes in the underlying value.
 * @param PROC_PART Integer type variable for process part. It is also constant 
 * in order to make its value fix, to prevent changes in the underlying value.
 * @param m This is a pointer to an integer to dereference memory value.
 * @param p This is a pointer to an integer to dereference process value.
 * @see firstFit(), bestFit(), worstFit(), runAll()
 */
void changeVals(const int MEM_PART, const int PROC_PART, 
const int *m, const int *p)
{
    int i = 0;
    for (i = 0; i < MEM_PART; i++)
        memPart[i] = m[i];
    for (i = 0; i < PROC_PART; i++)
        procPart[i] = p[i];
}
/**
 * @brief This is preset test case 1
 * @note First-case will 1 process that have no memory space for it.
 * @note Best-case with all processes allocated.
 * @note Worst-case with 3 processes that have no memory space for it.
 * @see firstFit(), bestFit(), worstFit(), runAll()
 */
void testCase1()
{
    int m[12] = {160, 350, 650, 80, 410, 50, 720, 905, 570, 130, 260, 830};
    int p[10] = {123, 456, 78, 901, 234, 567, 89, 600, 200, 345};
    MEM_PART = 12;
    PROC_PART = 10;
    changeVals(MEM_PART, PROC_PART, m, p);
    runProgram(0);
}

/**
 * @brief This is preset test case 2
 * @note First-case will 1 process that have no memory space for it.
 * @note Best-case with all processes allocated.
 * @note Worst-case with 1 process that have no memory space for it.\
 * @see firstFit(), bestFit(), worstFit(), runAll()
 */
void testCase2()
{
    /*tut8 question*/
    int m[5]={100,500,200,300,600};
    int p[4]={212,417,112,426};
    MEM_PART=5;
    PROC_PART=4;
    changeVals(MEM_PART, PROC_PART, m, p);
    runProgram(0);
}