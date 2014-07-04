#include "InfoDispatcher.hpp"

#include <QDebug>
#include <QFile>
#include <QMapIterator>
#include <QObject>
#include <QWebFrame>
#include <QVariant>


/*
  TODOS:
  - DONE - Polling interval.
  - Read Submit.js from file if there is one, otherwise read from Qt resource
  - Read webIDs from file ..
  - Read URL from file ..
  - EMail option
  */

namespace COMPARIS{
//const QString URL("http://www.comparis.ch/immobilien/default.aspx");
//const QString SUBMIT("ctl00_ctl02_usercontrol_btnShowResults");


const QString URL("http://www.comparis.ch/immobilien/marktplatz/search.aspx?searchtab=search&mode=expand");
const QString SUBMIT("btnShowResults");
const QString TOWN_ID("SearchParams_LocationSearchString");
const QString MIN_ROOMS("SearchParams_RoomsFrom");
const QString MAX_RENT("SearchParams_PriceTo");
const QString OBJECT_TYPE("ddlPropertyType");

const QString START_TITLE("Preisvergleich Schweiz, Versicherungen und Krankenkassenvergleich - comparis.ch");

const QString SUBMIT_SCRIPT(":/ComparisSubmit.js");
}

namespace HOMEGATE {
const QString URL("http://www.homegate.ch/mieten/wohnung-und-haus/bezirk-zuerich/trefferliste?mn=ctn_zh&ao=&oa=false&am=&tab=list&incsubs=default&fromItem=ctn_zh&be=&tid=1");
const QString SUBMIT_SCRIPT(":/HomegateSubmit.js");
const QString START_TITLE("Wohnung und Haus mieten in Bezirk Zürich | homegate.ch");
const QString RESULT_TITLE("Wohnung und Haus mieten in Zürich | homegate.ch");
//Wohnung und Haus mieten in Bezirk Zürich | homegate.ch
}

InfoDispatcher::InfoDispatcher(QWebPage *page)
   : ScriptRunnerBase(page)
   , m_loadCounter(0)
   , m_suppliedAllInfosAlready(false)
{
   setupConnections();

}

InfoDispatcher::~InfoDispatcher()
{

}


void InfoDispatcher::setupProperties()
{
   //Setup the properties from the ids list
   QMapIterator<QString, NamedPair> itr(m_ids);
   while(itr.hasNext())
   {
      itr.next();


      QString webKey = itr.key() + "_webID";
      setProperty(webKey.toUtf8(),QVariant(itr.value().id));

      QString webValue = itr.key() + "_webValue";
      setProperty(webValue.toUtf8(),QVariant(itr.value().value));
   }

   //Add additional properties like submit id
   setProperty("submit",QVariant(COMPARIS::SUBMIT));
}

void InfoDispatcher::setupIDs()
{

   //if(!m_town.isEmpty())
   m_ids["town"] = NamedPair(COMPARIS::TOWN_ID, m_town);
   //if(!m_type.isEmpty())
   //   qDebug() << "To be implmeneted in " << Q_FUNC_INFO;
   //if(m_minRooms > 0)
   m_ids["minRooms"] = NamedPair(COMPARIS::MIN_ROOMS,QString::number(m_minRooms));
   //if(m_maxRent > 0)
   m_ids["maxRent"] = NamedPair(COMPARIS::MAX_RENT, QString::number(m_maxRent));

   setupProperties();

}

void InfoDispatcher::setupConnections()
{
   connect(m_webPage->mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
           this, SLOT(injectJavaScriptIntoWindowObject()));
   connect(m_webPage, SIGNAL(loadFinished(bool)),
           this, SLOT(supplyInfos(bool)));
}

void InfoDispatcher::injectJavaScriptIntoWindowObject()
{
   m_webPage->mainFrame()->addToJavaScriptWindowObject("info", this);
}

void InfoDispatcher::supplyInfos(bool ok)
{
   if (!ok) {
      emit statusUpdate("Error loading web data.");
      return;
   }

//   setupConnections();

   QDateTime local(QDateTime::currentDateTime());
   qDebug() << local <<": MainFrame title: " << m_webPage->mainFrame()->title();
   if(m_webPage->mainFrame()->title() == HOMEGATE::START_TITLE)
      //      if(true)
//   if(!m_suppliedAllInfosAlready)
   {
//      if(m_loadCounter >= 2)
//      {
//         emit halt("Invalid data provided.");
//         return;
//      }
      //      QString javaScript = COMPARIS::SUBMIT_SCRIPT;
      QString javaScript = HOMEGATE::SUBMIT_SCRIPT;
      if (HOMEGATE::SUBMIT_SCRIPT.endsWith(".js")) {
         QFile file(HOMEGATE::SUBMIT_SCRIPT);
         if (!file.open(QIODevice::ReadOnly)) {
            emit halt("Invalid script provided.");
            return;
         }
         javaScript = QString::fromUtf8(file.readAll());
      }

      m_webPage->mainFrame()->evaluateJavaScript(javaScript);

      m_loadCounter += 1;
      m_suppliedAllInfosAlready = true;
      emit statusUpdate("Infos submitted.");
   }

   else if(m_webPage->mainFrame()->title() ==  HOMEGATE::RESULT_TITLE)
   {
      m_suppliedAllInfosAlready = false;
//      QObject::disconnect(this, SLOT(supplyInfos(bool)));
      emit readyForFetching();
      emit statusUpdate("Fetching flats ...");
   }
}

void InfoDispatcher::run()
{
   m_loadCounter = 0;
   m_webPage->mainFrame()->load(HOMEGATE::URL);
   //   m_page.mainFrame()->load(COMPARIS::URL);
}

void InfoDispatcher::setKeywords(const QString &town, float maxRent, float minRooms, const QString &type)
{
   m_town = town;
   m_maxRent = maxRent;
   m_minRooms = minRooms;
   m_type = type;

   setupIDs();
}


