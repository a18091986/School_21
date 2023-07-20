#include "UI/ui.h"

#define ROTATE 1
#define DONT_ROTATE 0

// char in_string[512] = {'\0'};
// char result_string[50] = {'\0'};
// double x_value = NAN;

GtkEntry *input_expression;
GtkEntry *input_x;
GtkWidget *label_result;

GtkEntry *credit_sum;
GtkEntry *credit_time;
GtkEntry *credit_percent;
GtkRadioButton *credit_type_ann;
GtkRadioButton *credit_type_dif;
GtkLabel *month_pay_result;
GtkLabel *additional_payment_result;
GtkLabel *sum_payment_result;
GtkLabel *credit_error;

GtkEntry *depo_start;
GtkEntry *depo_time;
GtkEntry *depo_pct;
GtkEntry *depo_tax_pct;
GtkRadioButton *depo_cap_yes;
GtkRadioButton *depo_cap_no;
GtkRadioButton *period_month;
GtkRadioButton *period_day;
GtkEntry *depo_plus_period;
GtkEntry *depo_plus_sum;
GtkEntry *depo_minus_period;
GtkEntry *depo_minus_sum;
GtkLabel *depo_pct_res;
GtkLabel *depo_tax_res;
GtkLabel *depo_sum_res;
GtkLabel *depo_error;

GtkWidget *drawing_area;
// GtkWidget *domain_max_spin;
// GtkWidget *codomain_max_spin;
// GtkWidget *domain_min_spin;
// GtkWidget *codomain_min_spin;

GtkEntry *x_min_input;
GtkEntry *x_max_input;
GtkEntry *y_min_input;
GtkEntry *y_max_input;

// int max_is_eq_to_min = 0;
// int dom_is_eq_to_codom = 0;

int app() {
  gtk_init(NULL, NULL);

  GtkBuilder *builder;
  GError *err_gtk = NULL;

  builder = gtk_builder_new();
  if (!gtk_builder_add_from_file(builder, "UI/calc_ui.glade", &err_gtk)) {
    // g_critical("Не вышло загрузить файл с UI : %s", err_gtk->message);
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

  x_min_input = GTK_ENTRY(gtk_builder_get_object(builder, "x_min_input"));
  x_max_input = GTK_ENTRY(gtk_builder_get_object(builder, "x_max_input"));
  y_min_input = GTK_ENTRY(gtk_builder_get_object(builder, "y_min_input"));
  y_max_input = GTK_ENTRY(gtk_builder_get_object(builder, "y_max_input"));

  credit_sum = GTK_ENTRY(gtk_builder_get_object(builder, "credit_sum"));
  credit_time = GTK_ENTRY(gtk_builder_get_object(builder, "credit_time"));
  credit_percent = GTK_ENTRY(gtk_builder_get_object(builder, "credit_percent"));
  credit_type_ann =
      GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "credit_type_ann"));
  credit_type_dif =
      GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "credit_type_diff"));
  month_pay_result =
      GTK_LABEL(gtk_builder_get_object(builder, "month_pay_result"));
  additional_payment_result =
      GTK_LABEL(gtk_builder_get_object(builder, "additional_payment_result"));
  sum_payment_result =
      GTK_LABEL(gtk_builder_get_object(builder, "sum_payment_result"));
  credit_error = GTK_LABEL(gtk_builder_get_object(builder, "credit_error"));

  depo_start = GTK_ENTRY(gtk_builder_get_object(builder, "depo_start"));
  depo_time = GTK_ENTRY(gtk_builder_get_object(builder, "depo_time"));
  depo_pct = GTK_ENTRY(gtk_builder_get_object(builder, "depo_pct"));
  depo_tax_pct = GTK_ENTRY(gtk_builder_get_object(builder, "depo_tax_pct"));
  depo_cap_yes =
      GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "depo_cap_yes"));
  depo_cap_no =
      GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "depo_cap_no"));
  period_month =
      GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "period_month"));
  period_day = GTK_RADIO_BUTTON(gtk_builder_get_object(builder, "period_day"));
  depo_plus_sum = GTK_ENTRY(gtk_builder_get_object(builder, "depo_plus_sum"));
  depo_plus_period =
      GTK_ENTRY(gtk_builder_get_object(builder, "depo_plus_period"));
  depo_minus_period =
      GTK_ENTRY(gtk_builder_get_object(builder, "depo_minus_period"));
  depo_minus_sum = GTK_ENTRY(gtk_builder_get_object(builder, "depo_minus_sum"));
  depo_pct_res = GTK_LABEL(gtk_builder_get_object(builder, "depo_pct_res"));
  depo_tax_res = GTK_LABEL(gtk_builder_get_object(builder, "depo_tax_res"));
  depo_sum_res = GTK_LABEL(gtk_builder_get_object(builder, "depo_sum_res"));
  depo_error = GTK_LABEL(gtk_builder_get_object(builder, "depo_error"));

  gtk_builder_connect_signals(builder, NULL);
  gtk_widget_show_all(window);
  gtk_main();

  return 0;
}

void onDepoCalcBtnClicked() {
  setlocale(LC_NUMERIC, "C");
  int is_cap =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(depo_cap_yes)) ? 1 : 0;

  int depo_pay_period =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(period_month)) ? 1 : 0;

  char depo_start_num[256] = {'\0'};
  char depo_time_num[256] = {'\0'};
  char depo_pct_num[256] = {'\0'};
  char depo_tax_pct_num[256] = {'\0'};
  char depo_plus_period_num[256] = {'\0'};
  char depo_plus_sum_num[256] = {'\0'};
  char depo_minus_period_num[256] = {'\0'};
  char depo_minus_sum_num[256] = {'\0'};

  strcpy(depo_start_num, gtk_entry_get_text(depo_start));
  strcpy(depo_time_num, gtk_entry_get_text(depo_time));
  strcpy(depo_pct_num, gtk_entry_get_text(depo_pct));
  strcpy(depo_tax_pct_num, gtk_entry_get_text(depo_tax_pct));
  strcpy(depo_plus_period_num, gtk_entry_get_text(depo_plus_period));
  strcpy(depo_plus_sum_num, gtk_entry_get_text(depo_plus_sum));
  strcpy(depo_minus_period_num, gtk_entry_get_text(depo_minus_period));
  strcpy(depo_minus_sum_num, gtk_entry_get_text(depo_minus_sum));

  printf("Начальная сумма вклада: %s\n", depo_start_num);
  printf("Срок вклада: %s\n", depo_time_num);
  printf("Процентная ставка: %s\n", depo_pct_num);
  printf("Налоговая ставка:  %s\n", depo_tax_pct_num);
  printf("Периодичность выплаты процентов:  %s\n",
         depo_pay_period ? "месяц" : "день");
  printf("Капитализация процентов: %s\n", is_cap ? "да" : "нет");
  printf("Периодичность пополнений:  %s\n", depo_plus_period_num);
  printf("Сумма пополнения:  %s\n", depo_plus_sum_num);
  printf("Периодичность снятий:  %s\n", depo_minus_period_num);
  printf("Сумма снятия:  %s\n", depo_minus_sum_num);

  double depo_result_pct_num = 0.0;
  double depo_result_tax_num = 0.0;
  double depo_result_sum_num = 0.0;

  int err =
      deposit(depo_start_num, depo_time_num, depo_pct_num, depo_tax_pct_num,
              depo_pay_period, is_cap, depo_plus_period_num, depo_plus_sum_num,
              depo_minus_period_num, depo_minus_sum_num, &depo_result_sum_num,
              &depo_result_pct_num, &depo_result_tax_num);
  if (!err) {
    char depo_result_pct_str[256] = {'\0'};
    char depo_result_tax_str[256] = {'\0'};
    char depo_result_sum_str[256] = {'\0'};

    sprintf(depo_result_pct_str, "%f", depo_result_pct_num);
    sprintf(depo_result_tax_str, "%f", depo_result_tax_num);
    sprintf(depo_result_sum_str, "%f", depo_result_sum_num);

    gtk_label_set_text(depo_pct_res, depo_result_pct_str);
    gtk_label_set_text(depo_tax_res, depo_result_tax_str);
    gtk_label_set_text(depo_sum_res, depo_result_sum_str);
  } else {
    gtk_label_set_text(depo_error, "НЕВЕРНЫЕ ВХОДНЫЕ ДАННЫЕ");
    gtk_label_set_text(depo_pct_res, "");
    gtk_label_set_text(depo_tax_res, "");
    gtk_label_set_text(depo_sum_res, "");
  }
}

void onCreditCalcBtnClicked() {
  setlocale(LC_NUMERIC, "C");
  int credit_type =
      gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(credit_type_ann)) ? 1 : 0;

  char credit_sum_num[256] = {'\0'};
  char credit_time_num[256] = {'\0'};
  char credit_percent_num[256] = {'\0'};

  strcpy(credit_sum_num, gtk_entry_get_text(credit_sum));
  strcpy(credit_time_num, gtk_entry_get_text(credit_time));
  strcpy(credit_percent_num, gtk_entry_get_text(credit_percent));

  printf("credit_sum_num: %s\n", credit_sum_num);
  printf("credit_time_num: %s\n", credit_time_num);
  printf("credit_percent_num: %s\n", credit_percent_num);
  printf("схема платежей: %s\n",
         credit_type ? "аннуитетная" : "дифференциальная");

  double month_pay_result_num_f = 0.0;
  double month_pay_result_num_l = 0.0;
  double additional_payment_result_num = 0.0;
  double sum_payment_result_num = 0.0;

  int err =
      credit(credit_sum_num, credit_time_num, credit_percent_num, credit_type,
             &month_pay_result_num_f, &month_pay_result_num_l,
             &additional_payment_result_num, &sum_payment_result_num);
  if (!err) {
    char month_pay_result_str[256] = {'\0'};
    char month_pay_result_str_f[256] = {'\0'};
    char month_pay_result_str_l[256] = {'\0'};
    char additional_payment_result_str[256] = {'\0'};
    char sum_payment_result_str[256] = {'\0'};

    sprintf(month_pay_result_str_f, "%.2f", month_pay_result_num_f);
    sprintf(month_pay_result_str_l, "%.2f", month_pay_result_num_l);
    strcat(month_pay_result_str, month_pay_result_str_f);
    strcat(month_pay_result_str, " / ");
    strcat(month_pay_result_str, month_pay_result_str_l);
    sprintf(additional_payment_result_str, "%.2f",
            additional_payment_result_num);
    sprintf(sum_payment_result_str, "%.2f", sum_payment_result_num);

    gtk_label_set_text(month_pay_result, month_pay_result_str);
    gtk_label_set_text(additional_payment_result,
                       additional_payment_result_str);
    gtk_label_set_text(sum_payment_result, sum_payment_result_str);
  } else {
    gtk_label_set_text(credit_error, "НЕВЕРНЫЕ ВХОДНЫЕ ДАННЫЕ");
    gtk_label_set_text(month_pay_result, "");
    gtk_label_set_text(additional_payment_result, "");
    gtk_label_set_text(sum_payment_result, "");
  }
}

void clearClicked() {
  //   in_string[] = {'\0'};
  //   gtk_entry_set_text(input_expression, (const gchar *)in_string);
  gtk_entry_set_text(input_expression, (const gchar *)"");
  gtk_entry_set_text(input_x, (const gchar *)"");
  gtk_label_set_text(GTK_LABEL(label_result), (const gchar *)"0.00");
}

void deleteClicked() {
  //   int input_size = strlen(in_string);
  char in_string[256] = {'\0'};
  strcpy(in_string, gtk_entry_get_text(input_expression));
  //   in_string = gtk_entry_get_text(input_expression);
  int input_size = strlen(in_string);
  //   int input_size = strlen(gtk_entry_get_text(input_expression));
  if (input_size > 0) {
    in_string[input_size - 1] = '\0';
    // input_expression[input_size - 1] = '\0';
    gtk_entry_set_text(input_expression, (const gchar *)in_string);
  }
}

void calculateClicked() {
  setlocale(LC_NUMERIC, "C");
  int err = 0;
  double result_digit = 0.0;
  double x = 1.0;
  char x_num[512] = {'\0'};
  char input_string[512] = {'\0'};
  char polish_string[512] = {'\0'};
  char result_string[512] = {'\0'};

  strcpy(input_string, gtk_entry_get_text(input_expression));
  strcat(input_string, "\n");
  strcpy(x_num, gtk_entry_get_text(input_x));

  if (strstr(input_string, "x") && (strcmp(x_num, "\0") ? 1 : 0) &&
      !get_num(x_num) && check_correct_input(x_num))
    x = atof(x_num);
  else {
    // printf("strcmp: %d\n", strcmp(input_string, "x"));
    // printf("!get_num: %d\n", !get_num(x_num));
    // printf("check_correct_input: %d\n", check_correct_input(x_num));
    err = 1;
    gtk_label_set_text(GTK_LABEL(label_result),
                       "----------ERROR IN X VALUE---------");
  }
  if (!err) {
    queue q_in;
    queue q_polish;

    StackElement *s_in = NULL;
    StackElement *s_pol = NULL;

    init_queue(&q_in);
    init_queue(&q_polish);

    result_digit = back_process(input_string, polish_string, x, &q_in,
                                &q_polish, s_in, s_pol, &err);
    if (!err) {
      sprintf(result_string, "%f", result_digit);
      gtk_label_set_text(GTK_LABEL(label_result), result_string);
    } else
      gtk_label_set_text(GTK_LABEL(label_result), "----------ERROR---------");
    freeStack(s_in);
    freeStack(s_pol);
  }
}

int calculateForGraph(double x, double *result) {
  setlocale(LC_NUMERIC, "C");
  int err = 0;

  char input_string[512] = {'\0'};
  char polish_string[512] = {'\0'};

  strcpy(input_string, gtk_entry_get_text(input_expression));
  strcat(input_string, "\n");

  queue q_in;
  queue q_polish;
  StackElement *s_in = NULL;
  StackElement *s_pol = NULL;

  init_queue(&q_in);
  init_queue(&q_polish);

  *result = back_process(input_string, polish_string, x, &q_in, &q_polish, s_in,
                         s_pol, &err);
  if (err)
    gtk_label_set_text(GTK_LABEL(label_result), "----------ERROR---------");
  freeStack(s_in);
  freeStack(s_pol);
  return err;
}

void numbtnClicked(GtkButton *button) {
  const gchar *text = gtk_button_get_label(button);
  char in_string[512] = {'\0'};
  strcat(in_string, gtk_entry_get_text(input_expression));
  strcat(in_string, text);
  gtk_entry_set_text(input_expression, (const gchar *)in_string);
}

void funcbtnClicked(GtkButton *button) {
  const gchar *text = gtk_button_get_label(button);
  char in_string[512] = {'\0'};
  strcat(in_string, gtk_entry_get_text(input_expression));
  strcat(in_string, text);
  gtk_entry_set_text(input_expression, (const gchar *)in_string);
}

int button_draw_graph_clicked_cb() {
  char in_string[512] = {'\0'};
  strcat(in_string, gtk_entry_get_text(input_expression));
  strcat(in_string, "\n");

  //   GtkWidget *da;
  GtkBuilder *builder;
  //   GtkWidget *close_button;
  //   GtkWidget *draw_button;
  //   GtkEntry *graph_entry = NULL;
  GtkWidget *graph_window;

  builder = gtk_builder_new_from_file("UI/graph_gui.glade");
  //   gtk_builder_connect_signals(builder, NULL);

  graph_window = GTK_WIDGET(gtk_builder_get_object(builder, "graph_window"));
  drawing_area = GTK_WIDGET(gtk_builder_get_object(builder, "graph_da"));
  //   draw_button =
  //       GTK_WIDGET(gtk_builder_get_object(builder, "graph_draw_button"));

  //   domain_max_spin =
  //       GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_domain_max"));
  //   codomain_max_spin =
  //       GTK_WIDGET(gtk_builder_get_object(builder,
  //       "graph_spin_codomain_max"));
  //   domain_min_spin =
  //       GTK_WIDGET(gtk_builder_get_object(builder, "graph_spin_domain_min"));
  //   codomain_min_spin =
  //       GTK_WIDGET(gtk_builder_get_object(builder,
  //       "graph_spin_codomain_min"));

  //   gtk_entry_set_text(graph_entry, (const gchar *)in_string);
  gtk_widget_set_size_request(drawing_area, 600,
                              600);  // size in pixels

  g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(on_draw), NULL);
  //   g_signal_connect(G_OBJECT(draw_button), "clicked",
  //                    G_CALLBACK(button_draw_clicked), G_OBJECT(graph_entry));
  //   g_signal_connect(G_OBJECT(close_button), "clicked",
  //   G_CALLBACK(close_window),
  //                    G_OBJECT(graph_window));

  g_object_unref(builder);
  gtk_window_set_position(GTK_WINDOW(graph_window), GTK_WIN_POS_CENTER);
  gtk_widget_show_all(graph_window);

  return 0;
}

gboolean on_draw(GtkWidget *widget, cairo_t *cairo) {
  if (!widget) printf(" ");
  s_graph_properties gp = {'\0'};
  double x_middle;
  double y_middle;
  double x_range;
  double y_range;
  double y_value;
  int err = 0;
  gp.cr = cairo;

  cairo_set_source_rgb(gp.cr, 0.69, 0.91, 0.91);
  cairo_paint(gp.cr);
  cairo_device_to_user_distance(gp.cr, &gp.dx, &gp.dy);

  char x_min_graph_num[512] = {'\0'};
  char x_max_graph_num[256] = {'\0'};
  char y_min_graph_num[256] = {'\0'};
  char y_max_graph_num[256] = {'\0'};

  strcpy(x_min_graph_num, gtk_entry_get_text(x_min_input));
  strcpy(x_max_graph_num, gtk_entry_get_text(x_max_input));
  strcpy(y_min_graph_num, gtk_entry_get_text(y_min_input));
  strcpy(y_max_graph_num, gtk_entry_get_text(y_max_input));

  if (!get_num(x_min_graph_num) && !get_num(x_max_graph_num) &&
      !get_num(y_min_graph_num) && !get_num(y_max_graph_num) &&
      check_correct_input(x_min_graph_num) &&
      check_correct_input(x_max_graph_num) &&
      check_correct_input(y_min_graph_num) &&
      check_correct_input(y_max_graph_num)) {
    gp.max_x = atof(x_max_graph_num);
    gp.max_y = atof(y_max_graph_num);
    gp.min_x = atof(x_min_graph_num);
    gp.min_y = atof(y_min_graph_num);
    // printf("x_min: %lf, x_max: %lf, y_min: %lf, y_max: %lf\n", gp.min_x,
    //        gp.max_x, gp.min_y, gp.max_y);
  } else {
    err = 1;
    gtk_label_set_text(GTK_LABEL(label_result),
                       "----ERROR IN INPUT X OR Y RANGE----");
  }

  //   gp.max_x = 10;
  //   gp.max_y = 100;
  //   gp.min_x = -10;
  //   gp.min_y = -1;

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
  if (!err && !calculateForGraph((gp.max_x - gp.min_x) / 2, &y_value)) {
    /* Draw on a background */

    /* max value is always positive, min value is always negative */
    gp.right_limit = gp.min_x > gp.min_y ? gp.min_y : gp.min_x;
    gp.left_limit = gp.max_x < gp.max_y ? gp.max_y : gp.max_x;
    /* inverting Y axes*/
    gp.lower_limit = -gp.max_y > -gp.max_x ? -gp.max_x : -gp.max_y;
    gp.upper_limit = -gp.min_y < -gp.min_x ? -gp.min_x : -gp.min_y;

    x_range = gp.left_limit - gp.right_limit;
    y_range = gp.upper_limit - gp.lower_limit;

    /* Pixels between each point, has to be same */
    gp.dx = (x_range) / 600;
    gp.dy = (x_range) / 600;

    x_middle = (fabs(gp.right_limit) / (x_range)) * 600;
    y_middle = (fabs(gp.lower_limit)) / (y_range)*600;

    cairo_translate(gp.cr, x_middle, y_middle);

    cairo_scale(gp.cr, 1 / gp.dx, 1 / gp.dy);

    draw_axis(&gp);

    draw_graph_line(&gp);

    // //   if (input_validation(expression) == S21_CORRECT_INPUT) {
    // printf("In string from on_draw %s\n",
    // gtk_entry_get_text(input_expression)); if
    // (gtk_entry_get_text(input_expression)) {
    //     char buffer[64];
    //     if (gp.dx < 1)
    //     sprintf(buffer, "scale px/unit: %.4g/%g", 1 / gp.dx, 1.0);
    //     else
    //     sprintf(buffer, "scale px/unit: %g/%.4g", 1.0, gp.dx);
    //     gtk_label_set_text(GTK_LABEL(label_result), buffer);
    //     draw_graph_line(&gp);
    // } else {
    //     gtk_label_set_text(GTK_LABEL(label_result),
    //                     (const gchar *)"INCORRECT INPUT");
    // }
  } else {
    gtk_label_set_text(GTK_LABEL(label_result),
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
    gdouble y_value;
    calculateForGraph(x, &y_value);
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

// void button_draw_clicked(GtkWidget *button, gpointer entry) {
//   printf("from button_draw_clicked");
//   //   sprintf(expression, "%s", gtk_entry_get_text(entry));
//   gtk_widget_queue_draw(drawing_area);
// }

// void close_window(GtkWidget *widget, gpointer window) {
//   gtk_widget_destroy(GTK_WIDGET(window));
// }

// void check_same_dom_codom_toggled_cb(GtkCheckButton *button) {
//   gboolean status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
//   if (status) {
//     dom_is_eq_to_codom = 1;
//     gtk_widget_set_sensitive(codomain_max_spin, FALSE);
//     gtk_widget_set_sensitive(codomain_min_spin, FALSE);
//   } else {
//     dom_is_eq_to_codom = 0;
//     gtk_widget_set_sensitive(codomain_max_spin, TRUE);
//     if (!max_is_eq_to_min) gtk_widget_set_sensitive(codomain_min_spin, TRUE);
//   }
// }

// void check_same_max_min_toggled_cb(GtkCheckButton *button) {
//   gboolean status = gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(button));
//   if (status) {
//     max_is_eq_to_min = 1;
//     gtk_widget_set_sensitive(domain_min_spin, FALSE);
//     gtk_widget_set_sensitive(codomain_min_spin, FALSE);
//   } else {
//     max_is_eq_to_min = 0;
//     gtk_widget_set_sensitive(domain_min_spin, TRUE);
//     if (!dom_is_eq_to_codom) gtk_widget_set_sensitive(codomain_min_spin,
//     TRUE);
//   }
// }