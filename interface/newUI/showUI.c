#include <stdlib.h>
#include <gtk/gtk.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

char* concat(char *s1, char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

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
  ////////////////////////////////////////////////////////////////////////

  GtkWidget *p_button1= gtk_button_new_with_label("Rechercher");
  gtk_widget_set_size_request(p_button1,120,90);
  GtkWidget *p_button2= gtk_button_new_with_label("Identifier");
  gtk_widget_set_size_request(p_button2,120,90);

  GtkWidget *layout = gtk_layout_new(NULL, NULL);
  GtkWidget *backgrd = gtk_image_new_from_file("backgroundUI.jpg");
  GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
  GtkWidget *scrollbar = gtk_scrolled_window_new(NULL, NULL);
  
  DIR* FD = opendir ("./DataBase");
  struct dirent* in_file;

  GtkWidget *ImgScr;
  GdkPixbuf *Pbx;

  //if (NULL != FD) 
  //{
      while ((in_file =readdir(FD)))
	{

	  Pbx = gdk_pixbuf_new_from_file_at_scale (concat("/DataBase/",in_file->d_name),220,150,TRUE,NULL);
	  ImgScr = gtk_image_new_from_pixbuf(Pbx);

	  g_object_unref (Pbx);
	  gtk_box_pack_start(GTK_BOX(box), ImgScr, FALSE, FALSE, 3);
	}
      (void) closedir (FD);
      //}
  /*
  GdkPixbuf *Pbx1 = gdk_pixbuf_new_from_file_at_scale ("1.jpg",220,150,TRUE,NULL);
  GtkWidget *ImgScr1 = gtk_image_new_from_pixbuf(Pbx1);
  g_object_unref (Pbx1);
  GdkPixbuf *Pbx2 = gdk_pixbuf_new_from_file_at_scale ("2.jpg",220,150,TRUE,NULL);
  GtkWidget *ImgScr2 = gtk_image_new_from_pixbuf(Pbx2);
  g_object_unref (Pbx2);
  GdkPixbuf *Pbx3 = gdk_pixbuf_new_from_file_at_scale ("3.jpg",220,150,TRUE,NULL);
  GtkWidget *ImgScr3 = gtk_image_new_from_pixbuf(Pbx3);
  g_object_unref (Pbx3);
  GdkPixbuf *Pbx4 = gdk_pixbuf_new_from_file_at_scale ("4.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr4 = gtk_image_new_from_pixbuf(Pbx4);
  g_object_unref (Pbx4);
  GdkPixbuf *Pbx5 = gdk_pixbuf_new_from_file_at_scale ("5.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr5 = gtk_image_new_from_pixbuf(Pbx5);
  g_object_unref (Pbx5);
  GdkPixbuf *Pbx6 = gdk_pixbuf_new_from_file_at_scale ("6.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr6 = gtk_image_new_from_pixbuf(Pbx6);
  g_object_unref (Pbx6);
  GdkPixbuf *Pbx7 = gdk_pixbuf_new_from_file_at_scale ("7.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr7 = gtk_image_new_from_pixbuf(Pbx7);
  g_object_unref (Pbx7);
  GdkPixbuf *Pbx8 = gdk_pixbuf_new_from_file_at_scale ("8.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr8 = gtk_image_new_from_pixbuf(Pbx8);
  g_object_unref (Pbx8);
  GdkPixbuf *Pbx9 = gdk_pixbuf_new_from_file_at_scale ("9.jpg",220,100,TRUE,NULL);
  GtkWidget *ImgScr9 = gtk_image_new_from_pixbuf(Pbx9);
  g_object_unref (Pbx9);*/
  GdkPixbuf *PbxFcd = gdk_pixbuf_new_from_file_at_scale ("violajones.png",500,330,TRUE,NULL);
  GtkWidget *ImgF = gtk_image_new_from_pixbuf(PbxFcd);
  g_object_unref (PbxFcd);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

  gtk_widget_set_size_request(scrollbar, 253,398);
  gtk_container_add(GTK_CONTAINER(scrollbar), box);
  //
  /*gtk_box_pack_start(GTK_BOX(box), ImgScr1, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr2, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr3, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr4, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr5, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr6, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr7, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr8, FALSE, FALSE, 3);
  gtk_box_pack_start(GTK_BOX(box), ImgScr9, FALSE, FALSE, 3);*/
  
  gtk_layout_put(GTK_LAYOUT(layout), backgrd, 0, 0);

  gtk_container_add(GTK_CONTAINER(p_window), layout);
  gtk_layout_put(GTK_LAYOUT (layout), scrollbar, 548,0);
  gtk_layout_put (GTK_LAYOUT (layout), ImgF, 20, 25);

  gtk_layout_put (GTK_LAYOUT (layout), p_button1, 250, 405);
  gtk_layout_put (GTK_LAYOUT (layout), p_button2, 100, 405);


  ////////////////////////////////////////////////////////
  g_signal_connect(G_OBJECT(p_window), "destroy",
        G_CALLBACK(gtk_main_quit), NULL);
  /* Affichage de la fenetre principale */
  gtk_widget_show_all (p_window); 
  /* Lancement de la boucle principale */
  gtk_main ();
  return EXIT_SUCCESS;

}
