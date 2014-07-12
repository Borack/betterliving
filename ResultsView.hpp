#ifndef RESULTSVIEW_HPP
#define RESULTSVIEW_HPP

#include <QWidget>

class QAbstractTableModel;

namespace Ui {
class ResultsView;
}

class ResultsView : public QWidget
{
   Q_OBJECT

public:
   explicit ResultsView(QAbstractTableModel * model, QWidget *parent = 0);
   ~ResultsView();

private slots:
   void on_tableView_clicked(const QModelIndex &index);

private:
   Ui::ResultsView *ui;
   QAbstractTableModel *m_model;
};

#endif // RESULTSVIEW_HPP
