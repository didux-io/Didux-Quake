#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <stdlib.h>
#include "../../inc/common/http.h"
#include "../../inc/client/smilo.h"

int clientPort = 46290;
char token[65];

void CL_Smilo_Connected(char* contractAddress, char* buffer, int bufferSize) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/participate?contractaddress=%s&token=%s";
    sprintf(url, urlTemplate, contractAddress, token);

    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
        strncpy(buffer, "1", bufferSize);
    } else {
        strncpy(buffer, response, bufferSize);
    }
}

int CL_Smilo_GetBalance(char* publickey) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/balanceNonBigInt?publickey=%s";
    sprintf(url, urlTemplate, publickey);

    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
        return atoi(response);
    }
    else {
        printf("CL_Smilo_GetBalance - Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_CheckTokenFunds(char* contractAddress) {
    printf("Get token funds!\n");

    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/checkTokenFunds?contractaddress=%s&token=%s";
    sprintf(url, urlTemplate, contractAddress, token);

    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
        printf("CL_Smilo_CheckTokenFunds - Response: %s \n", response);
        return 1;
    }
    else {
        printf("CL_Smilo_CheckTokenFunds - Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_GetPublicKey(char* buffer, int bufferSize) {
    // Notify Smilo server agent
    char response[4096];
    if (HTTP_Get("127.0.0.1", "v1/client/publickey", clientPort, response, sizeof(response), 1)) {
        // Copy response in buffer
        strncpy(buffer, response, bufferSize);

        return 1;
    }
    else {
        printf("CL_Smilo_GetPublicKey - Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_RequestMoreFunds() {
    printf("Get request more funds!\n");

    char url[1024];
    char* urlTemplate = "v1/client/requestMoreFunds?token=%s";
    sprintf(url, urlTemplate, token);
    // Notify Smilo server agent
    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {      
        // Copy response in buffer
        strncpy(token, response, sizeof(token) - 1);

        return 1;
    }
    else {
        printf("CL_Smilo_RequestMoreFunds - Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_RequestToken(char* gametokencode) {
    printf("Get request token!\n");

    if (strlen(gametokencode) == 0) {
        // Since the API will return a gametoken in devmode send it as a random string so the query parameter isn't empty for the API middleware 
        gametokencode = "devmode";
    } 

    char url[1024];
    char* urlTemplate = "v1/client/requestToken?startupToken=%s";
    sprintf(url, urlTemplate, gametokencode);
    
    // Notify Smilo server agent
    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
        // Copy response in buffer
        strncpy(token, response, sizeof(token) - 1);

        return 1;
    }
    else {
        printf("CL_Smilo_RequestToken - Failed to do HTTP call...\n");
        return 0;
    }
}

int CL_Smilo_BetConfirmed(char* publickey, char* contractaddress) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/betconfirmed?publickey=%s&contractaddress=%s";
    sprintf(url, urlTemplate, publickey, contractaddress);

    // Notify Smilo server agent
    char response[4096];
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
        if (!strcmp(response, "true")) {
            return 1;
        } else {
            return 0;
        }
    }
    else {
        printf("CL_Smilo_BetConfirmed - Failed to do HTTP call...\n");
        return 0;
    }
}

gameDetails_t CL_Smilo_Get_Game_Details(char* contractaddress) {
    // Format url to contain query parameter
    char url[1024];
    char* urlTemplate = "v1/client/gameDetailsWelcomeMenu?contractaddress=%s";
    sprintf(url, urlTemplate, contractaddress);

    char response[4096];
    gameDetails_t gamedetails;
    gamedetails.deposit = -1;
    gamedetails.firstReward = -1;
    gamedetails.secondReward = -1;
    gamedetails.thirdReward = 1;
    gamedetails.playerCount = -1;
    if (HTTP_Get("127.0.0.1", url, clientPort, response, sizeof(response), 1)) {
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
        printf("CL_Smilo_Get_Game_Details - Failed to do HTTP call...\n");
        return gamedetails;
    }
}
