#include <QtGui>
#include "mytexteditor.h"
#include "ui_mytexteditor.h"

myTextEditor::myTextEditor(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myTextEditor)
{
    ui->setupUi(this);
    setCentralWidget(ui->textEdit);
    createMenus();
}

myTextEditor::~myTextEditor()
{
    delete ui;
}

/*
Have to create my own connection since Qt4 does not support custom slots.
*/
void myTextEditor::createMenus()
{
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(newFile()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSave_As, SIGNAL(triggered()), this, SLOT(saveAs()));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionCopy, SIGNAL(triggered()), this, SLOT(copy()));
    connect(ui->actionCut, SIGNAL(triggered()), this, SLOT(cut()));
    connect(ui->actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
    connect(ui->actionSelect_All, SIGNAL(triggered()), this, SLOT(selectAll()));
}

void myTextEditor::newFile()
{

    setCurrentFile("");
}

void myTextEditor::setCurrentFile(const QString &fileName)
{
    currentFile = fileName;

    setWindowTitle(tr("%1[*] - %2").arg("Untitled")
                   .arg(tr("File")));

}

bool myTextEditor::save()
{
    if(ui->textEdit->toPlainText().trimmed().isEmpty())
    {
        statusBar()->showMessage(tr("Cannot save an empty document."));
    }
    else
    {
        if(currentFile.isEmpty())
        {
            return saveAs();
        }
        else
            return saveFile(currentFile);
    }
}

bool myTextEditor::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this,
                                                    tr("Save File"), ".",
                                                    tr("myTextEditor files (*.txt)"));
    if (fileName.isEmpty())
        return false;

    return saveFile(fileName);
}

bool myTextEditor::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
    {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    else
    {
        QTextStream out(&file);
        QApplication::setOverrideCursor(Qt::WaitCursor);
        out << ui->textEdit->toPlainText();
        QApplication::restoreOverrideCursor();

        setCurrentFile(fileName);
        statusBar()->showMessage(tr("File saved"), 2000);
        setWindowTitle(fileName);
        return true;
    }

}

void myTextEditor::copy()
{
    ui->textEdit->copy();
}

void myTextEditor::paste()
{
    ui->textEdit->paste();
}

void myTextEditor::cut()
{
    ui->textEdit->cut();
}

void myTextEditor::selectAll()
{
    ui->textEdit->selectAll();
}

void myTextEditor::open()
{
    // getOpenFileName() is a convenient function that obtains
    // a new file name from the user.
    QString fileName = QFileDialog::getOpenFileName(this, // parent widget
                                                    tr("Open Text File"),  // title
                                                    ".", //start from current directory
                                                    tr("Text files (*.*)")); //file filters
    if (!fileName.isEmpty())
        loadFile(fileName);
}

bool myTextEditor::loadFile(const QString &fileName)
{

    //file to be loaded
    QFile file(fileName);

    //try to open it in ReadOnly mode
    if (!file.open(QIODevice::ReadOnly))
    {
        //failed for some reason
        QMessageBox::warning(this, tr("myTextEditor"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(file.fileName())
                             .arg(file.errorString()));
        statusBar()->showMessage(tr("Loading canceled"), 2000);
        return false;
    }
    else
    {
        //QTextStream class provides a convenient interface for
        //reading and writing text.
        QTextStream in(&file);
        //set the hour glass
        QApplication::setOverrideCursor(Qt::WaitCursor);

        ui->textEdit->setPlainText(in.readAll());

        //restore the cursor
        QApplication::restoreOverrideCursor();

        statusBar()->showMessage(tr("File loaded"), 2000); //display a message in the status bar
        // for 2 seconds
        return true;
    }
}
