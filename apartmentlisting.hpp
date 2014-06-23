#ifndef APARTMENTLISTING_HPP
#define APARTMENTLISTING_HPP

#include <QObject>
#include <QUrl>

class ApartmentListing : public QObject
{
   Q_OBJECT

public:
   explicit ApartmentListing(const QString &desc, const int &prize, const QUrl &url, const QString address, QObject *parent = 0);
   ApartmentListing(const ApartmentListing &other);
   QString id() const;


   ApartmentListing & operator =(const ApartmentListing &other);
signals:

public slots:

private:
   QString m_description;
   int m_prize;
   QUrl m_webUrl;
   QString m_address;

};

#endif // APARTMENTLISTING_HPP
