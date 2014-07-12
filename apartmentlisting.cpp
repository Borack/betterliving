#include "apartmentlisting.hpp"


ApartmentListing::ApartmentListing(QObject *parent)
   : QObject(parent)
   , m_description()
   , m_prize(0)
   , m_webUrl()
   , m_address()
{

}

ApartmentListing::ApartmentListing(const QString &desc, const int &prize, const QUrl &url, const QString address, QObject *parent)
   : QObject(parent)
   , m_description(desc)
   , m_prize(prize)
   , m_webUrl(url)
   , m_address(address)
{

}

ApartmentListing::ApartmentListing(const ApartmentListing &other)
   : QObject(other.parent())
   , m_description(other.m_description)
   , m_prize(other.m_prize)
   , m_webUrl(other.m_webUrl)
   , m_address(other.m_address)
{

}

QString ApartmentListing::id() const
{
   return m_webUrl.toString();
}

ApartmentListing &ApartmentListing::operator =(const ApartmentListing &other)
{
   this->setParent(other.parent());
   this->m_description = other.m_description;
   this->m_address = other.m_address;
   this->m_prize = other.m_prize;
   this->m_webUrl = other.m_webUrl;

   return *this;
}


QDataStream &operator<<(QDataStream &out, const ApartmentListing &listing)
{
   out << listing.addr() << listing.desc() << listing.url() << quint32(listing.prize());
   return out;
}


QDataStream &operator>>(QDataStream &in, ApartmentListing &listing)
{
   QString address;
   QString desc;
   QUrl url;
   quint32 prize;
   in >> address >> desc >> url >> prize;
   listing = ApartmentListing(desc, prize, url, address);
   return in;
}
