#ifndef HTML_DOUBLY_LINKED_LIST
#define HTML_DOUBLY_LINKED_LIST

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HTML
{
    char *text;
    struct HTML *previous;
    struct HTML *next;
} HTML;

void generate_html_file(char *file_name);

HTML *create_html(char *text, HTML *previous, HTML *next);

void insert_html_tag(char *tag, char *params);

void insert_text(char *text);

void exit_html_field(int count);

void cleanup();

#endif