#include <iostream>

class MemeGenerator {
private:
    std::string topText;
    std::string bottomText;
public:
    MemeGenerator(std::string top, std::string bottom)
        : topText(top), bottomText(bottom) {}
    void generate() {
        std::cout << topText << "\n\n" << bottomText << std::endl;
    }
};

class EmojiMemeGenerator: public MemeGenerator {
private:
public:
    EmojiMemeGenerator(std::string top, std::string bottom)
        : MemeGenerator(top, bottom) {}
    void generate() override {
        std::cout << topText << "\n\n" << bottomText << std::endl;
    }
};

int main(void)
{
    EmojiMemeGenerator emoji(":)", ":/");
    std::cout << "\n";
    emoji.generate();
    return 0;
}