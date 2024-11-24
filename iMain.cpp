# include "iGraphics.h"
#include<iostream>
#include<stdlib.h>
#include<vector>
#include<set>
#include<queue>
#include<map>
#include<algorithm>
#define f first
#define s second
#define double long double 

using namespace std;
int x = 300, y = 300, r = 20;
/*
	function iDraw() is called again and again by the system.

	*/
double dx = 5;
double dy = 5;
double ghost_dx = 10;
double ghost_dy = 10;

double pac_x = 15, pac_y = 15 , pac_r = 15, slice = 100;
int ghost1_x = 405 , ghost1_y = 330 + 15;
//int ghost1_x = 15 , ghost1_y = 15;
// {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
 
int grid1[21][27] = {
 {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0},
 {1,1,1,1,1,1,0,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1,1,1,1,1,1},
 {0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1},
 {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1},
 {0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,0,0},
 {0,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,0,1,0,1,0,1,0,1,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
 {1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1},
 {0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,0,0,0,1,0,1,0,1,0,0},
 {1,1,1,1,0,1,1,1,1,0,1,0,0,0,1,0,1,1,1,0,1,0,1,0,1,0,1},
 {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
 {0,1,0,1,0,1,1,1,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
 {0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1},
 {0,1,0,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,0,1},
 {0,1,0,1,0,1,0,1,0,0,0,1,0,0,1,0,0,0,0,0,0,0,0,0,1,0,0},
 {0,1,0,1,0,0,0,0,0,1,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,0},
 {0,1,0,1,0,1,1,1,1,1,1,0,1,1,1,1,1,0,1,0,1,0,0,0,0,0,0},
 {0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,1,0,1,0,1,0,1,1,1,1,1},
};

double triangle_area(double x1 , double y1 , double x2, double y2, double x3, double y3) {
	double ans = x1*y2 + x2*y3 + x3 * y1 - y1 * x2 - y2 * x3 - y3 * x1;
	if(ans < 0) ans*=(-1);
	return 0.5 * ans;
}

int collision(int i , int j, double x , double y) {
	double sq_x1 = j *30 , sq_y1 = i * 30;
	double sq_x2 = sq_x1 , sq_y2 = sq_y1 + 30;
	double sq_x3 = sq_x1 + 30 , sq_y3 = sq_y1 + 30;
	double sq_x4 = sq_x1 + 30 , sq_y4 = sq_y1 ;
	double tot_area = triangle_area( x, y , sq_x1, sq_y1, sq_x2, sq_y2) + triangle_area( x, y , sq_x3, sq_y3, sq_x2, sq_y2) +
		triangle_area( x, y , sq_x3, sq_y3, sq_x4, sq_y4) + triangle_area( x, y , sq_x1, sq_y1, sq_x4, sq_y4);
	//cout << i <<  " " << j << " " << tot_area << endl;
	if( tot_area - 900 < 1e-6 ) {
		//printf("done");
		//cout << i << " " << j << " " << tot_area << endl;
		return 0;
	}
	//printf("failed");
	return 1;
}

int collision_ghost(int type, int ghost_x ,int ghost_y) {
	if(type ==0) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (ghost_x - 15 ) + (ghost_dx + 30 - 1) , (ghost_y - 15) + 1); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (ghost_x - 15 ) + (ghost_dx + 30 - 1) , (ghost_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout <<"right " <<  i << " " << j << endl;
						//cout <<"up " <<  i << " " << j << endl;
					}
				}
			}
		}

		if(flag == 1 && ghost_x + ghost_dx <= 26 * 30 + 15){
			return 1;
		}
		return 0;
	}
	if( type == 1) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (ghost_x - 15 ) + ( - ghost_dx + 1) , (ghost_y - 15) + 1); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (ghost_x - 15 ) + ( - ghost_dx + 1) , (ghost_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout <<"left " <<  i << " " << j << endl;
					}
				}
			}
		}
		if(ghost_x - ghost_dx >= 15 && flag == 1 ) {
			return 1;
		}
		return 0;
	}
	if(type == 3) {
		//pac_y-=dy;
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (ghost_x - 15 ) + 1 , (ghost_y - 15) + 1 - ghost_dy); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (ghost_x - 15 ) + 30 - 1 , (ghost_y - 15) + 1 - ghost_dy); ;
					if(in_flag == 0) {
						flag = 0;
						//cout <<"down " <<  i << " " << j << endl;
					}
				}
			}
		}
		if(ghost_y - ghost_dy >= 15 && flag == 1 ) {
			return 1;
		}
		return 0;
	}
	if( type == 2) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (ghost_x - 15 ) + 1 , (ghost_y - 15) + 30 - 1 + ghost_dy); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (ghost_x - 15 ) + 30 - 1 , (ghost_y - 15) + 30 - 1 + ghost_dy); ;
					if(in_flag == 0) {
						flag = 0;
						//cout <<"up " <<  i << " " << j << endl;
						
					}
				}
			}
		}
		if(ghost_y + ghost_dy <= 585 && flag == 1 ) {
			return 1;
		}
		return 0;
	}
	return 0;
	//place your codes for other keys here
}


vector<vector<pair<int,int> > > ghost_path(3);
vector<set<pair<int,int> > > vis(3);
int flag[3] = {0,0,0};
int gx[4] = { 1, -1, 0, 0};
int gy[4] = { 0, 0, 1, -1};
int ptr[3];
int depth = 100;
vector< pair<int,int> > keep;
/*set<pair<int,int> > st;
void dfs(int i , int j,int par_i, int par_j, int ghost_number) {
	//depth--;
	keep.push_back({i,j});
	st.insert({i,j});
	//cout << i <<  " " << j << " --> ";
	//vis[ghost_number].insert({i,j});
	//if(i == pac_x && j == pac_y) {
	//	flag[ghost_number] = 1;
	//	return;
	//}
	if( i == pac_x && j == pac_y) {
		flag[ghost_number] = 1;
		for(int i = 0 ; i < keep.size(); i++) {
			ghost_path[ghost_number].push_back(keep[i]);
		}
		return;
	}
	for(int k = 0 ; k < 4; k++) {
		int nxt_i = ghost_dx * gx[k] + i;
		int nxt_j = ghost_dy * gy[k] + j;
		//cout << " lol " << nxt_i << " " << nxt_j << endl;
		if(collision_ghost(k, i , j) == 1 && st.find({nxt_i,nxt_j}) == st.end()) {
			
			dfs(nxt_i, nxt_j , i, j, ghost_number);
			//if(depth == 0) return ;
			if(flag[ghost_number] == 1) return;
		}
	}
	keep.pop_back();
	st.erase({i,j});
}*/
void bfs(int i ,int j) {
	queue<pair<int,int> > qq;
	qq.push({i,j});
	map<pair<int,int> , pair<int,int>> mp;
	mp[{i,j}] = {-1,-1};
	int inpac_x = pac_x , inpac_y = pac_y;
	if(i == inpac_x && inpac_y == j) {
		keep.push_back({i,j});
		return;
	}
	set<pair<int,int>> st;
	
	st.insert({i,j});
	while(!qq.empty()) {
		auto cur = qq.front();qq.pop();
		int l = cur.f , m = cur.s;
		if(l == inpac_x && m == inpac_y) break;
		for(int k = 0 ; k < 4; k++) {
			int nxt_i = ghost_dx * gx[k] + l;
			int nxt_j = ghost_dy * gy[k] + m;
			
			//cout << " lol " << nxt_i << " " << nxt_j << endl;
			if(collision_ghost(k, l , m) == 1 && st.find({nxt_i,nxt_j}) == st.end()) {
				//cout << l << " " << m << " to " << nxt_i << " " << nxt_j << endl;
				mp[{nxt_i,nxt_j}] = {l, m};
				st.insert({nxt_i,nxt_j});
				qq.push({nxt_i,nxt_j});
				//if(depth == 0) return ;
			}
		}
	}
	auto cur = mp[{inpac_x,inpac_y}];
	keep.push_back({inpac_x,inpac_y});
	while( cur.f != i || cur.s != j) {
		keep.push_back(cur);
		//cout << cur.f << " " << cur.s << " -->  ";  
		cur = mp[cur];
	}
	cout << endl << endl;
	keep.push_back({i,j});
	reverse(keep.begin(),keep.end());
	while(!qq.empty()) qq.pop();
	st.clear();

}
void iDraw() {
	//place your drawing codes here
	iClear();
	iSetColor(20, 200, 200);

	double cur_x = 0 , cur_y = 0;
	for(int i  = 0 ; i < 20; i++) {
		for(int j = 0 ; j < 27; j++){
			if(grid1[i][j] == 1 ) {
				iFilledRectangle(cur_x, cur_y,30,30);
			}
			else{
				double point_x = cur_x + 15;
				double point_y = cur_y + 15;
				iFilledCircle(point_x, point_y, 2, 5);
				//printf("%f % f -- ", point_x, point_y);
			}
			cur_x+=30;
		}
		cur_x=0;
		cur_y+=30;
	}
	iSetColor(20, 200, 0);
	//iText(40, 40, "Hi, I am iGraphics");
	iFilledCircle(pac_x,pac_y,15,500);
	

	/*ghost*/
	for(int i = 0 ; i < 1; i++) {
		if(ghost_path[i].size() > ptr[i]) {
			ghost1_x = ghost_path[i][ptr[i]].first;
			ghost1_y = ghost_path[i][ptr[i]].second;
			iFilledCircle(ghost1_x, ghost1_y ,15,500);
		}
		else {
			//ghost1_x = ghost_path[i][ptr[i]-1].first;
			//ghost1_y = ghost_path[i][ptr[i]-1].second;
			iFilledCircle(ghost1_x, ghost1_y ,15,500);
		}
 	}
}
bool p = true;
bool q = false;
void createPath() {
	if(ptr[0] >= ghost_path[0].size()) {
		for(int i = 0 ; i < 1; i++) {ghost_path[i].clear();} //vis[i].clear(); flag[i] = 0;}
		//dfs(ghost_path[0][ptr[0]-1].first , ghost_path[0][ptr[0]-1].second, -1, -1 , 0);
		bfs(ghost1_x , ghost1_y);
		ptr[0] = 0;
		//cout << ghost1_x << " " << ghost2_y << " "
		for(int i = 0 ; i < keep.size(); i++) {
			ghost_path[0].push_back(keep[i]);
			
		}
		for(int i = 0 ; i < ghost_path[0].size() ; i++) {
			//cout << ghost_path[0][i].f << " " << ghost_path[0][i].s << " --> ";
		}
		cout << endl;
		keep.clear(); //st.clear();
	}
	else{
		ptr[0]++;
	}
	/*if(p) {
		for(int i = 0 ; i < ghost_path[0].size(); i++) {
			cout << "( " << ghost_path[0][i].first << " " << ghost_path[0][i].second << ") ";
		}
		p = false;
		q = true;
	}
	if(q) {
		for(int i = 0 ; i < ghost_path[0].size(); i++) {
			cout << "( " << ghost_path[0][i].first << " " << ghost_path[0][i].second << ") ";
		}
		q = false;
		//q = true;
	}*/
}
/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my) {
	printf("x = %d, y= %d\n",mx,my);
	//place your codes here
}

/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		//	printf("x = %d, y= %d\n",mx,my);
		x += dx;
		y += dy;
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
		//place your codes here
		x -= dx;
		y -= dy;
	}
}

/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
	*/
void iKeyboard(unsigned char key) {
	if (key == 'q') {
		exit(0);
	}
	//place your codes for other keys here
}

/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key) {
	if(key == GLUT_KEY_RIGHT) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15) + 1); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout <<"up " <<  i << " " << j << endl;
					}
				}
			}
		}

		if(flag == 1 && pac_x + dx <= 26 * 30 + 15) pac_x+=dx;
	}
	if(key == GLUT_KEY_LEFT) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (pac_x - 15 ) + ( - dx + 1) , (pac_y - 15) + 1); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (pac_x - 15 ) + ( - dx + 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout <<"up " <<  i << " " << j << endl;
					}
				}
			}
		}
		if(pac_x - dx >= 15 && flag == 1 ) {
			pac_x-=dx;
		}
	}
	if(key == GLUT_KEY_DOWN) {
		//pac_y-=dy;
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (pac_x - 15 ) + 1 , (pac_y - 15) + 1 - dy); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (pac_x - 15 ) + 30 - 1 , (pac_y - 15) + 1 - dy); ;
					if(in_flag == 0) {
						flag = 0;
						//\\cout <<"up " <<  i << " " << j << endl;
					}
				}
			}
		}
		if(pac_y - dy >= 15 && flag == 1 ) {
			pac_y-=dy;
		}
	}
	if(key == GLUT_KEY_UP) {
		int flag = 1;
		for(int i = 0 ; i < 20 ; i++) {
			for(int j = 0 ; j < 27 ; j++) {
				if(grid1[i][j] == 1) {
					int in_flag = collision(i, j , (pac_x - 15 ) + 1 , (pac_y - 15) + 30 - 1 + dy); 
					//in_flag = in_flag | collision(i, j , (pac_x - 15 ) + (dx + 30 - 1) , (pac_y - 15 ) + 30 - 1);
					if(in_flag == 0) {
						flag = 0;
						//cout << i << " " << j << endl;
					}
					in_flag = collision(i, j , (pac_x - 15 ) + 30 - 1 , (pac_y - 15) + 30 - 1 + dy); ;
					if(in_flag == 0) {
						flag = 0;
						//cout <<"up " <<  i << " " << j << endl;
					}
				}
			}
		}
		if(pac_y + dy <= 585 && flag == 1 ) {
			pac_y+=dy;
		}
	}
	
	if (key == GLUT_KEY_END) {
		exit(0);
	}
	//place your codes for other keys here
}


int main() {
	//cout << collision(1,1, 61, 90);B
	//place your own initialization codes here.
	//iSetTimer(25,iSpecialKeyboard());
	//createPath();
	iSetTimer(250,createPath);
	iInitialize(810,600, "demo");
	//pac_x = 705, pac_y = 135;
	//ghost1_x = 405 , ghost1_y = 345;
	//ghost_path[0].clear();
	//createPath();
	//cout << endl ;
	//createPath();	
	return 0;
}
