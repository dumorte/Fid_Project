#include "callback.h"

void cb_open (GtkWidget *p_widget)
{
  GtkWidget *p_dialog = NULL;
  p_dialog = gtk_file_chooser_dialog_new ("Image selection", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    gchar *file_name;
    GtkWidget *pVBox;
    GtkWidget *pImage;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), pVBox);

    pImage = gtk_image_new_from_file(file_name);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 5);
   
    gtk_widget_show_all (window);
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


