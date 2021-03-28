void changeVals(const int MEM_PART, const int PROC_PART, 
const int *m, const int *p)
{
    int i = 0;
    for (i = 0; i < MEM_PART; i++)
        memPart[i] = m[i];
    for (i = 0; i < PROC_PART; i++)
        procPart[i] = p[i];
}

void testCase1()
{
    int m[12] = {160, 350, 650, 80, 410, 50, 720, 905, 570, 130, 260, 830};
    int p[10] = {123, 456, 78, 901, 234, 567, 89, 600, 200, 345};
    MEM_PART = 12;
    PROC_PART = 10;
    changeVals(MEM_PART, PROC_PART, m, p);
    runProgram(0);
}

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