#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <string>
using namespace std;

// pretend this returns the current hour (0 .. 23):
int currentHourHand() throw()
{ return rand() % 24; }

class NoGas : public runtime_error {
public:
  NoGas(const string& what) throw();
};

NoGas::NoGas(const string& what)
: runtime_error (what) 
{ }

class LawnMower {
public:
  LawnMower() throw();
  void mowOneRow() throw(NoGas);
  void fillErUp() throw(NoGas);
  bool empty() const throw();
protected:
  unsigned gasLeft_;
};

LawnMower::LawnMower() throw()
: gasLeft_(10)
{ }

void LawnMower::mowOneRow() throw(NoGas)
{
  if (empty()) fillErUp();
  --gasLeft_;
}

void LawnMower::fillErUp() throw(NoGas)
{
  if (currentHourHand() >= 17) {
    cout << "sorry, gas stations are closed at this hour\n";
    throw NoGas("Gas stations are closed");
  }
  cout << "filling up the tank\n";
  gasLeft_ = 10;
}

bool LawnMower::empty() const throw()
{ return gasLeft_ == 0; }

class Gardener {
public:
  Gardener() throw();
  void mowTheLawn() throw(NoGas);
protected:
  LawnMower mower_;
  int       rowsInLawn_;
};

Gardener::Gardener() throw()
: mower_()
, rowsInLawn_(25)
{ }

void Gardener::mowTheLawn() throw(NoGas)
{
  for (int row = 0; row < rowsInLawn_; ++row) {
    cout << "starting to mow a row\n";
    mower_.mowOneRow();
  }
}

int main()
{
  Gardener mac;
  try {
    cout << "Mac is trying to mow the lawn\n";
    mac.mowTheLawn();
    cout << "Mac succeeded at mowing the lawn!\n";
  }
  catch (NoGas) {
    cout << "sorry, Mac ran out of gas after 5pm\n";
  }
}

