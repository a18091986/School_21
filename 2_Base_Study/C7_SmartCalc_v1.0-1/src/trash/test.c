//Подключаем заголовочные файлы gtk

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>

#include "main.h"

#define WIDTH 640
#define HEIGHT 480

#define ZOOM_X 100.0
#define ZOOM_Y 100.0

GtkEntry *input_expression;
GtkEntry *input_x;
GtkWidget *label_result;

char in_string[256] = {'\0'};
double x_value = NAN;

#define DA_WIDTH 600
#define DA_HEIGHT 600
#define ROTATE 1
#define DONT_ROTATE 0

char *expression;
GtkWidget *drawing_area;
GtkWidget *graph_error_label;
GtkWidget *domain_max_spin;
GtkWidget *codomain_max_spin;
GtkWidget *domain_min_spin;
GtkWidget *codomain_min_spin;
int max_is_eq_to_min = 0;
int dom_is_eq_to_codom = 0;

// Слот выхода из программы
// G_MODULE_EXPORT void onExit(GtkWidget * w) {
//     gtk_main_quit();
// }

// G_MODULE_EXPORT void onOneClicked(GtkButton * btn, input_string * is) {
//     strcpy(&is->data[is->position], "1 ");
//     is->position += 2;
//     // printf("string: %s\n", is->data);
//     // printf("from one_clicked\n");
// }

// gfloat f (gfloat x)
// {
//     return 0.03 * pow (x, 3);
// }

// static gboolean on_draw (GtkWidget *widget, cairo_t *cr, gpointer user_data)
// {
//     GdkRectangle da;            /* GtkDrawingArea size */
//     gdouble dx = 5.0, dy = 5.0; /* Pixels between each point */
//     gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
//     GdkWindow *window = gtk_widget_get_window(widget);
//     /* Determine GtkDrawingArea dimensions */
//     gdk_window_get_geometry (window,
//             &da.x,
//             &da.y,
//             &da.width,
//             &da.height);
//     /* Draw on a black background */
// cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
// cairo_paint (cr);
// /* Change the transformation matrix */
// cairo_translate (cr, da.width / 2, da.height / 2);
// cairo_scale (cr, ZOOM_X, -ZOOM_Y);
// /* Determine the data points to calculate (ie. those in the clipping zone */
// cairo_device_to_user_distance (cr, &dx, &dy);
// cairo_clip_extents (cr, &clip_x1, &clip_y1, &clip_x2, &clip_y2);
// cairo_set_line_width (cr, dx);
// /* Draws x and y axis */
// cairo_set_source_rgb (cr, 0.0, 1.0, 0.0);
// cairo_move_to (cr, clip_x1, 0.0);
// cairo_line_to (cr, clip_x2, 0.0);
// cairo_move_to (cr, 0.0, clip_y1);
// cairo_line_to (cr, 0.0, clip_y2);
// cairo_stroke (cr);
// /* Link each data point */
// for (i = clip_x1; i < clip_x2; i += dx)
//     cairo_line_to (cr, i, f (i));
// /* Draw the curve */
// cairo_set_source_rgba (cr, 1, 0.2, 0.2, 0.6);
// cairo_stroke (cr);
////////////////////////////////////////////////////////////////////////////
//     int width = 640;
//     int height = 480;
//     cairo_text_extents_t te;
//     cairo_set_source_rgb(cr, 0.0, 0.0, 0.0);
//     cairo_move_to (cr, width/2, 0);
//     cairo_line_to (cr, width/2, height);
//     cairo_move_to (cr, 0, height/2);
//     cairo_line_to (cr, width, height / 2);
//   	cairo_set_line_width (cr, 2);
//   	cairo_stroke (cr);
// 	cairo_select_font_face (cr, "Georgia",
//                             CAIRO_FONT_SLANT_NORMAL,
//                             CAIRO_FONT_WEIGHT_BOLD);
// 	cairo_set_font_size (cr, 25);
// 	cairo_text_extents (cr, "x", &te);
// 	cairo_move_to(cr, (double)width - te.width - 2, (double)height/2.0 - 4);
// 	cairo_show_text (cr, "x");
// 	cairo_text_extents (cr, "f(x)", &te);
// 	cairo_move_to(cr, (double)width/2.0 - te.width - 4, te.height);
// 	cairo_show_text (cr, "f(x)");
//     return FALSE;
// }

// static gboolean on_draw_grid (GtkWidget *widget, cairo_t *cr, gpointer
// user_data)
// {
//     GdkRectangle da;            /* GtkDrawingArea size */
//     gdouble dx = 5.0, dy = 5.0; /* Pixels between each point */
//     gdouble i, clip_x1 = 0.0, clip_y1 = 0.0, clip_x2 = 0.0, clip_y2 = 0.0;
//     GdkWindow *window = gtk_widget_get_window(widget);
//     /* Determine GtkDrawingArea dimensions */
//     gdk_window_get_geometry (window,
//             &da.x,
//             &da.y,
//             &da.width,
//             &da.height);
//     int width = 640;
//     int height = 480;
//     double dmin = -10;
//     double dmax = 10;
//     double emin = -10;
//     double emax = 10;
//     cairo_t *cr_src;
//     cr_src = cr;
//     double dif = dmax - dmin;
// 	double emax_tmp = emax, emin_tmp = emin;
// 	double dmax_tmp = dmax, dmin_tmp = dmin;
// 	double r, wscale, hscale;
// 	// cairo_t *cr;
// 	cairo_surface_t *surface;
// 	if (emax - emin > dif) {
// 		dif = emax - emin;
// 		r = (dif - (dmax - dmin)) / 2.0;
// 		dmax += r;
// 		dmin -= r;
// 	} else {
// 		r = (dif - (emax - emin)) / 2.0;
// 		emax += r;
// 		emin -= r;
// 	}
// 	wscale = width / dif;
// 	hscale = height / dif;
// 	surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
//                                          width, height);
//     cr = cairo_create (surface);
//   	cairo_set_source_rgb(cr, 0.909803922,  0.639215686, 0.090196078);
// 	for (int a = 0; a < width; a += 40) {
// 		cairo_move_to(cr, a, 0);
// 		cairo_line_to(cr, a, height);
// 		cairo_move_to(cr, 0, a);
// 		cairo_line_to(cr, width, a);
// 	}
//   	cairo_set_line_width (cr, 1);
// 	cairo_stroke (cr);
// 	surface = cairo_get_target(cr);
// 	cairo_set_source_surface(cr_src, surface, 0, 0);
// 	cairo_rectangle(cr_src,
//                     width/2 + (dmin_tmp - (dmin + dif/2)) * wscale,
//                     height/2 - (emax_tmp - (emin + dif/2)) * hscale,
//                     (dmax_tmp - dmin_tmp) * wscale,
//                     (emax_tmp - emin_tmp) * hscale);
// 	cairo_fill(cr_src);
// 	cairo_set_source_rgb(cr_src, 0.294117647, 0.0, 0.509803922);
// 	cairo_rectangle(cr_src,
//                     width/2 + (dmin_tmp - (dmin + dif/2)) * wscale,
//                     height/2 - (emax_tmp - (emin + dif/2)) * hscale,
//                     (dmax_tmp - dmin_tmp) * wscale,
//                     (emax_tmp - emin_tmp) * hscale);
// 	cairo_stroke(cr_src);
// 	cairo_surface_destroy(surface);
// 	cairo_destroy(cr);
//     return FALSE;
// }

// static gboolean on_draw_x (GtkWidget *widget, cairo_t *cr, gpointer
// user_data)
// {
//     int width = 640;
//     int height = 480;
//     double dmin = -10;
//     double dmax = 10;
//     double emin = -10;
//     double emax = 10;
//     cairo_text_extents_t te;
// 	double d, delta, tmp;
// 	int source;
// 	char str[256];
// 	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
// 	cairo_select_font_face (cr, "Georgia",
//                             CAIRO_FONT_SLANT_NORMAL,
//                             CAIRO_FONT_WEIGHT_BOLD);
// 	cairo_set_font_size (cr, 10);
// 	delta = (dmax-dmin > emax-emin) ? (dmax-dmin)/20.0 : (emax-emin)/20.0;
// 	d = (dmin + dmax) / 2.0;
// 	source = width / 2;
// 	sprintf(str, "%.2g", d);
// 	cairo_save(cr);
// 	cairo_text_extents (cr, str, &te);
// 	cairo_translate(cr, source, 2 + height / 2);
// 	cairo_rotate(cr, M_PI / 2);
// 	cairo_move_to(cr, 0, 0);
// 	cairo_show_text (cr, str);
// 	cairo_restore(cr);
// 	source = width / 2 + 40;
// 	for (tmp = d + delta; source <= width; tmp += delta, source += 40) {
// 		sprintf(str, "%.2g", tmp);
// 		cairo_save(cr);
// 		cairo_text_extents (cr, str, &te);
// 		cairo_translate(cr, source - te.height, 2 + height / 2);
// 		// cairo_rotate(cr, M_PI / 2);
// 		cairo_move_to(cr, 0, 0);
// 		cairo_show_text (cr, str);
// 		cairo_restore(cr);
// 	}
// 	source = width / 2 - 40;
// 	for (tmp = d - delta; source >= 0; tmp -= delta, source -= 40) {
// 		sprintf(str, "%.2g", tmp);
// 		cairo_save(cr);
// 		cairo_text_extents (cr, str, &te);
// 		cairo_translate(cr, source , height / 2 - te.width - 2);
// 		cairo_text_extents (cr, str, &te);
// 		cairo_rotate(cr, M_PI / 2.0);
// 		cairo_move_to(cr, 0, 0);
// 		cairo_show_text (cr, str);
// 		cairo_restore(cr);
// 	}
//     return FALSE;
// }

// static gboolean on_draw_y (GtkWidget *widget, cairo_t *cr, gpointer
// user_data)
// {
//     int width = 640;
//     int height = 480;
//     double dmin = -10;
//     double dmax = 10;
//     double emin = -10;
//     double emax = 10;
//     cairo_text_extents_t te;
// 	double d, delta, tmp;
// 	int source;
// 	char str[256];
// 	cairo_set_source_rgb (cr, 0.0, 0.0, 0.0);
// 	cairo_select_font_face (cr, "Georgia",
//                             CAIRO_FONT_SLANT_NORMAL,
//                             CAIRO_FONT_WEIGHT_BOLD);
// 	cairo_set_font_size (cr, 10);
// 	delta = (dmax-dmin > emax-emin) ? (dmax-dmin)/20.0 : (emax-emin)/20.0;
// 	d = (emin + emax) / 2.0;
// 	source = height / 2;
// 	sprintf(str, "%.2g", d);
// 	cairo_text_extents (cr, str, &te);
// 	cairo_move_to(cr, 2 + width / 2, source);
// 	cairo_show_text (cr, str);
// 	source = height / 2 - 40;
// 	for (tmp = d + delta; source >= 0; tmp += delta, source -= 40) {
// 		sprintf(str, "%.2g", tmp);
// 		cairo_text_extents (cr, str, &te);
// 		cairo_move_to(cr, 2 + width/2, source + te.height);
// 		cairo_show_text (cr, str);
// 	}
// 	source = height / 2 + 40;
// 	for (tmp = d - delta; source <= height; tmp -= delta, source += 40) {
// 		sprintf(str, "%.2g", tmp);
// 		cairo_text_extents (cr, str, &te);
// 		cairo_move_to(cr, width/2 - te.width - 2, source);
// 		cairo_show_text (cr, str);
// 	}
//     return FALSE;
// }

// void draw_graph (GtkWidget *widget, cairo_t *cr, gpointer user_data) {
//   setlocale(LC_NUMERIC, "C");
//   gdouble dx = 1;
//   int min_x = 1;
//   int max_x = 2;
//   int max_y  = 200;
//   int min_y  = -10;
//   int vector = - 1; /* 1 or -1, depending on y axis*/
//   int flag = 0;
//   cairo_set_source_rgb(cr, 0.60, 0.15, 1.0);
//   cairo_set_line_width(cr, 2 * dx);
//   cairo_move_to(cr, 0, 0);
//   cairo_line_to(cr, 1, 1);
// int width = 640;
// int height = 480;
//   cairo_surface_t *surface;
//   surface = cairo_image_surface_create(CAIRO_FORMAT_ARGB32,
//                                         width, height);
//   cr = cairo_create (surface);
//   cairo_set_source_rgb(cr, 0.909803922,  0.639215686, 0.090196078);
//   cairo_move_to(cr, 0, 0);
//   cairo_line_to(cr, 100, 100);
//   cairo_move_to(cr, 100, 100);
//   gdouble step = dx / 1;
//   for (gdouble x = min_x; x < max_x; x += step) {
//     gdouble y_value = x;
//     if (y_value > max_y) {
//         printf("1");
//       if (flag == 1) cairo_line_to(cr, x, vector * max_y);
//       cairo_move_to(cr, x, vector * max_y);
//       flag = 0;
//     } else if ((y_value < min_y)) {
//       printf("2");
//       if (flag == 1) cairo_line_to(cr, x, vector * min_y);
//       cairo_move_to(cr, x, vector * min_y);
//       flag = 0;
//     } else if (isnan(y_value)) {
//       printf("3");
//       flag = 2;
//     } else if (flag < 2) {
//       cairo_line_to(cr, x, y_value);
//       printf("x: %lf, y: %lf\n", x, y_value);
//       flag = 1;
//     } else {
//       cairo_move_to(cr, x, y_value);
//       flag = 1;
//     }
//   }
//   cairo_stroke(cr);
// }

void clearClicked() {
  in_string[0] = '\0';
  gtk_entry_set_text(input_expression, (const gchar *)in_string);
  gtk_entry_set_text(input_x, (const gchar *)"");
  gtk_label_set_text(GTK_LABEL(label_result), (const gchar *)"0.00");
}

void deleteClicked() {
  int input_size = strlen(in_string);
  if (input_size > 0) {
    in_string[input_size - 1] = '\0';
    gtk_entry_set_text(input_expression, (const gchar *)in_string);
  }
}

void calculateClicked() {
  printf("%s", in_string);
  gtk_label_set_text(GTK_LABEL(label_result), in_string);
}

void numbtnClicked(GtkButton *button) {
  const gchar *text = gtk_button_get_label(button);
  strcat(in_string, text);
  gtk_entry_set_text(input_expression, (const gchar *)in_string);
}

void funcbtnClicked(GtkButton *button) {
  const gchar *text = gtk_button_get_label(button);
  strcat(in_string, text);
  gtk_entry_set_text(input_expression, (const gchar *)in_string);
}

int button_draw_graph_clicked_cb() {
  GtkWidget *window_graph;

  GtkWidget *da;
  GtkBuilder *builder;
  GtkWidget *close_button;
  GtkWidget *draw_button;
  GtkEntry *graph_entry;
  GtkWidget *graph_window;

  char input[] = {'1', '2'};
  // expression = input;

  builder = gtk_builder_new_from_file("graph_gui.glade");
  gtk_builder_connect_signals(builder, NULL);

  graph_window = GTK_WIDGET(gtk_builder_get_object(builder, "graph_window"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "graph_da"));
  close_button = GTK_WIDGET(gtk_builder_get_object(builder, "graph_close"));
  draw_button =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_draw_button"));

  graph_error_label =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_error_label"));
  domain_max_spin =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_domain_max"));
  codomain_max_spin =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_codomain_max"));
  domain_min_spin =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_domain_min"));
  codomain_min_spin =
      GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_codomain_min"));

  gtk_entry_set_text(graph_entry, (const gchar *)input);
  gtk_widget_set_size_request(drawing_area, DA_WIDTH,
                              DA_HEIGHT);  // size in pixels

  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);
  g_signal_connect(G_OBJECT(draw_button), "clicked",
                   G_CALLBACK(button_draw_clicked), G_OBJECT(graph_entry));
  g_signal_connect(G_OBJECT(close_button), "clicked", G_CALLBACK(close_window),
                   G_OBJECT(graph_window));

  g_object_unref(builder);
  gtk_window_set_position(GTK_WINDOW(graph_window), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(graph_window);

  return 0;
}

static gboolean on_draw(GtkWidget *widget, cairo_t *cairo) {
  printf("test\n");
  s_graph_properties gp = {};
  double x_middle;
  double y_middle;
  double x_range;
  double y_range;

  gp.cr = cairo;

  /* Draw on a background */
  cairo_set_source_rgb(gp.cr, 0.69, 0.91, 0.91);
  cairo_paint(gp.cr);

  cairo_device_to_user_distance(gp.cr, &gp.dx, &gp.dy);

  /* max value is always positive, min value is always negative */
  //   gp.max_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(domain_max_spin));
  //   gp.max_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(codomain_max_spin));
  //   gp.min_x = gtk_spin_button_get_value(GTK_SPIN_BUTTON(domain_min_spin));
  //   gp.min_y = gtk_spin_button_get_value(GTK_SPIN_BUTTON(codomain_min_spin));

  gp.max_x = 10;
  gp.max_y = 100;
  gp.min_x = -10;
  gp.min_y = -1;

  //   if (dom_is_eq_to_codom) {
  //     gp.max_y = gp.max_x;
  //     gp.min_y = gp.min_x;
  //   }

  //   if (max_is_eq_to_min) {
  //     gp.min_x = -gp.max_x;
  //     gp.min_y = -gp.max_y;
  //   }

  /* right_limit is Xmin on a graph axes, left_limit is Xmax
    if Xmax < Ymax, axes doesn't print fully */
  gp.right_limit = gp.min_x > gp.min_y ? gp.min_y : gp.min_x;
  gp.left_limit = gp.max_x < gp.max_y ? gp.max_y : gp.max_x;
  /* inverting Y axes*/
  gp.lower_limit = -gp.max_y > -gp.max_x ? -gp.max_x : -gp.max_y;
  gp.upper_limit = -gp.min_y < -gp.min_x ? -gp.min_x : -gp.min_y;

  x_range = gp.left_limit - gp.right_limit;
  y_range = gp.upper_limit - gp.lower_limit;

  /* Pixels between each point, has to be same */
  gp.dx = (x_range) / DA_WIDTH;
  gp.dy = (x_range) / DA_HEIGHT;

  x_middle = (fabs(gp.right_limit) / (x_range)) * DA_WIDTH;
  y_middle = (fabs(gp.lower_limit)) / (y_range)*DA_HEIGHT;

  cairo_translate(gp.cr, x_middle, y_middle);

  cairo_scale(gp.cr, 1 / gp.dx, 1 / gp.dy);

  draw_axis(&gp);

  //   if (input_validation(expression) == S21_CORRECT_INPUT) {
  if (1) {
    char buffer[64];
    if (gp.dx < 1)
      sprintf(buffer, "scale px/unit: %.4g/%g", 1 / gp.dx, 1.0);
    else
      sprintf(buffer, "scale px/unit: %g/%.4g", 1.0, gp.dx);
    gtk_label_set_text(GTK_LABEL(graph_error_label), buffer);
    draw_graph_line(&gp);
  } else {
    gtk_label_set_text(GTK_LABEL(graph_error_label),
                       (const gchar *)"INCORRECT INPUT");
  }
  return FALSE;
}

void draw_graph_line(s_graph_properties *gp) {
  // setlocale(LC_NUMERIC, "C");
  int vector = -1; /* 1 or -1, depending on y axis*/
  int flag = 0;
  cairo_set_source_rgb(gp->cr, 0.60, 0.15, 1.0);
  cairo_set_line_width(gp->cr, 2 * gp->dx);
  gdouble step = gp->dx / 10;
  for (gdouble x = gp->min_x; x < gp->max_x; x += step) {
    // gdouble y_value = calculation(expression, &x, NULL);
    gdouble y_value = pow(x, 2);
    if (y_value > gp->max_y) {
      if (flag == 1) cairo_line_to(gp->cr, x, vector * gp->max_y);
      cairo_move_to(gp->cr, x, vector * gp->max_y);
      flag = 0;
    } else if ((y_value < gp->min_y)) {
      if (flag == 1) cairo_line_to(gp->cr, x, vector * gp->min_y);
      cairo_move_to(gp->cr, x, vector * gp->min_y);
      flag = 0;
    } else if (isnan(y_value)) {
      flag = 2;
    } else if (flag < 2) {
      cairo_line_to(gp->cr, x, vector * y_value);
      flag = 1;
    } else {
      cairo_move_to(gp->cr, x, vector * y_value);
      flag = 1;
    }
  }
  cairo_stroke(gp->cr);
}

void roundTo2digits(gdouble *step) {
  char buffer[64];
  sprintf(buffer, "%lf", *step);
  for (int i = 1; i < strlen(buffer); i++) {
    if (buffer[i] != '.') buffer[i] = '0';
  }
  sscanf(buffer, "%lf", step);
}

gdouble set_axis_step(s_graph_properties *gp) {
  gdouble step = 20 * gp->dx;
  if (step > 10) {
    roundTo2digits(&step);
  } else if (step > 5) {
    step = 10;
  } else if (step > 2) {
    step = 5;
  } else if (step > 1) {
    step = 2;
  } else {
    for (gdouble i = 0.1; i <= 1; i += 0.1) {
      if (step < i) {
        step = i;
        break;
      }
    }
  }
  return step;
}

void draw_axis_text(s_graph_properties *gp, gdouble value, int rotate) {
  char buffer[64];
  sprintf(buffer, "%g", value);
  if (rotate) {
    cairo_rotate(gp->cr, -1);
    cairo_show_text(gp->cr, buffer);
    cairo_rotate(gp->cr, 1);
  } else {
    cairo_show_text(gp->cr, buffer);
  }
}

void draw_axis(s_graph_properties *gp) {
  char buffer[64];
  gdouble step = set_axis_step(gp);
  int flag = 1;
  gdouble text_offset = 2 * gp->dx;
  int vector = -1;

  cairo_set_source_rgb(gp->cr, 0.0, 0.0, 0.0);
  cairo_set_line_width(gp->cr, gp->dx / 10);

  cairo_select_font_face(gp->cr, "Arial", CAIRO_FONT_SLANT_NORMAL,
                         CAIRO_FONT_WEIGHT_NORMAL);
  cairo_set_font_size(gp->cr, 10 * gp->dx);

  for (gdouble i = 0; i < gp->left_limit; i += step) {
    cairo_move_to(gp->cr, i, gp->lower_limit);
    cairo_line_to(gp->cr, i, gp->upper_limit);
    cairo_move_to(gp->cr, i, gp->upper_limit - text_offset);
    draw_axis_text(gp, i, ROTATE);
  }
  for (gdouble i = 0; i > gp->right_limit; i -= step) {
    cairo_move_to(gp->cr, i, gp->lower_limit);
    cairo_line_to(gp->cr, i, gp->upper_limit);
    cairo_move_to(gp->cr, i, gp->upper_limit - text_offset);
    draw_axis_text(gp, i, ROTATE);
  }
  for (gdouble i = 0; i < gp->upper_limit; i += step) {
    cairo_move_to(gp->cr, gp->right_limit, i);
    cairo_line_to(gp->cr, gp->left_limit, i);
    cairo_move_to(gp->cr, gp->right_limit, i);
    draw_axis_text(gp, vector * i, DONT_ROTATE);
  }
  // last line has to be without text
  // cairo_move_to(gp->cr, gp->right_limit, gp->upper_limit);
  // cairo_line_to(gp->cr, gp->left_limit, gp->upper_limit);

  for (gdouble i = 0; i > gp->lower_limit; i -= step) {
    cairo_move_to(gp->cr, gp->right_limit, i);
    cairo_line_to(gp->cr, gp->left_limit, i);
    cairo_move_to(gp->cr, gp->right_limit, i);
    draw_axis_text(gp, vector * i, DONT_ROTATE);
  }
  // last line has to be without text
  // cairo_move_to(gp->cr, gp->right_limit, gp->lower_limit);
  // cairo_line_to(gp->cr, gp->left_limit, gp->lower_limit);

  cairo_stroke(gp->cr);

  cairo_set_line_width(gp->cr, gp->dx / 2);
  cairo_move_to(gp->cr, gp->right_limit, 0);
  cairo_line_to(gp->cr, gp->left_limit, 0);
  cairo_move_to(gp->cr, 0, gp->lower_limit);
  cairo_line_to(gp->cr, 0, gp->upper_limit);

  cairo_set_font_size(gp->cr, 15 * gp->dx);
  cairo_move_to(gp->cr, gp->left_limit - 15 * gp->dx, 0 + 15 * gp->dx);
  sprintf(buffer, "X");
  cairo_show_text(gp->cr, buffer);
  cairo_move_to(gp->cr, 0 + 5 * gp->dx, gp->lower_limit + 15 * gp->dx);
  sprintf(buffer, "Y");
  cairo_show_text(gp->cr, buffer);

  cairo_stroke(gp->cr);
}

void button_draw_clicked(GtkWidget *button, gpointer entry) {
  printf("from button_draw_clicked");
  //   sprintf(expression, "%s", gtk_entry_get_text(entry));
  gtk_widget_queue_draw(drawing_area);
}

void close_window(GtkWidget *widget, gpointer window) {
  gtk_widget_destroy(GTK_WIDGET(window));
}

void check_same_dom_codom_toggled_cb(GtkCheckButton *button) {
  gboolean status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
  if (status) {
    dom_is_eq_to_codom = 1;
    gtk_widget_set_sensitive(codomain_max_spin, FALSE);
    gtk_widget_set_sensitive(codomain_min_spin, FALSE);
  } else {
    dom_is_eq_to_codom = 0;
    gtk_widget_set_sensitive(codomain_max_spin, TRUE);
    if (!max_is_eq_to_min) gtk_widget_set_sensitive(codomain_min_spin, TRUE);
  }
}

void check_same_max_min_toggled_cb(GtkCheckButton *button) {
  gboolean status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
  if (status) {
    max_is_eq_to_min = 1;
    gtk_widget_set_sensitive(domain_min_spin, FALSE);
    gtk_widget_set_sensitive(codomain_min_spin, FALSE);
  } else {
    max_is_eq_to_min = 0;
    gtk_widget_set_sensitive(domain_min_spin, TRUE);
    if (!dom_is_eq_to_codom) gtk_widget_set_sensitive(codomain_min_spin, TRUE);
  }
}

//     window_graph = gtk_window_new (GTK_WINDOW_TOPLEVEL);
//     gtk_window_set_default_size (GTK_WINDOW (window_graph), WIDTH, HEIGHT);
//     gtk_window_set_title (GTK_WINDOW (window_graph), "Graph drawing");
//     g_signal_connect (G_OBJECT (window_graph), "destroy", gtk_main_quit,
//     NULL); da = gtk_drawing_area_new (); gtk_container_add (GTK_CONTAINER
//     (window_graph), da);
//     // g_signal_connect (G_OBJECT (da), "draw", G_CALLBACK (on_draw), NULL);
//     // g_signal_connect (G_OBJECT (da), "draw", G_CALLBACK (on_draw_grid),
//     NULL);
//     // g_signal_connect (G_OBJECT (da), "draw", G_CALLBACK (on_draw_x),
//     NULL);
//     // g_signal_connect (G_OBJECT (da), "draw", G_CALLBACK (on_draw_y),
//     NULL);
//     // g_signal_connect (G_OBJECT (da), "draw", G_CALLBACK (draw_graph),
//     NULL); gtk_widget_show_all(window_graph);
// }

//   setlocale(LC_NUMERIC, "C");
//   double *x = NULL;
//   if (!isnan(x_value)) x = &x_value;
//   char *output_string = calloc(S21_MAX_INPUT, sizeof(char));
//   if (output_string != NULL) {
//     calculation(input, x, output_string);
//     gtk_label_set_text(GTK_LABEL(label_result), output_string);
//   }
//   free(output_string);
// }

// void button_draw_graph_clicked_cb() {
//   if (input_validation(input) == S21_INCORRECT_INPUT) {
//     gtk_label_set_text(GTK_LABEL(label_result),
//                        (const gchar *)"INCORRECT INPUT");
//   } else {
//     graph_output(input);
//   }
// }

int main(int argc, char *argv[]) {
  gtk_init(&argc, &argv);

  GtkBuilder *builder;
  GError *err = NULL;

  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "calc_ui.glade", &err)) {
    g_critical("Не вышло загрузить файл с UI : %s", err->message);
    g_error_free(err);
  }

  GtkWidget *window =
      GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  // GtkButton * one_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder,
  // "one_btn"));

  label_result = GTK_WIDGET(gtk_builder_get_object(builder, "label_result"));
  input_expression =
      GTK_ENTRY(gtk_builder_get_object(builder, "input_expression"));
  input_x = GTK_ENTRY(gtk_builder_get_object(builder, "input_x"));

  // g_signal_connect(G_OBJECT(one_btn), "clicked", G_CALLBACK(onOneClicked),
  // &is);
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}
