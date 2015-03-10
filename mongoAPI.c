#include <time.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include "analyser.h"
#include "EBULink.h"


int insertIn (char *buff, long timedate, char *DB, char *coll) //(char *DB, char *coll) Takes the buffer-data, the timestamp, which database and which collection argument
{

    mongoc_client_t *client;
    mongoc_collection_t *collection;
    mongoc_cursor_t *cursor;
    bson_error_t error;
    bson_oid_t oid;
    bson_t *doc;

    mongoc_init ();

    client = mongoc_client_new ("mongodb://localhost:27017/");
    collection = mongoc_client_get_collection (client, DB, coll);	//(client, DB, coll);
	

	doc = bson_new ();
    bson_oid_init (&oid, NULL);
    BSON_APPEND_OID (doc, "_id", &oid);					// ID for every document
    //BSON_APPEND_UTF8(doc, "Data:" , buff);				// The actually data
    BSON_APPEND_BINARY(doc, "Data:", BSON_SUBTYPE_BINARY, buff, 48);
	BSON_APPEND_INT64(doc, "Time:", timedate); 			// The time the data package is inserted (in microseconds) from baseline
    
	if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, doc, NULL, &error)) {
        printf ("%s\n", error.message);
    }

    bson_destroy (doc);
    mongoc_collection_destroy (collection);
    mongoc_client_destroy (client);
    return 0;
}

int extract(){
	mongoc_client_t *client;
	mongoc_collection_t *collection;
	mongoc_cursor_t *cursor;
	bson_error_t error;
	const bson_t *doc;
	const char *uristr = "mongodb://127.0.0.1/";
	const char *collection_name = "test";
	char *str;

	bson_t query;

	bson_t fields;
	bson_init(&fields);
	BSON_APPEND_BOOL(&fields, "Data", 1);
	BSON_APPEND_BOOL(&fields, "_id", 0);





	mongoc_init ();
	client = mongoc_client_new (uristr);
	if (!client) {
		fprintf (stderr, "Failed to parse URI.\n");
		return EXIT_FAILURE;
	}
	bson_init (&query);
	collection = mongoc_client_get_collection (client, "test", collection_name);


	cursor = mongoc_collection_find (collection,MONGOC_QUERY_NONE,0,0,0,&query, &fields, /* Fields, NULL for all. */ NULL); /* Read Prefs, NULL for default */
	while (mongoc_cursor_next (cursor, &doc)) {
		str = bson_as_json (doc, NULL);
		fprintf (stdout, "%s\n", str);
		bson_free (str);
	}
	if (mongoc_cursor_error (cursor, &error)) {
		fprintf (stderr, "Cursor Failure: %s\n", error.message);
		return EXIT_FAILURE;
	}
	bson_destroy (&query);
	mongoc_cursor_destroy (cursor);
	mongoc_collection_destroy (collection);
	mongoc_client_destroy (client);
	mongoc_cleanup ();
	return EXIT_SUCCESS;
}



