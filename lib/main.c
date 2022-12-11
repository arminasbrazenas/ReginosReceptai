#include "html-doubly-linked-list.h"

int main()
{
    char *name = "html";
    insert_html_tag(name, NULL);
    char *name1 = "head";
    insert_html_tag(name1, "Harambe is good");
    char *value = "Laba diena visiems";
    insert_text(value);
    exit_html_field(1);
    char *name2 = "body";
    insert_html_tag(name2, NULL);

    printf("Tag inserted\n");
    char *file_name = "output.html";
    generate_html_file(file_name);
    printf("File printed\n");
    free_html_code();
    return 0;
}

