#include <string>
#include <iostream>
#include <curl/curl.h>


auto main(int argc, char * argv[]) -> int
{
    (void) argc;
    (void) argv;

    auto data = std::string("arfle barfle gloop!");
    auto buffer = std::string();
    auto write_callback = [](char* ptr, size_t size, size_t nmemb, void* userdata)
    {
        std::cout << "ptr = " << (void*)ptr << ", size = " << size << ", nmemb = " << nmemb << ", userdata = " << userdata << "\n";
        ((std::string*)userdata)->append(ptr, size * nmemb);
        return size * nmemb;
    };
    auto handle = curl_easy_init();
    std::cout << "handle = " << handle << "\n";

    curl_slist * headers = nullptr;
    headers = curl_slist_append(headers, "X-Rollbar-Access-Token: invalid_token");
    headers = curl_slist_append(headers, "accept: application/json");
    headers = curl_slist_append(headers, "content-type: application/json");

    curl_easy_setopt(handle, CURLOPT_HTTPHEADER, headers);
    curl_easy_setopt(handle, CURLOPT_URL, "https://api.rollbar.com/api/1/item/");
    curl_easy_setopt(handle, CURLOPT_POST, 1);
    curl_easy_setopt(handle, CURLOPT_POSTFIELDS, data.c_str());
    curl_easy_setopt(handle, CURLOPT_POSTFIELDSIZE, data.size());
    curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, &write_callback);
    curl_easy_setopt(handle, CURLOPT_WRITEDATA, &buffer);

    auto res = curl_easy_perform(handle);
    if (res != CURLE_OK)
    {
        std::cout << "Curl failed: '" << curl_easy_strerror(res) << "'\n";
    }
    else
    {
        int status_code;
        curl_easy_getinfo(handle, CURLINFO_RESPONSE_CODE, &status_code);

        std::cout << "Curl succeeded: " << status_code << ", reponse: '" << buffer << "'\n";
    }

    curl_slist_free_all(headers);
    curl_easy_cleanup(handle);

    return 0;
}
