#include "http.h"
#include <esp_http_client.h>

char *payload;
// connect_to_wifi();
const struct addrinfo hints = {
    .ai_family = AF_INET,
    .ai_socktype = SOCK_STREAM,
};
// Function to copy the string

// return 0 if successful
int create_connection(int *server_socket)
{
    struct addrinfo *res;
    struct in_addr *addr;
    int r;

    char *request = malloc(700);

    int err = getaddrinfo(WEB_SERVER, WEB_PORT, &hints, &res);
    if (err != 0 || res == NULL)
    {
        ESP_LOGE(TAG, "DNS lookup failed err=%d res=%p", err, res);
        // vTaskDelay(10 / portTICK_PERIOD_MS);

        //  close(s);
        return -1;
    }

    addr = &((struct sockaddr_in *)res->ai_addr)->sin_addr;
    // ESP_LOGI(TAG, "DNS lookup succeeded. IP=%s", inet_ntoa(*addr));

    *server_socket = socket(res->ai_family, res->ai_socktype, 0);
    if (*server_socket < 0)
    {
        ESP_LOGE(TAG, "... Failed to allocate socket.");

        close(*server_socket);

        // if (payload != NULL)
        // {
        //     free(payload);
        //     payload = NULL;
        // }

        freeaddrinfo(res);
        // vTaskDelay(1 / portTICK_PERIOD_MS);
        return -1;
    }

    if (connect(*server_socket, res->ai_addr, res->ai_addrlen) != 0)
    {
        ESP_LOGE(TAG, "... socket connect failed errno=%d", errno);
        //  vTaskDelay(1 / portTICK_PERIOD_MS);
        close(*server_socket);

        freeaddrinfo(res);

        if (request != NULL)
        {
            free(request);
            request = NULL;
        }

        return -1;
    }

    return 0;
};

// hàm ok, đã tự giải phóng các biến nội bộ.
int sendToServer(int socket,unsigned char *packet, int len)

{

    if (write(socket, packet, len) < 0)
    {
        ESP_LOGE(TAG, "... socket send failed");

        vTaskDelay(2 / portTICK_PERIOD_MS);
        return -1;
    }

    return 0;
};

void http_get_task(void *pvParameters)
{

  

    // char txbuff[4000];
    int server_socket;

    int rc;

    while ((rc = create_connection(&server_socket)) != 0)
    {
        printf("Trying to connect to server ...\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }

    if (!queue)
        queue = xQueueCreate(ITEMS_NUM, ITEM_SIZE);

    char rxbuff[12];

    while (1)
    {
        if (xQueueReceive(queue, &rxbuff, (TickType_t)1))
        {
            sendToServer(server_socket,(unsigned char*) rxbuff, 12);
        };
    };
}

// đã giải phóng bộ nhớ cho mọi biến nội bộ.
char *createJsonBody(int timestamp, char *pir_id, char *pirs_vol)
{
    printf("Creating json with %s timestamp: %d\n", pir_id, timestamp);

    cJSON *root = cJSON_CreateObject();
    cJSON_AddNumberToObject(root, "timestamp", timestamp);
    // cJSON_AddStringToObject(root, "timestamp", timestamp);
    cJSON_AddStringToObject(root, "pir", pir_id);
    cJSON_AddStringToObject(root, "vol", pirs_vol);

    char *out = cJSON_Print(root);
    cJSON_Delete(root);
    return (char *)out;
}

// Function to copy the string
char *copyString(char s[], int len)
{

    return strdup(s);
}
