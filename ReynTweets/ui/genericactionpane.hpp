#ifndef GENERICACTIONPANE_HPP
#define GENERICACTIONPANE_HPP

#include <QLabel>
#include <QPushButton>
#include "qmlviewer.hpp"

class GenericActionPane : public QMLViewer
{
		Q_OBJECT
	public:
		GenericActionPane(QWidget *parent = 0);

	signals:

	public slots:
		void action();

	protected:
		QString descriptionText;
		QLabel descriptionLabel;

		QString buttonText;
		QPushButton actionButton;
};

#endif // GENERICACTIONPANE_HPP
