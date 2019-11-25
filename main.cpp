#include <iostream>
#include "include/MainHeader.h"

int unit_test()
{
    int tmp = 0;
    int ret = 0;

    const char* a = "+";
    const char* b = "^";
    const char* c = "x";
    const char* d = "sinh";

    StrCmdToNum<int>(a, &ret, &tmp);
    if (ADD != ret && tmp != OPERATION)
        printf("error STR_CMD_TO_NUM ADD return %d\n", ret);

    StrCmdToNum<int>(b, &ret, &tmp);
    if (POW != ret && tmp != OPERATION)
        printf("error STR_CMD_TO_NUM pow return %d\n", ret);

    StrCmdToNum<int>(c, &ret, &tmp);
    if (VAR != ret && tmp != VARIABLE)
        printf("error STR_CMD_TO_NUM var return %d\n", ret);

    StrCmdToNum<int>(d, &ret, &tmp);
    if (SINH != ret && tmp != FUNC)
        printf("error STR_CMD_TO_NUM sinh return %d\n", ret);
}

int main()
{
    unit_test();
    CalcTree<double>* cur = new CalcTree<double>;
    CalcTree<double>* diff = new CalcTree<double>;

    cur->head_node = Parser<double>::CreateTree("input.txt");

    cur->GraphToDot();

    diff->head_node = cur->head_node->DiffNode();

    diff->GraphToDot();

    printf("we end %lf\n", cur->GetResult(2));

    delete cur;
    //delete diff;

    return 0;
}
