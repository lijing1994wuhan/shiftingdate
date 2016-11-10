/*Author:Jing Li,Yang Bai

  link functions and buttons, tell buttons what they should do when they are clicked.

*/
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>

MainWindow::MainWindow(createassignmentcontroller *controller,QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_controller(controller)
{ /*
     * We use Q_ASSERT to check the dependencies we received.
     */
    Q_ASSERT(controller!=nullptr);
    ui->setupUi(this);

    setupConnections();
    /*
     * Finally, we can also alter the create UI items a bit, e.g. by setting some custom shortcuts
     * for menu items.
     *
     * Note: Setting shortcuts can also be done in the designer, but sometimes it makes sense
     * to set stuff in C++ instead.
     */
    ui->actionAdd->setShortcut( QKeySequence::New );
    ui->actionEdit->setShortcut( tr( "Ctrl+E" ) );
    ui->actionRemove->setShortcut( QKeySequence::Delete );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createEntry()
{
    auto entry=m_controller->createEntry();
    if(entry){
        ui->listWidget->addItem(entry->name());
        auto listItem=ui->listWidget->item(ui->listWidget->count()-1);
        m_entryMap.insert(listItem,entry);

    }
}

void MainWindow::deleteEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          if(m_controller->deleteEntry(entry)){
              m_entryMap.remove(listItem);
              delete listItem;
          }
        }
    }

}

void MainWindow::editEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          ui->stackedWidget->setCurrentWidget(ui->detailpage);
          ui->menuEntries->setEnabled(false);
          resetEntry();
        }
    }
}

void MainWindow::saveEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          entry->setName(ui->nameEdit->text());
          entry->setTheme(ui->themeEdit->text());
          entry->setExpirationdate(ui->expirationdateEdit->dateTime());
          entry->setAssignment(ui->assignmentEdit->toPlainText());
          ui->nameEdit->setText(entry->name());
          ui->themeEdit->setText(entry->theme());
          ui->expirationdateEdit->setDateTime(entry->expirationdate());
          ui->assignmentEdit->setPlainText(entry->assignment());
          listItem->setText(entry->name());
          discardEntry();
        }
    }
}

void MainWindow::discardEntry()
{
   ui->stackedWidget->setCurrentWidget(ui->listpage);
   ui->menuEntries->setEnabled(true);

}

void MainWindow::resetEntry()
{
    auto listItem=ui->listWidget->currentItem();
    if(listItem){
        auto entry=m_entryMap.value(listItem);
        if(entry){
          ui->nameEdit->setText(entry->name());
          ui->themeEdit->setText(entry->theme());
          ui->expirationdateEdit->setDateTime(entry->expirationdate());
          ui->assignmentEdit->setPlainText(entry->assignment());
        }
    }

}

void MainWindow::newFileSlot()
{
    if(ui->textEdit->document()->isModified())
    {
        qDebug()<<"current file modified";

    }
    else
    {
       //qDebug()<<"not modified";
        ui->textEdit->clear();
       this->setWindowTitle("time.txt");
    }

}

void MainWindow::openFileSlot()
{

  QString fileName=QFileDialog::getOpenFileName(this,"Open File",QDir::currentPath());
  //qDebug()<<"fileName is"<<fileName;
  if(fileName.isEmpty())
  {
      QMessageBox::information(this,"error" ,"please select a text file");
      return;
  }
  QFile*file=new QFile;
  file->setFileName(fileName);
  bool ok=file->open(QIODevice::ReadOnly);
  if(ok)
  {
     QTextStream in(file);
     ui->textEdit->setText(in.readAll());
     file->close();
     delete file;
  }
  else
  {
      QMessageBox::information(this,"error message","file open error"+file->errorString());

      return;
  }
}
void MainWindow:: AddaWeek()
{
   QDateTime datetimes = ui->expirationdateEdit->dateTime();
    datetimes =datetimes.addDays(7);
     ui->expirationdateEdit->setDateTime(datetimes);
}
void MainWindow:: AddaDay()
{
   QDateTime datetimes = ui->expirationdateEdit->dateTime();
        datetimes =datetimes.addDays(1);
         ui->expirationdateEdit->setDateTime(datetimes);
}
void MainWindow::setupConnections()
{/*
     * This connects various signals in the UI to slots we defined accordingly.
     */
   connect(ui->actionAdd,SIGNAL(triggered(bool)),
           this,SLOT(createEntry()));
   connect(ui->actionRemove,&QAction::triggered,
           this,&MainWindow::deleteEntry);
   connect(ui->actionEdit,&QAction::triggered,
           this,&MainWindow::editEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Save),&QPushButton::clicked,
           this,&MainWindow::saveEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Discard),&QPushButton::clicked,
           this,&MainWindow::discardEntry);
   connect(ui->buttonBox->button(QDialogButtonBox::Reset),&QPushButton::clicked,
           this,&MainWindow::resetEntry);
   connect(ui->actionNew,SIGNAL(triggered()),this,SLOT(newFileSlot()));
   connect(ui->actionOpen,SIGNAL(triggered()),this,SLOT(openFileSlot()));
   connect(ui->Button1,&QPushButton::clicked,
           this,&MainWindow::AddaWeek);
   connect(ui->Button2,&QPushButton::clicked,
           this,&MainWindow::AddaDay);

}
