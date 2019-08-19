#include "stdio.h"
#include "string.h"
#include "../../inc/common/http.h"
#include "../../inc/server/smilo.h"

char confirmedPlayerPublickeys[128];
int playeruidsIndex;
int port = 46280;
// The max amount of times a HTTP may be repeated before it fails.
// Does not apply to all HTTP calls.
// Effectively each try is about one second. 
int maxHttpTries = 120;

#if DEV_MODE
char* host = "127.0.0.1";
#else 
char* host = "agent";
#endif


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
        printf("SV_Smilo_EndMatch - Failed to do HTTP call...\n");
    }
}

int SV_Smilo_BetConfirmed(char publickey[1024], char* contractaddress) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/isValidParticipant?contractaddress=%s&publickey=%s";
    sprintf(url, urlTemplate, contractaddress, publickey);

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
        printf("SV_Smilo_BetConfirmed - Failed to do HTTP call...\n");
        return 0;
    }
}

/*
* Returns 1 if failure since that will enable the idle kick. If 0 it will return as Elite and disable idle kick
*/
int SV_Smilo_Is_Rookie(char* contractaddress) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/server/isRookie?contractaddress=%s";
    sprintf(url, urlTemplate, contractaddress);

    int callsRemaining = maxHttpTries;
    while(1) {
        // Notify Smilo server agent
        char response[4096];
        if(HTTP_Get(host, url, port, response, sizeof(response), 0)) {
            if (strcmp(response, "false") == 0) {
                return 0;
            } else {
                return 1;
            }
        }
        else {
            printf("SV_Smilo_Is_Rookie - Failed to do HTTP call...\n");
            if(--callsRemaining == 0)
                return -1;
        }

        sleep(1);
    }
}

int SV_Smilo_GetContractAddress(char* buffer, int bufferSize) {
    int callsRemaining = maxHttpTries;
    while(1) {
        // Notify Smilo server agent
        char response[4096];
        if(HTTP_Get(host, "v1/server/contractaddress", port, response, sizeof(response), 0)) {
            // Copy response in buffer
            strncpy(buffer, response, bufferSize);

            return 1;
        }
        else {
            printf("SV_Smilo_GetContractAddress - Failed to do HTTP call...\n");
            if(--callsRemaining == 0)
                return 0;
        }

        sleep(1);
    }
}