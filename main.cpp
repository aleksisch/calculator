#include <iostream>
#include "include/MainHeader.h"

int main()
{

    CalcTree<double>* cur = new CalcTree<double>;
    CalcTree<double>* diff = new CalcTree<double>;

    cur->head_node = Parser<double>::CreateTree("input.txt");

    cur->GraphToDot();

    diff->head_node = cur->head_node->DiffNode();

    diff->GraphToDot();

    diff->WriteGraphFile();

    printf("we end %lf\n", diff->GetResult(2));

    delete cur;
    delete diff;

    return 0;
}
