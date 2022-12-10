#ifndef HTML_DOUBLY_LINKED_LIST
#define HTML_DOUBLY_LINKED_LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct HTML
{
    char *text;
    struct HTML *previous;
    struct HTML *next;
} HTML;

int generate_html_file(char *file_name);
int insert_html_tag(char *tag, char *attributes);
int insert_text(char *text);
void exit_html_field(int count);
void free_html_code();

#endif