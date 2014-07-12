#include "ApartmentModel.hpp"

ApartmentModel::ApartmentModel(QObject *parent) :
   QAbstractTableModel(parent)
{
}

void ApartmentModel::insert(const QString &key, const ApartmentListing &listing)
{
   beginInsertRows(QModelIndex(),0,0);
   m_listings.insert(key, listing);
   endInsertRows();
   //   insertRow(0);
}

int ApartmentModel::size() const
{
   return m_listings.size();
}

bool ApartmentModel::contains(const QString &key) const
{
   return m_listings.contains(key);
}

int ApartmentModel::rowCount(const QModelIndex &/*parent*/) const
{
   return size();
}

int ApartmentModel::columnCount(const QModelIndex &/*parent*/) const
{
   return 4;
}

QVariant ApartmentModel::data(const QModelIndex &index, int role) const
{
   if (role == Qt::DisplayRole)
   {
      ApartmentListing listing = m_listings.values().at(index.row());
      switch (index.column()) {
         case 0:
            return listing.desc();
            break;
         case 1:
            return listing.addr();
            break;
         case 2:
            return listing.prize();
            break;
         case 3:
            return listing.url();
            break;
         default:
            break;
      }
   }
   return QVariant();
}

QVariant ApartmentModel::headerData(int section, Qt::Orientation orientation, int role) const
{
   if (role == Qt::DisplayRole)
   {
      if(orientation == Qt::Horizontal)
      {
         switch (section) {
            case 0:
               return "Description";
               break;
            case 1:
               return "Address";
               break;
            case 2:
               return "Prize";
               break;
            case 3:
               return "URL";
               break;
            default:
               return "other";
               break;
         }
      }
   }

   return QAbstractItemModel::headerData(section, orientation, role);
}

//bool ApartmentModel::insertRow(int row, const QModelIndex &parent)
//{
//   beginInsertRows(parent,row,row);

//   endInsertRows();
//   return true;
//}


QDataStream &operator<<(QDataStream &out, const ApartmentModel &model)
{
   out << quint32(model.m_listings.size());
   QMapIterator<QString, ApartmentListing> i(model.m_listings);
   while (i.hasNext()) {
      i.next();
      out << i.key() << i.value();
   }

   return out;
}



QDataStream &operator>>(QDataStream &in, ApartmentModel &model)
{
   quint32 nElements;
   in >> nElements;

   QString key;
   ApartmentListing listing;
   for(int i = 0; i< nElements; i++)
   {
      in >> key;
      in >> listing;
      model.m_listings.insert(key, listing);
   }

   return in;
}
