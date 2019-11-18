#include "include/MainHeader.h"

int main()
{
    CalcTree cur;

    cur.ReadGraphFile();
    cur.GraphToDot();
    cur.WriteGraphFile();
    printf("\n%d\n", cur.GetResult());

    CalcTree n;

    n.SetHead(cur.GetHead()->DiffNode());
    printf("HERE");
    n.GraphToDot();
    n.WriteGraphFile();
    return 0;
}
