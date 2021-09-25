#include <iostream>
#include <vector>
#include <chrono>
#include <thread>

enum Colour{
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

class Display{
    private:
        std::vector<std::vector<int>> buffer;

        int frameRate{30};
        std::chrono::steady_clock::time_point oldTime{std::chrono::steady_clock::now()};
        std::chrono::steady_clock::time_point currentTime;

    public:
        // constructor function
        Display(int w, int h): buffer (h, std::vector<int> (w, colour_black)){}



        // THIS COULD PROBABLY BE MORE EFFECIENT BUT I THINK THIS IS ALRIGHT AND IM A LITTLE DENSE
        void rect(int x, int y, int width, int height, Colour colour, bool filled = false) {
            if (filled){
                // loop through all pixels in rect and set them to colour
                for (int i{x}; i < x + width; i++){
                    for (int j{y}; j < y + height; j++){
                        buffer[j][i] = colour;
                    }
                }
            }
            else{
                //create horizontal lines by looping through the pixels from x to x + width
                for (int i{x}; i < x + width; i++){
                    buffer[y][i] = colour;
                    buffer[y + height - 1][i] = colour;
                }
                //create vertical lines though the same process
                for (int i{y}; i < y + height; i++){
                    buffer[i][x] = colour;
                    buffer[i][x + width - 1] = colour;
                }
            }
        }

        void clear(Colour colour){
            //loop through all pixels and set them to colour | i dont think i can use range for loops here
            for (unsigned long y{0}; y < buffer.size(); y++){
                for (unsigned long x{0}; x < buffer[y].size(); x++){
                    buffer[y][x] = colour;
                }
            }


        }

        void render() {
            // clear console
            system("clear");
            //loop thru all pixels in buffer
            for (unsigned long y{0}; y < buffer.size(); y++){
                for (unsigned long x{0}; x < buffer[y].size(); x++){
                    // set the colour
                    std::cout << "\x1b[" << buffer[y][x] << ";" << buffer[y][x] + 10 << "m";
                    // print character
                    std::cout << "#";
                    //reset colour | this f*cks stuff up if i do it after this loop. might be invis characters?
                    std::cout << "\x1b[0m";

                }
                std::cout << "\n";
            }
            // calculate time since last render and wait if needed to match framerate
            currentTime = std::chrono::steady_clock::now();
            int timeElapsed = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - oldTime).count();
            oldTime = std::chrono::steady_clock::now();
            std::this_thread::sleep_for(std::chrono::milliseconds((1000 / frameRate) - timeElapsed));
        }
};





int main(){
    Display screen{64, 32};
    // logic loop
    while (true) {
        screen.clear(colour_cyan);
        screen.rect(5, 5, 16, 6, colour_red, true);
        screen.render();
    }
    return 0;
}
