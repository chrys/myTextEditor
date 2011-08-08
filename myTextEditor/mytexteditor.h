#ifndef MYTEXTEDITOR_H
#define MYTEXTEDITOR_H

#include <QMainWindow>

namespace Ui {
    class myTextEditor;
}

class myTextEditor : public QMainWindow
{
    Q_OBJECT

public:
    explicit myTextEditor(QWidget *parent = 0);
    ~myTextEditor();

private:
    Ui::myTextEditor *ui;
};

#endif // MYTEXTEDITOR_H
