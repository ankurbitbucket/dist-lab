// this is the lock server
// the lock client has a similar interface

#ifndef lock_server_h
#define lock_server_h

#include <string>
#include <pthread.h>
#include <ext/hash_map>
#include "lock_protocol.h"
#include "lock_client.h"
#include "rpc.h"

typedef struct lock_status
{
	int clt;
	bool st;
}lck;

struct eqstr {
	bool operator()(const int& a, const int& b) const {
		return ( a == b );
	}
};

struct hashme {
	int operator() (const int& key) const {
		return (key);
	}
};

struct eqstr2 {
	bool operator()(const lock_protocol::lockid_t& a, const lock_protocol::lockid_t& b) const {
		return ( a == b );
	}
};

struct hashme2 {
	int operator() (const lock_protocol::lockid_t& key) const {
		return (key);
	}
};

typedef __gnu_cxx::hash_map<lock_protocol::lockid_t, lck, hashme2, eqstr2> lock;
typedef __gnu_cxx::hash_map<lock_protocol::lockid_t, lck, hashme2, eqstr2>::iterator lock_iterator;

class lock_server {
private:
	lock locklist;
	pthread_mutex_t table_lock;

protected:
  	int nacquire;

public:
  	lock_server();
  	~lock_server() {};
  	lock_protocol::status stat(int clt, lock_protocol::lockid_t lid, int &);
  	lock_protocol::status acquire(int clt, lock_protocol::lockid_t lid, int &);
  	lock_protocol::status release(int clt, lock_protocol::lockid_t lid, int &);
};

#endif 







