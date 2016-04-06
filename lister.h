#ifndef _LISTER_H_
#define _LISTER_H_

#include <stdbool.h>

extern bool lister_init (char *name);
extern void lister_exit (void);
extern bool get_source_line (void);

#endif
