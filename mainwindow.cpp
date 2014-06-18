#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "InfoDispatcher.hpp"

#include <QDebug>
#include <QObject>

namespace {
const int g_interval = 5;
const int g_statusTime = 5000;
}

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow(parent),
   ui(new Ui::MainWindow),
   m_running(false)

{
   ui->setupUi(this);

   setupUI();
   setupConnections();

}

MainWindow::~MainWindow()
{
   delete ui;
}

void MainWindow::setupConnections()
{
   connect(ui->submitButton, SIGNAL(clicked()),this,SLOT(startOrStopClicked()));
   connect(&m_infoDispatcher, SIGNAL(statusUpdate(QString)),this,SLOT(showStatus(QString)));
   connect(&m_infoDispatcher, SIGNAL(halt(QString)),this,SLOT(haltTimer(QString)));
   connect(&m_timer,SIGNAL(timeout()),&m_infoDispatcher,SLOT(run()));
}

void MainWindow::startOrStopClicked()
{
   if(!m_running)
   {
      start();
   }
   else
   {
      stop();
   }


}

void MainWindow::dispatcherFinished(bool ok)
{
   if(ok)
   {
      showStatus(tr("Fetching new flats..."));
   }
   else{
      showStatus(tr("Ouch, a failure!"));
   }
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
   if(event->key() == Qt::Key_Enter || event->key() == Qt::Key_Return)
   {
      startOrStopClicked();
   }
}

void MainWindow::setupUI()
{
   setWindowTitle(tr("Better Living"));

//   setWindowFlags(Qt);

   ui->intervalSpinBox->setValue(g_interval);
   ui->intervalSpinBox->setMinimum(g_interval);
   ui->intervalSpinBox->setSingleStep(g_interval);
}

void MainWindow::runDispatcher()
{
   QString town = ui->townEdit->text();
   QString type = ui->typeCombo->currentText();
   float maxRent = ui->rentEdit->text().toFloat();
   float minRooms = ui->roomsEdit->text().toFloat();

   m_infoDispatcher.setKeywords(town,maxRent,minRooms,type);
   m_infoDispatcher.run();
}

bool MainWindow::isAtLeastOneValueSet() const
{
   QString town = ui->townEdit->text();
   QString type = ui->typeCombo->currentText();
   float maxRent = ui->rentEdit->text().toFloat();
   float minRooms = ui->roomsEdit->text().toFloat();

   return ((!QString(town /*+ type*/).isEmpty()) || (minRooms + maxRent > 0));
}

void MainWindow::showStatus(const QString &status)
{
   ui->statusBar->showMessage(status, g_statusTime);
}

void MainWindow::haltTimer(const QString &haltMsg)
{
   stop();
   showStatus(haltMsg);
}

void MainWindow::start()
{
   if(isAtLeastOneValueSet())
   {
      runDispatcher();
      m_timer.setInterval(ui->intervalSpinBox->value()*(60*1000));
      m_timer.start();

      ui->statusBar->clearMessage();
      ui->submitButton->setText("Stop");
      showStatus(tr("Submitting..."));

      ui->searchBox->setEnabled(false);
      ui->intervalBox->setEnabled(false);

      m_running = !m_running;
   }
   else
   {
      showStatus(tr("Please fill in the form."));
   }
}

void MainWindow::stop()
{
   m_timer.stop();

   ui->submitButton->setText("Start");

   ui->searchBox->setEnabled(true);
   ui->intervalBox->setEnabled(true);

   m_running = !m_running;
}
