#include <iostream>
#include <curl/curl.h>


auto main() -> int
{
    auto handle = curl_easy_init();
    curl_easy_cleanup(handle);

    return 0;
}
