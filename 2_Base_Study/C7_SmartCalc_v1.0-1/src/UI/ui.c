#include "UI/ui.h"

#include <cairo.h>
#include <gtk/gtk.h>
#include <math.h>
#include <string.h>

#include "main.h"

#define WIDTH 640
#define HEIGHT 480

#define ZOOM_X 100.0
#define ZOOM_Y 100.0

char in_string[512] = {'\0'};
char result_string[50] = {'\0'};
double x_value = NAN;

#define DA_WIDTH 600
#define DA_HEIGHT 600
#define ROTATE 1
#define DONT_ROTATE 0

GtkEntry *input_expression;
GtkEntry *input_x;
GtkWidget *label_result;

char *expression;
GtkWidget *drawing_area;
GtkWidget *graph_error_label;
GtkWidget *domain_max_spin;
GtkWidget *codomain_max_spin;
GtkWidget *domain_min_spin;
GtkWidget *codomain_min_spin;
int max_is_eq_to_min = 0;
int dom_is_eq_to_codom = 0;

int app() {
  gtk_init(NULL, NULL);

  GtkBuilder *builder;
  GError *err_gtk = NULL;

  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "UI/calc_ui.glade", &err_gtk)) {
    g_critical("Не вышло загрузить файл с UI : %s", err_gtk->message);
    g_error_free(err_gtk);
  }

  GtkWidget *window =
      GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  g_signal_connect(G_OBJECT(window), "destroy", G_CALLBACK(gtk_main_quit),
                   NULL);

  label_result = GTK_WIDGET(gtk_builder_get_object(builder, "label_result"));
  input_expression =
      GTK_ENTRY(gtk_builder_get_object(builder, "input_expression"));
  input_x = GTK_ENTRY(gtk_builder_get_object(builder, "input_x"));
  //   if (gtk_entry_get_text(input_x)) x = atof(gtk_entry_get_text(input_x));
  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

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

double calculateClicked() {
  int err = 0;
  double result_digit = 0.0;
  char input_string[512] = {'\0'};
  char polish_string[512] = {'\0'};
  double x = 1.0;
  //   printf("%s\n", gtk_entry_get_text(input_x));
  if (gtk_entry_get_text(input_x)) x = atof(gtk_entry_get_text(input_x));

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  printf("%s\n", in_string);
  strcat(in_string, "\n");
  printf("%s\n", in_string);
  strcpy(input_string, in_string);
  //   strtok(input_string, "\0");

  result_digit = back_process(input_string, polish_string, x, &q_in, &q_polish,
                              s_in, s_pol, &err);

  if (!err) {
    sprintf(result_string, "%f", result_digit);
    gtk_label_set_text(GTK_LABEL(label_result), result_string);
  } else
    gtk_label_set_text(GTK_LABEL(label_result), "Error");

  freeStack(s_in);
  freeStack(s_pol);
  return result_digit;
}

double calculateForGraph(double x) {
  int err = 0;
  double result_digit = 0.0;
  char input_string[512] = {'\0'};
  char polish_string[512] = {'\0'};
  //   double x = 1.0;
  // //   printf("%s\n", gtk_entry_get_text(input_x));
  //   if (gtk_entry_get_text(input_x)) x = atof(gtk_entry_get_text(input_x));

  queue q_in;
  queue q_polish;

  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  //   printf("%s\n", in_string);
  //   strcat(in_string, "\n");
  //   printf("%s\n", in_string);
  strcpy(input_string, in_string);
  //   strtok(input_string, "\0");

  result_digit = back_process(input_string, polish_string, x, &q_in, &q_polish,
                              s_in, s_pol, &err);

  if (!err) {
    sprintf(result_string, "%f", result_digit);
    gtk_label_set_text(GTK_LABEL(label_result), result_string);
  } else
    gtk_label_set_text(GTK_LABEL(label_result), "Error");

  freeStack(s_in);
  freeStack(s_pol);
  return result_digit;
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
  //   expression = in_string;
  //   printf("Expression: %s\n", expression);
  strcat(in_string, "\n");
  GtkWidget *window_graph;

  GtkWidget *da;
  GtkBuilder *builder;
  GtkWidget *close_button;
  GtkWidget *draw_button;
  GtkEntry *graph_entry = NULL;
  GtkWidget *graph_window;

  //   //   char input[] = {'1', '2'};

  builder = gtk_builder_new_from_file("UI/graph_gui.glade");
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

  gtk_entry_set_text(graph_entry, (const gchar *)in_string);
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
  //   printf("test\n");
  s_graph_properties gp = {'\0'};
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
  printf("In string from on_draw %s\n", in_string);
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
  setlocale(LC_NUMERIC, "C");
  int vector = -1; /* 1 or -1, depending on y axis*/
  int flag = 0;
  cairo_set_source_rgb(gp->cr, 0.60, 0.15, 1.0);
  cairo_set_line_width(gp->cr, 2 * gp->dx);
  gdouble step = gp->dx / 10;
  for (gdouble x = gp->min_x; x < gp->max_x; x += step) {
    // gdouble y_value = calculation(expression, &x, NULL);
    // gdouble y_value = pow(x, 2);
    gdouble y_value = calculateForGraph(x);
    // double y_value = calculateForGraph(x);
    // printf("Y_VALUE: %lf\n", y_value);
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
  for (size_t i = 1; i < strlen(buffer); i++) {
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