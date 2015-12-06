#include "callback.h"

int main (int argc, char **argv)
{
  GtkWidget *p_window;
  GtkWidget *p_button[1];
  //GtkWidget *pTable;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);  

  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(p_window),"Face Identifier");
  //gtk_window_maximize(GTK_WINDOW(p_window));
  gtk_window_set_default_size(GTK_WINDOW(p_window),800,500);
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);
  
  /*Creation et insertion de la table 1 ligne 2 colonnes*/
  //pTable=gtk_table_new(1,2,TRUE);
  //gtk_container_add(GTK_CONTAINER(p_window), GTK_WIDGET(pTable));
  
  /*Creation des boutons*/
  p_button[0] = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  p_button[1] = gtk_button_new_from_stock (GTK_STOCK_OPEN);

  gtk_widget_set_size_request(p_button[0],120,90);
  gtk_widget_set_size_request(p_button[1],120,90);

  /*Insertion des boutons*/
  //gtk_table_attach(GTK_TABLE(pTable), p_button[0], 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
  g_signal_connect (G_OBJECT (p_button[0]), "clicked", G_CALLBACK (cb_quit), NULL);
  //gtk_table_attach(GTK_TABLE(pTable), p_button[1], 1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND, 0, 0);
  g_signal_connect (G_OBJECT (p_button[1]), "clicked", G_CALLBACK (cb_open), NULL);

  GtkWidget *layout = gtk_layout_new(NULL,NULL);
  GtkWidget *image = gtk_image_new_from_file("backgroundUI.jpg");
  gtk_layout_put(GTK_LAYOUT(layout), image,0,0);

  gtk_container_add(GTK_CONTAINER(p_window), layout);
  
  gtk_layout_put(GTK_LAYOUT(layout), p_button[0],250,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[1],50,405);
  
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
