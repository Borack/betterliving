#ifndef IMMOFETCHER_HPP
#define IMMOFETCHER_HPP

#include "ScriptRunnerBase.hpp"

#include <QUrl>
#include <QStringList>

class QWebFrame;

class ImmoFetcher : protected ScriptRunnerBase
{
   Q_OBJECT

public:
   ImmoFetcher();
   ~ImmoFetcher();

   void run(QWebFrame*frame);

public slots:
   void foundResult(const QString& description, const QString &address, const QString & price, const QString &link);

   ////   void   storeLink(const QString& link);
   //   void finished();

private:

   QString m_oldUrl;
   QStringList m_newUrls;

};
#endif // IMMOFETCHER_HPP
