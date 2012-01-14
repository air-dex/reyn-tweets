#ifndef HASHTAGLIST_HPP
#define HASHTAGLIST_HPP

#include "hashtag.hpp"
#include "reyntweetslistable.hpp"
//#include "reyntweetsserializablelist.hpp"

class HashtagList : public ReynTweetsListable, public QList<Hashtag>
{//*
	public:
		HashtagList();

	protected:
		virtual void syncProperties();
		virtual void syncMembers();//*/
};

#endif // HASHTAGLIST_HPP
