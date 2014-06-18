#ifndef INFODISPATCHER_HPP
#define INFODISPATCHER_HPP

#include <QMap>
#include <QWebPage>

#include <ScriptRunnerBase.hpp>
#include "ImmoFetcher.hpp"

struct NamedPair{
      NamedPair() {}
      NamedPair(QString inId) : id(inId) {}
      NamedPair(QString inId, QString inValue) : id(inId), value(inValue) {}
      QString id;
      QString value;
};



class InfoDispatcher : public ScriptRunnerBase
{
   Q_OBJECT

   public:
      InfoDispatcher();
      ~InfoDispatcher();

      void setKeywords(const QString& town = "", float maxRent = 0, float minRooms = 0, const QString& type = "");

   public slots:
      void run();

   private slots:
      void injectJavaScriptIntoWindowObject();
      void supplyInfos(bool);

   private:
      void setupConnections();
      void setupWebPage();
      void setupIDs();
      void setupProperties();
      bool isAtLeastOneValueSet() const;

      void submit();

      ImmoFetcher m_immoFetcher;

      QMap<QString,NamedPair> m_ids;
      QWebPage m_page;

      QString m_town;
      QString m_type;
      float m_maxRent;
      float m_minRooms;

      int m_loadCounter;
};


#endif // INFODISPATCHER_HPP