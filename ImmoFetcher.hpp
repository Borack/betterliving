#ifndef IMMOFETCHER_HPP
#define IMMOFETCHER_HPP

#include "ScriptRunnerBase.hpp"

#include <QUrl>
#include <QStringList>

class QWebFrame;

class ImmoFetcher : public ScriptRunnerBase
{
   Q_OBJECT

public:
   ImmoFetcher(QWebPage* page);
   ~ImmoFetcher();


public slots:
   void run();

   void foundResult(const QString& description, const QString &address, const QString & price, const QString &link);

   ////   void   storeLink(const QString& link);
   //   void finished();

private:

   QString m_oldUrl;
   QStringList m_newUrls;
   int m_immoCounter;

};
#endif // IMMOFETCHER_HPP
