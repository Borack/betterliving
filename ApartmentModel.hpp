#ifndef APARTMENTMODEL_HPP
#define APARTMENTMODEL_HPP

#include <QAbstractTableModel>
#include <apartmentlisting.hpp>

class ApartmentModel : public QAbstractTableModel
{
   Q_OBJECT
public:
   explicit ApartmentModel(QObject *parent = 0);

   void insert(const QString &key, const ApartmentListing &listing);

   int size() const;
   bool contains(const QString &key) const;


   virtual int rowCount(const QModelIndex &parent =  QModelIndex()) const ;
   virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
   virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
   virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
//   virtual bool insertRow(int row, const QModelIndex &parent = QModelIndex());


   friend QDataStream &operator<<(QDataStream &out, const ApartmentModel &model);
   friend QDataStream &operator>>(QDataStream &in, ApartmentModel &model);

signals:

public slots:

private:
   QMap<QString, ApartmentListing> m_listings;

};

QDataStream &operator<<(QDataStream &out, const ApartmentModel &model);
QDataStream &operator>>(QDataStream &in, ApartmentModel &model);

#endif // APARTMENTMODEL_HPP
