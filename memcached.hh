/*
* Max pending connections queue length
*/
#define MAX_CONNECTIONS 25
#define CLIENT_BUFFER_SIZE 1024
#define MEMCACHED_PORT 11211
#define WHITESPACE " \t\n\v\f\r"

#define _WRITER(X) write(client_sockfd, X "\r\n", sizeof(X "\r\n"))

/*
* Replies
*/

#define STORED _WRITER("STORED")
#define NOT_STORED _WRITER("NOT_STORED")
#define EXISTS _WRITER("EXISTS")
#define NOT_FOUND _WRITER("NOT_FOUND")
#define DELETED _WRITER("DELETED")
#define TOUCHED _WRITER("TOUCHED")
#define END _WRITER("END")


/*
* Error strings
*/
#define ERROR _WRITER("ERROR")
#define CLIENT_ERROR(X) _WRITER("CLIENT_ERROR " X)
#define SERVER_ERROR(X) _WRITER("SERVER_ERROR " X)

/*
* This is the Cache Entry data structure stored as value in the map
*/
typedef struct {
	std::string key;
	uint16_t flags;
	int64_t expiry;
	/* not including the delimiting \r\n */
	uint32_t bytes;
	uint64_t cas_unique;
	bool noreply;
	char *data;
} cache_entry;

static void write_VALUE(int client_sockfd, cache_entry *entry)
{
	std::ostringstream os;  
	os << "VALUE " << entry->key << " " << entry->flags << " " << entry->bytes << "\r\n";
	write(client_sockfd, os.str().c_str(), strlen(os.str().c_str()));
}

static void print_map(std::map<std::string, cache_entry> *map)
{
	for (const auto &p : *map) {
		std::cout << "map[" << p.first << "] = ";
		std::cout << p.second.key << ", ";
		std::cout << p.second.flags << ", ";
		std::cout << p.second.expiry << ", ";
		std::cout << p.second.bytes << '\n';
	}
}