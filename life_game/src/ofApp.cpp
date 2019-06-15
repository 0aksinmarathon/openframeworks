#include "ofApp.h"


//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(100);
    cell_size_x = 5 ;
    cell_size_y = 5;
    time_stop = true;
    num_horizontal = ofGetWidth()/cell_size_x;
    num_vertical = ofGetHeight()/cell_size_y;
    generation = 0;
    rate = 1;
    std::vector<std::vector<bool>> tmp(num_vertical, std::vector<bool>(num_horizontal, false));
    state = tmp;
    cout << state[0][0]<< "asocja" << endl;
    ofSetLineWidth(1);
    ofFill();
    reset();
    
    
}

//--------------------------------------------------------------
void ofApp::update(){
    
    if (!time_stop){
        if (ofGetFrameNum() % rate == 0){
            calc();
            generation++;
            cout << generation << endl;
        }
    }
     
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    render();
}


/*
 initialize the state and graphics
 */
void ofApp::reset(){
    
    ofBackground(0);

    ofSetColor(255);
    for (int i = 0; i < ofGetWidth(); i += cell_size_x){
        ofDrawLine(i, 0 , i, ofGetHeight());
    }
   
    for (int i = 0; i < ofGetHeight(); i+=cell_size_y){
        ofDrawLine(0, i, ofGetWidth(), i);
    }

    generation = 0;
    initialize_state();
    
}

/*
 kill every cell
 */
void ofApp::initialize_state(){
    for (int i = 0; i < num_horizontal; i++){
        for (int j = 0; j < num_vertical; j++){
            
            state[i][j] = false;
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == ' '){
        time_control();
    }
    if (key == OF_KEY_RETURN){
        reset();
    }
    if (key == OF_KEY_LEFT){
        if(rate != 1){
            --rate;
        }
    }
    if (key == OF_KEY_RIGHT){
            ++rate;
    }
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    try{
        int coordinate_x = x / cell_size_x;
        int coordinate_y = y / cell_size_y;
        
        if (state[coordinate_x][coordinate_y]){
            state[coordinate_x][coordinate_y] = false;
        } else {
            state[coordinate_x][coordinate_y] = true;
        }
        if (coordinate_x < 0 || coordinate_x >= num_horizontal || coordinate_y < 0 || coordinate_x >= num_vertical){
            throw"Array Index Out of Bounds";
        }
            
    } catch(char* str){
        cout << "Exception: " << str << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    try{
        int coordinate_x = x / cell_size_x;
        int coordinate_y = y / cell_size_y;
        
        if (state[coordinate_x][coordinate_y]){
            state[coordinate_x][coordinate_y] = false;
        } else {
            state[coordinate_x][coordinate_y] = true;
        }
        
        if (coordinate_x < 0 || coordinate_x >= num_horizontal || coordinate_y < 0 || coordinate_x >= num_vertical){
            throw"Array Index Out of Bounds";
        }
    } catch(char* str){
        cout << "Exception: " << str << endl;
    }
}

/*
 time on <==> off
 */
void ofApp::time_control(){
    if (time_stop){
        time_stop = false;
    } else {
        time_stop = true;
    }
}




void ofApp::calc(){
    std::vector<std::vector<bool> > state_tmp(num_horizontal, vector<bool>(num_vertical));
    for (int i = 0; i < num_horizontal; i++){
        for (int j = 0; j < num_vertical; j++){
            state_tmp[i][j] = state[i][j];
        }
    }
    for (int i = 0; i < num_horizontal; i++){
        for (int j = 0; j < num_vertical; j++){
            int count = 0;
            if (i == 0 && j == 0){
                count = int(state_tmp[i+1][j] == true)
                + int(state_tmp[i][j+1] == true)
                + int(state_tmp[i+1][j+1] == true);
            } else if (i == 0 && j == num_vertical-1){
                count = int(state_tmp[i+1][j] == true)
                + int(state_tmp[i][j-1] == true)
                + int(state_tmp[i+1][j-1] == true);
            } else if (i == num_horizontal-1 && j == 0){
                count = int(state_tmp[i-1][j] == true)
                + int(state_tmp[i][j+1] == true)
                + int(state_tmp[i-1][j+1] == true);
            } else if (i == num_horizontal-1 && j == num_vertical-1){
                count = int(state_tmp[i-1][j] == true)
                + int(state_tmp[i][j-1] == true)
                + int(state_tmp[i-1][j-1] == true);
            } else if (i == 0){
                count = int(state_tmp[i][j-1] == true)
                + int(state_tmp[i+1][j-1] == true)
                + int(state_tmp[i+1][j] == true)
                + int(state_tmp[i+1][j+1] == true)
                + int(state_tmp[i][j+1] == true);
            } else if (i == num_horizontal-1){
                count = int(state_tmp[i][j-1] == true)
                + int(state_tmp[i-1][j-1] == true)
                + int(state_tmp[i-1][j] == true)
                + int(state_tmp[i-1][j+1] == true)
                + int(state_tmp[i][j+1] == true);
            } else if (j == 0){
                count = int(state_tmp[i-1][j] == true)
                + int(state_tmp[i-1][j+1] == true)
                + int(state_tmp[i][j+1] == true)
                + int(state_tmp[i+1][j+1] == true)
                + int(state_tmp[i+1][j] == true);
            } else if (j == num_vertical-1){
                count = int(state_tmp[i-1][j] == true)
                + int(state_tmp[i-1][j-1] == true)
                + int(state_tmp[i][j-1] == true)
                + int(state_tmp[i+1][j-1] == true)
                + int(state_tmp[i+1][j] == true);
            } else {
                count = int(state_tmp[i-1][j-1] == true)
                + int(state_tmp[i][j-1] == true)
                + int(state_tmp[i+1][j-1] == true)
                + int(state_tmp[i+1][j] == true)
                + int(state_tmp[i+1][j+1] == true)
                + int(state_tmp[i][j+1] == true)
                + int(state_tmp[i-1][j+1] == true)
                + int(state_tmp[i-1][j] == true);
            }
            
            if (state_tmp[i][j] == false && count == 3){
                state[i][j] = true; // birth
            }  else if (state_tmp[i][j] == true && count <= 1){
                state[i][j] = false; // isolation
            } else if (state_tmp[i][j] == true && count >= 4){
                state[i][j] = false; //overpopulation
            }
        }
    }
    
}

void ofApp::render(){
    
    for (int i = 0; i < num_horizontal; i++){
        for (int j = 0; j < num_vertical; j++){
            if (state[i][j] == true){
                ofSetColor(255);
                ofDrawRectangle((i*cell_size_x)+1, (j*cell_size_y)+1,
                     (i*cell_size_x)+cell_size_x-1, (j*cell_size_y)+cell_size_y-1);
                
            } else if (state[i][j] == false){
                ofSetColor(0);
                ofDrawRectangle((i*cell_size_x)+1, (j*cell_size_y)+1,
                     (i*cell_size_x)+cell_size_x-1, (j*cell_size_y)+cell_size_y-1);
            }
        }
    }
}
