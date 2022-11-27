//
// Created by Augustinas on 2022-11-26.
//
#include "HTML_code_doubly_linked_list.h"

void generate_html_file(char *file_name)
{
    if(___HTML_START___ != NULL)
    {
        FILE *file = fopen(file_name, "w");
        if(file == NULL)
        {
            printf("Failed to open the output file\n");
            return;
        }
        HTML_CODE *currentLine = ___HTML_START___;
        while(currentLine != NULL)
        {
            fprintf(file, "%s\n", (*currentLine).text);
            currentLine = (*currentLine).next;
        }
        fclose(file);
    }
    else
    {
        printf("ERROR: no code has been generated\n");
    }
}

HTML_CODE *create_HTML_CODE(char *text, HTML_CODE *previous, HTML_CODE *next)
{
    HTML_CODE *new_elem = malloc(sizeof(HTML_CODE));
    if(new_elem == NULL)
    {
        printf("Failed to allocate memory for new element\n");
        return NULL;
    }
    (*new_elem).next = next;
    (*new_elem).previous = previous;
    (*new_elem).text = text;
    if(previous != NULL)
        (*previous).next = new_elem;
    if(next != NULL)
        (*next).previous = new_elem;
    ___HTML_CURRENT___ = new_elem;
    return new_elem;
}

void insert_tag(char *name, char *param)
{
    int str_size = 2 + strlen(name);
    if(param != NULL)
    {
        str_size += 1 + strlen(param);
    }

    char *start_text = calloc(str_size, sizeof(char));
    if(start_text == NULL)
    {
        printf("Failed to allocate memory for start_text\n");
        return;
    }
    strcat(start_text, "<");
    strcat(start_text, name);
    if(param != NULL)
    {
        strcat(start_text, " ");
        strcat(start_text, param);
    }
    strcat(start_text, ">");

    str_size = 3 + strlen(name);
    char *end_text = calloc(str_size, sizeof(char));
    if(end_text == NULL)
    {
        printf("Failed to allocate memory for end_text\n");
        return;
    }
    strcat(end_text, "</");
    strcat(end_text, name);
    strcat(end_text, ">");

    if(___HTML_START___ != NULL)
    {
        HTML_CODE *field_start = create_HTML_CODE(start_text, ___HTML_CURRENT___, (*___HTML_CURRENT___).next);
        HTML_CODE *field_end = create_HTML_CODE(end_text, ___HTML_CURRENT___, (*___HTML_CURRENT___).next);
        ___HTML_CURRENT___ = (*___HTML_CURRENT___).previous;
    }
    else
    {
        HTML_CODE *field_start = create_HTML_CODE(start_text, NULL, NULL);
        HTML_CODE *field_end = create_HTML_CODE(end_text, ___HTML_CURRENT___, (*___HTML_CURRENT___).next);
        ___HTML_CURRENT___ = (*___HTML_CURRENT___).previous;
        ___HTML_START___ = field_start;
        ___HTML_END___ = field_end;
    }
}

void insert_text(char *text)
{
    if(___HTML_START___ != NULL)
    {
        HTML_CODE *field_start = create_HTML_CODE(text, ___HTML_END___, NULL);
    }
    else
    {
        HTML_CODE *line = create_HTML_CODE(text, NULL, NULL);
        ___HTML_START___ = line;
        ___HTML_END___ = line;
    }
}

void exit_field(int count)
{
    for(int i = 0; i < count; i++) {
        ___HTML_CURRENT___ = (*___HTML_CURRENT___).next;
    }
}