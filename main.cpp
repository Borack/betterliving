//Qt
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTime>

#include "mainwindow.hpp"
#include <iostream>


void myMessageOutput(QtMsgType type, const char *msg)
{


   static QFile file("better_living.log");
   if(!file.isOpen())
   {
      if(!file.open(QIODevice::WriteOnly))
      {
         std::cout << "Cannot open log file for writing!" << std::endl;
         return;
      }
   }

   static QTextStream out(&file);

   out << QTime::currentTime().toString("HH:mm:ss:z");
   switch (type) {
   case QtDebugMsg:
      out << " Debug: " << msg << "\n";
      break;
   case QtWarningMsg:
      out << " Warning: " << msg << "\n";
      break;
   case QtCriticalMsg:
      out << " Critical: " << msg << "\n";
      break;
   case QtFatalMsg:
      out << " Fatal: " << msg << "\n";
      abort();
   }

   std::cout << msg << std::endl;
   out.flush();
}

int main(int argc, char *argv[])
{
//   qInstallMessageHandler(myMessageOutput);
   QApplication app(argc, argv);
   app.setWindowIcon(QIcon(":/better_living_round.png"));

   MainWindow w;
   w.show();

   return app.exec();
}
