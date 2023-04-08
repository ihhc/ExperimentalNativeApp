#include "hiredis.h"

int main()
{
    int port = 6379;
    redisContext* c = redisConnect("localhost", port);
    if (c != NULL && c->err) {
        printf("Error: %s\r\n", c->errstr);
        // handle error
    }
    else {
        printf("Connected to Redis\r\n");
    }

//redis commands
    redisReply* reply;
//key and value
    reply = (redisReply*)redisCommand(c, "EXISTS first");//check by key
    if (reply->type != REDIS_REPLY_STRING)
    {
        freeReplyObject(reply);
        reply = (redisReply*)redisCommand(c, "SET first 1 EX 10");//adding key value pair for 10 seconds
        if (reply->type != REDIS_REPLY_ERROR)
        {
            freeReplyObject(reply);
            reply = (redisReply*)redisCommand(c, "GET first");//reading value by key
            //reply = (redisReply*)redisCommand(c, "GETSET first 123");//or reading and updating existing value
            if (reply->type == REDIS_REPLY_STRING)
                printf("Value: first Key: %s\r\n", reply->str);
            else
                printf("Value not found\r\n");
            
            freeReplyObject(reply);
        }
        else
            freeReplyObject(reply);
    }

//and other commands: https://redis.io/commands/
 
//Deleting all values
    reply = (redisReply*)redisCommand(c, "FLUSHALL");
    freeReplyObject(reply);
    redisFree(c);
}
