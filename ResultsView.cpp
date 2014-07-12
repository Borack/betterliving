#include "ResultsView.hpp"
#include "ui_ResultsView.h"

#include <QUrl>
#include <QDesktopServices>

ResultsView::ResultsView(QAbstractTableModel * model, QWidget *parent) :
   QWidget(parent),
   m_model(model),
   ui(new Ui::ResultsView)
{
   ui->setupUi(this);
   ui->tableView->setModel(m_model);
}


ResultsView::~ResultsView()
{
   delete ui;
}

void ResultsView::on_tableView_clicked(const QModelIndex &index)
{
    if(index.column() == 3) // 3 == URL field
    {
      QUrl url(m_model->data(index).toString());
      QDesktopServices::openUrl(url);
    }
}
