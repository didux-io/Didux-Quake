#include "stdio.h"
#include "string.h"
#include "../../inc/common/http.h"
#include "../../inc/server/smilo.h"

char confirmedPlayerPublickeys[128];
int playeruidsIndex;
int port = 46280;
char* host = "127.0.0.1"; // agent

void
SV_Smilo_EndMatch(char* score_list) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/newRound?gameResults=%s";
    sprintf(url, urlTemplate, score_list);

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, url, port, response, sizeof(response), 0)) {
        
    }
    else {
        printf("Failed to do HTTP call...\n");
    }
}

int SV_Smilo_BetConfirmed(char publickey[1024], char* contractaddress) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/isvalidparticipant?publickey=%s&contractaddress=%s";
    sprintf(url, urlTemplate, publickey, contractaddress);

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, url, port, response, sizeof(response), 0)) {
        if (!strcmp(response, "true")) {
            confirmedPlayerPublickeys[playeruidsIndex] = *publickey;
            playeruidsIndex++;
            return 1;
        } else {
            return 0;
        }
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int SV_Smilo_GetContractAddress(char* buffer, int bufferSize) {
    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, "v1/server/contractaddress", port, response, sizeof(response), 0)) {
        // Copy response in buffer
        strncpy(buffer, response, bufferSize);

        return 1;
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}