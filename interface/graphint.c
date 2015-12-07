#include "callback.h"
char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


int main (int argc, char **argv)
{
  GtkWidget *p_window;
  GtkWidget *p_button[3];
  GdkPixbuf *pixbuf;
  GtkWidget *image;
  GtkWidget *scrollbar;
  GtkWidget *box;
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
  
  box = gtk_vbox_new(GTK_ORIENTATION_VERTICAL, 5);
  scrollbar = gtk_scrolled_window_new(NULL,NULL);
  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW(scrollbar),GTK_POLICY_AUTOMATIC,GTK_POLICY_ALWAYS);    
  
  DIR* FD = opendir ("./Database");
  struct dirent* in_file;

  GtkWidget *ImgScr;
  GdkPixbuf *Pbx;

  while ((in_file =readdir(FD)))
  {
    Pbx = gdk_pixbuf_new_from_file_at_scale (concat("/Database/",in_file->d_name),220,150,TRUE,NULL);    ImgScr = gtk_image_new_from_pixbuf(Pbx);

    g_object_unref (Pbx);
    gtk_box_pack_start(GTK_BOX(box), ImgScr, FALSE, FALSE, 3);
  }
  (void) closedir (FD);
   
  /*Creation des boutons*/
  p_button[0] = gtk_button_new_from_stock (GTK_STOCK_QUIT);
  p_button[1] = gtk_button_new_from_stock (GTK_STOCK_OPEN);
  p_button[2] = gtk_button_new_with_label ("Identify");
  p_button[3] = gtk_button_new_from_stock (GTK_STOCK_ADD);

  gtk_widget_set_size_request(p_button[0],120,90);
  gtk_widget_set_size_request(p_button[1],120,90);
  gtk_widget_set_size_request(p_button[2],120,90);
  gtk_widget_set_size_request(p_button[3],120,90);
  gtk_widget_set_size_request(scrollbar,253,398);
  
  /*Insertion des boutons*/
  g_signal_connect (G_OBJECT (p_button[0]), "clicked", G_CALLBACK (cb_quit), NULL);
  g_signal_connect (G_OBJECT (p_button[1]), "clicked", G_CALLBACK (cb_open), NULL);
  g_signal_connect (G_OBJECT (p_button[2]), "clicked", G_CALLBACK (cb_program), NULL);
  g_signal_connect (G_OBJECT (p_button[3]), "clicked", G_CALLBACK (cb_add), NULL);

  layout = gtk_layout_new(NULL,NULL);
  image = gtk_image_new_from_file("ressources/backgroundUI.jpg");
  gtk_layout_put(GTK_LAYOUT(layout), image,0,0);

  gtk_container_add(GTK_CONTAINER(p_window), layout);
  gtk_container_add(GTK_CONTAINER(scrollbar), box);
 
  gtk_layout_put(GTK_LAYOUT(layout), p_button[0],600,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[1],50,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[2],200,405);
  gtk_layout_put(GTK_LAYOUT(layout), p_button[3],350,405);
  gtk_layout_put(GTK_LAYOUT(layout), scrollbar,548,0);

  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window);
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;
}
