#include "HTML_code_doubly_linked_list.h"

HTML_CODE *_HTML_START_ = NULL;
HTML_CODE *_HTML_CURRENT_ = NULL;

void generate_html_file(char *file_name)
{
    if(_HTML_START_ != NULL)
    {
        FILE *file = fopen(file_name, "w");
        if(file == NULL) {
            printf("Failed to open the output file\n");
            return;
        }
        HTML_CODE *currentLine = _HTML_START_;
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
    _HTML_CURRENT_ = new_elem;
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

    if(_HTML_START_ != NULL)
    {
        HTML_CODE *field_start = create_HTML_CODE(start_text, _HTML_CURRENT_, (*_HTML_CURRENT_).next);
        HTML_CODE *field_end = create_HTML_CODE(end_text, _HTML_CURRENT_, (*_HTML_CURRENT_).next);
        _HTML_CURRENT_ = (*_HTML_CURRENT_).previous;
    }
    else
    {
        HTML_CODE *field_start = create_HTML_CODE(start_text, NULL, NULL);
        HTML_CODE *field_end = create_HTML_CODE(end_text, _HTML_CURRENT_, (*_HTML_CURRENT_).next);
        _HTML_CURRENT_ = (*_HTML_CURRENT_).previous;
        _HTML_START_ = field_start;
    }
}

void insert_text(char *text)
{
    if(_HTML_START_ != NULL)
    {
        HTML_CODE *field_start = create_HTML_CODE(text, _HTML_CURRENT_, (*_HTML_CURRENT_).next);
    }
    else
    {
        HTML_CODE *line = create_HTML_CODE(text, NULL, NULL);
        _HTML_START_ = line;
    }
}

void exit_field(int count)
{
    for(int i = 0; i < count; i++) {
        _HTML_CURRENT_ = (*_HTML_CURRENT_).next;
    }
}