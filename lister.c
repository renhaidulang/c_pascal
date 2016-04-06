#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lister.h"

static char *source_file_name = NULL;
static char *date_str = NULL;

static FILE *source_file = NULL;

extern bool lister_init (char *name)
{
    source_file_name = (char *)malloc (strlen (name) + 1);
    if (source_file_name == NULL) {
        return false;
    }
    strcpy (source_file_name, name);
    source_file = fopen(source_file_name, "r");
    if (source_file == NULL) {
        return false;
    }

    time_t timer;
    time (&timer);
    char *date = asctime( localtime (&timer));
    date_str = (char *)malloc (strlen (date) + 1);
    if (date_str == NULL) {
        return false;
    }
    strcpy (date_str, date);

    return true;
}

extern void lister_exit (void)
{
    if (source_file != NULL) {
        fclose (source_file);
    }

    if (source_file_name != NULL) {
        free (source_file_name);
    }

    if (date_str != NULL) {
        free (date_str);
    }
}

static void print_page_header (void)
{
    static int cur_page_num = 0;

    putchar ('\f');
    printf ("Page %d %s %s\n\n", ++cur_page_num, source_file_name, date_str);
}

static void print_line (char *line)
{
    const int max_lines_per_page = 50;
    static int line_cnt = 50;

    if (++line_cnt > max_lines_per_page) {
        print_page_header ();
        line_cnt = 1;
    }

    printf ("%s", line);
}

static void get_line_rest (void)
{
    const int read_line_len = 5;
    char source_buf[read_line_len];

    if ((fgets (source_buf, read_line_len, source_file)) == NULL) {
        return ;
    }

    print_line (source_buf);

    if (strlen (source_buf) == read_line_len-1 &&
            source_buf[read_line_len-2] != '\n') {
        get_line_rest ();
    }
}

extern bool get_source_line (void)
{
    const int read_line_len = 5;
    static int cur_line_num = 0;

    char source_buf[read_line_len];
    char print_buf[read_line_len + 7];

    if ((fgets (source_buf, read_line_len, source_file)) == NULL) {
        return false;
    }

    cur_line_num++;
    sprintf (print_buf, "%4d: %s", cur_line_num, source_buf);
    print_line (print_buf);

    if (strlen (source_buf) == read_line_len-1 &&
            source_buf[read_line_len-2] != '\n') {
        get_line_rest ();
    }

    return true;
}
