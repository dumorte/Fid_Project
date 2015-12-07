#ifndef H_CALLBACK
#define H_CALLBACK

#include <stdlib.h>
#include <gtk/gtk.h>

char *file_name;
GtkWidget *pImage;
GtkWidget *layout;
void cb_open (GtkWidget *);
void cb_quit (GtkWidget *);
void cb_add (GtkWidget *);
GPid cb_program (gchar *, gchar *);
void save(GtkWidget *widget, GtkEntry *entry);
#endif
