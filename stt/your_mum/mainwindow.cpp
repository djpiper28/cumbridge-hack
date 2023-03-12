#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::DoThing);
  this->setWindowTitle(tr("Horsey Input Manager"));
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::DoThing()
{
  FILE *f = fopen("crappy_file", "w");
  fprintf(f, "Horse speaknow");
  fclose(f);
  exit(0);
}
