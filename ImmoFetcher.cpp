#include "ImmoFetcher.hpp"

#include <QWebFrame>
#include <QFile>
#include <QDebug>
#include <QDesktopServices>


namespace ResultIDs
{
const QString RESULT_LIST_ID("result_list_ajax_container");
const QString RESULT_TITLE_ID("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl%0_ProductListResultItem_PropertyDetailsLabel"); /* %0 has to be replaced with a 00, 02, 04 etc */
const QString RESULT_PRICE_ID("ctl00_ContentPlaceHolderApplication_ResultListUserControl_ResultListRepeater_ctl%0_ProductListResultItem_PriceLabel"); /* %0 has to be replaced with a 00, 02, 04 etc */
}

namespace Scripts{
const QString FETCH_SCRIPT(":/ComparisFetcher.js");
const QString HOMEGATE_FETCH_SCRIPT(":/HomegateFetcher.js");
}

ImmoFetcher::ImmoFetcher(QWebPage *page)
: ScriptRunnerBase(page)
, m_oldUrl()
, m_newUrls()
, m_immoCounter(0)
{

}

ImmoFetcher::~ImmoFetcher()
{
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

   save("");

}

void ImmoFetcher::foundResult(const QString &description, const QString &address, const QString &price, const QString &link)
{
   QString prix(price);
   prix = prix.trimmed();
   prix.replace("'","");
   prix.replace("-","");
   prix.replace(".","");
   prix.replace(",","");

   ApartmentListing apartement(description,prix.toInt(),QUrl(link), address);

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

void ImmoFetcher::save(const QString path)
{
   QFile file("SavedListings.dat");
   file.open(QIODevice::WriteOnly);
   QDataStream out(&file);   // we will serialize the data into the file

   QMapIterator<QString, ApartmentListing> i(m_apartements);
   while (i.hasNext()) {
      i.next();
      out << i.key() << i.value();
   }
}
