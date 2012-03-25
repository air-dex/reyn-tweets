#include <QtDeclarative>
#include "timelinemodel.hpp"

/////////////
// Coplien //
/////////////

TimelineModel::TimelineModel() :
	QObject(),
	QList<Tweet *>(),
	statuses()
{
	connect(this, SIGNAL(timelineChanged()),
			this, SLOT(syncModel()));
}

// Destructor
TimelineModel::~TimelineModel() {
	clear();
	disconnect(this, SIGNAL(timelineChanged()),
			   this, SLOT(syncModel()));
}

// Copy constructor
TimelineModel::TimelineModel(const TimelineModel & model) :
	QObject(),
	QList<Tweet *>(),
	statuses()
{
	recopie(model);
}

// Copying a Timeline
TimelineModel::TimelineModel(const Timeline & tl) :
	QObject(),
	QList<Tweet *>(),
	statuses()
{
	setTimeline(tl);
}

// Affectation of a timeline model
const TimelineModel & TimelineModel::operator=(const TimelineModel & model) {
	recopie(model);
	return *this;
}

// Affectation of a timeline
const TimelineModel & TimelineModel::operator=(const Timeline & tl) {
	setTimeline(tl);
	return *this;
}

// Recopying a Timeline model
void TimelineModel::recopie(const TimelineModel & model) {
	statuses = model.statuses;
	syncTimeline();
}


////////////////////////
// Timeline integrity //
////////////////////////

// Getting a reference on the timeline
Timeline & TimelineModel::getTimelineRef() {
	return statuses;
}

// Reading the timeline property
Timeline TimelineModel::getTimeline() {
	return statuses;
}

// Writing the timeline property
void TimelineModel::setTimeline(Timeline tl) {
	statuses = tl;
	syncModel();
}

// Updating the model.
void TimelineModel::syncModel() {
	clear();

	for (Timeline::Iterator it = statuses.begin();
		 it != statuses.end();
		 ++it)
	{
		append(it.operator->());
	}
}


/////////////
// For QML //
/////////////

// Declaring to the QML components
void TimelineModel::declareQML() {
	qmlRegisterType<TimelineModel>("ReynTweetsEntities",
								   0, 1,
								   "TimelineModel2");
}

// Syncing the timeline.
void TimelineModel::syncTimeline() {
	Timeline newTimeline;

	for (TimelineModel::Iterator it = begin();
		 it != end();
		 ++it)
	{
		if (*it) {
			newTimeline.append(**it);
		}
	}

	statuses = newTimeline;
	syncModel();	// Pointers on new objects
}
