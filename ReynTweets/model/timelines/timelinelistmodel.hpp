#ifndef TIMELINELISTMODEL_HPP
#define TIMELINELISTMODEL_HPP

#include <QAbstractListModel>
#include "timelinemodel.hpp"

/*
class TimelineListModel : public QAbstractListModel
{
		Q_OBJECT
	public:
		explicit TimelineListModel(QObject *parent = 0);

		int rowCount(const QModelIndex &parent) const;

		QVariant data(const QModelIndex &index, int role) const;

		void appendRow(Tweet* item);
		void appendRows(const QList<Tweet*> &items);
		void insertRow(int row, Tweet* item);
		bool removeRow(int row, const QModelIndex &parent = QModelIndex());
		bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
		Tweet* takeRow(int row);
		Tweet* find(const QString &id);
		QModelIndex indexFromItem( const ListItem* item) const;
		void clear();

	  private slots:
		void handleItemChange();

	signals:

	public slots:


	protected:
		TimelineModel timeline;

		Tweet * prototweet;
};
//*/
#endif // TIMELINELISTMODEL_HPP
