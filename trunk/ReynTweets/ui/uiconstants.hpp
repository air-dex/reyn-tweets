#ifndef UICONSTANTS_HPP
#define UICONSTANTS_HPP

#include <QObject>
#include <QString>
#include <QColor>

/// @class UIConstants
/// @brief Class whose values depends on the UI. Singleton.
class UIConstants : public QObject
{
		Q_OBJECT
	public:
		/// @fn UIConstants();
		/// @brief Constructor
		UIConstants();

		/// @fn static void declareQML();
		/// @brief Declares the class to the QML system.
		static void declareQML();

		/// @fn Q_INVOKABLE QString getVersion();
		/// @brief Getting the official version of Reyn Tweets
		/// @return Version under the following form :
		/// <code>MAJOR_VERSION</code>.<code>MINOR_VERSION</code>.<code>BUGFIX_VERSION</code>
		Q_INVOKABLE QString getVersion();


	////////////////
	// Properties //
	////////////////
		
	protected:
		//////////////////////
		// Application size //
		//////////////////////

		// Width
		/// @property reyn_tweets_width
		/// @brief Reyn Tweets' width
		Q_PROPERTY(int reyn_tweets_width
				   READ getReynTweetsWidth)

		/// @fn int getReynTweetsWidth();
		/// @brief Reading the property reyn_tweets_width.
		/// @return Reyn Tweets' width
		int getReynTweetsWidth();

		// Height
		/// @property reyn_tweets_height
		/// @brief Reyn Tweets' height
		Q_PROPERTY(int reyn_tweets_height
				   READ getReynTweetsHeight)

		/// @fn int getReynTweetsHeight();
		/// @brief Reading the property reyn_tweets_height.
		/// @return Reyn Tweets' height
		int getReynTweetsHeight();

		// Margin
		/// @property margin
		/// @brief Reyn Tweets' margin
		///
		/// It is a universal value for margins in Reyn Tweets.
		Q_PROPERTY(int margin
				   READ getMargin)

		/// @fn int getMargin();
		/// @brief Reading the property margin.
		/// @return Reyn Tweets' margin
		int getMargin();


		////////////
		// Colors //
		////////////

		// Orange Reyn Tweets
		/// @property orange
		/// @brief Value for the orange color in Reyn Tweets.
		Q_PROPERTY(QColor orange
				   READ getOrange)

		/// @fn QColor getOrange();
		/// @brief Reading the property orange.
		/// @return Value for the orange color in Reyn Tweets.
		QColor getOrange();

		// Grey
		/// @property grey
		/// @brief Value for the grey color in Reyn Tweets.
		Q_PROPERTY(QColor grey
				   READ getGrey)

		/// @fn QColor getGrey();
		/// @brief Reading the property grey.
		/// @return Value for the grey color in Reyn Tweets.
		QColor getGrey();

		// Light grey
		/// @property very_light_grey
		/// @brief Light grey, used for gradients.
		Q_PROPERTY(QColor very_light_grey
				   READ getVeryLightGrey)

		/// @fn QColor getVeryLightGrey();
		/// @brief Reading the property very_light_grey.
		/// @return Light grey, used for gradients.
		QColor getVeryLightGrey();

		// White
		/// @property white
		/// @brief The white color.
		Q_PROPERTY(QColor white
				   READ getWhite)

		/// @fn QColor getWhite();
		/// @brief Reading the property white.
		/// @return The white color.
		QColor getWhite();

		// Black
		/// @property black
		/// @brief The black color.
		Q_PROPERTY(QColor black
				   READ getBlack)

		/// @fn QColor getBlack();
		/// @brief Reading the property black.
		/// @return The black color.
		QColor getBlack();

		// Red
		/// @property red
		/// @brief The red color.
		Q_PROPERTY(QColor red
				   READ getRed)

		/// @fn QColor getRed();
		/// @brief Reading the property red.
		/// @return The red color.
		QColor getRed();

		// Green for mentions (separator_color)
		/// @property green_mention
		/// @brief Green color for mentions.
		Q_PROPERTY(QColor green_mention
				   READ getGreenMention)

		/// @fn QColor getGreenMention();
		/// @brief Reading the property green_mention.
		/// @return Green color for mentions.
		QColor getGreenMention();

		// Green for mentions (middle_color)
		/// @property light_green_mention
		/// @brief Light green color for mentions. Used in gradients.
		Q_PROPERTY(QColor light_green_mention
				   READ getLightGreenMention)

		/// @fn QColor getLightGreenMention();
		/// @brief Reading the property light_green_mention.
		/// @return Light green color for mentions. Used in gradients.
		QColor getLightGreenMention();

		// Blue for Direct messages (separator_color)
		/// @property blue_dm
		/// @brief Blue color for Direct Messages (DM).
		Q_PROPERTY(QColor blue_dm
				   READ getBlueDM)

		/// @fn QColor getBlueDM();
		/// @brief Reading the property blue_dm.
		/// @return Blue color for Direct Messages (DM).
		QColor getBlueDM();

		// Blue for Direct messages (middle_color)
		/// @property light_blue_dm
		/// @brief Light blue color for Direct Messages (DM). Used in gradients.
		Q_PROPERTY(QColor light_blue_dm
				   READ getLightBlueDM)

		/// @fn QColor getLightBlueDM();
		/// @brief Reading the property light_blue_dm.
		/// @return Light blue color for Direct Messages (DM). Used in gradients.
		QColor getLightBlueDM();

		// Orange for own tweets (separator_color)
		/// @property orange_author
		/// @brief Orange color for the author.
		Q_PROPERTY(QColor orange_author
				   READ getOrangeAuthor)

		/// @fn QColor getOrangeAuthor();
		/// @brief Reading the property orange_author.
		/// @return Orange color for the author.
		QColor getOrangeAuthor();

		// Orange for own tweets (middle_color)
		/// @property light_orange_author
		/// @brief Light orange color for the author. Used in gradients.
		Q_PROPERTY(QColor light_orange_author
				   READ getLightOrangeAuthor)

		/// @fn QColor getLightOrangeAuthor();
		/// @brief Reading the property light_orange_author.
		/// @return Light orange color for the author. Used in gradients.
		QColor getLightOrangeAuthor();


		//////////
		// Font //
		//////////

		// Font used for Reyn Tweets
		/// @property font
		/// @brief Name of the font used for display.
		Q_PROPERTY(QString font
				   READ getFont)

		/// @fn QString getFont();
		/// @brief Reading the property font.
		/// @return Name of the font used for display.
		QString getFont();

		// XL font size (for big titles)
		/// @property font_size_title
		/// @brief XL font size.
		Q_PROPERTY(int font_size_title
				   READ getFontSizeXL)

		/// @fn int getFontSizeXL();
		/// @brief Reading the property font_size_title.
		/// @return XL font size.
		int getFontSizeXL();

		// Large font size
		/// @property font_size_large
		/// @brief Large font size.
		Q_PROPERTY(int font_size_large
				   READ getFontSizeL)

		/// @fn int getFontSizeL();
		/// @brief Reading the property font_size_large.
		/// @return Large font size.
		int getFontSizeL();

		// Medium font size
		/// @property font_size
		/// @brief Medium font size.
		Q_PROPERTY(int font_size
				   READ getFontSizeM)

		/// @fn int getFontSizeM();
		/// @brief Reading the property font_size.
		/// @return Medium font size.
		int getFontSizeM();

		// Small font size
		/// @property font_size_s
		/// @brief Small font size.
		Q_PROPERTY(int font_size_s
				   READ getFontSizeS)

		/// @fn int getFontSizeS();
		/// @brief Reading the property font_size_s.
		/// @return Small font size.
		int getFontSizeS();

		// XS font size
		/// @property font_size_xs
		/// @brief XS font size.
		Q_PROPERTY(int font_size_xs
				   READ getFontSizeXS)

		/// @fn int getFontSizeXS();
		/// @brief Reading the property font_size_xs.
		/// @return XS font size.
		int getFontSizeXS();

		// XXS font size
		/// @property font_size_xxs
		/// @brief XXS font size.
		Q_PROPERTY(int font_size_xxs
				   READ getFontSizeXXS)

		/// @fn int getFontSizeXXS();
		/// @brief Reading the property font_size_xxs.
		/// @return XXS font size.
		int getFontSizeXXS();


		//////////////////
		// Miscanellous //
		//////////////////

		// Folder storing the icons
		/// @property icon_folder
		/// @brief Folder storing the icons
		Q_PROPERTY(QString icon_folder
				   READ getIconFolder)

		/// @fn QString getIconFolder();
		/// @brief Reading the property icon_folder.
		/// @return Folder storing the icons
		QString getIconFolder();
};

#endif // UICONSTANTS_HPP
