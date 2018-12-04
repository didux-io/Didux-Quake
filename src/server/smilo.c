#include "stdio.h"
#include "string.h"
#include "../../inc/common/http.h"
#include "../../inc/server/smilo.h"

char confirmedPlayerPublickeys[128];
int playeruidsIndex;
int port = 46280;
char* host = "agent";

void
SV_Smilo_EndMatch(char* score_list) {
    printf("Match end! Notifying Smilo Server Agent...\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/newRound?gameResults=%s";
    sprintf(url, urlTemplate, score_list);

    printf("Newround url: %s \n", url);;

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, url, port, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
    }
    else {
        printf("Failed to do HTTP call...\n");
    }
}

int SV_Smilo_BetConfirmed(char publickey[1024], char* contractaddress) {
    printf("Checking confirmed status for %s...\n", publickey);

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/isvalidparticipant?publickey=%s&contractaddress=%s";
    sprintf(url, urlTemplate, publickey, contractaddress);

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, url, port, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        if (!strcmp(response, "true")) {
            printf("  (SV) BET CONFIRMED: 1! \n");
            confirmedPlayerPublickeys[playeruidsIndex] = *publickey;
            playeruidsIndex++;
            return 1;
        } else {
            printf("  (SV) BET CONFIRMED: 0! \n");
            return 0;
        }
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int SV_Smilo_GetContractAddress(char* buffer, int bufferSize) {
    printf("Requesting contract address...\n");

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get(host, "v1/server/contractaddress", port, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        
        // Copy response in buffer
        strncpy(buffer, response, bufferSize);

        return 1;
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}