#ifndef APARTMENTLISTING_HPP
#define APARTMENTLISTING_HPP

#include <QObject>
#include <QUrl>
#include <QDataStream>
#include <QAbstractTableModel>

class ApartmentListing : public QObject
{
   Q_OBJECT

public:
   friend class QDataStream;

   explicit ApartmentListing(QObject *parent = 0);
   explicit ApartmentListing(const QString &desc, const int &prize, const QUrl &url, const QString address, QObject *parent = 0);
   ApartmentListing(const ApartmentListing &other);
   QString id() const;

   QString desc() const { return m_description; }
   QString addr() const { return m_address; }
   int prize() const { return m_prize; }
   QUrl url() const { return m_webUrl; }

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
