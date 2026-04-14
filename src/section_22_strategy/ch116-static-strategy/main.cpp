/**
 *    @file main.cpp
 *    @brief ch-115 Static Strategy
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

enum class OutputFormat { markdown, html };

// markdown list:
// * item 1
// * item 2
// * item 3
//
// html list:
// <ul>
//   <li>item 1</li>
//   <li>item 2</li>
//   <li>item 3</li>
// </ul>

struct ListStrategy {
    virtual ~ListStrategy() = default;
    ListStrategy() = default;
    ListStrategy(const ListStrategy& other) = default;
    ListStrategy& operator=(const ListStrategy& other) = default;
    ListStrategy(ListStrategy&& other) = default;
    ListStrategy& operator=(ListStrategy&& other) = default;

    virtual void start(std::ostringstream& oss) = 0;
    virtual void addListItem(std::ostringstream& oss, const std::string& item) = 0;
    virtual void end(std::ostringstream& oss) = 0;
};

struct MarkdownListStrategy : ListStrategy {
    void start(std::ostringstream& /*oss*/) override {}

    void addListItem(std::ostringstream& oss, const std::string& item) override {
        oss << " * " << item << std::endl;
    }

    void end(std::ostringstream& /*oss*/) override {}
};

struct HtmlListStrategy : ListStrategy {
    void start(std::ostringstream& oss) override {
        oss << "<ul>" << std::endl;
    }

    void addListItem(std::ostringstream& oss, const std::string& item) override {
        oss << " <li>" << item << "</li>" << std::endl;
    }

    void end(std::ostringstream& oss) override {
        oss << "</ul>" << std::endl;
    }
};

template <typename LS>
struct TextProcessor {
   public:
    void appendList(const std::vector<std::string>& items) {
        listStrategy_.start(oss_);
        for (const auto& item : items) {
            listStrategy_.addListItem(oss_, item);
        }
        listStrategy_.end(oss_);
    }

    std::string str() const {
        return oss_.str();
    }

    void clear() {
        oss_.str("");
        oss_.clear();
    }

   private:
    std::ostringstream oss_;
    LS listStrategy_;
};

static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 22 :\e[0m Strategy" << std::endl;
    std::cout << "\e[1mChapter 115 : Static Strategy\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

int main() {
    printTitle();

    std::vector<std::string> items = {"item 1", "item 2", "item 3"};

    TextProcessor<MarkdownListStrategy> tp;
    tp.appendList(items);
    std::cout << tp.str() << std::endl;

    TextProcessor<HtmlListStrategy> tp2;
    tp2.appendList(items);
    std::cout << tp2.str() << std::endl;

    return 0;
}
