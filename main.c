/**
 * Print the contents of a source file with line numbers and
 * page headings.
 */
#include <stdio.h>
#include "lister.h"

int main (int argc, char *argv[])
{
    if (argc != 2) {
        printf ("Usage: %s file_name\n", argv[0]);
        return 1;
    }

    bool res = lister_init (argv[1]);
    if (res == false) {
        goto exit;
    }

    while (get_source_line ()) {
        (void)0;
    }

exit:
    lister_exit ();
    return res;
}
