#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

// includeフォルダに配置したライブラリを読み込む
#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "json.hpp"

using json = nlohmann::json;

void open_browser(const std::string& url) {
#if defined(_WIN32)
    std::string command = "start " + url;
#elif defined(__APPLE__)
    std::string command = "open " + url;
#else
    std::string command = "xdg-open " + url;
#endif
    std::system(command.c_str());
}

int main() {
    std::string query;
    std::cout << "GitHub Repository Search: ";
    std::getline(std::cin, query);

    if (query.empty()) return 0;

    // GitHub APIへの接続設定
    httplib::SSLClient cli("api.github.com");
    cli.set_follow_location(true);

    // APIエンドポイント構築
    std::string path = "/search/repositories?q=" + query + "&per_page=10";
    
    // GitHub APIはUser-Agentが必須
    httplib::Headers headers = {
        {"User-Agent", "edu-github-fast-search-app"}
    };

    auto res = cli.Get(path.c_str(), headers);

    if (res && res->status == 200) {
        auto data = json::parse(res->body);
        auto items = data["items"];

        if (items.empty()) {
            std::cout << "結果が見つかりませんでした。" << std::endl;
            return 0;
        }

        std::vector<std::string> urls;
        std::cout << "\n--- 検索結果 ---" << std::endl;
        for (int i = 0; i < items.size(); ++i) {
            std::string name = items[i]["full_name"];
            std::string desc = items[i]["description"].is_null() ? "" : items[i]["description"];
            std::string url = items[i]["html_url"];
            
            urls.push_back(url);
            std::cout << "[" << i + 1 << "] " << name << "\n    " << desc << "\n" << std::endl;
        }

        std::cout << "開きたい番号を入力してください (0で終了): ";
        int choice;
        std::cin >> choice;

        if (choice > 0 && choice <= urls.size()) {
            std::cout << "ブラウザで開きます: " << urls[choice - 1] << std::endl;
            open_browser(urls[choice - 1]);
        }
    } else {
        std::cerr << "エラー: APIリクエストに失敗しました。ステータス: " << (res ? std::to_string(res->status) : "接続失敗") << std::endl;
    }

    return 0;
}
