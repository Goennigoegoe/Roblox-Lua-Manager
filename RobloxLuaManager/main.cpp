#define CURL_STATICLIB
#include <cstdio>
#include <curl/curl.h>
#include <string>
#include <iostream>
#include <Windows.h>

void clearScreen() {
    system("cls");
}

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written;
    written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadLua(std::string url, char path[FILENAME_MAX], CURL* curl) {
    if (curl) {
        FILE* fp;
        CURLcode res;

        fopen_s(&fp, path, "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        fclose(fp);
    }
}

int main() {
    CURL* curl;
    
    std::string url;//"http://www.joes-hardware.com/tools.html";
    char outfilename[FILENAME_MAX];
    curl = curl_easy_init();
    if (curl) {
        while (true) {
            clearScreen();
            int option = 1;

            std::cout << "What would you like to do?\n1: Set download path\n2: Download lua\n3: Exit lua manager\nOption: ";
            std::cin >> option;

            if (option == 1) {
                std::cout << "Please input path (./ for current dir) (example: C:\\\\hello_world.lua): ";
                std::cin >> outfilename;
            }
            else if (option == 2) {
                std::cout << "Please input url to lua (raw file link): ";
                std::cin >> url;

                downloadLua(url, outfilename, curl);
            }
            else if (option == 3) {
                std::cout << "Thank you for using Goennigoegoe's lua manager\n";
                Sleep(1000);
                return 0;
            }
            Sleep(50);
        }

        curl_easy_cleanup(curl);
    }
    return 0;
}