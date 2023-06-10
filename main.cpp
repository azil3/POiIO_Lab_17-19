#include "tetris.hpp"

using namespace std;

int main( int argc , char **argv ){
  srand( time( 0 ) );
  auto tetris = make_shared<Tetris>();
  tetris->run();
  return 0;
}
