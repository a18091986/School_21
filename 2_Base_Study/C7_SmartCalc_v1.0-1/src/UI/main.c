//Подключаем заголовочные файлы gtk
#include <gtk/gtk.h>
#include <string.h>
char input_string[256];
int j = 0;



// Слот выхода из программы
G_MODULE_EXPORT void onExit(GtkWidget * w) {
    gtk_main_quit();
}

// Слот нажатия на кнопку
G_MODULE_EXPORT void onBtnClicked(GtkButton * btn, gpointer data) {
    //Просто меняем надпись на кнопке
    gtk_button_set_label(GTK_BUTTON(btn), "Woof");
    printf("from btn_clicked\n");
}

// G_MODULE_EXPORT void onOneClicked(GtkButton * btn, gpointer data, int * j) {
void onOneClicked(GtkButton * btn, int * j) {
    //Просто меняем надпись на кнопке
    // gtk_button_set_label(GTK_BUTTON(btn), "Woof");
    // strcpy(input_string[j], "1 ");
    // (*j)+=2;
    // printf("j: %s\n", (char *)data);
    printf("j: %d\n", *j);
    (*j)++;
    printf("from one_clicked\n");
}

// G_MODULE_EXPORT void onTwoClicked(GtkButton * btn, gpointer data, char * input_string, int * j) {
//     //Просто меняем надпись на кнопке
//     // gtk_button_set_label(GTK_BUTTON(btn), "Woof");
//     strcpy(input_string[j], "2 ");
//     *j += 2;
//     printf("from two_clicked\n");
// }

// G_MODULE_EXPORT void onThreeClicked(GtkButton * btn, gpointer data, char input_string[256], int * j) {
//     //Просто меняем надпись на кнопке
//     // gtk_button_set_label(GTK_BUTTON(btn), "Woof");
//     strcpy(input_string[&j], "3 ");
//     *j += 2;
//     printf("from three_clicked\n");
// }

// G_MODULE_EXPORT void onEqualClicked(GtkButton * btn, gpointer data, char * input_string, int * j) {
//     //Просто меняем надпись на кнопке
//     // gtk_button_set_label(GTK_BUTTON(btn), "Woof");
//     printf("Input_string: %s\n", input_string);
//     printf("from btn_clicked\n");
// }

//Главная функция
int main(int argc, char * argv[]) {
    //Инициализация gtk
    // char input_string[256];
    int j = 0;


    printf("from main\n");
    gtk_init(&argc, &argv);
    
   
    // Этот объект будет считывать данные из формы
    // и создавать интерфейс на их основе
    GtkBuilder * ui_builder;
    // Если будут какие-либо ошибки, то они появятся здесь
    GError * err = NULL;

    // Инициализируем GtkBuilder
    ui_builder = gtk_builder_new();
    //Загрузка файла с UI в GtkBuilder
    if(!gtk_builder_add_from_file(ui_builder, "UI.glade", &err)) {
        g_critical ("Не вышло загрузить файл с UI : %s", err->message);
        g_error_free (err);
    }

    //Теперь получаем виджет из Builder
    // Помните мы указывали ID? Вот по нему мы и ищем нужный
    // В данном случае ищем виджет окна
    GtkWidget * window = GTK_WIDGET(gtk_builder_get_object(ui_builder, "main_window"));
    // GtkWidget * one_btn = GTK_WIDGET(gtk_builder_get_object(ui_builder, "onOneClicked"));
    GtkButton * one_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder, "one_btn"));
    
    // g_signal_connect(GTK_BUTTON(one_btn), "clicked", G_CALLBACK(onOneClicked), &j);
    // g_signal_connect(G_OBJECT(one_btn), "clicked", G_CALLBACK(onOneClicked), &j);
    g_signal_connect(G_OBJECT(one_btn), "clicked", G_CALLBACK(onOneClicked), &j);

    //Таким же образом можно получить и другие виджеты
    // но нам они не понадобятся

    //Подключаем сигналы)
    // gtk_builder_connect_signals(ui_builder, NULL);

    // Разрешаем отображение
    gtk_widget_show_all(window);

    //Пошла программа
    gtk_main();

    return 0;
}