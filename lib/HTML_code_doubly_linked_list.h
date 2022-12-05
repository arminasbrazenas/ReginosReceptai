#ifndef HTML_CODE_DOUBLE_LINKED_LIST
#define HTML_CODE_DOUBLE_LINKED_LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HTML_CODE
{
    char *text;
    struct HTML_CODE *previous;
    struct HTML_CODE *next;
} HTML_CODE;

void generate_html_file(char *file_name);

HTML_CODE *create_HTML_CODE(char *text, HTML_CODE *previous, HTML_CODE *next);

void insert_tag(char *name, char *param);

void insert_text(char *text);

void exit_field(int count);

void delete_code();

#endif