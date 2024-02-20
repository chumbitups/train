#include <iostream>
#include <cassert>
class TrainCar
{
  int passengersMax = 0;
  int passengers = 0;
  class Train *train = nullptr;

public:
  void load(int value)
  {
    passengers += value;
    if (passengers > passengersMax)
    {
      passengers = passengersMax;
    }
  }

  int getPassengers()
  {
    return passengers;
  }

  TrainCar(class Train *inTrain, int inPassengersMax)
      : train(inTrain), passengersMax(inPassengersMax)
  {
    assert(inTrain != nullptr);
    assert(inPassengersMax >= 0);
  }
  int getNumber();
};

class Train
{
  int count = 0;
  TrainCar **cars = nullptr;

public:
  TrainCar *getCarAt(int index)
  {
    if (this == nullptr)
      return nullptr;
    if (index < 0)
      return nullptr;
    if (index >= count)
      return nullptr;
    return this->cars[index];
  }

  int getCount()
  {
    return count;
  }

  Train(int inCount, int inPassengersMax) : count(inCount)
  {
    assert(inCount >= 0);
    cars = new TrainCar *[count];
    for (int i = 0; i < count; ++i)
    {
      cars[i] = new TrainCar(this, inPassengersMax);
    }
  }
};

int TrainCar::getNumber()
{
  for (int i = 0; i < train->getCount(); ++i)
  {
    TrainCar *car = train->getCarAt(i);
    if (car == this)
      return i;
  }
  assert(false);
}

int main()
{
  Train *train = nullptr;

  std::cout << "How many cars in your train and how many passengers one can accomodate? ";
  int carCount = 0;
  int passengersMax = 0;
  std::cin >> carCount >> passengersMax;

  train = new Train(carCount, passengersMax);

  for (int i = 0; i < train->getCount(); ++i)
  {
    int passengers = 0;
    std::cout << "Enter the quantity of passengers: ";
    std::cin >> passengers;
    train->getCarAt(i)->load(passengers);
  }
  std::cout << "What car do you need?'\n'";
  int carNumber;
  std::cin >> carNumber;

  TrainCar *carN = train->getCarAt(carNumber);
  std::cout << carN->getNumber() << " car has " << carN->getPassengers() << " passengers" << std::endl;
  delete train;
}