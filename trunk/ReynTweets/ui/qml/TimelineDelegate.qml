import QtQuick 1.1

// Delegate tweet
TweetPane {
	width: timeline_pane.width
	tweet: model.get(index)
}
