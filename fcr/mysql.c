#include "mysql.h"
#include <stdio.h>
#include <mysql/mysql.h>
#include <string.h>

#define SENTENCELEN 500

void myserver_init(void)
{
    if(mysql_init(&myserver) == NULL) {
        perror("mysql_init");
    }
    if (mysql_library_init(0, NULL, NULL) != 0) {
        perror("mysql_library_init");
    }
    if (mysql_real_connect(&myserver, "127.0.0.1", "root", "1017129dameinv", "fcr", 0, NULL, 0) == NULL) {
        perror("mysql_real_connect");
    }
    if(mysql_set_character_set(&myserver, "utf8") < 0) {
        perror("mysql_set_character_set");
    }
    printf("连接数据库成功\n");
}

void add_to_fcr_register(char *username, char *password)
{
    char buff[SENTENCELEN];
    sprintf(buff, "insert into register values(\"%s\",\"%s\")", username, password);
    mysql_query(&myserver, buff);
}

int fcr_login(char *username, char *password)
{
    char buff[SENTENCELEN];
    sprintf(buff, "select *from register where username = \"%s\" and password = \"%s\"", username, password);
    mysql_query(&myserver, buff);
    MYSQL_RES *result = mysql_store_result(&myserver);
    if (mysql_num_rows(result) > 0) {
        return 0;
    } else {
        return -1;
    }
}

void add_fri_each(char *ua, char *ub)
{
    char buff[SENTENCELEN];                                                         
    sprintf(buff, "insert into frilist values(\"%s\",\"%s\")", ua, ub);
    mysql_query(&myserver, buff);                                                   
}

void del_fri_each(char *ua, char *ub)
{
    char buff[SENTENCELEN];                                            
    sprintf(buff, "select *from frilist where ua = \"%s\" and ub = \"%s\"", ua, ub);
     mysql_query(&myserver, buff);                        
     MYSQL_RES *result = mysql_store_result(&myserver);
     if (mysql_num_rows(result) > 0) {                 
        sprintf(buff, "delete from frilist where ua = \"%s\" and ub = \"%s\"", ua, ub);
        mysql_query(&myserver, buff);                        
         return;                                     
     } else {                                          
         sprintf(buff, "delete from frilist where ua = \"%s\" and ub = \"%s\"", ub, ua);
         mysql_query(&myserver, buff);                        
     }                                                 
}

char *get_fri_list(char *username)
{
    char buff[SENTENCELEN];                                                         
    memset(buffer, 0 , 1024);
    sprintf(buff, "select *from frilist where ua = \"%s\"", username);
    mysql_query(&myserver, buff);                     
    MYSQL_RES *result = mysql_store_result(&myserver);
    //int rows = mysql_num_rows(result);
    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        strcat(buffer, row[1]);
        strcat(buffer, "*");
    }
    sprintf(buff, "select *from frilist where ub = \"%s\"", username);
    mysql_query(&myserver, buff);                                     
    result = mysql_store_result(&myserver);                
    while ((row = mysql_fetch_row(result))) {                         
        strcat(buffer, row[0]);                                       
        strcat(buffer, "*");                                          
    }                                                                 
    
    return buffer;
}

void create_group(char *groupname, char *username, int groupowner, int guan)
{
    char buff[SENTENCELEN];                                                         
    sprintf(buff, "insert into grouplist values(\"%s\",\"%s\",%d,%d)", groupname, username, groupowner, guan);
    mysql_query(&myserver, buff);                                                   
}

void come_group(char *groupname, char *username, int groupowner, int guan)                                  
{                                                                                                             
    char buff[SENTENCELEN];                                                                                   
    sprintf(buff, "insert into grouplist values(\"%s\",\"%s\",%d,%d)", groupname, username, groupowner, guan);
    mysql_query(&myserver, buff);                                                                             
}                                                                                                             

void back_group(char *groupname, char *username)
{
    char buff[SENTENCELEN];                                            
    //当没群时
    sprintf(buff, "select *from grouplist where groupname = \"%s\" and username = \"%s\"", groupname, username);
    mysql_query(&myserver, buff);                                     
    MYSQL_RES *result = mysql_store_result(&myserver);
    MYSQL_ROW row;                                    
    row = mysql_fetch_row(result);
    if (strcmp(row[3], "1") == 0) {
    sprintf(buff, "delete from grouplist where groupname = \"%s\"", groupname);
    mysql_query(&myserver, buff);                     
    } else {
        sprintf(buff, "delete from grouplist where groupname = \"%s\" and username = \"%s\"", groupname, username);
        mysql_query(&myserver, buff);                                                                              
    }
}

char *get_group_list(char *username)                                    
{                                                                     
    memset(buffer, 0 , 1024);
    char buff[SENTENCELEN];                                           
    sprintf(buff, "select *from grouplist where username = \"%s\"", username);
    mysql_query(&myserver, buff);                                     
    MYSQL_RES *result = mysql_store_result(&myserver);                
    MYSQL_ROW row;                                                    
    while ((row = mysql_fetch_row(result))) {                         
        strcat(buffer, row[0]);                                       
        strcat(buffer, "*");                                          
    }                                                                 
    return buffer;                                                    
}                                                                     

char *get_group_m(char *groupname)                                          
{                                                                             
    char buff[SENTENCELEN];                                                   
    //memset(buff, 0 , 1024);
    sprintf(buff, "select *from grouplist where groupname = \"%s\"", groupname);
    mysql_query(&myserver, buff);                                             
    MYSQL_RES *result = mysql_store_result(&myserver);                        
    MYSQL_ROW row;                                                            
    while ((row = mysql_fetch_row(result))) {                                 
        strcat(buffer, row[1]);                                               
        strcat(buffer, "*");                                                  
    }                                                                         
    return buffer;                                                            
}                                                                             

int set_guan(char *ua, char *username, char *groupname)
{
    char buff[SENTENCELEN];                                                     
    sprintf(buff, "select *from grouplist where groupname = \"%s\" and username = \"%s\" and groupowner = 1", groupname, ua);
    mysql_query(&myserver, buff);                                               
    MYSQL_RES *result = mysql_store_result(&myserver);                          
    if (mysql_num_rows(result) > 0) {
        sprintf(buff, "update grouplist set guan = 1 where username = \"%s\" and groupname = \"%s\"", username, groupname);
        mysql_query(&myserver, buff);                                               
        return 0;                    
    } else {                         
        return -1;                   
    }                                
}

int group_ti(char *ua, char *username, char *groupname)                                                                      
{                                                                                                                            
    char buff[SENTENCELEN];                                                                                                  
    sprintf(buff, "select *from grouplist where groupname = \"%s\" and username = \"%s\" and guan = 1", groupname, ua);
    mysql_query(&myserver, buff);                                                                                            
    MYSQL_RES *result = mysql_store_result(&myserver);                                                                       
    if (mysql_num_rows(result) > 0) {                                                                                        
        sprintf(buff, "delete from grouplist where groupname = \"%s\" and username = \"%s\"", groupname, username);
        mysql_query(&myserver, buff);                                                                                        
        return 0;                                                                                                            
    } else {                                                                                                                 
        return -1;                                                                                                           
    }                                                                                                                        
}                                                                                                                            

void group_mess(char *groupname, char *ua, char *message)
{    
    char buff[SENTENCELEN];                                                         
    sprintf(buff, "insert into groupchat values(\"%s\",\"%s\", \"%s\")", groupname, ua, message);   
    mysql_query(&myserver, buff);                                                   
}

MYSQL_RES *pull_groupmess(char *groupname)
{
    char buff[SENTENCELEN];                                                                                            
    sprintf(buff, "select *from groupchat where groupname = \"%s\"", groupname);
    mysql_query(&myserver, buff);                                                                                      
    RE = mysql_store_result(&myserver);                                                                 
    return RE;
}
