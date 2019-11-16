#include "../include/CalcTree.h"

int FirstWordFromText(char** ptr_on_text, int tmp_num)
{
    SkipToBrace(ptr_on_text);

    int readed = 0;
    tmp_num = 0;

    sscanf(*ptr_on_text, "%d%n", &tmp_num, &readed);

    if (readed == 0 && **ptr_on_text == '(')
        return NOT_READ;

    switch (**ptr_on_text)
    {
        case '+':
            tmp_num = ADD;
            break;
        case '-':
            tmp_num = SUB;
            break;
        case '*':
            tmp_num = MUL;
            break;
        case '/':
            tmp_num = DIV;

    }

    return OK;
}

void SkipToBrace(char** ptr_on_text)
{
    while (**ptr_on_text != '(' &&
           **ptr_on_text != ')')
           (*ptr_on_text)++;
    (*ptr_on_text)++;
}

char* ReadFile (const char* str, size_t *size, const char* chmod)
{
    FILE *fp = NULL;

    if ((fp = fopen(str, chmod)) == NULL)
    {
        printf("Cannot find text\n");
        system("pause");
        exit(0);
    }

    fseek (fp, 0L, SEEK_END);

    *size = ftell(fp);

    char *text = (char *) calloc(*size + 1, sizeof(char));

    fseek (fp, 0L, SEEK_SET);

    fread (text, sizeof(char), *size, fp);

    text[*size] = '\0';

    fclose (fp);

    return text;
}

const char* bool_to_str(bool a)
{
    if (a)
        return "Yes";

    else
        return "Not";
}

int GetString(char* str)
{
    fgets(str, STR_LENGTH, stdin);
    str[strlen(str) - 1] = '\0';
}


int PrintError(int err_code, const char* function_name)
{
    printf("Error occured in function %s code %d", function_name, err_code);
}
