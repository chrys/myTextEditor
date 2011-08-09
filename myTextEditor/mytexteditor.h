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

private slots:
    //menu options
    void newFile();
    bool save();
    bool saveAs();
    void cut();
    void copy();
    void paste();
    void selectAll();

private:
    Ui::myTextEditor *ui;
    QString currentFile;

    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;

    void createMenus();
    void setCurrentFile(const QString &fileName);
    bool saveFile(const QString &fileName);

};

#endif // MYTEXTEDITOR_H
