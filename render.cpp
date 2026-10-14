#include "render.h"
#include "ui_mainwindow.h"

Render::Render(QTableWidget *table, QMainWindow *wt): table(table), w(wt) {
}//mainWindow: width, height

void Render::initTable(int x, int y, int8_t theme){
    table->setStyleSheet("");

    table->verticalHeader()->hide();
    table->horizontalHeader()->hide();

    table->setShowGrid(false);
    table->setFrameShape(QFrame::NoFrame);
    table->setLineWidth(0);
    table->setMidLineWidth(0);



    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setFocusPolicy(Qt::NoFocus);
    //table->setSelectionMode(QAbstractItemView::NoSelection);


    const int size = w->size().width()/100;

    table->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->verticalHeader()->setMinimumSectionSize(size);
    table->verticalHeader()->setDefaultSectionSize(size);
    cout << "Size: " << size << endl;

    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    table->horizontalHeader()->setMinimumSectionSize(size);
    table->horizontalHeader()->setDefaultSectionSize(size);

    QFont font("monospace");
    font.setStyleHint(QFont::Monospace);
    font.setPixelSize(size * 0.85);
    table->setFont(font);

    setTable(x, y, theme);
}

void Render::setTable(int x, int y, int8_t theme){

    table->setColumnCount(x);
    table->setRowCount(y);

    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            if (!table->item(i, j))
                table->setItem(i, j, new QTableWidgetItem());
            this->applyTheme(table->item(i, j), 0, theme);
        }
    }

    table->setFixedSize(0.8 * w->width(), 0.8 * w->height());
}

void Render::renderMap(int x, int y, int8_t theme, const vector<vector<int8_t>>& matrix){
    cout << QString::number(matrix.size()).toStdString() << endl;
    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            if (!table->item(i, j))
                table->setItem(i, j, new QTableWidgetItem());
            if (i < matrix.size() && matrix.size() >= 1 && matrix[0].size() > j){
                applyTheme(table->item(i, j), matrix[i][j], theme);//still got a huge problem, this never runs
                //cout << "k" << endl;
            }
            else{
                applyTheme(table->item(i, j), 0, theme);
                //cout << "unsiccesful" << endl;
            }
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
