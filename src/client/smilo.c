#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdlib.h>
#include "../../inc/common/http.h"
#include "../../inc/client/smilo.h"

int clientPort = 46290;

void CL_Smilo_Connected(char* contractAddress, char* buffer, int bufferSize) {
    printf("Client connected! Notifying Smilo Client Agent...\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/participate?contractaddress=%s";
    sprintf(url, urlTemplate, contractAddress);

    printf("URL: %s \n", url);

    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        strncpy(buffer, "1", bufferSize);
    } else {
        printf("Failed to do HTTP call. Error message: %s\n", response);
        strncpy(buffer, response, bufferSize);
    }
}

int CL_Smilo_GetBalance(char* publickey) {
    printf("Get client balance!\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/balanceNonBigInt?publickey=%s";
    sprintf(url, urlTemplate, publickey);

    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        return atoi(response);
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_GetPublicKey(char* buffer, int bufferSize) {
    printf("Get client publickey!\n");

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get("127.0.0.1", "v1/client/publickey", clientPort, response, sizeof(response))) {
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

int CL_Smilo_BetConfirmed(char* publickey, char* contractaddress) {
    printf("Checking if bet is confirmed for publickey: %s\n", publickey);

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/betconfirmed?publickey=%s&contractaddress=%s";
    sprintf(url, urlTemplate, publickey, contractaddress);

    printf("Checking URL: %s \n", url);

    // Notify Smilo server agent
    char response[4096];
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        if (!strcmp(response, "true")) {
            printf("  BET CONFIRMED: 1! \n");
            return 1;
        } else {
            printf("  BET CONFIRMED: 0! \n");
            return 0;
        }
    }
    else {
        printf("Failed to do HTTP call...\n");
        return 0;
    }
}

gameDetails_t CL_Smilo_Get_Game_Details(char* contractaddress) {
    printf("Get player count!\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/gameDetailsWelcomeMenu?contractaddress=%s";
    sprintf(url, urlTemplate, contractaddress);

    printf("Validated URL: %s \n", url);

    char response[4096];
    gameDetails_t gamedetails;
    gamedetails.deposit = -1;
    gamedetails.firstReward = -1;
    gamedetails.secondReward = -1;
    gamedetails.thirdReward = 1;
    gamedetails.playerCount = -1;
    if(HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response))) {
        printf("  Agent response: %s\n", response);
        int count = 0;
        char *pt;
        pt = strtok (response, ":");
        while (pt != NULL) {
            int value = atoi(pt);
            if (count == 0) {
                gamedetails.firstReward = value;
            } else if (count == 1) {
                gamedetails.secondReward = value;
            } else if (count == 2) {
                gamedetails.thirdReward = value;
            } else if (count == 3) {
                gamedetails.playerCount = value + 1;
            } else if (count == 4) {
                gamedetails.deposit = value;
            }
            pt = strtok (NULL, ":");
            count++;
        }
        return gamedetails;
    } else {
        printf("Failed to do HTTP call...\n");
        return gamedetails;
    }
}
