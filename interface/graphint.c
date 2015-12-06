#include "callback.h"

int main (int argc, char **argv)
{
  GtkWidget *p_window;
  GtkWidget *p_button[3];
  GdkPixbuf *pixbuf;
  GtkWidget *layout;
  GtkWidget *image;
  GtkWidget *pImage;
  GtkWidget *p_dialog;
  gchar *file_name;
  GError *error = NULL;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);  

  pixbuf = gdk_pixbuf_new_from_file ("ressources/logo.jpeg", &error);
  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(p_window),"Face Identifier");
  gtk_window_set_icon(GTK_WINDOW(p_window), pixbuf);

  gtk_window_set_default_size(GTK_WINDOW(p_window),800,500);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);
     
  /*Creation des boutons*/
  p_button[0] = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  p_button[1] = gtk_button_new_from_stock (GTK_STOCK_OPEN);
  p_button[2] = gtk_button_new_with_label ("Identify");
  p_button[3] = gtk_button_new_from_stock (GTK_STOCK_ADD);

  gtk_widget_set_size_request(p_button[0],120,90);
  gtk_widget_set_size_request(p_button[1],120,90);
  gtk_widget_set_size_request(p_button[2],120,90);
  gtk_widget_set_size_request(p_button[3],120,90);

  /*Insertion des boutons*/
  g_signal_connect (G_OBJECT (p_button[0]), "clicked", G_CALLBACK (cb_quit), NULL);
  g_signal_connect (G_OBJECT (p_button[1]), "clicked", G_CALLBACK (cb_open), NULL);
  g_signal_connect (G_OBJECT (p_button[2]), "clicked", G_CALLBACK (cb_program), NULL);
  g_signal_connect (G_OBJECT (p_button[3]), "clicked", G_CALLBACK (cb_add), NULL);

  layout = gtk_layout_new(NULL,NULL);
  image = gtk_image_new_from_file("ressources/backgroundUI.jpg");
  gtk_layout_put(GTK_LAYOUT(layout), image,0,0);

  gtk_container_add(GTK_CONTAINER(p_window), layout);
  
  gtk_layout_put(GTK_LAYOUT(layout), p_button[0],600,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[1],50,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[2],200,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[3],350,405);


  p_dialog = gtk_file_chooser_dialog_new ("Image selection", NULL,
                                          GTK_FILE_CHOOSER_ACTION_OPEN,
                                          GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL,
                                          GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT,
                                          NULL);
  gtk_window_set_icon(GTK_WINDOW(p_dialog), pixbuf);

  if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
  {
    file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
    pImage = gtk_image_new_from_file(file_name);
    gtk_layout_put(GTK_LAYOUT(layout), pImage,200,50);  

   g_free(file_name), file_name=NULL; 
   gtk_widget_destroy (p_dialog);
 }
 
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
