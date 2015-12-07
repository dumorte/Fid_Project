#include "callback.h"

void cb_open (GtkWidget *p_widget)
{
	GtkWidget *p_dialog;
	gchar *file_name;

	p_dialog = gtk_file_chooser_dialog_new ("Image selection", NULL,
			GTK_FILE_CHOOSER_ACTION_OPEN,
			("_Cancel"), GTK_RESPONSE_CANCEL,
			("_Open"), GTK_RESPONSE_ACCEPT,
			NULL);
	if (gtk_dialog_run (GTK_DIALOG (p_dialog)) == GTK_RESPONSE_ACCEPT)
	{

		file_name = gtk_file_chooser_get_filename (GTK_FILE_CHOOSER (p_dialog));
		if(pImage)
			gtk_widget_destroy(pImage);

		GdkPixbuf *pBuf = gdk_pixbuf_new_from_file_at_scale (file_name,500,330,TRUE,NULL);
		pImage = gtk_image_new_from_pixbuf(pBuf);
		g_object_unref (pBuf);

		gtk_layout_put(GTK_LAYOUT(layout), pImage,150,25);  
		gtk_widget_show_all(pImage);
		g_free(file_name), file_name=NULL;
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
	GtkWidget *pSave;
	gchar *sUtf8;

	pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	/* On ajoute un espace de 5 sur les bords de la fenetre */
	gtk_container_set_border_width(GTK_CONTAINER(pWindow), 5);
	gtk_window_set_title(GTK_WINDOW(pWindow), "Identity");
	gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
	g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(cb_quit), NULL);

	pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(pWindow), pVBox);

	/* Creation du premier GtkFrame */
	pFrame = gtk_frame_new("Name");
	gtk_box_pack_start(GTK_BOX(pVBox), pFrame, TRUE, FALSE, 0);

	/* Creation et insertion d une boite pour le premier GtkFrame */
	pVBoxFrame = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
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

	pSave = gtk_button_new_with_label ("Save");
	gtk_box_pack_start(GTK_BOX(pVBoxFrame), pSave, TRUE, FALSE, 0);
	g_signal_connect(G_OBJECT(pSave), "clicked", G_CALLBACK(cb_open), NULL);

	gtk_widget_show_all(pWindow);

	gtk_main();

	(void)p_widget;
}

void cd_save (GtkWidget *p_widget)
{

	(void)p_widget;
}

GPid cb_program(gchar *program, gchar *arguments)
{
	gchar  **args;
	GPid pid;
	GError *error = NULL;
	gboolean status;

	args = g_new (gchar *, 3);
	args[0] = g_strdup ("../../main");                /* programme à lancer */
	args[1] = NULL;                                   /* zéro terminal obligatoire */

	status = g_spawn_async_with_pipes ( NULL,
			args,
			NULL,
			(GSpawnFlags) G_SPAWN_SEARCH_PATH 
			| G_SPAWN_DO_NOT_REAP_CHILD,
			NULL,
			NULL,
			&pid,
			NULL,
			NULL,
			NULL,
			&error);
	if (status == FALSE) 
	{    
		g_free (args[0]);
		g_free (args[1]);

		return -1;
	}
	g_free (args[0]);
	g_free (args[1]);

	(void)program;
	(void)arguments; 
	return pid;
}
