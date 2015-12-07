#ifndef H_CALLBACK
#define H_CALLBACK


#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

GtkWidget *pImage;
GtkWidget *layout;
void cb_open (GtkWidget *);
void cb_quit (GtkWidget *);
void cb_add (GtkWidget *);
void cd_save (GtkWidget *);
GPid cb_program (gchar *, gchar *);

#endif /* not H_CALLBACK */
