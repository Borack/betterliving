#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>

#include "InfoDispatcher.hpp"


namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

   protected:
      virtual void keyPressEvent(QKeyEvent *);

private slots:
      void startOrStopClicked();
      void dispatcherFinished(bool ok);
      void runDispatcher();
      void showStatus(const QString& status);
      void haltTimer(const QString& haltMsg);


private:

    void setupConnections();
    void setupUI();
    bool isAtLeastOneValueSet() const;

    void start();
    void stop();

    Ui::MainWindow *ui;
    InfoDispatcher m_infoDispatcher;
    bool m_running;
    QTimer m_timer;

    static const QString TOWN_SETTINGS_KEY;
    static const QString RENT_SETTINGS_KEY;
    static const QString TYPE_SETTINGS_KEY;
    static const QString ROOMS_SETTINGS_KEY;

};

#endif // MAINWINDOW_HPP
