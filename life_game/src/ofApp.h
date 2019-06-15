#pragma once

#include "ofMain.h"
#include <vector>
//#include "iostream.h"

class ofApp : public ofBaseApp{
	public:
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void mouseDragged(int x, int y, int button);
        void mousePressed(int x, int y, int button);
        void time_control();
        void reset();
        void initialize_state();
        void render();
        void calc();

        int cell_size_x;
        int cell_size_y;
        bool time_stop;
        //int f_rate;
        int num_horizontal;
        int num_vertical;
        std::vector<std::vector<bool>> state;
        int generation;
        int rate;

};
