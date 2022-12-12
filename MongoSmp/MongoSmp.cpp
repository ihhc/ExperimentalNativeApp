#define BSON_STATIC
#define MONGOC_STATIC
#include <mongoc.h>
#include <iostream>


int main()
{
    const char* uri_string = "mongodb://localhost:27017";
    mongoc_uri_t* uri;
    mongoc_client_t* client;
    mongoc_database_t* database;
    mongoc_collection_t* collection;
    bson_t* command, reply, * insert;
    bson_error_t error;
    char* str;
    bool retval;
    int ret = 1;
    mongoc_init();

    uri = mongoc_uri_new_with_error(uri_string, &error);
    if (!uri) {
        std::cout << "failed to parse URI: " << uri_string << "Error: " << error.message;
        return ret;
    }

    client = mongoc_client_new_from_uri(uri);
    if (!client)
        return ret;

    mongoc_client_set_appname(client, "MoongoSmp");
    database = mongoc_client_get_database(client, "TestDB");
    collection = mongoc_client_get_collection(client, "TestDB", "TestCollection");
    command = BCON_NEW("ping", BCON_INT32(1));

    retval = mongoc_client_command_simple(
        client, "TestDB", command, NULL, &reply, &error);

    if (!retval) {
        std::cout << "\n" << error.message;
        return ret;
    }

    str = bson_as_json(&reply, NULL);
    std::cout << "\n" << str;

    insert = BCON_NEW("title", BCON_UTF8("Construction specification"));
    if (!mongoc_collection_insert_one(collection, insert, NULL, NULL, &error)) 
        std::cout << "\n" << error.message;


    bson_destroy(insert);
    bson_destroy(&reply);
    bson_destroy(command);
    bson_free(str);
    mongoc_collection_destroy(collection);
    mongoc_database_destroy(database);
    mongoc_uri_destroy(uri);
    mongoc_client_destroy(client);
    mongoc_cleanup();

    ret = 0;
    std::cout << "\n SUCCESS";
    return ret;
   
}


