#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QToolBar>
#include <QStatusBar>
#include <QTextEdit>
#include <QLabel>
#include <QDebug>
#include <QTabWidget>
#include <QFileDialog>
#include <QColorDialog>
#include <QFontDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QKeyEvent>
#include <QDateTime>
#include <QTextCodec>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void FileNew();
    void FileOpen();
    void FileSave();
    void FileSaveas();
    void FileCopy();
    void FilePaste();
    void FileRevoke();
    void FileFind();
    void FileCount();


private:
    QTextEdit *MyText;
    QString fileName;       //文件路径
    int x;                  //横坐标
    int y;                  //纵坐标

    //计数
    int LetterNum;
    int SpaceNum;
    int NumberNum;

    //菜单栏
    QMenuBar *mbar; //获取QMenuBar对象
    QMenu *file;
    QMenu *edit;
    QMenu *tool;

    QAction *file_new;
    QAction *file_open;
    QAction *file_save;
    QAction *file_saveas;
    QAction *file_copy;
    QAction *file_paste;
    QAction *file_revoke;
    QAction *file_find;
    QAction *file_count;
};

#endif // MAINWINDOW_H
