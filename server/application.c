// Copyright (c) 2004-2012 Sergey Lyubka
// This file is a part of mongoose project, http://github.com/valenok/mongoose

#include <stdio.h>
#include <string.h>
#include "mongoose.h"
#include <errno.h>
#include <stdlib.h>
   // #ifndef HAVE_SNPRINTF
   // #endif
  char buff [5000];
  void write_in_file(const char *qs,const char *uri);
static int ev_handler(struct mg_connection *conn, enum mg_event ev); 

  static int send_index_page(struct mg_connection *conn) {
  const char *data;
  int data_len, ofs = 0;
  char var_name[100], file_name[100];


  mg_printf_data(conn, "%s",
                 "<html><body>Upload example."
                 "<form method=\"POST\" action=\"/handle_post_request?kkkk\" "
                 "  enctype=\"multipart/form-data\">"
                 "<input type=\"file\" name=\"file\" /> <br/>"                  
                 "<input type=\"submit\" value=\"Upload\" />"
                 "</form>");
while ((ofs = mg_parse_multipart(conn->content + ofs, conn->content_len - ofs, var_name, sizeof(var_name), file_name, sizeof(file_name), &data, &data_len)) > 0)

 {
       snprintf (buff,data_len,"%s",data); 
	write_in_file( conn->query_string,data);
       mg_printf_data(conn, "%d", data_len);
 }


  mg_printf_data(conn,"%s","</body></html>");

  return MG_TRUE;
}

/*---------------------------------------------------------------------------------------------*/

void write_in_file(const char *qs,const char *content)
        {
       
	
	FILE *fp;
   	fp = fopen (qs,"w");

    	if (fp == NULL) {
        printf ("File not created!, errno = %d\n", errno);
        		}

	fprintf (fp,"%s\n",content); 

     	fclose (fp);
	 
	}

/*---------------------------------------------------------------------------------------------*/


static int ev_handler(struct mg_connection *conn, enum mg_event ev) {
  switch (ev) {
    case MG_AUTH:     return MG_TRUE;
    case MG_REQUEST:  return send_index_page(conn);
    default:          return MG_FALSE;
  }
}
/*---------------------------------------------------------------------------------------------*/

int main(void) {
  struct mg_server *server;

  // Create and configure the server
  server = mg_create_server(NULL, ev_handler);
  mg_set_option(server, "listening_port", "8080");

  // Serve request. Hit Ctrl-C to terminate the program
  printf("Starting on port %s\n", mg_get_option(server, "listening_port"));
  for (;;) {
    mg_poll_server(server, 1000);
  }

  // Cleanup, and free server instance
  mg_destroy_server(&server);

  return 0;
}m njhjhvjvhj
