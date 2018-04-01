// automatically generated by the FlatBuffers compiler, do not modify

package com.example.hellojni.ReposNormal;

import com.google.gson.*;

@SuppressWarnings("unused")
public final class User{
  String login;
  long id;
  String avatar_url;
  String gravatar_id;
  String url;
  String html_url;
  String followers_url;
  String following_url;
  String gists_url;
  String starred_url;
  String subscriptions_url;
  String organizations_url;
  String repos_url;
  String events_url;
  String received_events_url;
  String type;
  boolean site_admin;

  public User fromJson(String json) {
    JsonObject jsonObj = (new JsonParser().parse(json)).getAsJsonObject();
    this.login = jsonObj.get("login").getAsString();
    this.id = jsonObj.get("id").getAsLong();
    this.avatar_url = jsonObj.get("avatar_url").getAsString();
    this.gravatar_id = jsonObj.get("gravatar_id").getAsString();
    this.url = jsonObj.get("url").getAsString();
    this.html_url = jsonObj.get("html_url").getAsString();
    this.followers_url = jsonObj.get("followers_url").getAsString();
    this.following_url = jsonObj.get("following_url").getAsString();
    this.gists_url = jsonObj.get("gists_url").getAsString();
    this.starred_url = jsonObj.get("starred_url").getAsString();
    this.subscriptions_url = jsonObj.get("subscriptions_url").getAsString();
    this.organizations_url = jsonObj.get("organizations_url").getAsString();
    this.repos_url = jsonObj.get("repos_url").getAsString();
    this.events_url = jsonObj.get("events_url").getAsString();
    this.received_events_url = jsonObj.get("received_events_url").getAsString();
    this.type = jsonObj.get("type").getAsString();
    this.site_admin = jsonObj.get("site_admin").getAsBoolean();
    return this;
  }
}

