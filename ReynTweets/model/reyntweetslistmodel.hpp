#ifndef REYNTWEETSLISTMODEL_HPP
#define REYNTWEETSLISTMODEL_HPP

#include <QAbstractListModel>
#include "reyntweetsitemmodel.hpp"
/*
template <class ListItem>
class ReynTweetsListModel : public QAbstractListModel
{
		Q_OBJECT
	public:
		explicit ReynTweetsListModel(QObject *parent = 0);

		int rowCount(const QModelIndex &parent = QModelIndex()) const;

		QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

		void appendRow(ListItem * item);
		void appendRows(const QList<ListItem *> &items);
		void insertRow(int row, ListItem * item);
		bool removeRow(int row, const QModelIndex &parent = QModelIndex());
		bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
		ListItem * takeRow(int row);
		ListItem * find(const QString &id);
		QModelIndex indexFromItem( const ListItem * item) const;
		void clear();

	signals:

	public slots:

};
//*/
#endif // REYNTWEETSLISTMODEL_HPP
