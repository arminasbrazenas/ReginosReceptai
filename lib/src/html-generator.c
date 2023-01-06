#include "html-generator.h"
#include <errno.h>

HTML *g_html_start = NULL;
HTML *g_html_current = NULL;
HTML *create_html(char *text, HTML *previous, HTML *next);

//-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
// Public functions
//-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
/// Generates a file containing HTML code.
/// \param file_name File to generate HTML in.
/// \return 0 on success, otherwise error code.
int generate_html_file(char *file_name)
{
    if (file_name == NULL)
    {
        return EINVAL;
    }

    if (g_html_start != NULL)
    {
        FILE *file = fopen(file_name, "w");
        if (file == NULL)
        {
            return errno;
        }

        HTML *current = g_html_start;
        while (current != NULL)
        {
            fprintf(file, "%s\n", current->text);
            current = current->next;
        }
        fclose(file);
    }
    else
    {
        return EINVAL;
    }

    return 0;
}

/// Inserts opening and closing tags to HTML code.
/// \param tag Tag to insert.
/// \param attributes Tag's attributes. Set to NULL if tag has no attributes.
/// \return 0 on success, otherwise error code.
int insert_html_tag(char *tag, char *attributes)
{
    if (tag == NULL)
    {
        return EINVAL;
    }
    size_t tag_length = 3 + strlen(tag);
    if (attributes != NULL)
    {
        tag_length += 1 + strlen(attributes);
    }

    char *opening_tag = calloc(tag_length, sizeof(char));
    if (opening_tag == NULL)
    {
        return ENOMEM;
    }

    strcat(opening_tag, "<");
    strcat(opening_tag, tag);
    if (attributes != NULL)
    {
        strcat(opening_tag, " ");
        strcat(opening_tag, attributes);
    }
    strcat(opening_tag, ">");

    tag_length = 4 + strlen(tag);
    char *closing_tag = calloc(tag_length, sizeof(char));
    if (closing_tag == NULL)
    {
        return ENOMEM;
    }
    strcat(closing_tag, "</");
    strcat(closing_tag, tag);
    strcat(closing_tag, ">");

    if (g_html_start != NULL)
    {
        create_html(opening_tag, g_html_current, g_html_current->next);
        create_html(closing_tag, g_html_current, g_html_current->next);

        if (g_html_current == NULL)
        {
            return ENOMEM;
        }

        g_html_current = g_html_current->previous;
    }
    else
    {
        g_html_start = create_html(opening_tag, NULL, NULL);
        create_html(closing_tag, g_html_current, g_html_current->next);

        if (g_html_current == NULL)
        {
            return ENOMEM;
        }

        g_html_current = g_html_current->previous;
    }
    return 0;
}

/// Inserts text to HTML code.
/// \param text Text to insert.
/// \return 0 on success, otherwise error code.
int insert_html_text(char *text)
{
    if (text == NULL)
    {
        return EINVAL;
    }
    char *text_buffer = malloc(sizeof(char) * (strlen(text) + 1));
    if (text_buffer == NULL)
    {
        return ENOMEM;
    }

    strcpy(text_buffer, text);
    if (g_html_start != NULL)
    {
        HTML *node = create_html(text_buffer, g_html_current, (*g_html_current).next);
        if (node == NULL)
        {
            return ENOMEM;
        }
    }
    else
    {
        HTML *line = create_html(text_buffer, NULL, NULL);
        if (line == NULL)
        {
            return ENOMEM;
        }
        g_html_start = line;
    }
    return 0;
}

/// Exits the current HTML field and moves to the upcoming ones.
/// \param count Number of HTML fields to exit.
void exit_html_field(int count)
{
    for (int i = 0; i < count; ++i)
    {
        if (g_html_current == NULL)
        {
            return;
        }

        g_html_current = g_html_current->next;
    }
}

/// Frees memory used by HTML code.
void delete_html_code()
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

//-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
// Private functions
//-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+-----+
/// Inserts node with text to an HTML doubly linked list.
/// \param text HTML struct text.
/// \param previous Pointer to previous HTML node.
/// \param next Pointer to upcoming HTML node.
/// \return Pointer to newly created HTML struct on success, NULL on failure.
HTML *create_html(char *text, HTML *previous, HTML *next)
{
    if (text == NULL)
    {
        return NULL;
    }

    HTML *new_html = malloc(sizeof(HTML));
    if (new_html == NULL)
    {
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