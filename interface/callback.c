#include "callback.h"

void cb_open (GtkWidget *p_widget)
{
  GtkWidget *p_dialog = NULL;
  p_dialog = gtk_file_chooser_dialog_new ("Ajout dans la base de donnee", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name;
 
    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    GtkWidget *view = gtk_image_view_new ();
    GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file (file_name, NULL);
    gtk_image_view_set_pixbuf (GTK_IMAGE_VIEW (view), pixbuf, TRUE);
    gtk_container_add (GTK_CONTAINER (window), view);
    gtk_widget_show_all(window);
 
    g_free (file_name), file_name = NULL;
  }
  gtk_widget_destroy (p_dialog);
	
  (void)p_widget;
}

void cb_quit (GtkWidget *p_widget)
{
  gtk_main_quit();
  
  (void)p_widget;
}


