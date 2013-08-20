#include "uiconstants.hpp"

#include <QtQml>
#include "../logic/reyntweetsutils.hpp"

// Constructor
UIConstants::UIConstants() :
	QObject()
{}

// Declare the class to the QML system.
void UIConstants::declareQML() {
	// @uri ReynTweetsComponents
	qmlRegisterType<UIConstants>(ReynTweets::QML_LIBRARY_NAME.toLatin1().constData(),
								 ReynTweets::MAJOR_VERSION, ReynTweets::MINOR_VERSION,
								 "Constants");
}

// Official version of Reyn Tweets
QString UIConstants::getVersion() {
	QString versionString = "";

	versionString.append(QString::number(ReynTweets::MAJOR_VERSION))
			.append('.')
			.append(QString::number(ReynTweets::MINOR_VERSION));

	if (ReynTweets::BUGFIX_VERSION > 0) {
		versionString.append('.')
				.append(QString::number(ReynTweets::BUGFIX_VERSION));
	}

	return versionString;
}


////////////////
// Properties //
////////////////

//////////////////////
// Application size //
//////////////////////

// Width (reyn_tweets_width)
int UIConstants::getReynTweetsWidth() {
	return 360;
}

// Height (reyn_tweets_height)
int UIConstants::getReynTweetsHeight() {
	return 640;
}

// Margin (margin)
int UIConstants::getMargin() {
	return 5;
}


////////////
// Colors //
////////////

// Orange Reyn Tweets (orange)
QColor UIConstants::getOrange() {
	return QColor("#eb8801");
}

// Grey (grey)
QColor UIConstants::getGrey() {
	return QColor("#c4c4c4");
}

// Light grey (very_light_grey)
QColor UIConstants::getVeryLightGrey() {
	return QColor("#fafafa");
}

// White (white)
QColor UIConstants::getWhite() {
	return QColor(Qt::white);
}

// Black (black)
QColor UIConstants::getBlack() {
	return QColor(Qt::black);
}

// Red (red)
QColor UIConstants::getRed() {
	return QColor(Qt::red);
}

// Green for mentions (green_mention)
QColor UIConstants::getGreenMention() {
	return QColor("#b8fe86");
}

// Green for mentions (light_green_mention)
QColor UIConstants::getLightGreenMention() {
	return QColor("#d3ffb4");
}

// Blue for Direct messages (blue_dm)
QColor UIConstants::getBlueDM() {
	return QColor("#90c0fd");
}

// Light blue for Direct messages (light_blue_dm)
QColor UIConstants::getLightBlueDM() {
	return QColor("#b3d3fd");
}

// Orange for own tweets (orange_author)
QColor UIConstants::getOrangeAuthor() {
	return QColor("#ffd35e");
}

// Orange for own tweets (light_orange_author)
QColor UIConstants::getLightOrangeAuthor() {
	return QColor("#ffe08d");
}


//////////
// Font //
//////////

// Font used for Reyn Tweets (font)
QString UIConstants::getFont() {
	#ifdef Q_OS_WIN
		return "Calibri";
	#elif defined(Q_OS_LINUX)
		return "Ubuntu";
	#endif
}

// XL (font_size_title)
int UIConstants::getFontSizeXL() {
	#ifdef Q_OS_WIN
		return 36;
	#elif defined(Q_OS_LINUX)
		return 36;
	#endif
}

// Large (font_size_large)
int UIConstants::getFontSizeL() {
	#ifdef Q_OS_WIN
		return 16;
	#elif defined(Q_OS_LINUX)
		return 16;
	#endif
}

// Medium (font_size)
int UIConstants::getFontSizeM() {
	#ifdef Q_OS_WIN
		return 11;
	#elif defined(Q_OS_LINUX)
		return 11;
	#endif
}

// Small (font_size_s)
int UIConstants::getFontSizeS() {
	#ifdef Q_OS_WIN
		return 10;
	#elif defined(Q_OS_LINUX)
		return 10;
	#endif
}

// XS (font_size_xs)
int UIConstants::getFontSizeXS() {
	#ifdef Q_OS_WIN
		return 9;
	#elif defined(Q_OS_LINUX)
		return 9;
	#endif
}

// XXS (font_size_xxs)
int UIConstants::getFontSizeXXS() {
	#ifdef Q_OS_WIN
		return 7;
	#elif defined(Q_OS_LINUX)
		return 7;
	#endif
}


//////////////////
// Miscanellous //
//////////////////

// Folder storing the icons (icon_folder)
QString UIConstants::getIconFolder() {
	return "/resources/icons";
}
