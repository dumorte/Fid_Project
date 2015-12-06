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
  GtkWidget *backgrd = gtk_image_new_from_file("backgroundUI.jpg");
  GtkWidget *ImgF = gtk_image_new_from_file("imgfocused.jpg");
  GtkWidget *ImgScr = gtk_image_new_from_file("violajones.png");

  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  //GtkWidget *text_view = gtk_text_view_new();   
  //GtkWidget *scrollbar = gtk_scrolled_window_new(NULL, NULL);
  //gtk_widget_set_size_request(scrollbar, 160,300);
  //gtk_container_set_border_width (GTK_CONTAINER 
  //GtkWidget *label1 = gtk_label_new("okok");
  //GtkWidget *label2 = gtk_label_new("ouaiuai");

  //gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_layout_put(GTK_LAYOUT (layout), box, 700,30);

  //gtk_container_add(GTK_CONTAINER(scrollbar), ImgScr);
  //
  //gtk_container_add(GTK_CONTAINER(box), scrollbar);
  //gtk_box_pack_start(GTK_BOX(box), label1, FALSE, FALSE, 5);
  gtk_box_pack_start(GTK_BOX(box), ImgScr, FALSE, FALSE, 5);

  //

  //gtk_container_add(GTK_CONTAINER(scrollbar), box);

  //int i;
  /*for(i = 1 ; i <= 10 ; ++i)
    {
      GtkWidget *label;
      char texte[10];
         
      sprintf(texte, "Label %d", i);
         
      label = gtk_label_new(texte);
         
      gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);
    }*/

  //gtk_box_pack_start(GTK_BOX(box), label1, FALSE, FALSE, 0);
  //gtk_box_pack_start(GTK_BOX(box), label2, FALSE, FALSE, 0);




  gtk_layout_put(GTK_LAYOUT(layout), backgrd, 0, 0);

  gtk_container_add(GTK_CONTAINER(p_window), layout);
  gtk_layout_put (GTK_LAYOUT (layout), ImgF, 20, 25);

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
