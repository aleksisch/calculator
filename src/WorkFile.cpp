#include "../include/AkinatorTree.h"

int FirstWordFromText(char** ptr_on_text, int tmp_word, bool is_operator)
{
    SkipToBrace(ptr_on_text);

    int counter = 0;



    printf("%s\n", tmp_word);
    if (counter > STR_LENGTH - 1)
        return LONG_STRING;

    if (**ptr_on_text == '}')
    {
        (*ptr_on_text)++;
        return NIL;
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
