#ifndef _DIR_HPP_
#define _DIR_HPP_
 
enum Dir {
    None, Up, Down, Left, Right
};
//				 none   up    down  left right
const int Mx[5] = { 0,	  0,    0,  -1,	  1};
const int My[5] = { 0,   -1, 	1, 	 0,   0};

#endif // _DIR_HPP_
