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

bool generate_html_file(char *file_name);

HTML *create_html(char *text, HTML *previous, HTML *next);

bool insert_html_tag(char *tag, char *params);

bool insert_text(char *text);

void exit_html_field(int count);

void cleanup();

#endif