#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <stdio.h>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent)
  , ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  connect(ui, &QAbstractPushButton::clicked, this, &MainWindow::make_dat_file);
}

MainWindow::~MainWindow()
{
  delete ui;
}

MainWindow::make_dat_file()
{
  FILE *f = fopen("crappy_file", "w");
  fprintf(f, "Yeah boy, horse be speaking");
  fclose(f);
}
