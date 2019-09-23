#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include "proto.h"

MYSQL myserver;

MYSQL_RES *RE;

char buffer[1024];

void myserver_init(void);

void add_to_fcr_register(char *username, char *password);

int fcr_login(char *username, char *password);

void add_fri_each(char *ua, char *ub);

void del_fri_each(char *ua, char *ub);

char *get_fri_list(char *username);

void create_group(char *groupname, char *username, int groupowner, int guan);

void come_group(char *groupname, char *username, int groupowner, int guan);

void back_group(char *groupname, char *username);

char *get_group_list(char *username);

char *get_group_m(char *groupname);

int set_guan(char *ua, char *username, char *groupname);

int group_ti(char *ua, char *username, char *groupname);

void group_mess(char *groupname, char *ua, char *message);

MYSQL_RES *pull_groupmess(char *groupname);

#endif
