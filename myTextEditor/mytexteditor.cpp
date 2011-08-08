#include "mytexteditor.h"
#include "ui_mytexteditor.h"

myTextEditor::myTextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myTextEditor)
{
    ui->setupUi(this);
}

myTextEditor::~myTextEditor()
{
    delete ui;
}
