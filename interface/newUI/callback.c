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
    GtkWidget *pAdd;

    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    
    GtkWidget *window = gtk_window_new (GTK_WINDOW_TOPLEVEL); 
    gtk_window_set_default_size(GTK_WINDOW(window),500,500);
    
    pVBox = gtk_vbox_new(FALSE, 0);
    gtk_container_add(GTK_CONTAINER(window), pVBox);

    pImage = gtk_image_new_from_file(file_name);
    gtk_box_pack_start(GTK_BOX(pVBox), pImage, FALSE, FALSE, 5);
   
    pAdd = gtk_button_new_from_stock (GTK_STOCK_ADD);
    gtk_box_pack_start(GTK_BOX(pVBox), pAdd, TRUE, FALSE, 5);
    g_signal_connect(G_OBJECT(pAdd), "clicked", G_CALLBACK(cb_add), NULL);

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

void cb_add (GtkWidget *p_widget){
  
    GtkWidget *pWindow;
    GtkWidget *pVBox;
    GtkWidget *pFrame;
    GtkWidget *pVBoxFrame;
    GtkWidget *pEntry;
    GtkWidget *pLabel;
    //GtkWidget *pSave;
    gchar *sUtf8;
 
    pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
   
    /* On ajoute un espace de 5 sur les bords de la fenetre */
    gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
    gtk_window_set_title(GTK_WINDOW(pWindow), "Identity");
    gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
    g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(cb_quit), NULL);
 
    pVBox = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pWindow), pVBox);
 
    /* Creation du premier GtkFrame */
    pFrame = gtk_frame_new("Name");
    gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);
 
    /* Creation et insertion d une boite pour le premier GtkFrame */
    pVBoxFrame = gtk_vbox_new(TRUE, 0);
    gtk_container_add(GTK_CONTAINER(pFrame), pVBoxFrame);
 
    /* Creation et insertion des elements contenus dans le premier GtkFrame */
    sUtf8 = g_locale_to_utf8("First name :", -1, NULL, NULL, NULL);
    pLabel = gtk_label_new(sUtf8);
    g_free(sUtf8);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
 
    pLabel = gtk_label_new("Last name :");
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pLabel, TRUE, FALSE, 0);
    pEntry = gtk_entry_new();
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pEntry, TRUE, FALSE, 0);
    
    /*pSave = gtk_button_new_from_stock (GTK_STOCK_SAVE);
    gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSave, TRUE, FALSE, 0);
    g_signal_connect(G_OBJECT(pSave), "clicked", G_CALLBACK(cb_save), NULL);
   */
    gtk_widget_show_all(pWindow);
 
    gtk_main();

  (void)p_widget;
}

void cd_save (GtkWidget *p_widget)
{
  
  (void)p_widget;
}
