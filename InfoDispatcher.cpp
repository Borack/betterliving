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
}

InfoDispatcher::InfoDispatcher()
: m_immoFetcher()
, m_loadCounter(0)
{
   setupConnections();
   setupWebPage();

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

void InfoDispatcher::setupWebPage()
{
   QWebSettings *webSettings = m_page.settings();
   webSettings->setAttribute(QWebSettings::AutoLoadImages, false);
   webSettings->setAttribute(QWebSettings::PluginsEnabled, false);
   webSettings->setAttribute(QWebSettings::JavaEnabled, false);
   webSettings->setAttribute(QWebSettings::JavascriptEnabled, true);
   webSettings->setAttribute(QWebSettings::PrivateBrowsingEnabled,true);
}

void InfoDispatcher::setupConnections()
{
   connect(m_page.mainFrame(), SIGNAL(javaScriptWindowObjectCleared()),
           this, SLOT(injectJavaScriptIntoWindowObject()));
   connect(&m_page, SIGNAL(loadFinished(bool)),
           this, SLOT(supplyInfos(bool)));
}

void InfoDispatcher::injectJavaScriptIntoWindowObject()
{
   m_page.mainFrame()->addToJavaScriptWindowObject("info", this);
}

void InfoDispatcher::supplyInfos(bool ok)
{
   if (!ok) {
      emit statusUpdate("Error loading web data.");
      return;
   }

      qDebug() << "MainFrame title: " << m_page.mainFrame()->title();
//      if(m_page.mainFrame()->title() == COMPARIS::START_TITLE)
      if(true)
   {
      if(m_loadCounter >= 2)
      {
         emit halt("Invalid data provided.");
         return;
      }
      QString javaScript = COMPARIS::SUBMIT_SCRIPT;
      if (COMPARIS::SUBMIT_SCRIPT.endsWith(".js")) {
         QFile file(COMPARIS::SUBMIT_SCRIPT);
         if (!file.open(QIODevice::ReadOnly)) {
            emit halt("Invalid script provided.");
            return;
         }
         javaScript = QString::fromUtf8(file.readAll());
      }

      m_page.mainFrame()->evaluateJavaScript(javaScript);

      m_loadCounter += 1;
      emit statusUpdate("Infos submitted.");
   }

   else
   {
      m_immoFetcher.run(m_page.mainFrame());
      emit statusUpdate("Fetching flats ...");
   }
}

void InfoDispatcher::run()
{
   m_loadCounter = 0;
   m_page.mainFrame()->load(COMPARIS::URL);
}

void InfoDispatcher::setKeywords(const QString &town, float maxRent, float minRooms, const QString &type)
{
   m_town = town;
   m_maxRent = maxRent;
   m_minRooms = minRooms;
   m_type = type;

   setupIDs();
}


