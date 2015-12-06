#include <stdlib.h>
#include <gtk/gtk.h>
void cb_quit (GtkWidget *p_widget)
{
  gtk_main_quit();
  
  (void)p_widget;
}

int main ( int argc, char **argv)
{
  //instalation de gtk+
  gtk_init (&argc, &argv);

  GtkWidget *p_window;
/* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  //gtk_window_set_position(GTK_WINDOW(p_window), GTK_WIN_POS_CENTER);
  gtk_window_set_title(GTK_WINDOW(p_window),"Face Identifier Project");
  gtk_window_set_default_size(GTK_WINDOW(p_window),800,500);

  GtkWidget *p_button1= gtk_button_new_with_label("Rechercher");
  gtk_widget_set_size_request(p_button1,120,90);
  GtkWidget *p_button2= gtk_button_new_with_label("Identifier");
  gtk_widget_set_size_request(p_button2,120,90);
  GtkWidget *layout = gtk_layout_new(NULL, NULL);
  GtkWidget *image = gtk_image_new_from_file("/home/dany/Projet/Fid_Project/interface/backgroupUI.jpg");
  gtk_layout_put(GTK_LAYOUT(layout), image, 0, 0);


  gtk_container_add(GTK_CONTAINER(p_window), layout);

  gtk_layout_put (GTK_LAYOUT (layout), p_button1, 250, 405);
  gtk_layout_put (GTK_LAYOUT (layout), p_button2, 100, 405);

  g_signal_connect(G_OBJECT(p_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;

}
