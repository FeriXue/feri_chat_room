#include "nextpth.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "all.h"
#include "client_menu.h"
#include "socket.h"
#include "client.h"
#include "log.h"
#include "proto.h"

void *refresha(void *c)
{    
    client_t *client = (client_t *)c;
    //printf("收消息线程开启\n");
    while (1) {
        request_refresh_pravmess_t *req = create_request_refresh_pravmess(PRAV, client->username);
        uint32_t nwritten = FERI_block_write(client->conn_fd, (char *)req, req->head.length);     
        if (nwritten != req->head.length) {                                                       
            log_error("send to server failed, exit");                                             
            abort();                                                                              
        }                                                                                         
        response_status_t *resp = (response_status_t *)malloc(sizeof(response_status_t));         
        int nread = FERI_block_read(client->conn_fd, (char *)resp, sizeof(response_status_t));    
        if (nread != sizeof(response_status_t)) {                                                 
            log_error("recv from server failed, exit");                                           
            abort();                                                                              
        }                                                                                         
        if (resp->head.type != RESP_STATUS) {                                                     
            log_error("recv from server data type != RESP_STATUS, exit");                         
            abort();                                                                              
        }                                                                                         
        if (resp->head.magic != FERI_PROTO_HEAD) {                                                
            log_error("recv from server data error, exit");                                       
            abort();                                                                              
        }                                                                                         
        if (strcmp(resp->message, "您暂时没有消息") == 0) {
            sleep(3);                                                                                 
            continue;
        } else {
            printf("\n\t%s\n", resp->message);                                                          
            sleep(3);                                                                                 
        }
    }
    return NULL;
}
