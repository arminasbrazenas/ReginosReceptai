#include "HTML_code_doubly_linked_list.h"

int main()
{
    char *name = "html";
    insert_tag(name, NULL);
    char *name1 = "head";
    insert_tag(name1, "Harambe is good");
    char *value = "Reginos receptai";
    insert_text(value);
    exit_field(1);
    char *name2 = "body";
    insert_tag(name2, NULL);

    printf("Tag inserted\n");
    char *file_name = "output.txt";
    generate_html_file(file_name);
    printf("File printed\n");
    delete_code();
    return 0;
}

