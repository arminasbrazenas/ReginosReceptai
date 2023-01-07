#include <stdio.h>
#include "html-generator.h"
#include <sys/stat.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    // Auto-incrementing from 1.
    unsigned id;

    // Recipes title. E.g. "Baton"
    char *title;

    // Recipes rating, max 5.
    unsigned rating;

    // Img file name in assets folder. E.g. "recipe_1_img.jpg"
    char *img;

    // Recipe description.
    char *description;

    // Recipe ingredients.
    char **ingredients;
} Recipe;

void insert_html_tag_and_exit(char *tag, char *attributes);
void insert_html_tag_with_text(char *tag, char *attributes, char *text);
void insert_boilerplate(char *cssPath);
void insert_navbar();
void insert_main_content();
void generate_css();
void generate_main_page();
void insert_recipe_card(const char *title, int rating/*, const char *image_address*/);

void insert_main_content()
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

void insert_recipe_header(char *title, unsigned rating)
{
    insert_html_tag("div", "class=\"page-header d-flex flex-column flex-wrap mb-3\"");
    insert_html_tag_with_text("h2", "class=\"h2 mb-0 py-1\"", title);
    insert_html_tag("div", NULL);
    insert_rating(rating);
    exit_html_field(1);
}

void insert_recipe(char *title, unsigned rating)
{
    insert_boilerplate("../styles.css");
    insert_navbar();

    insert_main_content();
    insert_recipe_header(title, rating);
}

void generate_recipes()
{
    mkdir("receptai");

    insert_recipe("Test", 4);
    generate_html_file("receptai/1.html");
    delete_html_code();
}

int main() {
    generate_css();
    generate_main_page();
    generate_recipes();

    return 0;
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
    insert_html_text(
            "@import url(\"https://fonts.googleapis.com/css2?family=Merriweather:ital,wght@0,400;0,700;1,400;1,700&family=Open+Sans&display=swap\");"
            ":root {"
                "--primary-font: \"Merriweather\", serif;"
                "--secondary-font: \"Open Sans\", sans-serif;"
                "--primary-font-color: #514343;"
                "--primary-font-color-hover: #a19a98;"
                "--secondary-font-color: #3b2222;"
                "--primary-background-color: #ede9e4;"
                "--light-background-color: #f8f5f1;"
                "--light-border: 1px solid #ebe1d6;"
                "--font-weight-bold: 700;"
            "}"
            "body {"
                "font-family: var(--secondary-font);"
                "color: var(--secondary-font-color);"
            "}"
            ".navbar {"
                "background-color: var(--primary-background-color);"
                "color: var(--primary-font-color);"
            "}"
            ".navbar-brand {"
                "font-family: var(--primary-font);"
                "color: inherit;"
                "transition: color 200ms ease-in-out;"
            "}"
            ".nav-link {"
                "text-transform: uppercase;"
                "color: inherit;"
            "}"
            ".nav-link:hover, .navbar-brand:hover {"
                "color: var(--primary-font-color-hover);"
            "}"
            ".page-header {"
                "font-family: var(--primary-font);"
                "color: var(--primary-font-color);"
            "}"
            ".fa-star {"
                "color: #514343;"
            "}"
            ".checked {"
                "color: #dfbb62;"
            "}"
            ".card {"
                "text-decoration: none;"
                "color: inherit;"
                "transition: opacity 200ms ease-in-out;"
            "}"
            ".card:hover {"
                "opacity: 0.8;"
            "}"
            ".card-body {"
                "background-color: var(--light-background-color);"
                "border-bottom: var(--light-border);"
            "}"
            ".card-title {"
                "color: var(--primary-font-color);"
                "font-family: var(--primary-font);"
            "}"
            ".page-section {"
                "font-family: var(--primary-font);"
                "font-weight: var(--font-weight-bold);"
                "color: var(--primary-font-color);"
            "}"
            ".ingredient {"
                "color: var(--secondary-font-color);"
            "}"
            ".container-md {"
                "max-width: 1220px;"
            "}"
            ".card-img-top {"
                "width: 100%;"
                "height: 15vw;"
                "min-height: 180px;"
                "max-height: 300px;"
                "object-fit: cover;"
            "}"
            ".recipe-img {"
                "max-height: 25vw;"
                "min-height: 240px;"
                "width: 100%;"
                "object-fit: cover;"
            "}"
            ".sort-select {"
                "min-width: 240px;"
                "color: var(--primary-font-color);"
                "font-family: var(--secondary-font);"
            "}"
            "option {"
                "font-family: inherit;"
                "color: inherit;"
            "}"
    );
    generate_html_file("styles.css");
    delete_html_code();
}

void insert_boilerplate(char *cssPath)
{
    insert_html_text("<!DOCTYPE html>");
    insert_html_tag("html", "lang=\"en\"");
    insert_html_tag("head", NULL);
    insert_html_tag_and_exit("meta", "charset=\"utf-8\"");
    insert_html_tag_and_exit("meta", "name=\"viewport\" content=\"width=device-width, initial-scale=1\"");
    insert_html_tag_and_exit("link", "href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\"");
    insert_html_tag_and_exit("link", "href=\"https://getbootstrap.com/docs/5.2/assets/css/docs.css\" rel=\"stylesheet\"");

    char cssAttributes[256];
    sprintf(cssAttributes, "href=\"%s\" rel=\"stylesheet\"", cssPath ? cssPath : "styles.css");
    insert_html_tag_and_exit("link", cssAttributes);

    insert_html_tag_with_text("title", NULL, "Reginos Receptai");
    insert_html_tag_and_exit("script", "src=\"https://cdn.jsdelivr.net/npm/bootstrap@5.2.2/dist/js/bootstrap.bundle.min.js\"");
    insert_html_tag_and_exit("link", "rel=\"stylesheet\" href=\"https://cdnjs.cloudflare.com/ajax/libs/font-awesome/4.7.0/css/font-awesome.min.css\"");
    exit_html_field(1);
    insert_html_tag("body", "class=\"pb-4\"");
}

void insert_navbar()
{
    insert_html_tag("nav", "class=\"navbar navbar-expand-lg navbar-light mb-3\"");
    insert_html_tag("div", "class=\"container-md px-3\"");
    insert_html_tag_with_text("a", "class=\"navbar-brand\" href=\"./index.html\"", "Reginos Receptai");
    insert_html_tag("button", "class=\"navbar-toggler\" type=\"button\" data-bs-toggle=\"collapse\" data-bs-target=\"#navbarSupportedContent\" aria-controls=\"navbarSupportedContent\" aria-expanded=\"false\" aria-label=\"Toggle navigation\"");
    insert_html_tag("span", "class=\"navbar-toggler-icon\"");
    exit_html_field(2);
    insert_html_tag("div", "class=\"collapse navbar-collapse\" id=\"navbarSupportedContent\"");
    insert_html_tag("ul", "class=\"navbar-nav ms-auto\"");

    // TODO: Fix linking from different directories
    insert_html_tag("li", "class=\"nav-item\"");
    insert_html_tag_with_text("a", "class=\"nav-link\" href=\"./index.html\"", "Receptai");
    exit_html_field(1);
    insert_html_tag("li", "class=\"nav-item\"");
    insert_html_tag_with_text("a", "class=\"nav-link\" href=\"./apie.html\"", "Apie mus");
    exit_html_field(5);
}

void generate_main_page()
{
    insert_boilerplate(NULL);
    insert_navbar();
    insert_main_content();
    insert_html_tag("div", "class=\"page-header d-flex flex-wrap mb-2 justify-content-between align-items-center\"");
    insert_html_tag_with_text("h2", "class=\"h5 mb-0 py-2\"", "Ką gaminam?");
    insert_html_tag("select", "class=\"form-select w-25 sort-select\" aria-label=\"Rūšiuoti receptus\"");
    insert_html_tag_with_text("option", "value=\"0\" selected", "Geriausiai įvertinti");
    insert_html_tag_with_text("option", "value=\"1\"", "Prasčiausiai įvertinti");
    insert_html_tag_with_text("option", "value=\"2\"", "Naujausi");
    insert_html_tag_with_text("option", "value=\"3\"", "Seniausi");
    exit_html_field(2);
    insert_html_tag("div", "class=\"row row-cols-1 row-cols-md-3 g-4\"");
    insert_recipe_card("Ryžiadešriai", 4);
    insert_recipe_card("Pieniška agurkų sriuba", 3);
    insert_recipe_card("Česnako skiltelės su klevų sirupu", 2);
    insert_recipe_card("Bananais įdaryta vištiena", 3);
    insert_recipe_card("Lašišos kaulų sriuba iš vietinės aludės", 3);
    insert_recipe_card("Pica su kumpiu ir sūriu iš maximos", 3);
    insert_recipe_card("Proteino bomba", 5);
    generate_html_file("index.html");
    delete_html_code();
}