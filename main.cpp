#include "include/CalcTree.h"

int main()
{
    int n = 0;
    int s = 0;

    CalcTree cur;

    cur.ReadGraphFile();
    cur.GraphToDot();
    printf("%d", cur.GetHead()->number);
    printf("%p", cur.GetHead()->left_child->number);
    printf("%p", cur.GetHead()->right_child);

    return 0;
}
