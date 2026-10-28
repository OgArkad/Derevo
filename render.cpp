#include "render.h"
#include "ui_mainwindow.h"

/// @brief This class contains the table's important functions
/// @param table The table, to handle (usually ui->Table)
/// @param wt the QMainWindow to work with
Render::Render(QTableWidget *table, QMainWindow *wt): table(table), w(wt) {
}//mainWindow: width, height

/// @brief This should only run once. It sets up the table, sets it's properties.
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
void Render::initTable(int x, int y, int8_t theme){
    table->setContentsMargins(0, 0, 0, 0);

    const int size = w->width()/x;

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setMinimumSectionSize(size);
    table->verticalHeader()->setDefaultSectionSize(size);
    std::cout << "Size: " << size << std::endl;

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setMinimumSectionSize(size);
    table->horizontalHeader()->setDefaultSectionSize(size);

    table->setFixedSize(x * size, y * size);

    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(size * 0.85);
    table->setFont(font);

    setTable(x, y, theme);
}

/// @brief Resizes the table, and recolors it
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
void Render::setTable(int x, int y, int8_t theme){
    table->setColumnCount(x);
    table->setRowCount(y);

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            if (!table->item(i, j)) table->setItem(i, j, new QTableWidgetItem());

            this->applyTheme(table->item(i, j), 0, theme);
        }
    }

    table->setFixedSize(0.8 * w->width(), 0.8 * w->height());
}

/// @brief Renders the whole table/map
/// @param x count of columns
/// @param y count of rows
/// @param theme the theme to set up
/// @param matrix the matrix, on wich it is based
void Render::renderMap(int x, int y, int8_t theme, const std::vector<std::vector<int8_t>>& matrix){
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (!table->item(i, j)) table->setItem(i, j, new QTableWidgetItem("0", 0));
            if (i < matrix.size() && matrix.size() >= 1 && matrix[0].size() > j) applyTheme(table->item(i, j), matrix[i][j], theme);
            else applyTheme(table->item(i, j), 0, theme);
        }
    }
}

/// @brief Sets a cell's value, and color
/// @param item the table cell
/// @param val the value that shoul be written in the cell you probably want to set it to 0 or 1
/// @param theme a theme from 0-4
void Render::applyTheme(QTableWidgetItem *item, int8_t val, int8_t theme){
    if (item == nullptr) return;
    item->setText(QString::number(val));
    switch(theme){
    case 0://normal
        if (val == 0){
            item->setBackground(QBrush(QColor("#71d1f1")));
            item->setForeground(QBrush(QColor("#71d1f1")));
        }else{
            item->setBackground(QBrush(QColor("#00d800")));
            item->setForeground(QBrush(QColor("#00d800")));
        }
        break;
    case 1://values
        if (val == 0){
            item->setBackground(QBrush(QColor("#000000")));
            item->setForeground(QBrush(QColor("#FFFFFF")));
        }else{
            item->setBackground(QBrush(QColor("#FFFFFF")));
            item->setForeground(QBrush(QColor("#000000")));
        }
        break;
    case 2://night
        if (val == 0){
            item->setBackground(QBrush(QColor("#00008b")));
            item->setForeground(QBrush(QColor("#00008b")));
        }else{
            item->setBackground(QBrush(QColor("#013220")));
            item->setForeground(QBrush(QColor("#013220")));
        }
        break;
    case 3://monochrome
        if (val == 0){
            item->setBackground(QBrush(QColor("#FFFFFF")));
            item->setForeground(QBrush(QColor("#FFFFFF")));
        }else{
            item->setBackground(QBrush(QColor("#000000")));
            item->setForeground(QBrush(QColor("#000000")));
        }
        break;
    case 4://debug
        item->setBackground(QBrush(QColor("#999999")));
        item->setForeground(QBrush(QColor("#FF0000")));
        break;
    default:
        throw new std::range_error("Unexpected theme: " + theme);
    }
}
