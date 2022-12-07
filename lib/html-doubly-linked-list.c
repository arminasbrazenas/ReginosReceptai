#include "html-doubly-linked-list.h"

static HTML *g_html_start = NULL;
static HTML *g_html_current = NULL;

void generate_html_file(char *file_name)
{
    if (g_html_start != NULL)
    {
        FILE *file = fopen(file_name, "w");
        if (file == NULL) {
            printf("Failed to open file %s: %s\n", file_name, strerror(errno));
            return;
        }

        HTML *html_current = g_html_start;
        while (html_current != NULL)
        {
            fprintf(file, "%s\n", html_current->text);
            html_current = html_current->next;
        }
        fclose(file);
    }
    else
    {
        printf("ERROR: HTML code does not exist.\n");
    }
}

HTML *create_html(char *text, HTML *previous, HTML *next)
{
    HTML *new_html = malloc(sizeof(HTML));
    if (new_html == NULL)
    {
        printf("Failed to allocate memory for new element.\n");
        return NULL;
    }

    new_html->next = next;
    new_html->previous = previous;
    new_html->text = text;

    if (previous != NULL)
    {
        previous->next = new_html;
    }
    if (next != NULL)
    {
        next->previous = new_html;
    }

    g_html_current = new_html;
    return new_html;
}

void insert_html_tag(char *tag, char *params)
{
    size_t tag_length = 2 + strlen(tag);
    if (params != NULL)
    {
        tag_length += 1 + strlen(params);
    }

    char *opening_tag = calloc(tag_length, sizeof(char));
    if (opening_tag == NULL)
    {
        printf("Failed to allocate memory for opening tag\n");
        return;
    }

    strcat(opening_tag, "<");
    strcat(opening_tag, tag);
    if (params != NULL)
    {
        strcat(opening_tag, " ");
        strcat(opening_tag, params);
    }
    strcat(opening_tag, ">");

    tag_length = 3 + strlen(tag);
    char *closing_tag = calloc(tag_length, sizeof(char));
    if (closing_tag == NULL)
    {
        printf("Failed to allocate memory for closing tag\n");
        return;
    }
    strcat(closing_tag, "</");
    strcat(closing_tag, tag);
    strcat(closing_tag, ">");

    if (g_html_start != NULL)
    {
        create_html(opening_tag, g_html_current, g_html_current->next);
        create_html(closing_tag, g_html_current, g_html_current->next);
        g_html_current = g_html_current->previous;
    }
    else
    {
        g_html_start = create_html(opening_tag, NULL, NULL);
        create_html(closing_tag, g_html_current, g_html_current->next);
        g_html_current = g_html_current->previous;
    }
}

void insert_text(char *text)
{
    char *text_buffer = malloc(sizeof(char) * strlen(text));
    if (text_buffer == NULL)
    {
        printf("Failed to allocate memory for text buffer\n");
        return;
    }

    strcpy(text_buffer, text);
    if (g_html_start != NULL)
    {
        create_html(text_buffer, g_html_current, (*g_html_current).next);
    }
    else
    {
        HTML *line = create_html(text_buffer, NULL, NULL);
        g_html_start = line;
    }
}

void exit_html_field(int count)
{
    for (int i = 0; i < count; ++i) {
        g_html_current = g_html_current->next;
    }
}

void cleanup()
{
    HTML *next_node;
    while (g_html_start != NULL)
    {
        next_node = g_html_start->next;
        free(g_html_start->text);
        free(g_html_start);
        g_html_start = next_node;
    }
    g_html_current = NULL;
}