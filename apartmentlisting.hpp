#ifndef APARTMENTLISTING_HPP
#define APARTMENTLISTING_HPP

#include <QObject>
#include <QUrl>
#include <QDataStream>

class ApartmentListing : public QObject
{
   Q_OBJECT

public:
   friend class QDataStream;

   explicit ApartmentListing(const QString &desc, const int &prize, const QUrl &url, const QString address, QObject *parent = 0);
   ApartmentListing(const ApartmentListing &other);
   QString id() const;

   friend QDataStream &operator<<(QDataStream &out, const ApartmentListing &listing);
   friend QDataStream &operator>>(QDataStream &in, ApartmentListing &listing);

   ApartmentListing & operator =(const ApartmentListing &other);
signals:

public slots:

private:
   QString m_description;
   int m_prize;
   QUrl m_webUrl;
   QString m_address;


};

QDataStream &operator<<(QDataStream &out, const ApartmentListing &listing);
QDataStream &operator>>(QDataStream &in, ApartmentListing &listing);

#endif // APARTMENTLISTING_HPP
