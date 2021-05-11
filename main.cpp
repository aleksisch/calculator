#include <iostream>
#include "include/MainHeader.h"

int main(int argc, char** argv)
{
    if (argc < 2) {
        printf("Expected file with expression\n");
        return 0;
    }
    CalcTree<double>* cur = new CalcTree<double>;
    CalcTree<double>* diff = new CalcTree<double>;

    cur->head_node = Parser<double>::CreateTree(argv[1]);

    cur->GraphToDot();

    diff->head_node = cur->head_node->DiffNode();

    diff->GraphToDot();

    diff->WriteGraphFile();

    printf("we end %lf\n", diff->GetResult(2));

    delete cur;
    delete diff;

    return 0;
}
