#include "html-generator.h"

// This is an example program, which generates HTML code for header.
int main()
{
    /* Generates first "html" tag with parameters (lang=en):
        <html lang=en>
        </html>
    */ 
    char *name = "html";
    insert_html_tag(name, "lang=\"en\"");

    /* Inserts new tag "head" into the html tag, without parameters (NULL):  
        <html lang=en>
            <head>
            </head>
        </html>
    */
    char *head_tag = "head";
    insert_html_tag(head_tag, NULL);

    /* Inserts new tag "title" into the head tag, without parameters (NULL):
        <html lang=en>
            <head>
                <title>
                </title>
            </head>
        </html>
    */
    insert_html_tag("title", NULL);

    /* Inserts text "Reginos receptai" into the "title" tag (the title of the page is now "Reginos receptai"):
        <html lang=en>
            <head>
                <title>
                    Reginos receptai
                </title>
            </head>
        </html>
    */
    char *title_name = "Reginos receptai";
    insert_html_text(title_name);

    /* Exits 2 tags ("title" and "head"), next code will be in the "html" tag only:
        <html lang=en>
            <head>
                <title>
                    Reginos receptai
                </title>
            </head>
            (This is where the new tag will be inserted)
        </html>
    */
    exit_html_field(2);

    /* Inserts new tag "body" into the "html" tag, without parameters (NULL):
        <html lang=en>
            <head>
                <title>
                    Reginos receptai
                </title>
            </head>
            <body>
            </body>
        </html>
    */
    char *name2 = "body";
    insert_html_tag(name2, NULL);

    // Generates the output file (output.html) containing the HTML code:
    char *file_name = "output.html";
    generate_html_file(file_name);

    // Deletes the HTML code and frees up the memory:
    delete_html_code();

    return 0;
}

