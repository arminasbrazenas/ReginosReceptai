#include <stdio.h>
#include "html-generator.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>
#include "css_header.h"

char* getline(FILE *file);

void insert_instructions(char **text);
void insert_ingredients(char **ingredients);
void insert_image(const int image_nr);
void insert_recipe_header(char *title, unsigned rating);
void insert_recipe(const int image_nr, char *title, unsigned rating, char **text, char **ingredients);
void generate_recipes(const int recipe_count, char ***recipe_titles, int **recipe_ratings);
void insert_html_tag_and_exit(char *tag, char *attributes);
void insert_html_tag_with_text(char *tag, char *attributes, char *text);
void insert_boilerplate(char *root_dir_path);
void insert_navbar(char *root_dir_path);
void insert_main_div_tag();
void generate_css();
void generate_main_page(const int recipe_count, char **recipe_titles, int *recipe_ratings);
void generate_about_page();
void insert_recipe_card(const char *title, int rating/*, const char *image_address*/);
void get_recipe_content(char filename[], char **title, int *rating, char ***ingredients, char ***text);

int main() {
    generate_css();
    char **recipe_titles = NULL;
    int *recipe_ratings = NULL;
    ///TODO: Insertable recipe count
    generate_recipes(7, &recipe_titles, &recipe_ratings);
    generate_main_page(7, recipe_titles, recipe_ratings);
    generate_about_page();

    return 0;
}

void generate_about_page()
{
    insert_boilerplate(".");
    insert_navbar(".");
    insert_main_div_tag();
    insert_html_tag("div", "class=\"page-header d-flex flex-wrap mb-2 justify-content-between align-items-center\"");
    insert_html_tag_with_text("h2", "class=\"h5 mb-0 py-2\"", "Apie mus");
    exit_html_field(1);
    insert_html_tag_with_text("p", NULL, "Mes nesame atsakingi už tai, kaip jausitės po valgio.");
    generate_html_file("apie.html");
    delete_html_code();
}

void insert_main_div_tag()
{
    insert_html_tag("div", "class=\"container-md px-3\"");
}

void insert_rating(unsigned rating)
{
    for (unsigned i = 1; i <= 5; ++i)
    {
        insert_html_tag_and_exit("span", i <= rating ? "class=\"fa fa-star checked\"" : "class=\"fa fa-star\"");
    }
}

void insert_instructions(char **text)
{
    for(int i = 0; text[i] != NULL; ++i)
    {
        insert_html_tag_with_text("p", NULL, text[i]);
    }
}

void insert_ingredients(char **ingredients)
{
    insert_html_tag_with_text("p", "class=\"page-section mb-2\"", "Ingredientai:");
    insert_html_tag("ul", "class=\"list-group\"");
    for(int i = 0; ingredients[i] != NULL; i++)
    {
        insert_html_tag("li", "class=\"list-group-item\"");
        insert_html_tag_and_exit("input", "class=\"form-check-input me-1\" type=\"checkbox\"");
        insert_html_tag_with_text("span", "class=\"ingredient\"", ingredients[i]);
        exit_html_field(1);
    }
    exit_html_field(1);
}

void insert_image(const int image_nr)
{
    char image[80] = "<img\n src=\"../assets/recipe_";
    char recipe_number_str[10] = {0};
    itoa(image_nr, recipe_number_str, 10);
    strcat(image, recipe_number_str);
    strcat(image, "_img.jpg\"\nclass=\"card-img-top rounded-0\"\n/>");
    insert_html_text(image);
}

void insert_recipe_header(char *title, unsigned rating)
{
    insert_html_tag("div", "class=\"page-header d-flex flex-column flex-wrap mb-3\"");
    insert_html_tag_with_text("h2", "class=\"h2 mb-0 py-1\"", title);
    insert_html_tag("div", NULL);
    insert_rating(rating);
    exit_html_field(2);
}

void insert_recipe(const int image_nr, char *title, unsigned int rating, char **text, char **ingredients)
{
    insert_boilerplate("..");
    insert_navbar("..");

    insert_main_div_tag();
    insert_recipe_header(title, rating);
    insert_image(image_nr);
    insert_instructions(text);
    insert_ingredients(ingredients);
}

void generate_recipes(const int recipe_count, char ***recipe_titles, int **recipe_ratings)
{
    mkdir("receptai");

    *recipe_titles = malloc(recipe_count * sizeof(char*));
    *recipe_ratings = malloc(recipe_count * sizeof(int));

    for(int i = 0; i < recipe_count; i++)
    {
        char *title = NULL;
        int rating;
        char **ingredients = NULL;
        char **text = NULL;
        char filename[40] = "Receptu_tekstai/Receptas_";
        char recipe_number_str[10] = {0};
        itoa(i + 1, recipe_number_str, 10);
        strcat(filename, recipe_number_str);
        strcat(filename , ".txt");

        get_recipe_content(filename, &title, &rating, &ingredients, &text);
        insert_recipe(i + 1, title, rating, text, ingredients);

        char created_file_path[30] = "receptai/";
        strcat(created_file_path, recipe_number_str);
        strcat(created_file_path , ".html");
        generate_html_file(created_file_path);
        delete_html_code();

        free(ingredients);
        free(text);
        (*recipe_titles)[i] = title;
        (*recipe_ratings)[i] = rating;
    }
}

void get_recipe_content(char filename[], char **title, int *rating, char ***ingredients, char ***text) {
    *title = NULL;
    *ingredients = NULL;
    *text = NULL;

    FILE *ptr = fopen(filename, "r");
    if(ptr == NULL) {
        printf("Error: unable to open file '%s'\n", filename);
        return;
    }

    int string_size = 0;
    *title = getline(ptr);
    while(getc(ptr) != ' ');    //skips a word before the rating

    fscanf(ptr, "%d\n", rating);
    while(getc(ptr) != '\n');    //skips a word before the ingredients

    int count = -1;
    do {
        ++count;
        *ingredients = realloc(*ingredients, (count + 1) * sizeof(char*));
        if(*ingredients == NULL) {
            printf("Error: unable to allocate memory for ingredients\n");
            return;
        }

        (*ingredients)[count] = NULL;
        string_size = 0;
        (*ingredients)[count] = getline(ptr);

    } while(strcmp((*ingredients)[count], "Gaminimas:") != 0);
    (*ingredients)[count] = NULL;

    count = -1;
    do {
        ++count;
        *text = realloc(*text, (count + 1) * sizeof(char*));
        if(*text == NULL) {
            printf("Error: unable to allocate memory for text\n");
            return;
        }
        (*text)[count] = NULL;

        string_size = 0;
        (*text)[count] = getline(ptr);
    } while(!feof(ptr));
    *text = realloc(*text, (count + 2) * sizeof(char*));
    (*text)[count + 1] = NULL;

    fclose(ptr);
}


void insert_recipe_card(const char *title, int rating/*, const char *image_address*/)
{
    static int recipe_number = 0;
    recipe_number++;
    insert_html_tag("div", "class=\"col\"");
    char parameters[75] = "class=\"card rounded-0 border-0 h-100\" href=\"./receptai/";
    char recipe_number_str[10] = {0};
    itoa(recipe_number, recipe_number_str, 10);
    strcat(parameters, recipe_number_str);
    strcat(parameters, ".html\"");
    insert_html_tag("a", parameters);
    char image[80] = "<img\n src=\"./assets/recipe_";
    strcat(image, recipe_number_str);
    strcat(image, "_img.jpg\"\nclass=\"card-img-top rounded-0\"\n/>");
    insert_html_text(image);
    insert_html_tag("div", "class=\"card-body\"");
    insert_html_tag("p", "class=\"card-title h6\"");
    insert_html_text(title);
    exit_html_field(1);
    insert_html_tag("p", "class=\"card-text\"");
    insert_rating(rating);
    exit_html_field(4);
}

void insert_html_tag_and_exit(char *tag, char *attributes)
{
    insert_html_tag(tag, attributes);
    exit_html_field(1);
}

void insert_html_tag_with_text(char *tag, char *attributes, char *text)
{
    insert_html_tag(tag, attributes);
    insert_html_text(text);
    exit_html_field(1);
}

void generate_css()
{
    CSS styles;
    initCSS(&styles);


    Style root;
    initStyle(&root, "@import url(\"https://fonts.googleapis.com/css2?family=Merriweather:ital,wght@0,400;0,700;1,400;1,700&family=Open+Sans&display=swap\");\n\n:root");

    addCSSProperty(&root, "--primary-font", "\"Merriweather\", serif");
    addCSSProperty(&root, "--secondary-font", "\"Open Sans\", sans-serif");
    addCSSProperty(&root, "--primary-font-color", "#514343");
    addCSSProperty(&root, "--primary-font-color-hover", "#a19a98");
    addCSSProperty(&root, "--secondary-font-color", "#3b2222");
    addCSSProperty(&root, "--primary-background-color", "#ede9e4");
    addCSSProperty(&root, "--light-background-color", "#f8f5f1");
    addCSSProperty(&root, "--light-border", "1px solid #ebe1d6");
    addCSSProperty(&root, "--font-weight-bold", "700");

    pushStyle(&styles, &root);


    Style body;
    initStyle(&body, "body");

    addCSSProperty(&body, "font-family", "var(--secondary-font)");
    addCSSProperty(&body, "color", "var(--secondary-font-color)");

    pushStyle(&styles, &body);


    Style navBar;
    initStyle(&navBar, ".navbar");

    addCSSProperty(&navBar, "background-color", "var(--primary-background-color)");
    addCSSProperty(&navBar, "color", "var(--primary-font-color)");

    pushStyle(&styles, &navBar);


    Style navBarBrand;
    initStyle(&navBarBrand, ".navbar-brand");

    addCSSProperty(&navBarBrand, "font-family", "var(--primary-font)");
    addCSSProperty(&navBarBrand, "color", "inherit");
    addCSSProperty(&navBarBrand, "transition", "color 200ms ease-in-out");

    pushStyle(&styles, &navBarBrand);


    Style navLink;
    initStyle(&navLink, ".nav-link");

    addCSSProperty(&navLink, "text-transform", "uppercase");
    addCSSProperty(&navLink, "color", "inherit");

    pushStyle(&styles, &navLink);


    Style navLinkHover;
    initStyle(&navLinkHover, ".nav-link:hover,\n.navbar-brand:hover");

    addCSSProperty(&navLinkHover, "color", "var(--primary-font-color-hover)");

    pushStyle(&styles, &navLinkHover);
    

    Style pageHeader;
    initStyle(&pageHeader, ".page-header");

    addCSSProperty(&pageHeader, "font-family", "var(--primary-font)");
    addCSSProperty(&pageHeader, "color", "var(--primary-font-color)");

    pushStyle(&styles, &pageHeader);


    Style faStar;
    initStyle(&faStar, ".fa-star");

    addCSSProperty(&faStar, "color", "#514343");

    pushStyle(&styles, &faStar);


    Style checked;
    initStyle(&checked, ".checked");

    addCSSProperty(&checked, "color", "#dfbb62");

    pushStyle(&styles, &checked);


    Style card;
    initStyle(&card, ".card");

    addCSSProperty(&card, "text-decoration", "none");
    addCSSProperty(&card, "color", "inherit");
    addCSSProperty(&card, "transition", "opacity 200ms ease-in-out");

    pushStyle(&styles, &card);


    Style cardHover;
    initStyle(&cardHover, ".card:hover");

    addCSSProperty(&cardHover, "opacity", "0.8");

    pushStyle(&styles, &cardHover);


    Style cardBody;
    initStyle(&cardBody, ".card-body");

    addCSSProperty(&cardBody, "background-color", "var(--light-background-color)");
    addCSSProperty(&cardBody, "border-bottom", "var(--light-border)");

    pushStyle(&styles, &cardBody);


    Style cardTitle;
    initStyle(&cardTitle, ".card-title");

    addCSSProperty(&cardTitle, "color", "var(--primary-font-color)");
    addCSSProperty(&cardTitle, "font-family", "var(--primary-font)");

    pushStyle(&styles, &cardTitle);


    Style pageSection;
    initStyle(&pageSection, ".page-section");

    addCSSProperty(&pageSection, "font-family", "var(--primary-font)");
    addCSSProperty(&pageSection, "font-weight", "var(--font-weight-bold)");
    addCSSProperty(&pageSection, "color", "var(--primary-font-color)");

    pushStyle(&styles, &pageSection);


    Style ingredient;
    initStyle(&ingredient, ".ingredient");

    addCSSProperty(&ingredient, "color", "var(--secondary-font-color)");

    pushStyle(&styles, &ingredient);


    Style container;
    initStyle(&container, ".container-md");

    addCSSProperty(&container, "max-width", "1220px");

    pushStyle(&styles, &container);


    Style cardImg;
    initStyle(&cardImg, ".card-img-top");

    addCSSProperty(&cardImg, "width", "100%");
    addCSSProperty(&cardImg, "height", "15vw");
    addCSSProperty(&cardImg, "min-height", "180px");
    addCSSProperty(&cardImg, "max-height", "300px");
    addCSSProperty(&cardImg, "object-fit", "cover");

    pushStyle(&styles, &cardImg);


    Style recipeImg;
    initStyle(&recipeImg, ".recipe-img");

    addCSSProperty(&recipeImg, "max-height", "25vw");
    addCSSProperty(&recipeImg, "min-height", "240px");
    addCSSProperty(&recipeImg, "width", "100%");
    addCSSProperty(&recipeImg, "object-fit", "cover");

    pushStyle(&styles, &recipeImg);


    Style sortSelect;
    initStyle(&sortSelect, ".sort-select");

    addCSSProperty(&sortSelect, "min-width", "240px");
    addCSSProperty(&sortSelect, "color", "var(--primary-font-color)");
    addCSSProperty(&sortSelect, "font-family", "var(--secondary-font)");

    pushStyle(&styles, &sortSelect);


    Style option;
    initStyle(&option, "option");

    addCSSProperty(&option, "font-family", "inherit");
    addCSSProperty(&option, "color", "inherit");

    pushStyle(&styles, &option);

    FILE *fp;
    fp = fopen("styles.css", "w+");
    renderCSS(&styles, fp);
    fclose(fp);

    freeCSS(&styles);  
}

void insert_boilerplate(char *root_dir_path)
{
    insert_html_text("<!DOCTYPE html>");
    insert_html_tag("html", "lang=\"en\"");
    insert_html_tag("head", NULL);
    insert_html_tag_and_exit("meta", "charset=\"utf-8\"");
    insert_html_tag_and_exit("meta", "name=\"viewport\" content=\"width=device-width, initial-scale=1\"");
    insert_html_tag_and_exit("link", "href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\"");
    insert_html_tag_and_exit("link", "href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\"");

    char cssAttributes[256];
    sprintf(cssAttributes, "href=\"%s/styles.css\" rel=\"stylesheet\"", root_dir_path ? root_dir_path : ".");
    insert_html_tag_and_exit("link", cssAttributes);

    insert_html_tag_with_text("title", NULL, "Reginos Receptai");
    insert_html_tag_and_exit("script", "src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js\"");
    insert_html_tag_and_exit("link", "rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"");
    exit_html_field(1);
    insert_html_tag("body", "class=\"pb-4\"");
}

void insert_navbar(char *root_dir_path)
{
    insert_html_tag("nav", "class=\"navbar navbar-expand-lg navbar-light mb-3\"");
    insert_html_tag("div", "class=\"container-md px-3\"");

    char title_link_attributes[256];
    sprintf(title_link_attributes, "class=\"navbar-brand\" href=\"%s/index.html\"", root_dir_path ? root_dir_path : ".");
    insert_html_tag_with_text("a", title_link_attributes, "Reginos Receptai");

    insert_html_tag("button", "class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#navbarSupportedContent\" aria-controls=\"navbarSupportedContent\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"");
    insert_html_tag("span", "class=\"navbar-toggler-icon\"");
    exit_html_field(2);
    insert_html_tag("div", "class=\"collapse navbar-collapse\" id=\"navbarSupportedContent\"");
    insert_html_tag("ul", "class=\"navbar-nav ms-auto\"");

    char index_link_attributes[256];
    sprintf(index_link_attributes, "class=\"nav-link\" href=\"%s/index.html\"", root_dir_path ? root_dir_path : ".");
    insert_html_tag("li", "class=\"nav-item\"");
    insert_html_tag_with_text("a", index_link_attributes, "Receptai");
    exit_html_field(1);

    char about_link_attributes[256];
    sprintf(about_link_attributes, "class=\"nav-link\" href=\"%s/apie.html\"", root_dir_path ? root_dir_path : ".");
    insert_html_tag("li", "class=\"nav-item\"");
    insert_html_tag_with_text("a", about_link_attributes, "Apie mus");
    exit_html_field(5);
}

void generate_main_page(const int recipe_count, char **recipe_titles, int *recipe_ratings)
{
    insert_boilerplate(".");
    insert_navbar(".");
    insert_main_div_tag();
    insert_html_tag("div", "class=\"page-header d-flex flex-wrap mb-2 justify-content-between align-items-center\"");
    insert_html_tag_with_text("h2", "class=\"h5 mb-0 py-2\"", "Ką gaminam?");
    insert_html_tag("select", "class=\"form-select w-25 sort-select\" aria-label=\"Rūšiuoti receptus\"");
    insert_html_tag_with_text("option", "value=\"0\" selected", "Geriausiai įvertinti");
    insert_html_tag_with_text("option", "value=\"1\"", "Prasčiausiai įvertinti");
    insert_html_tag_with_text("option", "value=\"2\"", "Naujausi");
    insert_html_tag_with_text("option", "value=\"3\"", "Seniausi");
    exit_html_field(2);
    insert_html_tag("div", "class=\"row row-cols-1 row-cols-md-3 g-4\"");
    for(int i = 0; i < recipe_count; i++)
    {
        insert_recipe_card(recipe_titles[i], recipe_ratings[i]);
    }
    generate_html_file("index.html");
    delete_html_code();
}

char* getline(FILE *file) {
    if (file == NULL)
        return NULL;

    const unsigned short CHARS_PER_ALLOC = 32;
    char* str = malloc(CHARS_PER_ALLOC * sizeof(*str));
    if (str == NULL)
        return NULL;

    int ch;
    size_t size = 0;
    while ((ch = fgetc(file)) && ch != EOF && ch != '\n') {
        str[size] = (char)ch;
        ++size;

        if (size % CHARS_PER_ALLOC == 0) {
            str = realloc(str, (size + CHARS_PER_ALLOC) * sizeof(*str));
            if (str == NULL)
                return NULL;
        }
    }

    if (ch == EOF && size == 0) {
        free(str);
        return NULL;
    }

    str[size] = '\0';
    ++size;

    str = realloc(str, sizeof(*str) * size);
    return str;
}
