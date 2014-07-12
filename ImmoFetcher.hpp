#ifndef IMMOFETCHER_HPP
#define IMMOFETCHER_HPP

#include "ScriptRunnerBase.hpp"

#include <QMap>
#include <QStringList>
#include <QUrl>

#include <apartmentlisting.hpp>
#include <ApartmentModel.hpp>
#include <ResultsView.hpp>

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

   void loadFromFile();
   void saveToFile();
private:

   QString m_oldUrl;
   QStringList m_newUrls;
   int m_immoCounter;

   ApartmentModel m_apartements;
   ResultsView *m_resultsView;


};
#endif // IMMOFETCHER_HPP
