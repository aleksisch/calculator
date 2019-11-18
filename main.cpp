#include "include/MainHeader.h"

int main()
{
    CalcTree cur;

    cur.ReadGraphFile();
    cur.GraphToDot();
    cur.WriteGraphFile();
    printf("\n%d\n", cur.GetResult());
    return 0;
}
