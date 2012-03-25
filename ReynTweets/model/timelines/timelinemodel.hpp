#ifndef TIMELINEMODEL_HPP
#define TIMELINEMODEL_HPP

#include <QObject>
#include "timeline.hpp"

class TimelineModel : public QObject, public QList<Tweet *>
{
	Q_OBJECT

	public:
		/////////////
		// Coplien //
		/////////////

		/// @fn TimelineModel();
		/// @brief Default constructor
		TimelineModel();

		/// @fn ~TimelineModel();
		/// @brief Destructor
		~TimelineModel();

		/// @fn TimelineModel(const TimelineModel & model);
		/// @brief Copy constructor
		/// @param model Timeline model to copy
		TimelineModel(const TimelineModel & model);

		/// @fn TimelineModel(const Timeline & tl);
		/// @brief Copying a Timeline
		/// @param tl Timeline to copy
		TimelineModel(const Timeline & tl);

		/// @fn const TimelineModel & operator=(const TimelineModel & model);
		/// @brief Affectation of a timeline model
		/// @param model Timeline model to copy
		/// @return The model with its new values
		const TimelineModel & operator=(const TimelineModel & model);

		/// @fn const TimelineModel & operator=(const Timeline & tl);
		/// @brief Affectation of a timeline
		/// @param tl Timeline to copy
		/// @return The model with its new values
		const TimelineModel & operator=(const Timeline & tl);


		// QML system

		/// @fn static void declareQML();
		/// @brief Declaring to the QML system
		static void declareQML();


		////////////////////////
		// Timeline integrity //
		////////////////////////

		/// @fn Timeline & getTimelineRef();
		/// @brief Getting a reference on the timeline
		/// @return A reference on statuses.
		Timeline & getTimelineRef();

		/// @fn Timeline getTimeline();
		/// @brief Reading the timeline property
		/// @return statuses
		Timeline getTimeline();

		/// @fn void setTimeline(Timeline tl);
		/// @brief Writing the timeline property
		/// @param tl A new value for statuses
		void setTimeline(Timeline tl);

		/// @fn Q_INVOKABLE void syncTimeline();
		/// @brief Syncing the timeline.
		///
		/// Made for QML views.
		Q_INVOKABLE void syncTimeline();

	signals:
		/// @fn void timelineChanged();
		/// @brief Signal to send to notify changes about the timeline property.
		void timelineChanged();

	protected slots:
		/// @fn void syncModel();
		/// @brief Slot executed just after sending the timelineChanged();
		/// signal to update the model.
		void syncModel();

	protected:
		/// @property timeline
		/// @brief Timeline behind the model.
		///
		/// Represented by the statuses attribute.
		Q_PROPERTY(Timeline timeline
				   READ getTimeline
				   WRITE setTimeline
				   NOTIFY timelineChanged)

		/// @brief Timeline behind the model
		Timeline statuses;


		// Coplien - Recopy

		/// @fn void recopie(const TimelineModel & model);
		/// @brief Recopying a Timeline model
		/// @param model Timeline to copy
		void recopie(const TimelineModel & model);
};

#endif // TIMELINEMODEL_HPP
