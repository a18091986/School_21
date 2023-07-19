#ifndef SRC_UI_H_
#define SRC_UI_H_

#include <cairo.h>
#include <gtk/gtk.h>
#include <locale.h>
#include <math.h>
#include <string.h>

#include "logic/deposit.h"
#include "main.h"

typedef struct {
  cairo_t *cr;
  gdouble min_x;
  gdouble max_x;
  gdouble min_y;
  gdouble max_y;
  gdouble dx;
  gdouble dy;
  gdouble right_limit;
  gdouble left_limit;
  gdouble lower_limit;
  gdouble upper_limit;
} s_graph_properties;

int app();
void printDepositOutput(long double value, char *output);
int button_draw_graph_clicked_cb();
void button_draw_clicked(GtkWidget *button, gpointer entry);
void set_values_from_spin_buttons(s_graph_properties *gp);

// graph

int graph_output(char *input);
static gboolean on_draw(GtkWidget *widget, cairo_t *cairo);
void close_window(GtkWidget *widget, gpointer window);
void draw_axis(s_graph_properties *gp);
void draw_graph_line(s_graph_properties *gp);

#endif  // SRC_UI_H_