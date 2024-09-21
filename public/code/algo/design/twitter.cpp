#include <chrono>
#include <iostream>
#include <queue>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;

class Twitter;

class Tweet {
public:
  int id;
  int time;
  Tweet *next;
  Tweet(int id, int time) : id(id), time(time) {}

  void setNext(Tweet *n) { this->next = n; }
}; // 保存了发布者的 id 和该推文的发布时间

class User {
private:
  int id;
  set<int> followed;
  Tweet *head;

public:
  friend class Twitter;

  User(int userId) {
    followed = set<int>();
    this->id = userId;
    this->head = NULL;
    follow(id);
  }

  void follow(int userId) { followed.insert(userId); }

  void unfollow(int userId) {
    if (userId != this->id)
      followed.erase(userId);
  }

  set<int> &getfollowed() { return followed; }

  void post(int tweeId) {
    Tweet *twt = new Tweet(
        tweeId, chrono::system_clock::to_time_t(chrono::system_clock::now()));
    twt->setNext(head);
    head = twt;
  }
}; // 保存了他关注的人列表和推文列表

class Twitter {
private:
  static int timestamp;

  unordered_map<int, User> userMap;

public:
  Twitter() { userMap = unordered_map<int, User>(); }
  // user 发表一条 tweet 动态
  void postTweet(int userId, int tweetId) {
    if (userMap.find(userId) == userMap.end()) {
      userMap.insert({userId, User(userId)});
    }
    User &u = userMap.at(userId);
    u.post(tweetId);
  }

  // 返回该 user 关注的人（包括他自己）最近的动态 id，
  // 最多 10 条，而且这些动态必须按从新到旧的时间线顺序排列
  vector<int> getNewsFeed(int userId) {
    vector<int> ans;

    priority_queue<pair<int, Tweet *>> pq;
    set<int> &followed = userMap.at(userId).getfollowed();
    for (int id : followed) {
      Tweet *t = gettwt(&userMap.at(id));
      if (t) {
        pq.push({t->time, t});
      }
    }
    int count = 0;
    while (!pq.empty() && count < 10) {
      Tweet *t = pq.top().second;
      pq.pop();
      ans.push_back(t->id);
      count++;
      if (t->next) {
        pq.push({t->next->time, t->next});
      }
    }

    return ans;
  }

  // follower 关注 followee，如果 Id 不存在则新建
  void follow(int followerId, int followeeId) {
    if (userMap.find(followerId) == userMap.end()) {
      User u(followerId);
      userMap.insert({followerId, u});
    }
    if (userMap.find(followeeId) == userMap.end()) {
      User u(followeeId);
      userMap.insert({followeeId, u});
    }
    userMap.at(followerId).follow(followeeId);
  }

  Tweet *gettwt(User *t) { return t->head; }

  // follower 取关 followee，如果 Id 不存在则什么都不做
  void unfollow(int followerId, int followeeId) {
    if (userMap.find(followerId) != userMap.end()) {
      User &flwer = userMap.at(followerId);
      flwer.unfollow(followeeId);
    }
  }
};

int Twitter::timestamp = 0;

int main() {
  Twitter twitter;          // 创建一个 Twitter 对象
  twitter.postTweet(1, 10); // 用户 a 发布一条 id 为 10 的推文
  vector<int> feed = twitter.getNewsFeed(1); // 用户 a 获取所有推文
  cout << "User a's news feed: ";            // 输出用户 a 的推文
  for (int id : feed) {
    cout << id << " ";
  }
  cout << endl;
  twitter.postTweet(2, 20);      // 用户 b 发布一条 id 为 20 的推文
  twitter.follow(1, 2);          // 用户 a 关注用户 b
  feed = twitter.getNewsFeed(1); // 用户 a 获取推文
  cout << "User a's news feed after following user b: "; // 输出用户 a 的推文
  for (int id : feed) {
    cout << id << " ";
  }
  cout << endl;
  twitter.unfollow(1, 2);        // 用户 a 取消关注用户 b
  feed = twitter.getNewsFeed(1); // 用户 a 获取推文
  cout << "User a's news feed after unfollowing user b: "; // 输出用户 a 的推文
  for (int id : feed) {
    cout << id << " ";
  }
  cout << endl;
  return 0;
}