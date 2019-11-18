#include "../include/MainHeader.h"

int FirstWordFromText(char** ptr_on_text, int* tmp_num)
{
    SkipToBrace(ptr_on_text);
    printf("%s", *ptr_on_text);
    int readed = 0;

    char tmp_str[STR_LENGTH] = {0};

    int read_var = sscanf(*ptr_on_text, "%[0-9.,]%n", tmp_str, &readed);
    printf("%d", read_var);
    if (read_var == 0)
    {
        int read_str = sscanf(*ptr_on_text, "%[^0-9().,x]%n", tmp_str, &readed);

        if (read_str == 0)
        {
            (*ptr_on_text)++;
            return NOT_READ;
        }

        else
        {
            printf("read str %s\n", tmp_str);
            (*ptr_on_text) += readed;
            int type_cmd = VALUE;
            *tmp_num = StrCmdToNum(tmp_str, &type_cmd);

            return type_cmd;
        }
    }

    else
    {
        printf("OOOOOOOOO%s", tmp_str);
        *tmp_num = std::stoi(tmp_str);
        (*ptr_on_text) += readed;
        return VALUE;
    }
}

void SkipToBrace(char** ptr_on_text)
{
    while (**ptr_on_text == '\n' ||
           **ptr_on_text == '\t' ||
           **ptr_on_text == ' ')
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

void GetString(char* str)
{
    fgets(str, STR_LENGTH, stdin);
    str[strlen(str) - 1] = '\0';
}


void PrintError(int err_code, const char* function_name)
{
    printf("Error occured in function %s code %d", function_name, err_code);
}
