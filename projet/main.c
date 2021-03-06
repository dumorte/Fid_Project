#include <err.h>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "eigenface.h"
#include "pixel_operations.h"
#include "integral_image.h"
#include "haar_feature.h"
#include "classifier.h"
#include "constantes.h"
#include "feature_scaling.h"
#include "adaboost.h"
#include "matrix.h"
#include "color.h"

#include <gtk/gtk.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "callback.h"


void wait_for_keypressed(void);
void init_sdl(void);
SDL_Surface *display_image(SDL_Surface *img);
char *concat(char *s1, char *s2);
char *remove_after_dot(char *s);

int main(int argc, char **argv){
	gtk_init (&argc, &argv);

	GtkWidget *p_window;
	GdkPixbuf *Pixbuf; 
	GError *error=NULL;

	/* Creation de la fenetre principale de notre application */
	p_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
	gtk_window_set_position(GTK_WINDOW(p_window), GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(p_window),"Face Identifier Project");
	gtk_window_set_default_size(GTK_WINDOW(p_window),800,500);
	Pixbuf = gdk_pixbuf_new_from_file("logo.jpeg",&error);
	gtk_window_set_icon(GTK_WINDOW(p_window),Pixbuf);
	GdkGeometry hints;
	hints.min_width = 800;
	hints.max_width = 800;
	hints.min_height = 500;
	hints.max_height = 500;

	gtk_window_set_geometry_hints(
			GTK_WINDOW(p_window),
			p_window,
			&hints,
			(GdkWindowHints)(GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE));

	/* Creation des buttons */
	GtkWidget *p_button1= gtk_button_new_with_label("Search");
	gtk_widget_set_size_request(p_button1,120,90);
	GtkWidget *p_button2= gtk_button_new_with_label("Identify");
	gtk_widget_set_size_request(p_button2,120,90);
	GtkWidget *p_button3= gtk_button_new_with_label("Add");
	gtk_widget_set_size_request(p_button3,120,90);

	/* Insertion des boutons */
	g_signal_connect (G_OBJECT (p_button1), "clicked", G_CALLBACK (cb_open), NULL);
	g_signal_connect (G_OBJECT (p_button2), "clicked", G_CALLBACK (face_detection), NULL);
	g_signal_connect (G_OBJECT (p_button3), "clicked", G_CALLBACK (cb_add), NULL);

	layout = gtk_layout_new(NULL, NULL);
	GtkWidget *backgrd = gtk_image_new_from_file("backgroundUI.jpg");
	GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
	GtkWidget *scrollbar = gtk_scrolled_window_new(NULL, NULL);
	
	DIR* FD = opendir ("./DataBase");
	struct dirent* in_file;

	GtkWidget *ImgScr;
	GdkPixbuf *Pbx;
	GtkWidget *Label;

	if (NULL != FD) 
	{
		while ((in_file =readdir(FD)))
		{
			if (!strcmp (in_file->d_name, "."))
				continue;
			if (!strcmp (in_file->d_name, ".."))    
				continue;

			Pbx = gdk_pixbuf_new_from_file_at_scale (concat("DataBase/",in_file->d_name),220,150,TRUE,NULL);
			ImgScr = gtk_image_new_from_pixbuf(Pbx);

			Label = gtk_label_new (remove_after_dot(in_file->d_name));
			g_object_unref (Pbx);
			gtk_box_pack_start(GTK_BOX(box), ImgScr, FALSE, FALSE, 3);
			gtk_box_pack_start(GTK_BOX(box), Label, FALSE, FALSE, 3);
		}
		(void) closedir (FD);
	}

	gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrollbar),GTK_POLICY_AUTOMATIC, GTK_POLICY_ALWAYS);

	gtk_widget_set_size_request(scrollbar, 253,398);
	gtk_container_add(GTK_CONTAINER(scrollbar), box);

	gtk_layout_put(GTK_LAYOUT(layout), backgrd, 0, 0);

	gtk_container_add(GTK_CONTAINER(p_window), layout);
	gtk_layout_put(GTK_LAYOUT (layout), scrollbar, 548,0);

	gtk_layout_put (GTK_LAYOUT (layout), p_button1, 250, 405);
	gtk_layout_put (GTK_LAYOUT (layout), p_button2, 100, 405);
	gtk_layout_put (GTK_LAYOUT (layout), p_button3, 400, 405);

	g_signal_connect(G_OBJECT(p_window), "destroy",
			G_CALLBACK(gtk_main_quit), NULL);
	/* Affichage de la fenetre principale */
	gtk_widget_show_all (p_window); 
	/* Lancement de la boucle principale */
	gtk_main ();
	return EXIT_SUCCESS;

	return 0;
}

char* concat(char *s1, char *s2)
{
	char *result = malloc(strlen(s1)+strlen(s2)+1);
	strcpy(result, s1);
	strcat(result, s2);
	return result;
}

char* remove_after_dot(char *s)
{
	char *c = s;
	while(*c !='.')
	{
		c++;
	}
	*c = '\0';
	return s;
}
