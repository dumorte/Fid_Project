#include "callback.h"

//static void open_file(char *file_name);

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
    GtkWidget *image;
    GtkWidget *event_box;

    event_box = gtk_event_box_new();

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    image = gtk_image_new_from_file(file_name);
    
    gtk_container_add (GTK_CONTAINER (event_box), image);

    g_signal_connect (G_OBJECT (event_box),
		      "button_press_event",
                      G_CALLBACK (cb_open),
		      image);
    
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
