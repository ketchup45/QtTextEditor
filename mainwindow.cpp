#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    /* 设置标题栏 */
    this->setWindowTitle("TextEditor");
    /* 设置菜单栏 */
    mbar = menuBar(); //获取QMenuBar对象
    file = new QMenu("文件");
    edit = new QMenu("编辑");
    tool = new QMenu("工具");

    file_new = new QAction("新建文件");
    file_open = new QAction("打开文件");
    file_save = new QAction("保存文件");
    file_saveas = new QAction("另存为");
    file_copy = new QAction("复制");
    file_paste = new QAction("粘贴");
    file_revoke = new QAction("撤销");
    file_find = new QAction("查找");
    file_count = new QAction("统计字符");

    mbar->addMenu(file);        //向QMenuBar添加menu
    mbar->addMenu(edit);
    mbar->addMenu(tool);

    file->addAction(file_new);  //向QMenu添加action
    file->addAction(file_open);
    file->addAction(file_save);
    file->addAction(file_saveas);

    edit->addAction(file_copy);
    edit->addAction(file_paste);
    edit->addAction(file_revoke);

    tool->addAction(file_find);
    tool->addAction(file_count);

    //初始化
    LetterNum = 0;
    SpaceNum = 0;
    NumberNum = 0;

    //设定大小
    MyText = new QTextEdit;
    this->setCentralWidget(MyText);
    this->setMinimumSize(400,300);      //最小大小
    this->resize(800,600);              //默认大小

    /* 连接action与槽函数 */
    connect(file_new,SIGNAL(triggered(bool)),this,SLOT(FileNew()));
    connect(file_open,SIGNAL(triggered(bool)),this,SLOT(FileOpen()));
    connect(file_save,SIGNAL(triggered(bool)),this,SLOT(FileSave()));
    connect(file_saveas,SIGNAL(triggered(bool)),this,SLOT(FileSaveas()));
    connect(file_copy,SIGNAL(triggered(bool)),this,SLOT(FileCopy()));
    connect(file_paste,SIGNAL(triggered(bool)),this,SLOT(FilePaste()));
    connect(file_find,SIGNAL(triggered(bool)),this,SLOT(FileFind()));
    connect(file_revoke,SIGNAL(triggered(bool)),this,SLOT(FileRevoke()));
    connect(file_count,SIGNAL(triggered(bool)),this,SLOT(FileCount()));

    //快捷键
    file_new->setShortcut(QKeySequence(QLatin1String("Ctrl+n"))); //新建
    file_open->setShortcut(QKeySequence(QLatin1String("Ctrl+o"))); //打开
    file_save->setShortcut(QKeySequence(QLatin1String("Ctrl+s"))); //保存
    file_copy->setShortcut(QKeySequence(QLatin1String("Ctrl+c"))); //复制
    file_paste->setShortcut(QKeySequence(QLatin1String("Ctrl+v"))); //粘贴
    file_find->setShortcut(QKeySequence(QLatin1String("Ctrl+f"))); //查找
    file_revoke->setShortcut(QKeySequence(QLatin1String("Ctrl+z"))); //撤销
}

void MainWindow::FileNew()
{
    x = this->geometry().x() + 30;
    y = this->geometry().y() + 30;
    MainWindow *NewWin;               //新窗口
    NewWin = new MainWindow;
    NewWin->setWindowTitle("*NewText");
    NewWin->move(x,y);
    NewWin->show();
}

void MainWindow::FileOpen()                 //打开文件
{
    fileName = QFileDialog::getOpenFileName(this, tr("Open File"),QDir::currentPath()); //获取路径
    QFile *file=new QFile;
    file->setFileName(fileName);
    bool IsOpen = file->open(QIODevice::ReadOnly);      //只读打开
    if(IsOpen) {
          QTextStream in(file);
          MyText->setText((in.readAll().toUtf8()));
          file->close();
    }
    delete file;
}

void MainWindow::FileSave()                 //保存文件
{
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool IsOpen = file->open(QIODevice::WriteOnly);     //只写打开
    if(IsOpen) {
        QString content = MyText->toPlainText();//这里是取出textEdit当中的纯文本
        QTextStream WriteToFile(file); //写入文件路径
        WriteToFile<<content;             //写入内容
        file->close();
    }
    delete file;
}


void MainWindow::FileSaveas()               //另存为
{
    QString fileName = QFileDialog::getSaveFileName(this,"Save File",QDir::currentPath()); //获取路径
    QFile *file = new QFile;
    file->setFileName(fileName);
    bool IsOpen = file->open(QIODevice::WriteOnly);     //只写打开
    if(IsOpen)
    {
        QString TempText = MyText->toPlainText();//这里是取出textEdit当中的纯文本
        QTextStream writefiletext(file); //写入文件路径
        writefiletext<<TempText;             //写入内容
        file->close();
    }
    delete file;
}

void MainWindow::FileCopy()
{
    MyText->copy();				//拷贝
}

void MainWindow::FilePaste()
{
    MyText->paste();			//粘贴
}

void MainWindow::FileRevoke()
{
    MyText->undo();			//撤销
}

void MainWindow::FileFind()
{
    MyText->moveCursor(QTextCursor::Start, QTextCursor::MoveAnchor);

    bool IsOk;
    QString ObjectString = QInputDialog::getText(this, tr("查找"),
                                         tr("请输入字符串："), QLineEdit::Normal,
                                         QDir::home().dirName(), &IsOk);

   int sum = 0;
   bool index = true;
   if(ObjectString != "") {                  //判断输入是否为空
       while(index)                  //循环查找
       {
           bool Found = MyText->find(ObjectString);	//查找
           if(Found == 1)
               sum++;               //数量++
           else
               index = false;
           if(Found == 0 && sum == 0){
               QMessageBox::warning(this,"查找",tr("查找不到%1").arg(ObjectString));
               return;
           }
       }
       QMessageBox::information(nullptr, "查找完成", tr("字符串数量为%1").arg(sum), QMessageBox::Yes);
   }
}

void MainWindow::FileCount()
{
    QString content = MyText->toPlainText();
    int StrLen = content.length();
    int i = 0; //当前读取到的字符位置
    while(i != StrLen){
        if(content[i] == ' ')
            SpaceNum++;
        else if(content[i].isNumber())
            NumberNum++;
        else if(content[i].isLetter())
            LetterNum++;
        i++;
    }
    QMessageBox::information(nullptr, "统计完成",
                                 "文字数量为" + QString::number(LetterNum) +
                             "\n\n数字数量为" + QString::number(NumberNum) +
                             "\n\n空格数量为" + QString::number(SpaceNum));
    SpaceNum = NumberNum = LetterNum = 0;//清零
}

MainWindow::~MainWindow()
{
    delete MyText;
    delete file;
    delete edit;
    delete tool;

    delete file_new;
    delete file_open;
    delete file_save;
    delete file_saveas;
    delete file_copy;
    delete file_paste;
    delete file_revoke;
    delete file_find;
    delete file_count;

}
