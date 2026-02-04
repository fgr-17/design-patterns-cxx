/**
 *    @file communication-proxy.cpp
 *    @brief ch-70 Communication Proxy
 *    @author rouxfederico@gmail.com
 */

#include <cpprest/details/basic_types.h>  // NOLINT
#include <cpprest/http_client.h>          // NOLINT

#include <codecvt>
#include <cstddef>
#include <iostream>
#include <locale>
#include <memory>  // for make_shared
#include <string>

#include "cpprest/base_uri.h"     // for uri
#include "cpprest/http_msg.h"     // for http_response, methods, met...
#include "cpprest/uri_builder.h"  // for uri_builder
#include "pplx/pplx.h"            // for _Interruption_exception
#include "pplx/pplxtasks.h"       // for task

static std::string wstringToUtf8(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

static std::wstring utf8ToWstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

struct Pingable {
    virtual std::wstring ping(const std::wstring& message) = 0;
    virtual ~Pingable() = default;
    Pingable() = default;
    Pingable(const Pingable&) = delete;
    Pingable& operator=(const Pingable&) = delete;
    Pingable(Pingable&&) = delete;
    Pingable& operator=(Pingable&&) = delete;
};

struct Pong : Pingable {
    std::wstring ping(const std::wstring& message) override {
        return message + L" pong";
    }
};

struct RemotePong : Pingable {
    std::wstring ping(const std::wstring& message) override {
        web::http::client::http_client client(U("http://localhost:8080"));
        web::uri_builder builder(U("/api/pingpong"));
        builder.append(web::uri(wstringToUtf8(message)));
        auto task =
            client.request(web::http::methods::GET, builder.to_string())
                .then([](web::http::http_response response) { return response.extract_string(); });

        task.wait();
        return utf8ToWstring(task.get());
    }
};

void test(Pingable& pp) {
    const std::wstring message(L"ping");
    std::wcout << pp.ping(message) << std::endl;
}

/**
 *   @fn printTitle
 *   @brief chapter title
 */
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 13 :\e[0m Proxy" << std::endl;
    std::cout << "\e[1mChapter 70 : Communication Proxy\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Communication Proxy
 */
int main() {
    printTitle();
    Pong pong;
    for (size_t i = 0; i < 3; ++i) {
        test(pong);
    }

    RemotePong remotePong;
    for (size_t i = 0; i < 3; ++i) {
        test(remotePong);
    }
    return 0;
}
