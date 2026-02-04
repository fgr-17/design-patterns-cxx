/**
 *    @file virtual-proxy.cpp
 *    @brief ch-69 Virtual Proxy
 *    @author rouxfederico@gmail.com
 */

#include <iostream>
#include <memory>
#include <string>
#include <utility>

struct Image {
    virtual void draw() = 0;
    virtual ~Image() = default;
};

struct Bitmap : Image {
    Bitmap(const std::string& filename) {
        std::cout << "Loading image from " << filename << std::endl;
    }
    void draw() override {
        std::cout << "Drawing image" << std::endl;
    }
};

// Lazy initialization:  I don't want to load the image until it's actually needed
struct LazyBitmap : Image {
    LazyBitmap(std::string filename) : filename_(std::move(filename)), bitmap_(nullptr) {
        std::cout << "Not still loading image from " << filename << std::endl;
    }
    void draw() override {
        if (!bitmap_) {
            bitmap_ = std::make_unique<Bitmap>(filename_);
        }
        bitmap_->draw();
    }

   private:
    std::string filename_;
    std::unique_ptr<Bitmap> bitmap_{nullptr};
};

/**
 *   @fn printTitle
 *   @brief chapter title
 */
static int printTitle() {
    std::cout << "=========================================" << std::endl;
    std::cout << "\e[1mDesign Patterns in Modern C++\e[0m" << std::endl;
    std::cout << "\e[1mSection 13 :\e[0m Proxy" << std::endl;
    std::cout << "\e[1mChapter 69 : Virtual Proxy\e[0m" << std::endl;
    std::cout << "=========================================" << std::endl;
    return 0;
}

/**
 *   @fn main
 *   @brief Virtual Proxy
 */
int main() {
    printTitle();

    Bitmap bitmap("face.png");
    bitmap.draw();

    LazyBitmap lazyBitmap("face.png");
    lazyBitmap.draw();

    return 0;
}
