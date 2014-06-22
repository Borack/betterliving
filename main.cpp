//Qt
#include <QApplication>
#include <QFile>
#include <QTextStream>
#include <QTime>

#include "mainwindow.hpp"
#include <iostream>


//void myMessageOutput(QtMsgType type, const char *msg)
//{


//   static QFile file("better_living.log");
//   if(!file.isOpen())
//   {
//      if(!file.open(QIODevice::WriteOnly))
//      {
//         std::cout << "Cannot open log file for writing!" << std::endl;
//         return;
//      }
//   }

//   static QTextStream out(&file);

//   out << QTime::currentTime().toString("HH:mm:ss:z");
//   switch (type) {
//   case QtDebugMsg:
//      out << " Debug: " << msg << "\n";
//      break;
//   case QtWarningMsg:
//      out << " Warning: " << msg << "\n";
//      break;
//   case QtCriticalMsg:
//      out << " Critical: " << msg << "\n";
//      break;
//   case QtFatalMsg:
//      out << " Fatal: " << msg << "\n";
//      abort();
//   }

//   std::cout << msg << std::endl;
//   out.flush();
//}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    switch (type) {
    case QtDebugMsg:
        fprintf(stderr, "Debug: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtWarningMsg:
        fprintf(stderr, "Warning: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtCriticalMsg:
        fprintf(stderr, "Critical: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        break;
    case QtFatalMsg:
        fprintf(stderr, "Fatal: %s (%s:%u, %s)\n", localMsg.constData(), context.file, context.line, context.function);
        abort();
    }
}



int main(int argc, char *argv[])
{
//   qInstallMessageHandler(myMessageOutput);
   QApplication app(argc, argv);
   app.setOrganizationName("Borack");
   app.setApplicationName("BetterLiving");
   Q_INIT_RESOURCE(BetterLiving);
   app.setWindowIcon(QIcon(":/better_living_round.png"));

   MainWindow w;
   w.show();

   return app.exec();
}
