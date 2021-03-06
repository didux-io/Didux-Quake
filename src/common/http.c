#include <stdio.h> /* printf, sprintf */
#include <stdlib.h> /* exit, atoi, malloc, free */
#include <unistd.h> /* read, write, close */
#include <string.h> /* memcpy, memset */

#include <curl/curl.h>

#include "../../inc/common/http.h"

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

int
HTTP_Get(char* host, char* url, int portno, char* responseBuffer, unsigned int responseBufferSize, int useHttps) {
    char* messageTemplate;
    if(useHttps)
      messageTemplate = "https://%s:%i/%s";
    else
      messageTemplate = "http://%s:%i/%s";
      
    char message[1024];

    sprintf(message, messageTemplate, host, portno, url);

    CURL* curl;
    CURLcode res;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl) {
        struct string s;
        init_string(&s);

        curl_easy_setopt(curl, CURLOPT_URL, message);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);

        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);

        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);

        res = curl_easy_perform(curl);

        long response_code;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);

        curl_easy_cleanup(curl);

        // Zero output buffer
        memset(responseBuffer, 0, responseBufferSize);

        // Copy data into output buffer
        memcpy(responseBuffer, s.ptr, s.len);

        // Free used memory
        free(s.ptr);

        if (response_code >= 200 && response_code <= 299) {
            return 1;
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            return 0;
        }
    }
    else {
        printf("Failed to initialize curl...");
        return 0;
    }
}
