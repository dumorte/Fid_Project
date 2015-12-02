#include <stdlib.h>
#include <gtk/gtk.h>
#include "callback.h"

int main (int argc, char **argv)
{
  GtkWidget *p_window;
  GtkWidget *p_button[2];
  GtkWidget *pTable;
  //GtkWidget *p_dialog;

  /* Initialisation de GTK+ */
  gtk_init (&argc, &argv);  

  //p_dialog = gtk_file_chooser_dialog_new ("Ajout dans la base de donnee", NULL, GTK_FILE_CHOOSER_ACTION_OPEN,
  //		  GTK_STOCK_CANCEL, GTK_RESPONSE_CANCEL, GTK_STOCK_OPEN, GTK_RESPONSE_ACCEPT, NULL);
  /* Creation de la fenetre principale de notre application */
  p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(p_window),"Ajout dans la base de donnee");
  g_signal_connect (G_OBJECT (p_window), "destroy", G_CALLBACK (cb_quit), NULL);

  /*Creation et insertion de la table 1 ligne 2 colonnes*/
  pTable=gtk_table_new(1,2,TRUE);
  gtk_container_add(GTK_CONTAINER(p_window), GTK_WIDGET(pTable));
  
  /*Creation des boutons*/
  //p_button[0] = gtk_button_new_from_stock (GTK_STOCK_ADD);
  //p_button[1] = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  p_button[2] = gtk_button_new_from_stock (GTK_STOCK_OPEN);

  /*Insertion des boutons*/
  //gtk_table_attach(GTK_TABLE(pTable), p_button[0], 0, 1, 0, 1, GTK_EXPAND, GTK_EXPAND | GTK_FILL, 0, 0);
  //gtk_table_attach(GTK_TABLE(pTable), p_button[1], 1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND | GTK_FILL, 0, 0);
  //g_signal_connect (G_OBJECT (p_button[1]), "clicked", G_CALLBACK (cb_quit), NULL);
  gtk_table_attach(GTK_TABLE(pTable), p_button[2], 1, 2, 0, 1, GTK_EXPAND, GTK_EXPAND | GTK_FILL, 0, 0);
  g_signal_connect (G_OBJECT (p_button[2]), "clicked", G_CALLBACK (cb_open), NULL);
  
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}