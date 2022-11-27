//
// Created by Augustinas on 2022-11-26.
//
#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct HTML_CODE
{
    char *text;
    struct HTML_CODE *previous;
    struct HTML_CODE *next;
} HTML_CODE;

HTML_CODE *___HTML_START___ = NULL;
HTML_CODE *___HTML_CURRENT___ = NULL;

void generate_html_file(char *file_name);

HTML_CODE *create_HTML_CODE(char *text, HTML_CODE *previous, HTML_CODE *next);

void insert_tag(char *name, char *param);

void insert_text(char *text);

void exit_field(int count);

