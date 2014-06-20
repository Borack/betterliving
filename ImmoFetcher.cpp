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
}

ImmoFetcher::ImmoFetcher()
: m_oldUrl()
, m_newUrls()
{

}

ImmoFetcher::~ImmoFetcher()
{

}

void ImmoFetcher::run(QWebFrame*frame)
{
   if(!m_newUrls.isEmpty())
   {
      m_oldUrl = m_newUrls.last();
      m_newUrls.clear();
   }

   /* search until link is equal to old one or we have run 10 iterations or so */

   setProperty("list_id",ResultIDs::RESULT_LIST_ID);
   setProperty("title_id",ResultIDs::RESULT_TITLE_ID.arg("00"));

   frame->addToJavaScriptWindowObject("info",this);

   QString javaScript = Scripts::FETCH_SCRIPT;
   if (Scripts::FETCH_SCRIPT.endsWith(".js")) {
      QFile file(Scripts::FETCH_SCRIPT);
      if (!file.open(QIODevice::ReadOnly)) {
         emit halt("Invalid script provided.");
         return;
      }
      javaScript = QString::fromUtf8(file.readAll());
   }
   frame->evaluateJavaScript(javaScript);

}

void ImmoFetcher::foundResult(const QString &description, const QString &address, const QString &price, const QString &link)
{
   qDebug() << "Found a flat (" << description << " at: " << address << " for " << price << ". See " << link << " for more details.";
}

//void ImmoFetcher::storeLink(const QString &link)
//{
//   m_newUrls << link;
//}

//void ImmoFetcher::finished()
//{
//   qDebug() << "Script finished";
//   qDebug() << m_newUrls.join("\n");

//   QDesktopServices::openUrl(QUrl(m_newUrls.last()));
//}

