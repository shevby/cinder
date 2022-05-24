namespace Cinder {

struct Character {
    enum class Color {
        White,
        Black,
        Green,
        Yellow,
        Blue,
        Red,
    };

    char ch;
    Color color;
    Color bgColor;

    Character(char _ch, Color _color = Color::White, Color _bgColor = Color::Black);

    void display();
};

} // namespace Cinder
