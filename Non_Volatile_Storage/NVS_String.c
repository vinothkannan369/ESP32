/* Non-Volatile Storage (NVS) Read and Write a Value - Example

   For other examples please check:
   https://github.com/espressif/esp-idf/tree/master/examples

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "nvs_flash.h"
#include "nvs.h"
#include <string.h>

void NVS_Read(char *data,char *Get_Data){
	 // Initialize NVS
	    esp_err_t err = nvs_flash_init();
	    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	        // NVS partition was truncated and needs to be erased
	        // Retry nvs_flash_init
	        ESP_ERROR_CHECK(nvs_flash_erase());
	        err = nvs_flash_init();
	    }
	    ESP_ERROR_CHECK( err );
	 // Open
	    printf("\n");
	    printf("Opening Non-Volatile Storage (NVS) handle... ");
	    nvs_handle_t my_handle;
	    err = nvs_open("storage", NVS_READWRITE, &my_handle);
	    if (err != ESP_OK) {
	        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
	    } else {
	        printf("Done\n");

	        // Read
	      //  printf("Reading restart counter from NVS ... ");
	     //   int32_t restart_counter = 0; // value will default to 0, if not set yet in NVS
	      //  err = nvs_get_i32(my_handle, "restart_counter", &restart_counter);
	        size_t required_size = 0;
	            nvs_get_str(my_handle, data, NULL, &required_size);
	            char *server_name = malloc(required_size);
	            err =   nvs_get_str(my_handle, data, server_name, &required_size);

	        switch (err) {
	            case ESP_OK:
	                printf("Done\n");
	               // printf("Restart counter = %d\n", restart_counter);
	                printf("Read data: %s\n", server_name);
	                strcpy(Get_Data,server_name);
	                break;
	            case ESP_ERR_NVS_NOT_FOUND:
	                printf("The value is not initialized yet!\n");
	                break;
	            default :
	                printf("Error (%s) reading!\n", esp_err_to_name(err));
	        }

         }
	    nvs_close(my_handle);
}
void NVS_Write(char *data,char *write_string){
	 // Initialize NVS
	    esp_err_t err = nvs_flash_init();
	    if (err == ESP_ERR_NVS_NO_FREE_PAGES || err == ESP_ERR_NVS_NEW_VERSION_FOUND) {
	        // NVS partition was truncated and needs to be erased
	        // Retry nvs_flash_init
	        ESP_ERROR_CHECK(nvs_flash_erase());
	        err = nvs_flash_init();
	    }
	    ESP_ERROR_CHECK( err );
	    // Open
	    printf("\n");
	    printf("Opening Non-Volatile Storage (NVS) handle... ");
	    nvs_handle_t my_handle;
	    err = nvs_open("storage", NVS_READWRITE, &my_handle);
	    if (err != ESP_OK) {
	        printf("Error (%s) opening NVS handle!\n", esp_err_to_name(err));
	    } else {
	    	//char *write_string = "Some string new...\0";
			nvs_set_str(my_handle, data, write_string);
			printf("Write data: %s\n", write_string);
			printf("Committing updates in NVS ... ");
			err = nvs_commit(my_handle);
			printf((err != ESP_OK) ? "Failed!\n" : "Done\n");
	       }
	       nvs_close(my_handle);
}

void app_main(void)
{
	esp_err_t ret = nvs_flash_init();
		    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
		        ESP_ERROR_CHECK(nvs_flash_erase());
		        ret = nvs_flash_init();
		    }
	int gg =0;
	char Name[100];
	char Place[100];
	NVS_Write("Name","Vinoth");
	NVS_Write("Place","Madurai");
	NVS_Read("Name",Name);
	NVS_Read("Place",Place);

	printf("String 1 = %s\n",Name);
	printf("String 2 = %s\n",Place);


}
