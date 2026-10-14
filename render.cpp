#include "render.h"
#include "ui_mainwindow.h"

Render::Render(QTableWidget *table, QMainWindow *wt): table(table), w(wt) {
}//mainWindow: width, height

void Render::initTable(int x, int y, int8_t theme){
    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    table->setShowGrid(false);
    table->setFrameShape(QFrame::NoFrame);
    table->setLineWidth(0);
    table->setMidLineWidth(0);

    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    //table->setSelectionMode(QAbstractItemView::NoSelection);


    const int size = w->size().width()/150;

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setMinimumSectionSize(size);
    table->verticalHeader()->setDefaultSectionSize(size);
    cout << "Size: " << size << endl;

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setMinimumSectionSize(size);
    table->horizontalHeader()->setDefaultSectionSize(size);
    setTable(x, y, theme);
}

void Render::setTable(int x, int y, int8_t theme){

    table->setColumnCount(x);
    table->setRowCount(y);

    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) {
            if (!table->item(i, j))
                table->setItem(i, j, new QTableWidgetItem());
            this->applyTheme(table->item(i, j), 0, theme);
        }
    }

    table->setFixedSize(0.7 * w->width(), 0.7 * w->width());
}

void Render::renderMap(int x, int y, int8_t theme, vector<vector<int8_t>> matrix){

    table->setStyleSheet("");
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            if (!table->item(i, j))
                table->setItem(i, j, new QTableWidgetItem());
            if (i < matrix.size() && matrix.size() >= 1 && matrix[0].size() > j)
                applyTheme(table->item(i, j), matrix[i][j], theme);
            else
                applyTheme(table->item(i, j), 0, theme);
        }
    }
}

void Render::applyTheme(QTableWidgetItem *item, int8_t val, int8_t theme){
    if (item == nullptr) return;
    item->setText(QString::number(val));
    cout << val << " ";
    switch(theme){
    case 0://normal
        if (val == 0){
            item->setBackground(QBrush(QColor("lightblue")));
            item->setForeground(QBrush(QColor("lightblue")));
        }else{
            item->setBackground(QBrush(QColor("green")));
            item->setForeground(QBrush(QColor("green")));
        }
        break;
    case 1://values
        if (val == 0){
            item->setBackground(QBrush(QColor("black")));
            item->setForeground(QBrush(QColor("white")));
        }else{
            item->setBackground(QBrush(QColor("white")));
            item->setForeground(QBrush(QColor("black")));
        }
        break;
    case 2://monochrome
        if (val == 0){
            item->setBackground(QBrush(QColor("white")));
            item->setForeground(QBrush(QColor("white")));
        }else{
            item->setBackground(QBrush(QColor("black")));
            item->setForeground(QBrush(QColor("black")));
        }
        break;
    case 3://debug
        item->setBackground(QBrush(QColor("darkgray")));
        item->setForeground(QBrush(QColor("red")));
        break;
    default:
        cout << "Unexpected theme:" << theme << endl;
        break;
    }
}
