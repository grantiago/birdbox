#!/usr/bin/env python3

###########
# my twitter app with rw permissons
# dev tweetajpg
###########
# importing the module

import tweepy

def main():
    twitter_auth_keys = {
        "consumer_key"        : "key",
        "consumer_secret"     : "skey",
        "access_token"        : "token",
        "access_token_secret" : "stoken"
    }
 
    auth = tweepy.OAuthHandler(
            twitter_auth_keys['consumer_key'],
            twitter_auth_keys['consumer_secret']
            )
    auth.set_access_token(
            twitter_auth_keys['access_token'],
            twitter_auth_keys['access_token_secret']
            )
    api = tweepy.API(auth)
 
    # Upload image
    media = api.media_upload("swell.png")
 
    # Post tweet with image
     # TODO
     # name it with formated time stamp . kestrel.jpg
    tweet = "north pacific wave height today."
    post_result = api.update_status(status=tweet, media_ids=[media.media_id])
 
if __name__ == "__main__":
    main()
