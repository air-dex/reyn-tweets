/// @file refreshtimelineprocess.hpp
/// @brief Header of RefreshTimelineProcess
/// @author Romain Ducher
///
/// @section LICENSE
///
/// Copyright 2013 Romain Ducher
///
/// This file is part of Reyn Tweets.
///
/// Reyn Tweets is free software: you can redistribute it and/or modify
/// it under the terms of the GNU Lesser General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
///
/// Reyn Tweets is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU Lesser General Public License for more details.
///
/// You should have received a copy of the GNU Lesser General Public License
/// along with Reyn Tweets. If not, see <http://www.gnu.org/licenses/>.

#ifndef REFRESHTIMELINEPROCESS_HPP
#define REFRESHTIMELINEPROCESS_HPP

#include "genericprocess.hpp"
#include "../../connection/twitter/reyntwittercalls.hpp"
#include "../core/timelines/timeline.hpp"

/// @class RefreshTimelineProcess
/// @brief Base class for processes refreshing a timeline.
///
/// The process for refreshing timelines consists in two steps :<ol>
/// <li>The main step will load the most recent tweets which are older than
/// the most recent tweet of the timeline to refresh.</li>
/// <li>However the Twitter API endpoint which retrieves the Home Timeline only
/// gives a limited number of tweets. It is determined by the "count" parameter
/// given to the endpoint, which gets a default value
/// (Twitter::DEFAULT_TWEETS_COUNT). But the number of newer tweets can be
/// greater than "count" and in this case the Twitter API will not give all the
/// tweets. So in this case Reyn Tweets will have to load the missing tweets.
/// They are called "intermediate tweets" because they are
/// older than the most recent tweet of the timeline before refreshing and
/// more recent than the newer tweets already loaded.</li>
/// </ol>
///
/// In order to avoid reloading tweets, Reyn Tweets tries to load as much tweets
/// as possible every time it loads tweets in the process. For this, Reyn Tweets
/// uses the maxmum value allowed for "count" (Twitter::MAX_TWEETS_COUNT).
/// But some tweets might still miss. That's why there is a second step
/// in the process.
///
/// The result of the process is a QVariantMap with three fields :<ul>
/// <li><strong>"newer_tweets"</strong> : the timeline with all the newer
/// tweets.</li>
/// <li><strong>"gap"</strong> : boolean indicating if despite the 2nd step of
/// the process, some tweets are still missing.</li>
/// <li><strong>"intermediate_end"</strong> : if the process has to load
/// timelines several times, all the timeline requests might not end successfully.
/// The process will stop at the first failed end and the CoreResult of these
/// failed end will be stored in this field.</li>
/// </ul>
class RefreshTimelineProcess : public GenericProcess
{
	Q_OBJECT

	public:
		/// @fn RefreshTimelineProcess(Tweet oldestTweet);
		/// @brief Constructor
		/// @param oldestTweet Value of latestTweet
		RefreshTimelineProcess(Tweet oldestTweet);

		/// @fn void startProcess();
		/// @brief Starting the process by getting the most recent tweets.
		void startProcess();


	protected:
		///////////
		// Calls //
		///////////

		/// @brief Entity calling Twitter
		ReynTwitterCalls twitter;


		////////////////
		// Parameters //
		////////////////

		/// @brief Most recent tweet in the timeline to refresh
		Tweet latestTweet;


		///////////////////////////
		// Internal informations //
		///////////////////////////

		/// @brief All the new tweets
		Timeline newerTweets;

		/// @brief Oldest tweet among the ones retrieved through
		/// the Twitter API.
		///
		/// The process stops when <code>oldestNewTweet == sinceID</code>.
		Tweet oldestNewTweet;

		/// @brief Result of the process.
		///
		/// If some tweets are loaded, the CoreResult is
		/// ReynTweets::TIMELINE_RETRIEVED, even if there are problems
		/// while retrieving intermediate tweets. Actually it depends on what
		/// happens while loading the most recent tweets.
		/// If something bad happens while loading intermediate tweets, it will
		/// be stored in the process results in a field called
		/// "intermediate_result".
		ReynTweets::CoreResult finalEnd;


		/////////////////
		// The process //
		/////////////////

		/// @fn void loadFirstTweets();
		/// @brief Loading the most recent tweets among the newer ones.
		void loadFirstTweets();

		/// @fn virtual void retrievingFirstTweets() = 0;
		/// @brief Calling Twitter to load the most recent tweets.
		virtual void retrievingFirstTweets() = 0;

		/// @fn void loadIntermediateTweets();
		/// @brief If loadFirstTweets(); does not load all the tweets, this
		/// method will load "intermediate tweets", i.e. tweets whch are both
		/// older than the ones loadad by loadFirstTweets(); and newer
		/// than sinceID.
		void loadIntermediateTweets();

		/// @fn virtual void retrievingIntermediateTweets() = 0;
		/// @brief Calling Twitter to load intermediate tweets.
		virtual void retrievingIntermediateTweets() = 0;

		/// @fn virtual void endProcess(QString errorMessage,
		///								bool gap = false,
		///								ReynTweets::CoreResult intermediateEnd = ReynTweets::INVALID_END);
		/// @brief Special overriding of endProcess();
		/// @param errorMessage Process error message.
		/// @param intermediateEnd Value of the field "intermediate_end".
		/// @param gap Value of the field "gap".
		virtual void endProcess(QString errorMessage,
								bool gap = false,
								ReynTweets::CoreResult intermediateEnd = ReynTweets::INVALID_END);

	protected slots:
		/// @fn void loadFirstTweetsEnded(ResultWrapper res);
		/// @brief After loading the most recent tweets.
		/// @param res Results from the Twitter API
		void loadFirstTweetsEnded(ResultWrapper res);

		/// @fn void loadIntermediateTweetsEnded(ResultWrapper res);
		/// @brief After loading intermediate tweets.
		/// @param res Results from the Twitter API
		void loadIntermediateTweetsEnded(ResultWrapper res);
};

#endif // REFRESHTIMELINEPROCESS_HPP
