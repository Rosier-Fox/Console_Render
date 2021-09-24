#include <iostream>
#include <vector>


class Display{
    private:
        enum Colour
        {
            colour_black = 30,
            colour_red,
            colour_green,
            colour_yellow,
            colour_blue,
            colour_magenta,
            colour_cyan,
            colour_white,
            colour_black_bright = 90,
            colour_red_bright,
            colour_green_bright,
            colour_yellow_bright,
            colour_blue_bright,
            colour_magenta_bright,
            colour_cyan_bright,
            colour_white_bright
        };

        std::vector<std::vector<int>> buffer;



    public:
        // constructor function
        Display(int w, int h): buffer (h, std::vector<int> (w, colour_black)){}

        void rect(int x, int y, int w, int h, Colour c) {


        }

        void render() {
            //loop thru all pixels in buffer
            for (unsigned long y{0}; y < buffer.size(); y++){
                for (unsigned long x{0}; x < buffer[y].size(); x++){
                    // set the colour
                    std::cout << "\x1b[" << buffer[y][x] << ";" << buffer[y][x] + 10 << "m";
                    // print character
                    std::cout << "#";
                    //reset colour
                    std::cout << "\x1b[0m";

                }
                std::cout << "\n";
            }
        }
};





int main()
{
    Display screen{64, 32};
    screen.render();
    return 0;
}
