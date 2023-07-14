//Подключаем заголовочные файлы gtk
#include <gtk/gtk.h>
#include <string.h>

typedef struct input_string {
    char data[256];
    int position;
} input_string;

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

G_MODULE_EXPORT void onOneClicked(GtkButton * btn, input_string * is) {   
    strcpy(&is->data[is->position], "1 ");
    is->position += 2;
    // printf("string: %s\n", is->data);
    // printf("from one_clicked\n");
}

void onTwoClicked(GtkButton * btn, input_string * is) {   
    strcpy(&is->data[is->position], "2 ");
    is->position += 2;
    // printf("string: %s\n", is->data);
    printf("from two_clicked\n");
}

void onThreeClicked(GtkButton * btn, input_string * is) {   
    strcpy(&is->data[is->position], "3 ");
    is->position += 2;
    // printf("string: %s\n", is->data);
    // printf("from one_clicked\n");
}

void onEqClicked(GtkButton * btn, input_string * is) {   
    // strcpy(&is->data[is->position], "1 ");
    // is->position += 2;
    printf("string: %s\n", is->data);
    // printf("from one_clicked\n");
}

//Главная функция
int main(int argc, char * argv[]) {
    //Инициализация gtk
    char in_string[256]={'\0'};
    // int j = 0;
    input_string is;
    strcpy(is.data, in_string);
    is.position = 0;

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

    GtkButton * one_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder, "one_btn"));
    GtkButton * two_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder, "two_btn"));
    GtkButton * three_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder, "three_btn"));
    GtkButton * eq_btn = GTK_BUTTON(gtk_builder_get_object(ui_builder, "eq_btn"));
    
    g_signal_connect(G_OBJECT(one_btn), "clicked", G_CALLBACK(onOneClicked), &is);
    g_signal_connect(G_OBJECT(two_btn), "clicked", G_CALLBACK(onTwoClicked), &is);
    g_signal_connect(G_OBJECT(three_btn), "clicked", G_CALLBACK(onThreeClicked), &is);
    g_signal_connect(G_OBJECT(eq_btn), "clicked", G_CALLBACK(onEqClicked), &is);


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