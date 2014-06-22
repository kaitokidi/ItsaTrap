#include "Dir.hpp"

Dir invers(Dir d){
	switch (d) {
		case None : return None;
		case Up : return Down;
		case Down : return Up;
		case Left : return Right;
		case Right : return Left;
	}
	return None;
}
