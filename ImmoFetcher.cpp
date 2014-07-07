#include "ImmoFetcher.hpp"

#include <QDebug>
#include <QDesktopServices>
#include <QFile>
#include <QFileInfo>
#include <QWebFrame>


namespace ResultIDs
{
const QString RESULT_LIST_ID("result_list_ajax_container");
const QString RESULT_TITLE_ID("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl%0_ProductListResultItem_PropertyDetailsLabel"); /* %0 has to be replaced with a 00, 02, 04 etc */
const QString RESULT_PRICE_ID("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl%0_ProductListResultItem_PriceLabel"); /* %0 has to be replaced with a 00, 02, 04 etc */
}

namespace Scripts{
static const QString FETCH_SCRIPT(":/ComparisFetcher.js");
static const QString HOMEGATE_FETCH_SCRIPT(":/HomegateFetcher.js");
}

namespace IO{
static const QString SAVE_NAME("SavedListings.txt");
static const quint32 MAGIC_NUMBER = 0xb0ac4000;
static const quint32 VERSION1 = 1;
}

ImmoFetcher::ImmoFetcher(QWebPage *page)
   : ScriptRunnerBase(page)
   , m_oldUrl()
   , m_newUrls()
   , m_immoCounter(0)
{
   loadFromFile();
   qDebug() << "number of apt loaded: " << m_apartements.size();
}

ImmoFetcher::~ImmoFetcher()
{
   saveToFile();
   qDebug() << "number of apt saved: " << m_apartements.size();
}

void ImmoFetcher::run()
{

   if(!m_newUrls.isEmpty())
   {
      m_oldUrl = m_newUrls.last();
      m_newUrls.clear();
   }

   /* search until link is equal to old one or we have run 10 iterations or so */

   setProperty("list_id",ResultIDs::RESULT_LIST_ID);
   setProperty("title_id",ResultIDs::RESULT_TITLE_ID.arg("00"));

   m_webPage->mainFrame()->addToJavaScriptWindowObject("info",this);

   QString javaScript = Scripts::HOMEGATE_FETCH_SCRIPT;
   if (Scripts::HOMEGATE_FETCH_SCRIPT.endsWith(".js")) {
      QFile file(Scripts::HOMEGATE_FETCH_SCRIPT);
      if (!file.open(QIODevice::ReadOnly)) {
         emit halt("Invalid script provided.");
         return;
      }
      javaScript = QString::fromUtf8(file.readAll());
   }
   m_webPage->mainFrame()->evaluateJavaScript(javaScript);
}

void ImmoFetcher::foundResult(const QString &description, const QString &address, const QString &price, const QString &link)
{
   QString prix(price);
   prix = prix.trimmed();
   prix.replace("'","");
   prix.replace("-","");
   prix.replace(".","");
   prix.replace(",","");

   ApartmentListing apartement(description.trimmed(),prix.toInt(),QUrl(link.trimmed()), address.trimmed());

   if(!m_apartements.contains(apartement.id()))
   {
      qDebug() << "A new apartement found!";
      m_immoCounter++;
      qDebug() << "Found flat #" << m_immoCounter << " (" << description.trimmed() << ") at: " << address.trimmed() << " for " << price.trimmed() << ". See " << link.trimmed() << " for more details.";
      m_apartements.insert(apartement.id(), apartement);
   }
   else
   {
      //      qDebug() << "This apt is already known to me. boring.. ";
   }
}

void ImmoFetcher::loadFromFile()
{

   QFileInfo info(IO::SAVE_NAME);
   if(info.exists())
   {
      QFile file(IO::SAVE_NAME);
      file.open(QIODevice::ReadOnly);
      QDataStream in(&file);   //read from file

      quint32 magic;
      in >> magic;
      if(magic != IO::MAGIC_NUMBER)
      {
         qDebug() << "Invalid magic number in database file";
         return;
      }

      quint32 version;
      in >> version;

      if(version != IO::VERSION1)
      {
         return;
      }

      quint32 nElements;
      in >> nElements;

      QString key;
      ApartmentListing listing;
      for(int i = 0; i< nElements; i++)
      {
         in >> key;
         in >> listing;
         m_apartements.insert(key, listing);
      }
   }

}

void ImmoFetcher::saveToFile()
{
   QFile file(IO::SAVE_NAME);
   file.open(QIODevice::WriteOnly);
   QDataStream out(&file);   // we will serialize the data into the file

   out << IO::MAGIC_NUMBER << IO::VERSION1 << quint32(m_apartements.size());

   QMapIterator<QString, ApartmentListing> i(m_apartements);
   while (i.hasNext()) {
      i.next();
      out << i.key() << i.value();
   }
}
