#include "html-doubly-linked-list.h"

int main()
{
    // This program outputs a text file containing html code which creates a title for the page.

    /* Generates first html tag with parameters (lang=en):
        <html lang=en>
        </html>
    */ 
    char *name = "html";
    insert_tag(name, "lang=\"en\"");

    /* Inserts new tag "head" into the html tag, without parameters (NULL):  
        <html lang=en>
        <head>
        </head>
        </html>
    */
    char *head_tag = "head";
    insert_tag(head_tag, NULL);

    /* Inserts new tag "title" into the head tag, without parameters (NULL):  
        <html lang=en>
        <head>
        <title>
        </title>
        </head>
        </html>
    */
    insert_tag("title", NULL);

    /* Inserts text "Reginos receptai" into the title tag (the title of the page is now "Reginos receptai"): 
        <html lang=en>
        <head>
        <title>
        Reginos receptai
        </title>
        </head>
        </html>
    */
    char *title_name = "Reginos receptai";
    insert_text(title_name);

    /* Exits 2 tags (title and head tags), next code will be in the html tag only
        <html lang=en>
        <head>
        <title>
        Reginos receptai
        </title>
        </head>
        (This is there the new tag will be inserted)
        </html>
    */
    exit_field(2);

    /* Inserts new tag "body" into the html tag, without parameters (NULL)
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
    insert_tag(name2, NULL);


    printf("Tag inserted\n");

    // Generates the output file (output.txt) containing the html code, which we created before
    char *file_name = "output.txt";
    generate_html_file(file_name);
    printf("File printed\n");

    // Deletes the linked list of html code and frees up the memory
    delete_code();
    return 0;
}
